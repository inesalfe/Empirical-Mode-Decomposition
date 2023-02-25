#include <math.h>
#include "Vec.h"
#include "FCmatrix.h"
#include "EqSolver.h"
#include "FCmatrixFull.h"
#include "FCmatrixBanded.h"

EqSolver::EqSolver() {
	FCmatrixFull * matrix = new FCmatrixFull;
	M = matrix;
	Vec line(0);
	b = line;
}

EqSolver::EqSolver(const FCmatrix & matrix_input, const Vec & vec_input) {
	if(matrix_input.GetDim()[1] != vec_input.size()) {
		cout << "This system makes no sense.";
		cout << "Number of columns of the matrix coeficient and size of constant's vector has to be the same" << endl;
		exit(0);
	}
	vector<Vec> matrix = matrix_input.GetM();
	if (matrix_input.GetClassname() == "FCmatrixFull") {
		FCmatrixFull * matrix_output1 = new FCmatrixFull;
		(*matrix_output1).SetM(matrix);
		M = matrix_output1;
	} else if (matrix_input.GetClassname() == "FCmatrixBanded") {
		FCmatrixBanded * matrix_output1 = new FCmatrixBanded;
		(*matrix_output1).SetM(matrix);
		M = matrix_output1;
	}

	b = vec_input;
}

EqSolver::~EqSolver() {
	//cout << "Called EqSolver Destructor" << endl;
	//delete[] M;
	// como é q eu chamo o destrutor do vec???
}

void EqSolver::SetConstants(const Vec & vec_input) {
	// explodir o programa dentro deste if
	if((*M).GetDim()[1] != vec_input.size()) {
		cout << "This system makes no sense.";
		cout << "Number of columns of the matrix coeficient and size of constant's vector has to be the same" << endl;
		exit(0);
	}
	b = vec_input;
}

void EqSolver::SetMatrix(const FCmatrix & matrix_input) {
	
	if((*M).GetDim()[1] != b.size()) {
		cout << "This system makes no sense.";
		cout << "Number of columns of the matrix coeficient and size of constant's vector has to be the same" << endl;
		exit(0);
	}
	vector<Vec> matrix = matrix_input.GetM();

	if (matrix_input.GetClassname() == "FCmatrixFull") {
		FCmatrixFull * matrix_output1 = new FCmatrixFull;
		(*matrix_output1).SetM(matrix);
		M = matrix_output1;
	} else if (matrix_input.GetClassname() == "FCmatrixBanded") {
		FCmatrixBanded * matrix_output1 = new FCmatrixBanded;
		(*matrix_output1).SetM(matrix);
		M = matrix_output1;
	}
}

void EqSolver::Print() {
	cout << "PRINT EQ SOLVER MATRIX AND CONSTANT'S VECTOR" << endl;
	cout << "Matriz de coeficientes:" << endl;
	(*M).Print();
	cout << "Vetor de constantes:" << endl;
	b.Print();
	cout << endl;
}

/* return triangular matrix and changed vector of constants */
void EqSolver::GaussElimination(FCmatrix & matrix_input, Vec & vec_input) {

	vector<Vec> matrix = matrix_input.GetM();
	int number_columns = (int)matrix[0].size();
	int number_rows = (int)matrix.size();
	FCmatrixFull matrix_full(matrix);
	double lambda;

	Vec col;
	int pivot = 0;

	for (int n = 0; n < number_columns - 1; n++) {

		// find pivot.

		// cout << "before swap" << endl;
		// matrix_full.Print();
		//cout << pivot << endl;

		col = matrix_full.GetCol(n);
		pivot = n;
		for (int j = n; j < number_columns; j++) {
			if(fabs(col[j]) > fabs(col[pivot]))
				pivot = j;
		}

		if(pivot != n) {
			matrix_full.swapRows(n, pivot);
			vec_input.swap(n, pivot);
			if(swapped == true)
				swapped = false;
			else
				swapped = true;
			// cout << "after swap" << endl;
			// matrix_full.Print();
		}
		
		matrix = matrix_full.GetM();

		for (int m = n; m < number_rows - 1; m++) {
			lambda = matrix[m+1][n] / matrix[n][n];
			matrix[m+1] = matrix[m+1] - lambda * matrix[n];
			vec_input[m+1] = vec_input[m+1] - lambda * vec_input[n];
		}

		matrix_full.SetM(matrix);
	}
	matrix_input.SetM(matrix);
	//SetConstants(vec_input);
}

