#ifndef _FCtools_
#define _FCtools_
#include <iostream>
#include <string>
#include <vector>
#include "Vec.h"
using namespace std;

class FCtools {
public:
	static vector<string> ReadFile_s(string); //file name, returns lines
	static vector<Vec> ReadFile_v(string); //file name, number of columns, returns vectors of Vecs
	static Vec* ReadFile(string, int); //file name, returns pointer to array of Vecs, int # of lines
};

#endif