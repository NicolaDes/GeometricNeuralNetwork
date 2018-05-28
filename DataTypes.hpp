#pragma once
#include "matrix.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>

template <typename T>
class NN
{
  private:
	Matrix<T> X, W1, H, W2, Y, B1, B2;
	Matrix<T> delta1, delta2, omega1, omega2;

	void feedforward(Matrix<T> &input)
	{
		X = input;
		H = ((X * W1) + B1)(sigmoid);
		Y = ((H * W2) + B2)(sigmoid);
	}

	void backpropagation(Matrix<T> &input, Matrix<T> &expected_output)
	{
		this->feedforward(input);
		Matrix<T> err = Y - expected_output;
		Matrix<T> arg = (H * W2) + B2;
		arg = arg(d_sigmoid);
		delta2 = err, arg;

		Matrix<T> W2_T = ~W2;
		err = delta2 * W2_T;
		arg = (X * W1) + B1;
		arg = arg(d_sigmoid);
		delta1 = err, arg;
		omega2 = (~H) * delta2;
		omega1 = (~X) * delta1;
	}

	void change_weights(T alpha)
	{
		delta2 = delta2 * alpha;
		B2 = B2 - delta2;
		delta1 = delta1 * alpha;
		B1 = B1 - delta1;
		omega2 = omega2 * alpha;
		W2 = W2 - omega2;
		omega1 = omega1 * alpha;
		W1 = W1 - omega1;
	}

  public:
	NN(size_t x, size_t h, size_t y) : X(Matrix<T>(1, x)), W1(Matrix<T>(x, h)), H(Matrix<T>(1, h)), W2(Matrix<T>(h, y)), Y(Matrix<T>(1, y)), B1(Matrix<T>(1, h)), B2(Matrix<T>(1, y))
	{

		W1 = W1(randomize);
		W2 = W2(randomize);
		B1 = B1(randomize);
		B2 = B2(randomize);
	}

	size_t inSize() { return X.cols(); }
	size_t outSize() { return Y.cols(); }

	void train(std::vector<Matrix<T>> &inputs, std::vector<Matrix<T>> &outputs, T alpha)
	{
		assert(inputs.size() == outputs.size());
		size_t size = inputs.size();
		size_t i = 0;
		std::cout << "Training the network with " << size << " elements...\n";
#pragma unroll
		for (; i < inputs.size(); ++i)
		{
			std::cout << std::right << std::setw(6) << "[" << static_cast<int>(i * 100 / size) << "\%]"
					  << "\r";
			this->backpropagation(inputs[i], outputs[i]);
			change_weights(alpha);
		}
		std::cout << std::right << std::setw(6) << "[" << 100 << "\%]"
				  << "\r";
	}

	Matrix<T> error(Matrix<T> &input, Matrix<T> &output)
	{
		this->feedforward(input);
		return Y - output;
	}

	friend std::ostream &operator<<(std::ostream &os, NN &nn)
	{

		return os;
	}

	Matrix<T> getOut()
	{
		return Y;
	}

	void submit(Matrix<T> &input) { this->feedforward(input); }
};
