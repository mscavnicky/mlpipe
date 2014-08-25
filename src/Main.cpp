#include <stdlib.h>
#include <iostream>

#include "Matrix.h"
#include "TrainingSetReader.h"
#include "NetworkReader.h"
#include "Backpropagation.h"

using namespace std;

/** Initialize a network with randomly initialized weights. */
void init_task(int argc, const char* argv[]) 
{
	Network network;

	string activation_function = argv[2];
	if (activation_function == "sigmoid")
		network.set_af(new Sigmoid());
	else if (activation_function == "tanh")
		network.set_af(new HyperbolicTangent());
	else
		throw "Invalid activation function.";

	// Random weight matrices
	int prev_num_neurons = to_int(argv[3]);
	for (int i = 1; i < argc - 3; i++) {
		int num_neurons = to_int(argv[i+3]);

		Matrix weights = Matrix::random_matrix(prev_num_neurons + 1, num_neurons);
		network.add_matrix(weights);

		prev_num_neurons = num_neurons;
	}

	// Output network to STDOUT
	cout << network;
}

void test_task(const char* argv[]) 
{
	string training_set_filename(argv[2]);
    string network_filename(argv[3]);

	// Reads training set
    TrainingSetReader training_set_reader;
    TrainingSet* training_set = training_set_reader.read(training_set_filename);
	
	// Reads network
    NetworkReader network_reader;
    Network* network = network_reader.read(network_filename);

	// Runs testing set through a network
    for (uint i = 0; i < training_set->size(); i++)
    {
		Pattern p = (*training_set)[i];
		Vector v = network->feed_forward(p.input_);
        cout << p << "| " << v << endl;
    }
		
	// Cleans
    delete network;
    delete training_set;
}

void train_task(const char* argv[]) 
{
	string training_set_filename(argv[2]);
	string network_filename(argv[3]);
	string c(argv[4]);
	int cycles = to_int(c);
	string r(argv[5]);
	double rate = to_double(r);	

	// Reads network
    NetworkReader network_reader;
    Network* network = network_reader.read(network_filename);

	// Reads training set
    TrainingSetReader training_set_reader;
    TrainingSet* training_set = training_set_reader.read(training_set_filename);
	
	// Trains network
	Backpropagation backpropagation(network, training_set, rate);
	for (int i = 0; i < cycles; i++)
		backpropagation.train();

	// Writes trained network to output
	cout << *network;

	// Cleans
	delete network;
	delete training_set;
}


int main(int argc, const char* argv[])
{
	if (argc == 1)
	{
		cout << "Usage: 'mlpipe init|train|test'" << endl;
		return 1;
	}

	string task(argv[1]);

	try
    {
    	if (task == "init")
    	{
    		if (argc < 5)
    		{
    			cout << "Usage: mlpipe init sigmoid|tanh layer1 layer2 ..." << endl;
    			return 1;
    		}
    		init_task(argc, argv);
    	}
		else if (task == "test") 
		{
			if (argc != 4)
			{
				cout << "Usage: mlpipe test testing_set_file network_file" << endl;
				return 1;
			}
			test_task(argv);
		}
		else if (task == "train") 
		{
			if (argc != 6)
			{
				cout << "Usage: mlpipe train training_set_file network_file cycles rate" << endl;
				return 1;
			}
			train_task(argv);
		} 
    }
    catch (const char* c_str)
    {
        cerr << "ERROR: " << c_str << endl;
        return 1;
    }

    return 0;
}