Vec EqSolver::GaussEliminationSolver() {

	GaussElimination((*M), b);

	Vec x(b.size());

	vector<Vec> matrix = (*M).GetM();
	int number_columns = (int)matrix[0].size();
	int number_rows = (int)matrix.size();

	if (number_rows != number_columns || number_columns != b.size()) {
		cout << "O sistema não é determinado" << endl;
		return x;
	}

	else {

		(*M).Print();

		double sum = 0;
		for (int i = number_rows - 1; i > -1; i--) {
			sum = 0;
			for (int j = i + 1 ; j < number_columns; j++) {
				sum = sum + matrix[i][j] * x[j];
				//cout << sum << endl;
			}
			x[i] = (b[i] - sum) / matrix[i][i]; 
		}

		return x;
	}
}

void EqSolver::LUdecomposition(FCmatrix& matrix_input, vector<int> index) {

	vector<Vec> matrix = matrix_input.GetM();
	int number_columns = (int)matrix[0].size();
	int number_rows = (int)matrix.size();

	double ** matrix_L = new double * [number_rows];
	for (int i = 0; i < number_rows; i++) {
		matrix_L[i] = new double [number_columns];
		for (int j = 0; j < number_columns; j++) {
				matrix_L[i][j] = 0;
		}
	}

	FCmatrixFull matrix_L_full(matrix_L, number_rows, number_columns);
	vector<Vec> matrix_L_vec = matrix_L_full.GetM();

	Vec index_2(b.size());
	for (int i = 0; i < b.size(); i++) {
		index_2[i] = index[i];
	}
	Vec col;
	int pivot = 0;

	for (int n = 0; n < number_columns - 1; n++) {

		col = matrix_input.GetCol(n);
		pivot = n;
		for (int j = n; j < number_columns; j++) {
			if(fabs(col[j]) > fabs(col[pivot]))
				pivot = j;
		}

		if(pivot != n) {
			matrix_input.swapRows(n, pivot);
			matrix_L_full.swapRows(n, pivot);
			index_2.swap(n, pivot);
		}
		
		matrix = matrix_input.GetM();
		matrix_L_vec = matrix_L_full.GetM();

		for (int m = n; m < number_rows - 1; m++) {
			matrix_L_vec[m+1][n] = matrix[m+1][n] / matrix[n][n];
			matrix[m+1] = matrix[m+1] - matrix_L_vec[m+1][n] * matrix[n];
		}

		matrix_input.SetM(matrix);
		matrix_L_full.SetM(matrix_L_vec);

		//index_2.Print();
	}

	// ordenar o b de acordo com o vector de inteiros index

	Vec temp = b;
	//temp.Print();

	for (int i = 0; i < b.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			if (i == index_2[j])
				b[i] = temp[j];
		}
	}

	//cout << "b ordenado" << endl;
	//b.Print();

	cout << "Matriz input transformada em U" << endl;
	matrix_input.Print();
	cout << "Matriz L" << endl;
	matrix_L_full.Print();

	double ** matrix_output = new double * [number_rows];
	for (int i = 0; i < number_rows; i++) {
		matrix_output[i] = new double [number_columns];
		for (int j = 0; j < number_columns; j++) {
			if (j >= i) {
				matrix_output[i][j] = matrix_input.GetM()[i][j];
			}
			else {
				matrix_output[i][j] = matrix_L_full.GetM()[i][j];
			}
		}
	}

	FCmatrixFull matrix_final(matrix_output, number_rows, number_columns);
	vector<Vec> matrix_output_vec = matrix_final.GetM();

	matrix_input.SetM(matrix_output_vec);

	cout << "Matriz conjunta" << endl;
	matrix_input.Print();

}

