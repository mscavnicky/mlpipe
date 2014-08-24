#include <iostream>
#include <sstream>
#include "Utils.h"

using namespace std;

int to_int(string s) 
{
	istringstream buffer(s);
	int value;
	buffer >> value; 
	return value;
}

double to_double(string s) 
{
	istringstream buffer(s);
	double value;
	buffer >> value; 
	return value;
}