#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>  //for EXIT
#include "Vec.h"
#include "FCmatrixFull.h"
#include "EqSolver.h"
using namespace std;

FCmatrixFull::FCmatrixFull() : FCmatrix() {

	rowindices = NULL;
	classname = "FCmatrixFull";
}

FCmatrixFull::FCmatrixFull(double **fm, int m, int n) : FCmatrix(fm,m,n) {

	rowindices = new int [m];

	for (int i = 0; i < m; ++i)
	{
		rowindices[i] = i;
	}
	
	classname = "FCmatrixFull";
} 

//matrix mxn
FCmatrixFull::FCmatrixFull(double *fm, int m, int n) : FCmatrix(fm,m,n) {

	rowindices = new int [m];

	for (int i = 0; i < m; ++i)
	{
		rowindices[i] = i;
	}
	
	classname = "FCmatrixFull";
}

FCmatrixFull::FCmatrixFull(vector<Vec> a) : FCmatrix(a) {

	rowindices = new int [a.size()];

	for (int i = 0; i < a.size(); ++i)
	{
		rowindices[i] = i;
	}

	classname = "FCmatrixFull";
}

FCmatrixFull::FCmatrixFull(const FCmatrixFull& a) :FCmatrix(a) {

	rowindices = new int[a.M.size()];

	for (int i = 0; i < a.M.size(); ++i)
	{
		rowindices[i] = i;
	}

	classname = "FCmatrixFull";
}

void FCmatrixFull::Print() const {

	for (int i1 = 0; i1 < M.size(); ++i1)
	{
		for (int i2 = 0; i2 < M[i1].size(); ++i2)
		{
			cout << " " << M[i1][i2] << " ";
		}
		cout << endl;
	}
}

double FCmatrixFull::Determinant() const {

	if (M.size() != M[0].size()) {
		cout << "ERROR: Cannot compute determinant of non-square matrix." << endl;
		exit(1);
	}

	EqSolver gauss(*this,Vec((int)M.size(),(double)0));

	FCmatrixFull temp = gauss.GetU();

	double solution = temp[0][0];

	for (int i = 1; i < M.size(); ++i)
	{
		solution *= temp[i][i]; 
	}

	if (gauss.GetSwapped() == true)
		solution = -solution;

	return solution;
}

/*FCmatrixFull FCmatrixFull::GetInvert() const {

	if (M.size() != M[0].size()) {
	cout << "ERROR: Cannot compute inverse of non-square matrix." << endl;
	exit(1);
	} 

	int n = M.size();

	vector<Vec> inverse(n);
	vector<Vec> identity(n);

	for (int i1 = 0; i1 < n; ++i1)   //make identity matrix
	{
		double *temp = new double [n];

		for (int i2 = 0; i2 < n; ++i2)
		{
			if (i2 == i1)
				temp[i2] = 1;
			else
				temp[i2] = 0;
		}

		identity[i1] = Vec(n,temp);

		delete[] temp;
	}

	FCmatrixFull ID(identity);
	
	for (int i = 0; i < n; ++i)
	{
		EqSolver inv((*this),ID.GetCol(i));
		inverse[i] = inv.GaussEliminationSolver();
	}

	return FCmatrixFull(inverse);
}*/

void FCmatrixFull::swapRows(int a,int b) {

	if (a == b)
		cout << "Selecionou trocar duas linhas iguais." << endl;
	else
	{
		Vec temp;

		temp = M[a];
		M[a] = M[b];
		M[b] = temp;
	}
}

Vec& FCmatrixFull::operator[] (int i) {

	return M[i];
}

Vec FCmatrixFull::GetRow(int i) const {

	return M[i];
}

Vec FCmatrixFull::GetCol(int i) const {

	double *a = new double [M.size()];

	for (int i1 = 0; i1 < M.size(); ++i1)
	{
		a[i1] = M[i1][i];
	}

	return Vec(M.size(),a);
}

