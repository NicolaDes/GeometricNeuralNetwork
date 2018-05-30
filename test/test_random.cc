/**
 * @copyright GeometricNeuralNetwork
 * license Apache2
 * @author Nicola Dessi'
 * @version v1.0
 * @date May, 2018
 * @file
 */
#define TRAIN_TEST_MODULE
#include "Parser.hpp"
#include "Vector.hpp"
#include "NN.hpp"
#include <random>
#include <chrono>

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator = std::default_random_engine(seed);
std::uniform_real_distribution<type> distribution(0, 1);

template <typename T>
constexpr void print_comment(T p_comment)
{
	std::cout << p_comment << "\n";
	std::cout.flush();
}

template <>
type randomize()
{
    return distribution(generator);
}

int main()
{
    print_comment<const char*>("Generating first random element between [0,1]: ");
    print_comment<double>(distribution(generator)); // first random number
    print_comment<const char*>("Generating second random element between [0,1]: ");
    print_comment<double>(distribution(generator)); // second random number

    print_comment<const char*>("Generating NN with randomize full specification function...\n");
    NN nn(100,1000,100);
    std::cout<<nn.getWeights();

    return 0;
}