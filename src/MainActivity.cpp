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

namespace po = boost::program_options;
const std::string version = std::to_string(MAJOR_VERSION) + "." + std::to_string(MINOR_VERSION) + "v";

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
                    std::string train_set_, double alpha_, std::string weights_pos_) : x(x_), y(y_), z(z_), test_set(test_set_),
                                                                                       train_set(train_set_), weights_pos(weights_pos_), alpha(alpha_) {}
    size_t x, y, z;
    std::string test_set, train_set, weights_pos;
    double alpha;
};

int main(int argc, char **argv)
{
    NNConfiguration configuration(784, 15, 10, "../data/mnist_test.csv", "../data/mnist_train.csv", 0.65, "../data/weights.data");

    NN nn(configuration.x, configuration.y, configuration.z);

    po::options_description description("Geometric Neural Network " + version + " ");

    description.add_options()
    ("help,h", "Display this help message")
    ("save,s", po::value<std::string>(), "Save the weights at the end of computation in file")
    ("train,t", po::value<std::string>(), "Train the network with default files given in input")
    ("put-up,p", po::value<std::string>(), "Input files containing test set. At the end of the computation a log file will be generated")
    ("weights,w", po::value<std::string>(), "Input file containing weights")("version,v", "Display the version number");

    po::positional_options_description p;
    p.add("input-files", -1);
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(description).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << description;
        return 0;
    }
    if (vm.count("version"))
    {
        std::cout << " " << version << "\n";
        return 0;
    }

    if (vm.count("weights"))
    {
        std::string file = vm["weights"].as<std::string>();
        std::cout << "Loading the weights from file " << file << "...\n";
        nn.loadWeights(file);
        std::cout << "Weights loaded!\n";
    }

    if (vm.count("train"))
    {
        std::string file = vm["train"].as<std::string>();
        std::ifstream train_in(configuration.train_set);
        unsigned line_count = 0;

        std::string line;
        while (std::getline(train_in, line))
            ++line_count;

        laobject::Vector<laobject::Vector<type>> inputs_train(line_count);
        laobject::Vector<laobject::Vector<type>> outputs_train(line_count);

        hand_number::fillFromFile(configuration.train_set, inputs_train, outputs_train, 28, 28, 10);

        nn.train(inputs_train, outputs_train, configuration.alpha);

        std::cout << "Network trained!\n";
    }

    if (vm.count("save"))
    {
        std::string file = vm["save"].as<std::string>();
        std::cout << "Saving the weights in file " << file << "...\n";
        nn.saveWeights(file);
        std::cout << "Weights saved!\n";
    }

    if (vm.count("put-up"))
    {
        std::string filename = vm["put-up"].as<std::string>();
        std::ifstream file(filename);

        unsigned line_count = 0;

        std::string line;
        while (std::getline(file, line))
            ++line_count;

        laobject::Vector<Vector<type>> inputs(line_count);
        laobject::Vector<Vector<type>> outputs(line_count);
        hand_number::fillFromFile(filename, inputs, outputs, 28, 28, 10);
        std::cout << "Submitting test case to the network...\n";
        unsigned correct = 0;
        for (size_t i = 0; i < line_count; ++i)
        {
            nn.submit(inputs[i]);
            if (nn.isCorrect(outputs[i]))
                correct++;
        }
        std::cout<<"Test case submitted. Saving log...\n";
        std::ofstream log("vectorNeuralNetwork.log");
        std::cout<<"Correct: "<<correct<<"\nWrong: "<<line_count-correct<<"\nPercentage of success: "<<(static_cast<double>(correct)/static_cast<double>(line_count))*100<<" %\n";
        log<<"Correct: "<<correct<<"\nWrong: "<<line_count-correct<<"\nPercentage of success: "<<(static_cast<double>(correct)/static_cast<double>(line_count))*100<<" %\n";


        log.close();
        std::cout<<"Log saved!\n";
    }

    if(vm.size()==0) ///default launch
    {
        
    }
} // main