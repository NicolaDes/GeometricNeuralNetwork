#pragma once

#include "LAObject.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

#include <iostream>
#include <iomanip>
#include <ostream>
#include <random>
#include <chrono>

using type = double;

using namespace laobject;

#include "NN.i.hpp"

class NN
{
private:
	size_t 			size_{0};		///size of network
	Vector<type> 	X, H, Y;		///layers
	Vector<type> 	B1, B2;			///bias
	Vector<type> 	delta1, delta2; ///delta errors
	Matrix<type> 	W1, W2;			///weights
	Matrix<type> 	omega1, omega2; ///omega errors

	void feedforward(Vector<type> &input);
	void backpropagation(Vector<type> &input, Vector<type> &expected_output);
	void change_weights(type alpha);

public:
	NN(size_t x, size_t h, size_t y);
	~NN();
	void train(Vector<Vector<type>> &inputs, Vector<Vector<type>> &outputs, type alpha);
	const Vector<type> getOut();
	const Vector<type> submit(Vector<type> &input);
	const Vector<Matrix<type>> getWeights();
	
	template <typename T>
	void fillFromFile(const char *file, laobject::Vector<laobject::Vector<T>> &inputs, laobject::Vector<laobject::Vector<T>> &outputs, size_t h, size_t w, size_t outsize);
};