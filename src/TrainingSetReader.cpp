#include <iostream>

#include "Utils.h"
#include "Pattern.h"
#include "TrainingSetReader.h"

using namespace std;

TrainingSet* TrainingSetReader::read(string& filename)
{
    TrainingSet* training_set = new TrainingSet();

    // Read all lines in file
    vector<string>* lines = linesReader_.read_lines(filename);
    if (lines->size() == 0)
        throw "Training set is empty.";

    for (unsigned int i = 0; i < lines->size(); i++)
    {
        // Check for empty line
        string line = (*lines)[i];
        if (line.empty())
            throw "Empty line in training set.";

        // Split string into input and output
        int separator_pos = line.find(" | ");
        if (separator_pos < 0)
            throw "Training set separator not found.";

        string input = line.substr(0, separator_pos);
        string output = line.substr(separator_pos + 3, line.size());

        // Parses input and output Vector
        Vector input_vec(input);
        Vector output_vec(output);

        Vector v(line);
        if (i == 0) {
            // First sets the expected length of all inputs and outputs
            input_length_ = input_vec.length();
            output_length_ = output_vec.length();
        }
        else if (input_vec.length() != input_length_ || output_vec.length() != output_length_)
            throw "Corrupted training set file.";       

        // Add Pattern to TrainingSet
        Pattern p(input_vec, output_vec);
        training_set->push_back(p);
    }
    delete lines;

    return training_set;
}
