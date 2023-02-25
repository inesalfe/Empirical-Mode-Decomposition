#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "FCtools.h"
#include "Vec.h"
using namespace std;

//(file name) returns lines, skips comment lines started by '//'
vector<string> FCtools::ReadFile_s(string name) {

	ifstream myfile (name.c_str());
	string line;
	vector <string> lines;

	if(myfile.is_open())
	{
		while (getline (myfile, line))
		{
			if (line.find("//") != -1)   //skip comment line
				continue;
			
			lines.push_back(line);
		}
	}
	else
		cout << "ERROR: Unable to open file." << endl;

	myfile.close();

	return lines;
} 

//(file name) returns vectors of Vec's
vector<Vec> FCtools::ReadFile_v(string name) {

	vector<string> lines = FCtools::ReadFile_s(name);
	//NOTA - os espaços antes e depois dos <> de fora são NECESSÁRIOS
	vector< vector<double> > m;

	vector<Vec> result((int)lines.size());

	for (int i=0; i< (int)lines.size(); i++) {

		double x;

		stringstream ss(lines[i]);    //dump line
		vector<double> a;

		while (ss >> x) {

			a.push_back(x);
		}

		m.push_back(a);
	}

	//dump matrix
	//numbers - ponteiro para array de linhas, cujo tamanho é n. de colunas

	for (int i1 = 0; i1 < (int)m.size(); ++i1)
	{
		for (int i2 = 0; i2 < (int)m[i1].size() ; ++i2)
		{
			double *numbers = new double[(int)m[i1].size()];

			for (int i3 = 0; i3 < (int)m[i1].size(); ++i3)
			{
				numbers[i3] = m[i1][i3];
			}

			result[i1] = Vec((int)m[i1].size(),numbers);

			delete[] numbers;
		}
	}

	return result;
} 

Vec* FCtools::ReadFile(string name, int nlines) {

	vector<Vec> veto = ReadFile_v(name);

	Vec* result = new Vec [nlines];

	for (int i = 0; i < nlines; ++i)
	{
		result[i] = veto[i];
	}

	return result;
}