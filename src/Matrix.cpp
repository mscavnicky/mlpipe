#include <cstdlib>
#include <iostream>
#include "Utils.h"
#include "Vector.h"
#include "Matrix.h"

using namespace std;

Matrix::Matrix(int rows, int cols):
rows_(rows), cols_(cols)
{
	allocate();

	for (uint i = 0; i < cols_; i++)
		for (uint j = 0; j < rows_; j++)
			m_[i][j] = 0.0;
}

Matrix::Matrix(const vector<string>& lines)
{
    rows_ = lines.size();

	// Parses lines by converting them onto Vector
    vector<Vector> vector_rows;
    for (uint i = 0; i < rows_; i++)
    {
        Vector v(lines[i]);
        vector_rows.push_back(v);
    }

    cols_ = vector_rows[0].length();

    allocate();

	// Copies data from parsed Vectors
    for (uint i = 0; i < cols_; i++)
        for (uint j = 0; j < rows_; j++)
            m_[i][j] = vector_rows[j][i];
}

Matrix::Matrix(const Matrix& m)
{
    copy(m);
}

Matrix& Matrix::operator=(const Matrix& m)
{
    if (this != &m)
    {
		clean();
		copy(m);
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
	if (cols_ != m.cols() || rows_ != m.rows())
		throw "Matrices not of same size.";

	for (uint i = 0; i < cols_; i++)
		for (uint j = 0; j < rows_; j++)
			m_[i][j] += m.get(i, j);
	return *this;
}

Matrix& Matrix::operator*=(const double d)
{
    for (uint i = 0; i < cols_; i++)
		for (uint j = 0; j < rows_; j++)
			m_[i][j] *= d;
    return *this;
}

Vector Matrix::operator*(const Vector& v)
{
	if (cols_ != v.length())
      throw "Multiplying matrix with vector of incorrect length.";

	Vector res(rows_);
    for (uint i = 0; i < rows_; i++)
		for (uint j = 0; j < cols_; j++)
			res.set(i, res[i] + v[j] * m_[j][i]);

    return res;
}

Matrix Matrix::operator*(const Matrix& m)
{
	if (cols_ != m.rows())
      throw "Multiplying matrix with matrix of incorrect size";

    Matrix result(rows_, m.cols());
    for (uint i = 0; i < rows_; i++) 
      for (uint j = 0; j < m.cols(); j++) 
	  {
        double sum = 0.0;
        for (uint k = 0; k < cols_; k++)
          sum += m_[k][i] * m.get(j, k);
        result.set(j, i, sum);
      }

    return result;
}

Matrix::~Matrix()
{
    clean();
}

void Matrix::allocate()
{
    m_ = new double*[cols_];
    for (uint i = 0; i < cols_; i++)
        m_[i] = new double[rows_];
}

void Matrix::clean()
{
    for (uint i = 0; i < cols_; i++)
        delete [] m_[i];
    delete [] m_;
}

void Matrix::copy(const Matrix& m)
{
    rows_ = m.rows();
    cols_ = m.cols();
    allocate();
    for (uint i = 0; i < cols_; i++)
        for (uint j = 0; j < rows_; j++)
            m_[i][j] = m.get(i, j);
}

Matrix Matrix::submatrix(uint rows, uint cols)
{
	Matrix m(rows, cols);
	for (uint i = 0; i < cols; i++)
        for (uint j = 0; j < rows; j++)
            m.set(i, j, m_[i][j]);		
	return m;
}

Matrix Matrix::transpose()
{
	Matrix m(cols_, rows_);
	for (uint i = 0; i < cols_; i++)
        for (uint j = 0; j < rows_; j++)
            m.set(j, i, m_[i][j]);
	return m;
}

Matrix Matrix::diagonal_matrix(Vector& diagonal)
{
    Matrix m(diagonal.length(), diagonal.length());
    for (uint i = 0; i < diagonal.length(); i++)
        m.set(i, i, diagonal[i]);
    return m;
}

Matrix Matrix::random_matrix(uint rows, uint cols)
{
    Matrix m(rows, cols);
    for (uint i = 0; i < rows; i++)
        for (uint j = 0; j < cols; j++)
        {
            // Random number in the range [0, 1]
            double d = (double) rand() / (double) RAND_MAX;
            m.set(j, i, d);
        }
    return m;
}

ostream& operator<<(ostream& out, const Matrix& m)
{
	for (uint i = 0; i < m.rows(); i++)
	{		
		for (uint j = 0; j < m.cols(); j++)
			out << m.get(j, i) << " ";
		out << endl;
	}
	return out;
}