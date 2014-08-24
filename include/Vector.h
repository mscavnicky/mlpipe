#ifndef __VECTOR_H
#define __VECTOR_H

#include <ostream>
#include <string>

#include "Matrix.h"

using namespace std;

class Vector
{
private:
    double* components_;
    uint length_;

	/** Deletes referenced memory. */
	void clean();
	/** Internal copy method for copy ctor and assignment operator. */
    void copy(const Vector& v);

public:
	/** Create vector of zeros of specified length. */
    Vector(int length);
	/** Parses list of values separated by space. */
    Vector(const string& s);
	Vector(const Vector& v);
    ~Vector();

	Vector& operator=(const Vector& v);
	/** Multiply transposed vector with vector from the left. */
	Matrix operator*(const Vector& v);
	/** Multiply vector with matrix from the left. */
    Vector operator*(const Matrix& m);
	/** Multiply vector with scalar. */
    Vector& operator*=(const double d);
	/** Subtract vector from this. */
	Vector& operator-=(const Vector& v);
    
	/** Access operator to single values. */
    double operator[](int i) const { return components_[i]; }	

    uint length() const { return length_; }
    void set(int i, double d);

    friend ostream& operator<<(ostream& out, const Vector& v);
};



#endif
