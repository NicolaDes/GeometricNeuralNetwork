#include "Config.h"
#include "Parser.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "NN.hpp"

#include "boost/program_options.hpp" 

#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

void wellcome();
void mainloop();

namespace po = boost::program_options;
const std::string version = std::to_string(MAJOR_VERSION)+"."+std::to_string(MINOR_VERSION)+"v";

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator = std::default_random_engine(seed);
std::uniform_real_distribution<type> distribution(0, 1);

template <>
type randomize()
{
    return distribution(generator);
}

struct NNConfiguration
{
    NNConfiguration(size_t x_, size_t y_, size_t z_, std::string test_set_, 
        std::string train_set_, double alpha_) : x(x_), y(y_), z(z_), test_set(test_set_), 
        train_set(train_set_), alpha(alpha_) {}
    size_t x,y,z;
    std::string test_set,train_set;
    double alpha;
};

int main(int argc, char** argv) 
{ 
    NNConfiguration configuration(784,15,10,"data/mnist_test.csv","data/mnist_train.csv", 0.8);

    po::options_description description("Geometric Neural Network "+version+" ");

    description.add_options()
    ("help,h", "Display this help message")
    ("input-files,f", po::value<std::vector<std::string>>(), "Input files")
    ("version,v", "Display the version number");

    po::positional_options_description p;
    p.add("input-files", -1);
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(description).positional(p).run(), vm);
    po::notify(vm);

    if(vm.count("help"))
    {
        std::cout << description;
    }
    if(vm.count("version"))
    {
        std::cout<<" "<<version<<"\n";
    }

    if(vm.count("input-files"))
    {
        std::vector<std::string> files = vm["input-files"].as<std::vector<std::string>>();
        if(files.size()!=2)
        {
            std::cerr << "Input files must be 2: training set and test set! \n";
            std::exit(EXIT_FAILURE);
        }
        configuration.train_set=files[0];
        configuration.test_set=files[1];
    }

    NN nn(configuration.x,configuration.y,configuration.z);
    
    std::ifstream train_in(configuration.train_set);
    std::ifstream test_in(configuration.test_set);
	unsigned line_count = 0;

	std::string line;
	while(std::getline(train_in,line))
		++line_count;
    
    laobject::Vector<laobject::Vector<type> > inputs_train(line_count);
	laobject::Vector<laobject::Vector<type> > outputs_train(line_count);    

    line_count = 0;
    while(std::getline(test_in,line))
	    ++line_count;

    laobject::Vector<laobject::Vector<type> > inputs_test(line_count);
	laobject::Vector<laobject::Vector<type> > outputs_test(line_count); 

	std::cout<<"Line count: "<<line_count<<"\n";

    hand_number::fillFromFile(configuration.train_set, inputs_train, outputs_train, 28, 28, 10);

    nn.train(inputs_train, outputs_train, configuration.alpha);

    std::cout<<"Network trained!\n";
} // main 