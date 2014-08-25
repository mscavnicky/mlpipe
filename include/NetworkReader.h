#ifndef __NETWORK_READER_H
#define __NETWORK_READER_H

#include <string>

#include "LinesReader.h"
#include "Network.h"

/** Reads network from txt file. */
class NetworkReader
{
private:
    LinesReader linerReader_;
public:
    /* Reads network from a file. */
    Network* read(const string& filename);
};

#endif
