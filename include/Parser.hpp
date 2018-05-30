/**
 * @copyright GeometricNeuralNetwork
 * license Apache2
 * @author Nicola Dessi'
 * @version v1.0
 * @date May, 2018
 * @file
 */
#pragma once

#include "Vector.hpp"

#include <fstream>
#include <iomanip>

namespace hand_number
{
/**
	 * @brief Fill inputs and outputs vector of vectors with a csv format input filee
	 * @tparam T type of neural network 
	 */
template <typename T>
void fillFromFile(std::string file, laobject::Vector<laobject::Vector<T>> &inputs, laobject::Vector<laobject::Vector<T>> &outputs, size_t h, size_t w, size_t outsize)
{
	std::ifstream fin(file);
	if (!fin.is_open())
	{
		std::cerr << "Error, no file was found with name " << file << "\n";
		std::exit(2);
	}
	size_t training_set;
	training_set = inputs.size();
	for (size_t k = 0; k < training_set; ++k)
	{
		std::cout << std::right << std::setw(6) << "[" << static_cast<int>(k * 100 / training_set) << "%]"
				  << "\r";
		laobject::Vector<T> input(h * w);
		laobject::Vector<T> output(outsize);
		char c;
		size_t out;
		fin >> c;
		out = c - '0';
		output[out] = 1;
		outputs[k] = output;
		for (size_t i = 0; i < h; ++i)
		{
			for (size_t j = 0; j < w; ++j)
			{
				fin >> c;
				while (c != ',')
				{
					input[i * w + j] += c - '0';
					fin >> c;
				}
			}
		}
		inputs[k] = input;
		fin >> c;
	}
	std::cout << std::right << std::setw(6) << "[" << 100 << "%]"
			  << "\r";
}
} // namespace hand_number