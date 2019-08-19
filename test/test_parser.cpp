/**
 * @copyright GeometricNeuralNetwork
 * license Apache2
 * @author Nicola Dessi'
 * @version v1.0
 * @date May, 2018
 * @file
 */
#define PARSER_TEST_MODULE
#include "NN.hpp"
#include "Vector.hpp"

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

    Vector<Vector<type>> inputs(line_count);
    Vector<Vector<type>> outputs(line_count);

    print_comment<const char *>("Opening file...");
    print_comment<const char *>(pos);

    NN::fillFromFile(pos, inputs, outputs, 28, 28, 10);

    return 0;
}
