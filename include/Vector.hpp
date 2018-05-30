/**
 * @copyright GeometricNeuralNetwork
 * license Apache2
 * @author Nicola Dessi'
 * @version v1.0
 * @date May, 2018
 * @file
 */
#pragma once

#include "LAObject.hpp"

#include <ostream>
#include <iostream>

/// @brief Namespace brief
///        This is a vector object of linear algebra
namespace laobject
{

/// @brief Matrix class friend
/// @tparam T Type of elements inside the vector object
template <typename T>
class Matrix;


/// @brief This class model a vector of elements.
/// @tparam T Class template for linear algebra vector (in general numbers)
template <typename T>
class Vector : public LAObject<T>
{
  public:
    /// Default constructor and constructor specifying size.
    explicit Vector(size_t size = 1);
    /// Destructor
    ~Vector();

    /**
    * @brief Return the size of elements allocated
    * @return number of allocated elements of type T.
    */
    size_t size() const override;
    /// @brief Print the elements allocated
    void print() const override;
    /**
     * @brief Return the number of rows, wich is the size of vector.
     * @return size_t
     */
    size_t rows() const;
    /**
     * @brief Return the number of cols, wich is 0
     * @return size_t
     */
    size_t cols() const;

    /**
    * @brief Return pointer to location @p row. For example V[1] access to element in position i=1.
    * @return read only pointer to @tparam T
    */
    T at(size_t index) const;
    
    ///Operators
    /**
    * @brief Return pointer to location @p row. For example V[1] access to element in position i=1.
    * @return read only element to 
    */
    T operator[](size_t index) const;
    /**
    * @brief Return pointer to location @p row. For example V[1] access to element in position i=1.
    * V[5]=219.1 is a valid operation.
    * @return read and write reference to 
    */
    T &operator[](size_t index);
    /**
     * @brief Assignment operator
     */
    Vector<T> &operator=(const Vector<T> &v);
    Matrix<T> &operator=(const Matrix<T> &m);
    /**
     * @brief Sum of two Vector
     * @return Vector. The original vector remain unchanged.
     */
    Vector<T> operator+(const Vector<T> &v);
    /**
     * @brief Diff of two Vector
     * @return Vector. The original vector remain unchanged.
     */
    Vector<T> operator-(const Vector<T> &v);
    /**
     * @brief Define function application operator. This means that if f(T val)
     * is defined, V(f) will apply f function to all member of V.
     * @return Vector with applied function. The original vector remain unchanged.
     */
    Vector<T> operator()(T (*fptr)(T val)) const;
    /**
     * @brief Define function application operator. This means that if f(T val)
     * is defined, V(f) will apply f function to all member of V.
     * @return Vector with applied function. The original vector remain unchanged.
     */
    Vector<T> operator()(T (*fptr)()) const;
    /**
     * @brief Hadamard product of two vector
     * @return Vector. The original vector remain unchanged.
     */
    Vector<T> operator,(const Vector<T> &v);

    /**
     * @brief Multiplication of a scalar with a vector
     * @return Vector. The original vector remain unchanged.
     */
    friend Vector<T> operator*(const T &scalar, const Vector<T> &v)
    {
        Vector<T> ret(v.size_);
        for (size_t i = 0; i < v.size_; ++i)
            ret[i] = scalar * v.values_[i];
        return ret;
    }
    /// Print on a stream!
    friend std::ostream &operator<<(std::ostream &stream, const Vector<T> &v)
    {
        for (size_t i = 0; i < v.size_; i++)
            stream << v.values_[i] << "\n";
        return stream;
    }
    /**
     * @brief Multiplicatin of a vector with a Vector
     * @warning Automatic the operation between v1(1xj) and v2(1xi) is
     * v1*v2 = _v(jxi)
     * @return Vector The original vector remain unchanged.
     */
    friend Matrix<T> operator*(const Vector<T> &v1, const Vector<T> &v2)
    {
        Matrix<T> ret(v1.size_, v2.size_);
        for (size_t i = 0; i < v1.size_; ++i)
        {
            for (size_t j = 0; j < v2.size_; ++j)
            {
                ret[i][j] = v1.values_[i] * v2.values_[j];
            }
        }
        return ret;
    }
};
} //namespace laobject

#include "Vector.i.hpp"