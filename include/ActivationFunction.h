#ifndef __ACTIVATION_FUNCTION_H
#define __ACTIVATION_FUNCTION_H

#include "Vector.h"

/** Interface for activation function used by neurons. */
class ActivationFunction
{
public:
    virtual double compute(double x) = 0;
    /** Compute derivative value using previously computed primitive function. */
    virtual double compute_derivative(double primitive) = 0;

    /** Applies activation functions to all components of the vector. */
    Vector& apply(Vector& v);
    /** Applies derivative of activation functions to all components of the vector. */
    Vector& apply_derivative(Vector& v);
};

/** Sigmoid activation functions for values from [0,1]. */
class Sigmoid : public ActivationFunction
{
public:
    virtual double compute(double t);
    virtual double compute_derivative(double primitive);
};

/** Tanh activation functions for values from [-1,1]. */
class HyperbolicTangent : public ActivationFunction
{
public:
    virtual double compute(double t);
    virtual double compute_derivative(double primitive);
};

#endif