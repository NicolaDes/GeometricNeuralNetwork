/**
 * @copyright GeometricNeuralNetwork
 * license Apache2
 * @author Nicola Dessi'
 * @version v1.0
 * @date May, 2018
 * @file
 */
#define TRAIN_TEST_MODULE
#include "NN.hpp"
#include "Vector.hpp"
#include <chrono>
#include <random>

template <typename T> constexpr void print_comment(T p_comment)
{
    std::cout << p_comment << "\n";
    std::cout.flush();
}

int main()
{
    const char *pos = "../../data/mnist_train.csv";

    std::ifstream file(pos);

    unsigned line_count = 0;

    std::string line;
    while (std::getline(file, line))
        ++line_count;

    laobject::Vector<laobject::Vector<type>> inputs(line_count);
    laobject::Vector<laobject::Vector<type>> outputs(line_count);

    print_comment<const char *>("Opening file...");
    print_comment<const char *>(pos);

    NN::fillFromFile(pos, inputs, outputs, 28, 28, 10);

    print_comment<const char *>("Training the network...");

    NN nn(784, 15, 10);

    nn.train(inputs, outputs, 0.8);
}
