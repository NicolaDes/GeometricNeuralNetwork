/**
 * @copyright GeometricNeuralNetwork
 * license Apache2
 * @author Nicola Dessi'
 * @version v1.0
 * @date May, 2018
 * @file
 */
#pragma once

#include <cstddef>

/// @brief This is a general linear algebra object
namespace laobject
{

/// @brief Generic linear algebra object. It can be a vector, a matrix, a
/// triangle, etc.
/// @tparam T Class template for linear algebra object (in general numbers)
template <typename T> class LAObject
{
  protected:
    T *values_{nullptr}; /// values in heap
    size_t size_{0};     /// size of values

  public:
    /// Default constructor
    explicit LAObject() = default;
    /// Constructor with size of allocation.
    explicit LAObject(size_t size) : size_(size) {}
    /// Descructor
    virtual ~LAObject() {}

    /**
     * @brief Return the size of elements allocated
     * @return number of allocated elements of type T.
     */
    virtual size_t size() const = 0;
    /// @brief Print the elements allocated
    virtual void print() const = 0;
};
}