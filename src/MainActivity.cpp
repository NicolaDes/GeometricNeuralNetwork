#include "Vector.hpp"
#include "Matrix.hpp"
#include "NN.hpp"
#include "Config.h"

#include "boost/program_options.hpp" 

#include <string>
#include <iostream>
#include <fstream>

namespace po = boost::program_options;
int main(int argc, char** argv) 
{ 
    po::options_description description("\
        //////////////////////////////////////////\n\
        /////////Geometric Neural Network/////////\n\
        //////////////////////////////////////////\n");

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
        std::cout<<RELEASE<<" "<<MAJOR_VERSION<<"."<<MINOR_VERSION<<"v\n";
    }

    if(vm.count("input-files"))
    {
        std::vector<std::string> files = vm["input-files"].as<std::vector<std::string>>();
        for(std::string file : files){
            std::cout << "Input file " << file << std::endl;
        }
    }

} // main 