FCmatrixFull FCmatrixFull::operator+(const FCmatrix& a) {

	if (M.size() != (a.GetM()).size())
	{
		cout << "ERROR: FCmatrixFull::operator+(const FCmatrix& a)";
		exit(1);
	}

	if (M[0].size() != (a.GetM())[0].size())
	{
		cout << "ERROR: FCmatrixFull::operator+(const FCmatrix& a)";
		exit(1);
	}

	vector<Vec> output(M.size());
	vector<Vec> input(a.GetM());

	for (int i = 0; i < M.size(); ++i)
	{
		output[i] = M[i] + input[i];
	}

	return FCmatrixFull(output);
} 

FCmatrixFull FCmatrixFull::operator-(const FCmatrix& a) {

	if (M.size() != (a.GetM()).size())
	{
		cout << "ERROR: FCmatrixFull::operator-(const FCmatrix& a)";
		exit(1);
	}

	if (M[0].size() != (a.GetM())[0].size())
	{
		cout << "ERROR: FCmatrixFull::operator-(const FCmatrix& a)";
		exit(1);
	}

	vector<Vec> output(M.size());
	vector<Vec> input(a.GetM());

	for (int i = 0; i < M.size(); ++i)
	{
		output[i] = M[i] - input[i];
	}

	return FCmatrixFull(output);

} 

FCmatrixFull FCmatrixFull::operator*(double lambda) {

	vector<Vec> output(M.size());

	for (int i = 0; i < (int)M.size(); ++i)
	{
		output[i] = M[i] * lambda;
	}

	return FCmatrixFull(output);
}

FCmatrixFull FCmatrixFull::operator*(const FCmatrix& Obj) {

	int number_row_1 = M.size();
	int number_col_1 = M[0].size();
	vector<Vec> m_obj = Obj.GetM();
	FCmatrixFull matrix_obj(m_obj);
	int number_row_2 = m_obj.size();
	int number_col_2 = m_obj[0].size();
	if (number_col_1 != number_row_2) {
		cout << "Not possible to multiply" << endl;
		return *this;
	}
	else {
		double line[number_row_1];
		for (int i = 0; i < number_col_2; i++) {
			line[i] = 0;
		}
		FCmatrixFull matrix_output(line, number_row_1, number_col_2);
		for (int j = 0; j < number_col_2; j++){
			for (int i = 0; i < number_row_1; i++) {
				matrix_output[i][j] = M[i].dot(matrix_obj.GetCol(j));
			}
		}
		return matrix_output;
	}
}

Vec FCmatrixFull::operator*(const Vec& a) {

	if (M[0].size() != a.size())
	{
		cout << "ERROR: FCmatrixFull::operator*(const Vec& a)";
		exit(1);
	}

	double *mat = new double[M[0].size()];

	for (int i = 0; i < M.size(); ++i)
	{
		Vec temp = M[i];
		mat[i] = temp.dot(a);
	}

	Vec b(M.size(),mat);

	delete[] mat;

	return b;
}

int FCmatrixFull::GetRowMax(int j=0) const {

	Vec temp = (*this).GetRow(j);
	int i = 0;

	temp.fabs_bubbleSort(0,temp.size()-1,1);

	if (temp[0])

	for (i = 0; i < M[j].size(); ++i)
	{
		if (temp[0] == M[j][i])
			break;
	}

	return i;
}

int FCmatrixFull::GetColMax(int j=0) const {

	Vec temp = (*this).GetCol(j);
	int i = 0;

	temp.fabs_bubbleSort(0,temp.size()-1,1);

	temp.Print();

	for (i = 0; i < M.size(); ++i)
	{
		if (temp[0] == M[i][j])
			break;
	}

	return i;
}

int* FCmatrixFull::GetDim() const {

	int *solution = new int[2];
	solution[0] = M.size();
	solution[1] = M[0].size();

	return solution;
}

FCmatrixFull operator*(double a, FCmatrixFull& b) {
	return b*a;
}

FCmatrixFull::~FCmatrixFull() {
	delete[] rowindices;
}