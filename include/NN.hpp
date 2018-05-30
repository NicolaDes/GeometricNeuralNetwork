/**
 * @copyright MultiformNN
 * license Apache2
 * @author Nicola Dessi'
 * @version v1.0
 * @date May, 2018
 * @file
 */
#pragma once

#include "LAObject.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <random>
#include <chrono>
#include <cassert>

using type = double; ///type of templates (laobject)

using namespace laobject;

/// @brief NN class is a neural network implemented with vectors
class NN
{
private:
	size_t 			size_{0};		///size of network
	Vector<type> 	X, H, Y;		///layers
	Vector<type> 	B1, B2;			///bias
	Vector<type> 	delta1, delta2; ///delta errors
	Matrix<type> 	W1, W2;			///weights
	Matrix<type> 	omega1, omega2; ///omega errors

	/**
	 * Propagate the input to the output layers
	 * @param[in] input the input vector.
	 * @warning @p input vector must be the same size of X
	 */
	void feedforward(Vector<type> &input);

	/**
	 * @brief Backpropagate the output to the input layers computing errors for the 
	 * current assignment
	 * @param[in] input the input vector.
	 * @param[in] output the expected_output vector.
	 * @warning @p input @p output vector must be the same size of X and Y respectively
	 */
	void backpropagation(Vector<type> &input, Vector<type> &expected_output);

	/**
	 * @brief Change the weigths with a growth factor of @p alpha
	 * @param[in] alpha growth factor
	 */
	void change_weights(type alpha);

public:

	/**
	 * @brief Constructor with dimension of X,Y,Z layers
	 * @param[in] x size of X
	 * @param[in] h size of H
	 * @param[in] y size of Y
	 */
	NN(size_t x, size_t h, size_t y);

	/**
	 * Defautl descrutor.
	 */
	~NN();

	/**
	 * @brief Train the network giving @p inputs vector and @p outputs expected 
	 * vector.
	 * @param[in] inputs Reference to the input vector
	 * @param[in] outputs Reference to the expected output
	 * @param[in] alpha Growth factor
	 */
	void train(Vector<Vector<type>> &inputs, Vector<Vector<type>> &outputs, type alpha);

	/**
	 * @brief Verify if the current output is correct respect the expected.
	 * @return True if correct, False otherwise.
	 */
	bool isCorrect(Vector<type> &expected);	
	/**
	 * @brief Submit to the networ an input.
	 * @warning input and X must have the same dimension
	 */
	void submit(Vector<type> &input);

	/**
	 * @brief Return the weight of each node of the network
	 * @return A vector of matrix wich is all the links  between nodes
	 */
	const Vector<Matrix<type>> getWeights();

	/**
	 * @brief Save the weights in a specific file
	 * @param file the file where the weights will be stored
	 */
	void saveWeights(const std::string& file);

	/**
	 * @brief Load the weights from a specific file
	 * @param file the file where the weights will be read
	 */
	void loadWeights(const std::string& file);

};

#include "NN.i.hpp"