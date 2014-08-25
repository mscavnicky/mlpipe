#include "NetworkReader.h"

Network* NetworkReader::read(const string& filename)
{
    Network* network = new Network();

    vector<string>* lines = linerReader_.read_lines(filename);
    if (lines->size() == 0)
        throw "Empty network file.";

    vector<string>::iterator it = lines->begin();

    // Reads AF
    string function = (*it);
    if (function.compare("SIGMOID") == 0)
        network->set_af(new Sigmoid());
    else if (function.compare("TANH") == 0)
        network->set_af(new HyperbolicTangent());
    else
        throw "Activation function not recognized.";
    it++;

    // Reads neurons
    Vector neurons(*it);
    it++;

    if (neurons.length() < 2)
        throw "Netwrok needs at least 2 layers.";

    // Reads matrices
    for (uint i = 0; i < neurons.length() - 1; i++)
    {
        vector<string> matrix_lines;
        for (int j = 0; j < neurons[i] + 1; j++)
        {
            matrix_lines.push_back(*it);
            it++;
        }

        Matrix m(matrix_lines);
        network->add_matrix(m);
    }

    delete lines;
    return network;
}
