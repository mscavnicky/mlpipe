#ifndef __MATRIX_H
#define __MATRIX_H

#include <vector>
#include <string>

#include "Utils.h"

using namespace std;

class Vector;

class Matrix
{
private:
    double** m_;
    uint rows_, cols_;

	/** Allocates new memory of size rows * cols. */
    void allocate();
	/** Deletes referenced memory. */
    void clean();
	/** Internal copy method. */
    void copy(const Matrix& m);

public:
	/** Allocate matrix of specified dimension. */
	Matrix(int rows, int cols);
	/** Parses matrix from a list of rows. Columns in a row are separated by column. */
    Matrix(const vector<string>& lines);
	Matrix(const Matrix& m);
    ~Matrix();

	Matrix& operator=(const Matrix& m);
	/** Adds matrix to this. */
	Matrix& operator+=(const Matrix& m);
	/** Multiplies this matrix by scalar. */
	Matrix& operator*=(const double d);
	/** Multiplies matrix with vector. Returns Vector. */
	Vector operator*(const Vector& v);
	/** Matrix multiplication. */
	Matrix operator*(const Matrix& m);

	/** Creates submatrix using first 'rows' rows and first 'cols' columns. */
	Matrix submatrix(uint rows, uint cols);
	/** Create transposed matrix. */
	Matrix transpose();

    uint cols() const { return cols_; }
    uint rows() const { return rows_; }
    double get(int x, int y) const { return m_[x][y]; }
	void set(int x, int y, double d) { m_[x][y] = d; }

	/** Create matrix with given diagonal. All other values are equal to 0. */
	static Matrix diagonal_matrix(Vector& diagonal);
	/** Create random matrix with weights randomly initialized in the interval [0,1] */
	static Matrix random_matrix(uint rows, uint cols);

	friend ostream& operator<<(ostream& out, const Matrix& m);
};

#endif
