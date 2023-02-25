#include <iostream> //cout
#include <stdlib.h> //exit
#include "FCmatrixBanded.h"
#include "EqSolver.h"

FCmatrixBanded::FCmatrixBanded() : FCmatrix() {

	dim = 0;
	classname = "FCmatrixBanded";
}

FCmatrixBanded::FCmatrixBanded(double **fm, int n) : dim(n) { 
//n - tamanho da mid diagonal - matrix nxn

	for (int i1 = 0; i1 < 3; ++i1)
	{
		int a = dim;
		if (i1 == 0 || i1 == 2)
			a = dim - 1;

		double *numbers = new double [a];

		for (int i2 = 0; i2 < a; ++i2)
		{
			numbers[i2] = fm[i1][i2];
		}

		M.push_back(Vec(a,numbers));

		delete[] numbers;
	}

	classname = "FCmatrixBanded";
} 

FCmatrixBanded::FCmatrixBanded(double *fm, int n) : dim(n) {

	int b = 0;

	for (int i1 = 0; i1 < 3; ++i1)
	{
		int a = dim;
		if (i1 == 0 || i1 == 2)
			a = dim - 1;

		double *numbers = new double [a];

		for (int i2 = 0; i2 < a; ++i2)
		{
			numbers[i2] = fm[b];
			b++;
		}

		M.push_back(Vec(a,numbers));

		delete[] numbers;
	}

	classname = "FCmatrixBanded";
}

FCmatrixBanded::FCmatrixBanded(vector<Vec> a) {

	M = a;
	//dim = (int)M[1].size();
	//cout << dim << endl;
	dim = (int)(*this).GetM()[1].size();
	//cout << dim << endl;
	classname = "FCmatrixBanded";
}

FCmatrixBanded::FCmatrixBanded(const FCmatrixBanded& obj) {

	M = obj.M;
	classname = obj.classname;
	dim = obj.dim;
}

int* FCmatrixBanded::GetDim() const {

	int *b = new int [2];
	b[0] = dim;
	b[1] = dim;
	
	return b;
}

//get diagonal i
Vec& FCmatrixBanded::operator[] (int i) {

	if (i < 0 || i > 2)
	{
		cout << "ERROR [FCmatrixBanded::operator[](int)]: Cannot get diagonal " << i << "." << endl;
		exit(1);
	}

	return M[i];
}

Vec FCmatrixBanded::GetRow(int i) const {

	double *numbers = new double [dim];

	for (int i = 0; i < dim; ++i)
	{
		numbers[i] = 0;
	}

	for (int i2 = 0; i2 < dim; ++i2)
	{
		if (i2 == i)
		{
			if (i2-1 >= 0)
				numbers[i2-1] = M[0][i-1];

				numbers[i2] = M[1][i];

			if (i2+1 < dim)
				numbers[i2+1] = M[2][i];
		}
	}

	Vec solution(dim,numbers);

	return solution;
}

Vec FCmatrixBanded::GetCol(int i) const {

	double *numbers = new double [dim];

	for (int i = 0; i < dim; ++i)
	{
		numbers[i] = 0;
	}

	for (int i2 = 0; i2 < dim; ++i2)
	{
		if (i2 == i)
		{
			if (i2-1 >= 0)
				numbers[i2-1] = M[2][i-1];

				numbers[i2] = M[1][i];

			if (i2+1 < dim)
				numbers[i2+1] = M[0][i];
		}
	}

	Vec solution(dim,numbers);

	return solution;
}

double FCmatrixBanded::Determinant() const {
	EqSolver a((*this), Vec(dim, (double)0));
	
	FCmatrixBanded matrix = a.GetD();
	matrix.Print();
	
	double det = 1;
	for (int i = 0; i < dim; i++) {
		det = det * matrix[1][i];		
	}
	return det;
}

void FCmatrixBanded::Print() const {

	for (int i = 0; i < dim; ++i)
	{
		Vec temp = (*this).GetRow(i);
		temp.Print();
	}
}

int FCmatrixBanded::GetRowMax(int j) const {

	Vec temp = (*this).GetRow(j);
	Vec rowj(temp);
	int i = 0;

	temp.fabs_bubbleSort(0,dim-1,1);

	if (temp[0])

	for (i = 0; i < dim; ++i)
	{
		if (temp[0] == rowj[i])
			break;
	}

	return i;
}

