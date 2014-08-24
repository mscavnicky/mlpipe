#include <fstream>

#include "LinesReader.h"

vector<string>* LinesReader::read_lines(const std::string &filename)
{
    vector<string>* lines = new vector<string>();

	// Open
	ifstream fin(filename.c_str());
	if (!fin)
		throw "File not found.";
	if (!fin.is_open())
		throw "Error opening file.";

	// Read
	while (!fin.eof())
    {
		string line;
		getline (fin, line);
		if (fin.fail())
			break;
		lines->push_back(line);
    }

	// Close
	fin.close();

	return lines;
}
