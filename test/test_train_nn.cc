#define PARSER_TEST_MODULE
#include "Parser.hpp"
#include "Vector.hpp"
#include "NN.hpp"
#include <random>
#include <chrono>

using type = double;

template <typename T>
constexpr void print_comment(T p_comment)
{
	std::cout << p_comment << "\n";
	std::cout.flush();
}

int main()
{
	const char* pos = "../../data/mnist_train.csv";

	laobject::Vector<laobject::Vector<type> > inputs(6000);
	laobject::Vector<laobject::Vector<type> > outputs(6000);

	print_comment<const char*>("Opening file...");
	print_comment<const char*>(pos);

	hand_number::fillFromFile(pos, inputs, outputs, 28, 28, 10);

    print_comment<const char*>("Training the network...");
    
    NN nn(784,15,10);

    nn.train(inputs,outputs,0.8);
	
}
