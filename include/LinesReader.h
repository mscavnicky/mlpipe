#ifndef __LINES_READER_H
#define __LINES_READER_H

#include <vector>
#include <string>

using namespace std;

/** Utility class used for reading lines of a text file. */
class LinesReader
{
public:
	/** Reads text file into vector of lines. */
	vector<string>* read_lines(const string& filename);
};

#endif
