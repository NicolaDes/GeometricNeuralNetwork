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

#include <ostream>
#include <iostream>

/// @brief This is a matrix object of linear algebra
namespace laobject
{

/// @brief Vector class friend
/// @tparam T Type of elements inside the vector object
template <typename T>
class Vector;

/// @brief This class model a matrix of elements.
/// @tparam T Class template for linear algebra matrix (in general numbers)
template <typename T>
class Matrix : public LAObject<T>
{
  protected:
    size_t row_offeset_{0}; ///number of cols before new row
    size_t leading_{0};     ///number of rows

  public:
    /// Default constructor and constructor specifying rows and cols.
    explicit Matrix(size_t rows = 1, size_t cols = 1);
    /// Destructor
    ~Matrix();

    /**
    * @brief Return the size of elements allocated
    * @return number of allocated elements of type T.
    */
    size_t size() const override;
    /// @brief Print the elements allocated
    void print() const override;
    /**
     * @brief Return the number of rows
     * @return size_t
     */
    size_t rows() const;
    /**
     * @brief Return the number of cols
     * @return size_t
     */
    size_t cols() const;

    ///Operators
    
    /**
    * @brief Return pointer to location @p row. For example A[1][1] access to element in position i=1,j=1.
    * @return read only pointer to @tparam T
    */
    T *operator[](size_t row) const;
    /**
    * @brief Return pointer to location @p row. For example A[1][1] access to element in position i=1,j=1.
    *         Also A[1][1]=32 is a valid operation.
    * @return read and write pointer to @tparam T
    */
    T *operator[](size_t row);
    /**
     * @brief Define the transpose operator of a matrix. Return the transposed matrix.
     * @return Matrix, this operation will not modify original matrix.
    */
    Matrix<T> operator~() const;
    /**
     * @brief Define function application operator. This means that if f(T val)
     * is defined, A(f) will apply f function to all member of A.
     * @return Matrix with applied function. The original matrix remain unchanged.
     */
    Matrix<T> operator()(T (*fptr)(T val)) const;
    /**
     * @brief Define function application operator. This means that if f(T val)
     * is defined, A(f) will apply f function to all member of A.
     * @return Matrix with applied function. The original matrix remain unchanged.
     */
    Matrix<T> operator()(T (*fptr)()) const;
    /**
     * @brief Assignmetn operator
     */
    Matrix<T> &operator=(const Matrix<T> &m);
    /**
     * @brief Sum of two Matrix
     * @return Matrix. The original matrix remain unchanged.
     */
    Matrix<T> operator+(const Matrix<T> &m);
    /**
     * @brief Diff of two Matrix
     * @return Matrix. The original matrix remain unchanged.
     */
    Matrix<T> operator-(const Matrix<T> &m);
    /**
     * @brief Multiplication of two matrix.
     * @return Matrix. The original matrix remain unchanged.
     */
    Matrix<T> operator*(const Matrix<T> &m);
    /**
     * @brief Hadamard product of two matrix
     * @return Matrix. The original matrix remain unchanged.
     */
    Matrix<T> operator,(const Matrix<T> &m);

    /**
     * @brief Multiplication of a scalar with a matrix
     * @return Matrix. The original matrix remain unchanged.
     */
    friend Matrix<T> operator*(const T &scalar, const Matrix<T> &m)
    {
        Matrix<T> ret(m.row_offeset_, m.leading_);
        ret = m;
        for (size_t i = 0; i < m.row_offeset_; ++i)
        {
            for (size_t j = 0; j < m.leading_; ++j)
                ret[i][j] *= scalar;
        }
        return ret;
    }

    /// Print on a stream!
    friend std::ostream &operator<<(std::ostream &stream, const Matrix<T> &m)
    {
        for (size_t i = 0; i < m.row_offeset_; ++i)
        {
            for (size_t j = 0; j < m.leading_; ++j)
                stream << m.values_[i * m.leading_ + j] << " ";
            stream << "\n";
        }
        return stream;
    }

    /**
     * @brief Multiplicatin of a vector with a Matrix
     * @warning Automatic the operation between m(ixj) and v(1xi) is
     * v'*m = _v(1xi)
     * @return Vector. The original matrix remain unchanged.
     */
    friend Vector<T> operator*(const Vector<T> &v, const Matrix<T> &m)
    {
        if (v.size() != m.row_offeset_)
        {
            std::cerr << "v1.size_, v2.rows do not match!\n";
            std::exit(EXIT_FAILURE);
        }

        Vector<T> ret(m.leading_);
        for (size_t i = 0; i < m.leading_; ++i)
        {
            ret[i] = 0;
            for (size_t j = 0; j < v.size(); ++j)
            {
                ret[i] += v[j] * m.values_[j * m.leading_ + i];
            }
        }
        return ret;
    }
};
} //namespace laobject

#include "Matrix.i.hpp"