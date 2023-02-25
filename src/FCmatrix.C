#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>  //for EXIT
#include "Vec.h"
#include "FCmatrix.h"

FCmatrix::FCmatrix() {

	vector<Vec> a(0);
	M = a;
	classname = "FCmatrix";
}

FCmatrix::FCmatrix(double** fm, int m, int n) {

	for (int i1 = 0; i1 < m; ++i1)
	{
		double *numbers = new double [n];

		for (int i2 = 0; i2 < n; ++i2)
		{
			numbers[i2] = fm[i1][i2];
		}

		M.push_back(Vec(n,numbers));

		delete[] numbers;
	}

	classname = "FCmatrix";
}

FCmatrix::FCmatrix(double* fm, int m, int n) {

	int a = 0;

	for (int i1 = 0; i1 < m; ++i1)
	{
		double *temp = new double[n];

		for (int i2 = 0; i2 < n; ++i2)
		{
			temp[i2] = fm[a];
			a++;
		}

		M.push_back(Vec(n,temp));

		delete[] temp;
	}

	classname = "FCmatrix";
}

FCmatrix::FCmatrix(vector<Vec> a) {

	M = a;
	classname = "FCmatrix";
}

FCmatrix::FCmatrix(const FCmatrix& bj) {

	M = bj.M;
	classname = bj.classname;
}

void FCmatrix::Print() const {}


vector<Vec> FCmatrix::GetM() const {

	return M;
}

string FCmatrix::GetClassname() const {

	return classname;
}

void FCmatrix::SetM(vector<Vec> a) {

	M.clear();
	M = a;
}

FCmatrix::~FCmatrix() {
	M.clear();
}