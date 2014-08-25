#ifndef __NETWORK_H
#define __NETWORK_H

#include <vector>
#include <iostream>

#include "Vector.h"
#include "Matrix.h"
#include "ActivationFunction.h"

using namespace std;

/** Multilayer network with same activation function for each neuron. */
class Network
{
private:
    ActivationFunction* af_;
    /** Weights between layers. */
    vector<Matrix> weights_;

    /** Computes output of one layer. */
    Vector step(const Vector& input, const Matrix& weights) const;
public:
    /** Computes output of the network. */
    Vector feed_forward(const Vector& input) const;
    /** 
      * Computes output of the network. Keeps outputs of all layers in the 
      * output argument. 
      */
    Vector feed_forward(const Vector& input, vector<Vector>& layer_outputs) const;

    uint number_of_layers() const { return weights_.size() + 1; }

    /** Adds new weights matrix. Used when creating. */
    void add_matrix(Matrix m);
    /** Weights of the i-th layer. */
    Matrix& get_weights(int i) { return weights_[i]; }

    void set_af(ActivationFunction* af) { af_ = af; }
    ActivationFunction* get_af() const { return af_; }

    friend ostream& operator<<(ostream& out, Network& v);
};

#endif
