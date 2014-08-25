# mlpipe

Command line implementation of multilayer perceptron and backpropagation algorithm. Enables training neural networks from command line.

# Usage

To create a new network with 3 layers, 4 input neurons, 1 output neuron, initialized with random weights you can use the following

```sh
mlpipe init sigmoid 4 6 1 > network.txt
```

This will make all the neurons in the network use sigmoid initialization function. To train your network using an input dataset

```sh
mlpipe train dataset.txt network.txt 1000 0.1 > trained.txt
```

Where 1000 is the number of training cycles to run, and 0.1 is the learning rate. Dataset.txt has to be in the format 

```
input1 input2 input3 input4 | output1
````

Finally, to run the trained network against a test set you should

```
mlpipe test testset.txt trained.txt
```