Vec EqSolver::LUdecompositionSolver() {

	vector<Vec> matrix = (*M).GetM();
	int number_columns = (int)matrix[0].size();
	int number_rows = (int)matrix.size();


	int size_vec = b.size();
	Vec x(size_vec);

	if (number_rows != number_columns || number_columns != b.size()) {
		cout << "O sistema não é determinado" << endl;
		return x;
	}

	vector<int> index;
	for (int i = 0; i < size_vec; i++) {
		index.push_back(i);
		//cout << i << endl;
	}

	LUdecomposition(*M, index);

	double ** matrix_L = new double * [number_rows];
	for (int i = 0; i < number_rows; i++) {
		matrix_L[i] = new double [number_columns];
		for (int j = 0; j < number_columns; j++) {
			if (j == i) {
				matrix_L[i][j] = 1;
			}
			if (j < i) {
				matrix_L[i][j] = (*M).GetM()[i][j];
			}			
			if (j > i) {
				matrix_L[i][j] = 0;
			}	
		}
	}

	// Resolver Ly = b

	cout << "lower triangular matriz" << endl;
	FCmatrixFull temp_L(matrix_L, number_rows, number_columns);
	temp_L.Print();

	double sum = 0;
	Vec y(b.size());
	for (int k = 0; k < number_rows; k++) {
		sum = 0;
		for (int i = 0; i < k; i++) {
			sum += y[i] * matrix_L[k][i];
		}
		y[k] = b[k] - sum;
	}

	// Agora o y passa a ser o b

	cout << endl;
	cout << endl;
	b = y;
	//b.Print();

	// Resolver Ux = y

	double ** matrix_U = new double * [number_rows];
	for (int i = 0; i < number_rows; i++) {
		matrix_U[i] = new double [number_columns];
		for (int j = 0; j < number_columns; j++) {
			if (j > i || j == i) {
				matrix_U[i][j] = (*M).GetM()[i][j];
			}	
			else {
				matrix_U[i][j] = 0;
			}
		}
	}

	FCmatrixFull temp_U(matrix_U, number_rows, number_columns);
	//temp_U.Print();

	double sum2 = 0;
	for (int i = number_rows - 1; i > -1; i--) {
		sum2 = 0;
		for (int j = i + 1 ; j < number_columns; j++) {
			sum2 = sum2 + matrix_U[i][j] * x[j];
			//cout << sum2 << endl;
		}
		x[i] = (b[i] - sum2) / matrix_U[i][i]; 
	}

	return x;
}

FCmatrixFull EqSolver::GetU() {
	GaussElimination(*M, b);
	vector<Vec> m = (*M).GetM();
	return FCmatrixFull(m);
}

FCmatrixBanded EqSolver::GetD() {

	int dim = (*M).GetM()[1].size();

	Vec x(dim);

	Vec a_vec = (*M).GetM()[0];

	Vec b_vec = (*M).GetM()[1];

	Vec c_vec = (*M).GetM()[2];

	Vec d = b;

	double l;

	for (int i = 1; i < dim; i++) {
		l = a_vec[i-1] / b_vec[i-1];
		b_vec[i] -= l * c_vec[i-1];
		d[i] -= l * d[i-1];
	}

	vector<Vec> matrix;
	matrix.push_back(Vec(dim-1, (double)0));
	matrix.push_back(b_vec);
	matrix.push_back(c_vec);

	return FCmatrixBanded(matrix);
}

bool EqSolver::GetSwapped() const {
	return swapped;
}

Vec EqSolver::BandedSolver() {

	//esta linha aqui debaixo nao funciona
	int dim = (M->GetDim())[0];
	dim = (*M).GetM()[1].size();

	Vec x(dim);
	Vec a_vec = (*M).GetM()[0];
	Vec b_vec = (*M).GetM()[1];
	Vec c_vec = (*M).GetM()[2];
	Vec d = b;

	double l;

	for (int i = 1; i < dim; i++) {
		l = a_vec[i-1] / b_vec[i-1];
		b_vec[i] -= l * c_vec[i-1];
		d[i] -= l * d[i-1];
	}

	for (int i = 0; i < dim; i++) {
		if (b_vec[i] == 0) {
			cout << "DET = 0 :: NO SOLUTION" << endl;
			exit(0);
		}
	}

	double sum = 0;

	x[dim-1] = d[dim-1] / b_vec[dim-1];

	for (int i = dim - 2; i > -1; i--) {
		sum = c_vec[i] * x[i+1];
		x[i] = (d[i] - sum) / b_vec[i];
	}

	return x;
}

Vec EqSolver::JacobiIterator(double tol) {

	// linear system of m unknowns

	vector<Vec> A = (*M).GetM();

	int m = (*M).GetDim()[0];

	Vec x(m);
	Vec x_aux(m); //zero’s

	bool btol = false;
	int it = 0;
	double eps = 1.E-4;

	while (!btol && (it++ < 1000)) {
		x_aux = x;
		for (int i = 0; i < m; i++) {
			x[i] = 0;
			for (int j = 0; j < m; j++)
			if (i != j)
				x[i] += - A[i][j] * x_aux[j];
			x[i] += b[i];
			x[i] /= A[i][i];

			//guarantee that all vector entries are converging equally
			
			if (fabs(x[i]-x_aux[i]) < eps)
				btol = true;
			else
				btol = false;
		}
	}

	return x;
}



