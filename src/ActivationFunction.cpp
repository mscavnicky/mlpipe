#include <math.h>

#include "ActivationFunction.h"

Vector& ActivationFunction::apply(Vector& v)
{
    for (uint i = 0; i < v.length(); i++)
        v.set(i, compute(v[i]));
    return v;
}

Vector& ActivationFunction::apply_derivative(Vector& v)
{
    for (uint i = 0; i < v.length(); i++)
        v.set(i, compute_derivative(v[i]));
    return v;
}

double Sigmoid::compute(double x)
{
	double ex = exp(-x);
    return (double) (1.0 / (1.0 + ex));
}

double Sigmoid::compute_derivative(double primitive)
{
	return primitive * (1.0 - primitive);
}

double HyperbolicTangent::compute(double x)
{
    double e2x = exp(2.0 * x);
    return (double) (e2x - 1.0f) / (e2x + 1.0f);
}

double HyperbolicTangent::compute_derivative(double primitive)
{
	return 1.0 - primitive * primitive;
}
