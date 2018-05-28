#define NN_TEST_MODULE
#include "NN.hpp"

#include <random>
#include <chrono>


using namespace laobject;

using type = double;

template <typename T>
constexpr void print_comment(T p_comment)
{
    std::cout << p_comment << "\n";
    std::cout.flush();
}

int main()
{
	NN nn(3,4,3);

	Vector<double> input(3);
	input[0]=1.0;
	input[1]=1.0;
	input[2]=1.0;

	Vector<Vector<double>> inputs(1);
	inputs[0]=input;
	Vector<Vector<double>> outputs(1);
	outputs[0]=input;

	nn.train(inputs,outputs,0.8);

	return 0;
};
