#ifndef __TRAINING_SET_READER_H
#define __TRAINING_SET_READER_H

#include "LinesReader.h"
#include "TrainingSet.h"

/** Reads training set from text file. */
class TrainingSetReader
{
private:
    LinesReader linesReader_;

    uint input_length_;
    uint output_length_;
public:
    /* Reads training set from a file. */
    TrainingSet* read(string& filename);
};

#endif
