#include <assert.h>
#include <iostream>
#include "Test.h"
#include "Vector.h"
#include "Matrix.h"

using namespace std;

void test_submatrix()
{
	Matrix m(3, 3);
	m.set(0, 0, 1);
	m.set(1, 0, 2);
	m.set(2, 0, 3);
	m.set(0, 1, 4);
	m.set(1, 1, 5);
	m.set(2, 1, 6);
	m.set(0, 2, 7);
	m.set(1, 2, 8);
	m.set(2, 2, 9);

	cout << m;

	Matrix sub = m.submatrix(2, 2);
	assert(sub.get(0, 0) == 1);
	assert(sub.get(1, 0) == 2);
	assert(sub.get(0, 1) == 4);
	assert(sub.get(1, 1) == 5);

	cout << sub;
}

void test_multiply_matrix()
{
	Matrix m1(3, 2);
	m1.set(0, 0, 1);
	m1.set(1, 0, 2);
	m1.set(0, 1, 3);
	m1.set(1, 1, 4);
	m1.set(0, 2, 5);
	m1.set(1, 2, 6);

	cout << m1;

	Matrix m2(2, 1);
	m2.set(0, 0, 2);
	m2.set(0, 1, 4);

	cout << m2;

	Matrix m = m1 * m2;
	assert(m.get(0, 0) == 10);
	assert(m.get(0, 1) == 22);

	cout << m;
}

void test_transpose1()
{
	Matrix m(3, 2);
	m.set(0, 0, 1);
	m.set(1, 0, 2);
	m.set(0, 1, 3);
	m.set(1, 1, 4);
	m.set(0, 2, 5);
	m.set(1, 2, 6);

	cout << m;

	Matrix mt = m.transpose();
	assert(mt.get(0, 0) == 1);
	assert(mt.get(1, 0) == 3);
	assert(mt.get(2, 0) == 5);
	assert(mt.get(0, 1) == 2);
	assert(mt.get(1, 1) == 4);
	assert(mt.get(2, 1) == 6);

	cout << mt;
}

void test_transpose2()
{
	Matrix m(2, 4);
	m.set(0, 0, 1);
	m.set(1, 0, 2);
	m.set(2, 0, 3);
	m.set(3, 0, 4);
	m.set(0, 1, 5);
	m.set(1, 1, 6);
	m.set(2, 1, 7);
	m.set(3, 1, 8);

	cout << m;

	Matrix mt = m.transpose();
	assert(mt.get(0, 0) == 1);
	assert(mt.get(1, 0) == 5);
	assert(mt.get(0, 1) == 2);
	assert(mt.get(1, 1) == 6);
	assert(mt.get(0, 2) == 3);
	assert(mt.get(1, 2) == 7);
	assert(mt.get(0, 3) == 4);
	assert(mt.get(1, 3) == 8);

	cout << mt;
}

void test_multiply_matrix_with_vector()
{
	Matrix m(3, 2);
	m.set(0, 0, 1);
	m.set(1, 0, 2);
	m.set(0, 1, 3);
	m.set(1, 1, 4);
	m.set(0, 2, 5);
	m.set(1, 2, 6);

	cout << m;

	Vector v(2);
	v.set(0, 2);
	v.set(1, 4);

	cout << v;

	Vector o = m * v;
	cout << o;

	assert(o[0] == 10);
	assert(o[1] == 22);
}

void test_vector_multiply_vector()
{
	Vector v1("1 2 3");
	cout << v1;
	Vector v2("4 5");
	cout << v2;

	Matrix m = v1 * v2;
	assert(m.rows() == 3);
	assert(m.cols() == 2);
	assert(m.get(0, 0) == 4);
	assert(m.get(1, 0) == 5);
	assert(m.get(0, 1) == 8);
	assert(m.get(1, 1) == 10);
	assert(m.get(0, 2) == 12);
	assert(m.get(1, 2) == 15);
}

void run_tests()
{
	cout << "TEST: SUBMATRIX" << endl;
	test_submatrix();
	cout << "TEST: MULTIPLY MATRIX" << endl;
	test_multiply_matrix();
	cout << "TEST: TRANSPOSE MATRIX" << endl;
	test_transpose1();
	test_transpose2();
	cout << "TEST: MULTIPLY MATRIX WITH VECTOR" << endl;
	test_multiply_matrix_with_vector();
	cout << "TEST: VECTOR MULTIPLY VECTOR" << endl;
	test_vector_multiply_vector();
}