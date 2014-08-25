#ifndef __PATTERN_H
#define __PATTERN_H

#include "Vector.h"

/** Pair of input and output vectors. */
class Pattern 
{
public:
    Vector input_;
    Vector output_;

    Pattern(Vector input, Vector output);

    friend ostream& operator<<(ostream& out, const Pattern& p);
};

#endif 