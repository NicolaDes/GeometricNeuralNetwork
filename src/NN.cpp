#include "NN.hpp"

NN::NN(size_t x, size_t h, size_t y)
{

    if (x<1 || h<1 || y<1)
    {
        std::cerr << "Number of layers must be 3, and not empty!\n";
        std::exit(EXIT_FAILURE);
    }

    size_ = 3;

    X = Vector<type>(x);
    H = Vector<type>(h);
    Y = Vector<type>(y);

    W1 = Matrix<type>(x, h)(randomize);
    W2 = Matrix<type>(h, y)(randomize);

    B1 = Vector<type>(h)(randomize);
    B2 = Vector<type>(y)(randomize);
}


NN::~NN(){

}

void NN::feedforward(Vector<type> &input)
{
    if (input.size() != X.size())
    {
        std::cerr << "FEEDFORWARD FAILURE: Inputs dimensions do not match!\n";
        std::exit(EXIT_FAILURE);
    }
    X = input;
    H = ((X * W1) + B1)(sigmoid<type>);
    Y = ((H * W2) + B2)(sigmoid<type>);
}

void NN::backpropagation(Vector<type> &input, Vector<type> &expected_output)
{
    if (input.size() != X.size() || expected_output.size() != Y.size())
    {
        std::cerr << "BACKPROPAGATION FAILURE: Inputs dimensions or output dimensions do not match -> input: "<<input.size()<<"=="<<X.size()<<", output: "<<expected_output.size()<<"=="<<Y.size()<<"\n";
        std::exit(EXIT_FAILURE);
    }
    feedforward(input);
    Vector<type> err = Y - expected_output;
    Vector<type> arg = (H * W2) + B2;
    arg = arg(d_sigmoid);
    delta2 = err, arg;
    
    err = delta2 * (~W2);
    arg = (X * W1) + B1;
    arg = arg(d_sigmoid);
    delta1 = err, arg;
    omega2 = H * delta2;
    omega1 = X * delta1;
}

void NN::change_weights(type alpha)
{
    delta2 = alpha * delta2;
    B2 = B2 - delta2;
    delta1 = alpha * delta1;
    B1 = B1 - delta1;
    omega2 = alpha * omega2;
    W2 = W2 - omega2;
    omega1 = alpha * omega1;
    W1 = W1 - omega1;
}

void NN::train(Vector<Vector<type>> &inputs, Vector<Vector<type>> &outputs, type alpha)
{
    const size_t size = inputs.size();
    size_t i = 0;
    std::cout << "Training the network with " << size << " elements...\n";

#pragma unroll
    for (; i < size; ++i)
    {
        std::cout << std::right << std::setw(6) << "[" << static_cast<int>(i * 100 / size) << "%]"
                  << "\r";
        backpropagation(inputs[i], outputs[i]);
        change_weights(alpha);
    }
    std::cout << std::right << std::setw(6) << "[" << 100 << "%]"
              << "\n";
}

const Vector<type> NN::getOut()
{
    return Y;
}

const Vector<type> NN::submit(Vector<type> &input)
{
    feedforward(input);

    return Y;
}

const Vector<Matrix<type>> NN::getWeights()
{
    Vector<Matrix<type>> ret(size_ - 1);
    ret[0] = W1;
    ret[1] = W2;

    return ret;
}