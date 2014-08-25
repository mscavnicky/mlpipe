#include <sstream>
#include <vector>

#include "Utils.h"
#include "Vector.h"

using namespace std;

Vector::Vector(int length)
{
    components_ = new double[length];
    length_ = length;
    for (uint i = 0; i < length_; i++)
        components_[i] = 0.0;
}

Vector::Vector(const string& s)
{
    istringstream iss(s);
    vector<double> v;

    double d;
    while (iss >> d)
        v.push_back(d);

    components_ = new double[v.size()];
    for (uint i = 0; i < v.size(); i++)
        components_[i] = v[i];
    length_ = v.size();
}

Vector::Vector(const Vector& v)
{
    copy(v);
}

Vector::~Vector()
{
    clean();
}

Vector& Vector::operator=(const Vector& v)
{
    if (this != &v)
    {
        clean();
        copy(v);
    }
    return *this;
}

Matrix Vector::operator*(const Vector& v)
{
    Matrix m(length_, v.length());
    for (uint i = 0; i < length_; i++)
      for (uint j = 0; j < v.length(); j++)
          m.set(j, i, components_[i] * v[j]);
    return m;
}

Vector Vector::operator*(const Matrix& m)
{
    if (length() != m.rows())
        throw "Matrix and vector do not match";

    Vector result(m.cols());
    for (uint i = 0; i < m.cols(); i++)
    {
        double sum = 0;
        for (uint j = 0; j < m.rows(); j++)
            sum += components_[j] * m.get(i, j);
        result.set(i, sum);
    }
    return result;
}

Vector& Vector::operator*=(const double d)
{
    for (uint i = 0; i < length(); i++)
        components_[i] *= d;
    return *this;
}

Vector& Vector::operator-=(const Vector& v)
{
    if (v.length() != length())
        throw "Cannot subtract vectors of different sizes.";

    for (uint i = 0; i < length(); i++)
        components_[i] -= v[i];
    return *this;
}

void Vector::set(int i, double d)
{
    components_[i] = d;
}

void Vector::clean()
{
    delete [] components_;
}

void Vector::copy(const Vector& v)
{
    length_ = v.length();
    components_ = new double[v.length()];
    for (uint i = 0; i < v.length(); i++)
        components_[i] = v[i];
}

ostream& operator<<(ostream& out, const Vector& v)
{   
    for (uint i = 0; i < v.length(); i++)
        out << v[i] << " ";
    return out;
}
