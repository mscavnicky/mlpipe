#ifndef __BACKPROPAGATION_H
#define __BACKPROPAGATION_H

#include <list>
#include "Network.h"
#include "TrainingSet.h"

using namespace std;

/** 
 * Backpropagation algorithm. Trains a network using a given training set and rate.
 * Backpropagation works by updating netowrk weights using gradient descent.
 */
class Backpropagation {
private:
	Network* network_;
	TrainingSet* training_set_;
	double rate_;

	/** List of change deltas for each layer in the last iteration. */
	vector<Vector> deltas_;
	/** List of changes to the weights for each layer in the last iteration. */
	vector<Matrix> weight_changes_;

	void process_output_layer(Vector& ideal, vector<Vector>& layer_outputs);
	void process_hidden_layers(vector<Vector>& layer_outputs);
	void compute_weight_changes(vector<Vector>& layer_outputs);
	void apply_weights_changes();
public:
	Backpropagation(Network* network, TrainingSet* trainingSet, double rate);

	/** 
	 * Performs a single training cycles of the network using whole training 
	 * set. Network weights are updated online.
	 */
	void train();
};

#endif