int FCmatrixBanded::GetColMax(int j) const {

	Vec temp = (*this).GetCol(j);
	Vec colj(temp);
	int i = 0;

	temp.fabs_bubbleSort(0,dim-1,1);

	//temp.Print();

	for (i = 0; i < dim; ++i)
	{
		if (temp[0] == colj[i])
			break;
	}

	return i;
}

void FCmatrixBanded::swapRows(int a, int b) {

	if (a == b)
	{
		cout << "You chose to swap the diagonal with itself." << endl;
		return;
	}

	if (a != 0 && a != 2)
	{
		cout << "ERROR [FCmatrixBanded::swapRows(int,int)]: You can only swap the lower diagonal with the upper diagonal." << endl;
		exit(1);
	}
	if (b != 0 && b != 2)
	{
		cout << "ERROR [FCmatrixBanded::swapRows(int,int)]: You can only swap the lower diagonal with the upper diagonal." << endl;
		exit(1);
	}

	Vec temp;
	temp = M[a];
	M[a] = M[b];
	M[b] = temp;
}

FCmatrixBanded FCmatrixBanded::operator+(const FCmatrix& a) {

	if (M.size() != (a.GetM()).size())
	{
		cout << "ERROR: FCmatrixBanded::operator+(const FCmatrix& a)" << endl;
		exit(1);
	}

	vector<Vec> output(M.size());
	vector<Vec> input(a.GetM());

	for (int i1 = 0; i1 < 3; ++i1)
	{
		double *array = new double [M[i1].size()];

		for (int i2 = 0; i2 < M[i1].size(); ++i2)
		{
			array[i2] = M[i1][i2] + input[i1][i2];
		}

		output[i1] = Vec(M[i1].size(),array);

		delete[] array;
	}

	/*for (int i1 = 0; i1 < 3; ++i1)
	{
		output[i1] = M[i1] + input[i1];
	}*/

	return FCmatrixBanded(output);
}

FCmatrixBanded FCmatrixBanded::operator-(const FCmatrix& a) {

	if (M.size() != (a.GetM()).size())
	{
		cout << "ERROR: FCmatrixBanded::operator-(const FCmatrix& a)" << endl;
		exit(1);
	}

	if (M[0].size() != (a.GetM())[0].size())
	{
		cout << "ERROR: FCmatrixBanded::operator-(const FCmatrix& a)" << endl;
		exit(1);
	}

	vector<Vec> output(M.size());
	vector<Vec> input(a.GetM());

	for (int i = 0; i < M.size(); ++i)
	{
		output[i] = M[i] - input[i];
	}

	return FCmatrixBanded(output);
}
FCmatrixFull FCmatrixBanded::operator*(const FCmatrix& a) {

	if (dim != a.GetDim()[0])
	{
		cout << "ERROR [FCmatrixBanded::operator*]: Cannot multiply these matrices." << endl;
		exit(1);
	}

	// vector<Vec> solution(dim);

	// for (int i1 = 0; i1 < dim; ++i1)
	// {
	// 	for (int i2 = 0; i2 < dim; ++i2)
	// 	{
	// 		solution[i1][i2] = ((*this).GetRow(i1)).dot(a.GetCol(i2));
	// 	}
	// }

	double ** matriz = new double * [dim];
	for (int i = 0; i < dim; i++) {
		matriz[i] = new double [dim];
		for (int j = 0; j < dim; j++) {
			matriz[i][j] = 0;
		}
	}

	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			matriz[i][j] = ((*this).GetRow(i)).dot(a.GetCol(j));
		}
	}

	return FCmatrixFull(matriz, dim, dim);
}

FCmatrixBanded FCmatrixBanded::operator*(double lambda) {

	vector<Vec> output(M.size());

	for (int i = 0; i < (int)M.size(); ++i)
	{
		output[i] = M[i] * lambda;
	}

	return FCmatrixBanded(output);
}

Vec FCmatrixBanded::operator*(const Vec& a) {

	if (dim != a.size())
	{
		cout << "ERROR: FCmatrixBanded::operator*(const Vec& a)" << endl;
		exit(1);
	}

	Vec solution(dim);

	for (int i = 0; i < dim; ++i)
	{
		solution[i] = GetRow(i).dot(a);
	}

	return solution;
}

FCmatrixBanded operator*(double a, FCmatrixBanded& b) {
	return b*a;
}

