/**
 * @copyright GeometricNeuralNetwork
 * license Apache2
 * @author Nicola Dessi'
 * @version v1.0
 * @date May, 2018
 * @file
 */
#define MATRIX_TEST_MODULE

#include "Matrix.hpp"
#include "Vector.hpp"
#include <iostream>

using namespace laobject;

using type = double;

template <typename T>
constexpr void print_comment(T p_comment)
{
    std::cout << p_comment << "\n";
    std::cout.flush();
}

type vals(type val) { return val; }

void testMult(Matrix<type> &m1, Matrix<type> &m2)
{
    print_comment<const char *>("Testing moltiplication");
    Matrix<type> test = m1 * m2;
}
void testAdd(Matrix<type> &m1, Matrix<type> &m2)
{
    print_comment<const char *>("Testing addition");
    m1 + m2;
}
void testTranspose(Matrix<type> &m1)
{
    print_comment<const char *>("Testing transpose matrix");
    ~m1;
}
void testEqual(Matrix<type> &m)
{
    print_comment<const char *>("Testing equal function");
    Matrix<type> ret = m;
}
void testMin(Matrix<type> &m1, Matrix<type> &m2)
{
    print_comment<const char *>("Testing minus");
    m1 - m2;
}
void testScalar(type scalar, Matrix<type> &m)
{
    print_comment<const char *>("Testing scalar moltiplication");
    scalar *m;
}
void testVector(Vector<type> &v, Matrix<type> &m)
{
    print_comment<const char *>("Testing vector moltiplication");
    v *m;
}
void testFunciton(Matrix<type> &m)
{
    print_comment<const char *>("Testing function application");
    m(vals);
}

int main()
{
    print_comment<const char *>("////////////////////////////////\nTest with matrix with double type\n////////////////////////////////\n");
    Matrix<type> m1(2, 3);
    m1[0][0] = static_cast<type>(3);
    m1[0][1] = static_cast<type>(23);
    m1[0][2] = static_cast<type>(21);
    m1[1][0] = static_cast<type>(3);
    m1[1][1] = static_cast<type>(23);
    m1[1][2] = static_cast<type>(21);

    Matrix<type> m2(3, 4);
    m2[0][0] = static_cast<type>(3);
    m2[0][1] = static_cast<type>(23);
    m2[0][2] = static_cast<type>(21);
    m2[0][3] = static_cast<type>(21);
    m2[1][0] = static_cast<type>(3);
    m2[1][1] = static_cast<type>(23);
    m2[1][2] = static_cast<type>(21);
    m2[1][3] = static_cast<type>(21);
    m2[2][0] = static_cast<type>(3);
    m2[2][1] = static_cast<type>(23);
    m2[2][2] = static_cast<type>(21);
    m2[2][3] = static_cast<type>(21);

    Matrix<type> m3(2, 3);
    m3[0][0] = static_cast<type>(3);
    m3[0][1] = static_cast<type>(23);
    m3[0][2] = static_cast<type>(21);
    m3[1][0] = static_cast<type>(3);
    m3[1][1] = static_cast<type>(23);
    m3[1][2] = static_cast<type>(21);

    Vector<type> v(2);
    v[0] = static_cast<type>(2321);
    v[1] = static_cast<type>(1231);

    type scalar = static_cast<type>(42);

    testMult(m1, m2);
    testAdd(m1, m3);
    testTranspose(m1);
    testEqual(m1);
    testMin(m1, m3);
    testScalar(scalar, m2);
    testVector(v, m1);

    return 0;
}