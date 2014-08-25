#include <typeinfo>
#include "Network.h"

Vector Network::step(const Vector& input, const Matrix& weights) const
{
    // Extend input by bias
    Vector input_extented(input.length() + 1);
    for (uint i = 0; i < input.length(); i++)
        input_extented.set(i, input[i]);
    input_extented.set(input.length(), 1);

    // Apply activation function
    Vector output = input_extented * weights;
    af_->apply(output);

    return output;
}

Vector Network::feed_forward(const Vector& input) const
{
    if (input.length() + 1 != weights_[0].rows())
        throw "Training set does not match network.";

    Vector output = Vector(input);
    for (uint i = 0; i < weights_.size(); i++)
        output = step(output, weights_[i]);
    return output;
}

Vector Network::feed_forward(const Vector& input, vector<Vector>& layer_outputs) const
{
    if (input.length() + 1 != weights_[0].rows())
        throw "Training set does not match network.";

    Vector output = Vector(input);
    for (uint i = 0; i < weights_.size(); i++)
    {
        layer_outputs.push_back(output);
        output = step(output, weights_[i]);     
    }
    layer_outputs.push_back(output);
    return output;
}

void Network::add_matrix(Matrix m)
{
    weights_.push_back(m);
}

ostream& operator<<(ostream& out, Network& n)
{
    Sigmoid* sigmoid = dynamic_cast<Sigmoid*>(n.get_af());
    if (sigmoid != NULL)
        out << "SIGMOID" << endl;

    HyperbolicTangent* tangent = dynamic_cast<HyperbolicTangent*>(n.get_af());
    if (tangent != NULL)
        out << "TANH" << endl;

    for (uint i = 0; i < n.number_of_layers() - 1; i++)
        out << n.get_weights(i).rows() - 1 << " ";
    out << n.get_weights(n.number_of_layers() - 2).cols() << endl;

    for (uint i = 0; i < n.number_of_layers() - 1; i++)
        out << n.get_weights(i);
    return out;
}