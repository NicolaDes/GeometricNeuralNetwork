/**
 * @copyright GeometricNeuralNetwork
 * license Apache2
 * @author Nicola Dessi'
 * @version v1.0
 * @date May, 2018
 * @file
 */
#define VECTOR_TEST_MODULE

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

void testMult(Vector<type> &m1, Vector<type> &m2)
{
    print_comment<const char *>("Testing moltiplication");
    Matrix<type> test = m1 * m2;
}
void testAdd(Vector<type> &m1, Vector<type> &m2)
{
    print_comment<const char *>("Testing addition");
    m1 + m2;
}
void testEqual(Vector<type> &m)
{
    print_comment<const char *>("Testing equal function");
    Vector<type> ret = m;
}
void testMin(Vector<type> &m1, Vector<type> &m2)
{
    print_comment<const char *>("Testing minus");
    m1 - m2;
}
void testScalar(type scalar, Vector<type> &m)
{
    print_comment<const char *>("Testing scalar moltiplication");
    scalar *m;
}
void testFunciton(Vector<type> &m)
{
    print_comment<const char *>("Testing function application");
    m(vals);
}

int main()
{
    print_comment<const char *>("////////////////////////////////\nTest with matrix with double type\n////////////////////////////////\n");
    Vector<type> m1(3);
    m1[0] = static_cast<type>(3);
    m1[1] = static_cast<type>(23);
    m1[2] = static_cast<type>(21);

    Vector<type> m2(3);
    m2[0] = static_cast<type>(3);
    m2[1] = static_cast<type>(23);
    m2[2] = static_cast<type>(21);

    type scalar = static_cast<type>(42);

    testMult(m1, m2);
    testAdd(m1, m2);
    testEqual(m1);
    testMin(m1, m2);
    testScalar(scalar, m2);

    return 0;
}