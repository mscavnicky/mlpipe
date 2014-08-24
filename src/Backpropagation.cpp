#include <algorithm>
#include <iostream>
#include "Backpropagation.h"

Backpropagation::Backpropagation(Network* network, TrainingSet* training_set, double rate):
network_(network), training_set_(training_set), rate_(rate) 
{}

void Backpropagation::train() 
{
	for (uint i = 0; i < training_set_->size(); i++)
    {
		Pattern p = (*training_set_)[i];
		
		// Clears
		deltas_.clear();
		weight_changes_.clear();

		// Get outputs of each layer
		vector<Vector> layer_outputs;
		network_->feed_forward(p.input_, layer_outputs);

		// Compute deltas for each layer
		process_output_layer(p.output_, layer_outputs);
		process_hidden_layers(layer_outputs);

		// Compute and apply weight changes
		compute_weight_changes(layer_outputs);
		apply_weights_changes();
	}
}

void Backpropagation::process_output_layer(Vector& ideal, vector<Vector>& layer_outputs)
{
	// Get output of the output layer
	Vector layer_output = layer_outputs.back();

	// Compute derivative of the output of the output layer
	Vector layer_output_derivative(layer_output);
	network_->get_af()->apply_derivative(layer_output_derivative);

	// Create a matrix of derivatives
	Matrix derivatives = Matrix::diagonal_matrix(layer_output_derivative);

	// Compute error of the layer
	Vector error(layer_output);
	error -= ideal;

	// Compute deltas for this layer		
    deltas_.push_back(derivatives * error);
}

void Backpropagation::process_hidden_layers(vector<Vector>& layer_outputs) 
{
	for (int i = layer_outputs.size() - 2; i > 0; i--) {
		// Get output of the output layer
		Vector layer_output = layer_outputs[i];

		// Compute derivative of the output of the output layer
		Vector layer_output_derivative(layer_output);
		network_->get_af()->apply_derivative(layer_output_derivative);

		// Create a matrix of derivatives
		Matrix derivatives = Matrix::diagonal_matrix(layer_output_derivative);

		// Get subweights for the synapse
		Matrix weights = network_->get_weights(i);
		Matrix sub_weights = weights.submatrix(weights.rows() - 1, weights.cols());

		// Compute deltas for this layer
		Vector new_deltas = (derivatives * sub_weights) * deltas_.back();
	    deltas_.push_back(new_deltas);
    }
 }

void Backpropagation::compute_weight_changes(vector<Vector>& layer_outputs)
{
	// Reverse deltas because their were computed backwards
	reverse(deltas_.begin(), deltas_.end());

    for (uint i = 0; i < layer_outputs.size() - 1; i++) 
	{
		// Get output extended by 1
		Vector layer_output = layer_outputs[i];
		Vector extended_output(layer_output.length() + 1);
		for (uint j = 0; j < layer_output.length(); j++)
			extended_output.set(j, layer_output[j]);
		extended_output.set(layer_output.length(), 1);
		
		// Compute actual weight changes
		Matrix weight_changes = deltas_[i] * extended_output;
		weight_changes *= -rate_;

		Matrix weight_changes_t = weight_changes.transpose();
		weight_changes_.push_back(weight_changes_t);
    }
}

void Backpropagation::apply_weights_changes() 
{
    for (uint i = 0; i < network_->number_of_layers() - 1; i++)
      network_->get_weights(i) += weight_changes_[i];
}