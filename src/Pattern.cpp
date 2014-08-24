#include "Pattern.h"

Pattern::Pattern(Vector input, Vector output):
input_(input), output_(output)
{}

ostream& operator<<(ostream& out, const Pattern& p)
{
    return out << p.input_ << "| " << p.output_;
}