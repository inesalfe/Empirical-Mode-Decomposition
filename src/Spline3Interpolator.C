#include "Spline3Interpolator.h"
#include "EqSolver.h"
#include "cFCgraphics.h"
#include "TGraph.h"
#include "TF1.h"
#include <cstdio>
#include <string>
using namespace std;

Spline3Interpolator::Spline3Interpolator(int fN, double *fx, double *fy, double xmin, double xmax) : DataPoints(fN,fx,fy) {

	//DataPoints::Print();
	F0 = NULL;

	K = new double[N];
	SetCurvatureLines(); //define segment interpolators

	FInterpolator_f = new TF1("FInterpolator", this, &Spline3Interpolator::FInterpolator, xmin ,xmax, 0);
	FInterpolator_f->SetNpx(10000);
	//FInterpolator_f = new TF1("FInterpolator", this, &Spline3Interpolator::FInterpolator, -5 ,10, 0);
}

Spline3Interpolator::~Spline3Interpolator() {
	delete[] K;
	delete FInterpolator_f;
	if (F0)
		delete F0;
}

Spline3Interpolator::Spline3Interpolator(const Spline3Interpolator& a) {
	*(FInterpolator_f) = *(a.FInterpolator_f);
	K = new double[N];

	for (int i = 0; i < N; i++) {
		K[i] = a.K[i];
	}

	if (a.F0)
		*(F0) = *(a.F0);
}

void Spline3Interpolator::SetCurvatureLines() {

	// define tri-diagonal matrix and array of constants
	//...
	// solve system and get the 2nd derivative coefficients
	// store coeffs on internal array K
	//...

	// cout << "TESTE 1" << endl;
	// cout << endl;
	// cout << endl;
	// cout << endl;

	int dim = N-2;

	// double ** matriz = new double * [dim];
	// for(int i = 0; i < dim; i++) {
	// 	matriz[i] = new double [dim];
	// 	for (int j = 0; j < dim; j++) {
	// 		matriz[i][j] = 0;
	// 	}
	// }

	// for (int i = 0; i < dim; i++) {
	// 	if (i == 0) {
	// 		matriz[i][0] = 2 * (x[0] - x[2]);
	// 		matriz[i][1] = (x[1] - x[2]);
	// 	}
	// 	if (i == dim - 1) {
	// 		matriz[i][i] = 2 * (x[i] - x[i+2]);
	// 		matriz[i][i-1] = (x[i] - x[i+1]);
	// 	}
	// 	else {
	// 		matriz[i][i-1] = x[i] - x[i+1];
	// 		matriz[i][i] = 2 * (x[i] - x[i+2]);
	// 		matriz[i][i+1] = x[i+1] - x[i+2];
	// 	}
	// }

	// cout << "TESTE 2" << endl;
	// cout << endl;
	// cout << endl;
	// cout << endl;

	//FCmatrixFull A(matriz, dim, dim);

	// cout << endl;
	// cout << endl;
	// cout << "Matriz para resolver o vetor K" << endl;
	// A.Print();
	// cout << endl;
	// cout << endl;

	double ** matriz = new double * [3];
	for(int i = 0; i < 3; i++) {
		if (i == 0 || i == 2) {
			matriz[i] = new double [dim-1];
			for (int j = 0; j < dim-1; j++)
				matriz[i][j] = 0;
		}
		if (i == 1) {
			matriz[i] = new double [dim];
			for (int j = 0; j < dim; j++)
				matriz[i][j] = 0;
		}
	}

	for (int i = 0; i < 3; i++) {
		if (i == 0 || i == 2) {
			for (int j = 0; j < dim-1; j++)
				matriz[i][j] = x[j+1] - x[j+2];
		}
		if (i == 1) {
			for (int j = 0; j < dim; j++)
				matriz[i][j] = 2 * (x[j] - x[j+2]);
		}
	}

	// cout << "TESTE 2" << endl;
	// cout << endl;
	// cout << endl;
	// cout << endl;

	FCmatrixBanded A(matriz, dim);

	// cout << endl;
	// cout << endl;
	// cout << "Matriz para resolver o vetor K" << endl;
	// A.Print();
	// cout << endl;
	// cout << endl;

	// for (int i = 0; i < 3; i++){
	// 	A[i].Print();
	// }

	double vec_cons[dim];

	for (int i = 1; i <= dim; i++) {
		vec_cons[i-1] = 6. * (((y[i-1] - y[i]) / (x[i-1] - x[i])) - ((y[i] - y[i+1]) / (x[i] - x[i+1])));
		// vec_cons[i] = 6 * (((y[i] - y[i+1]) / (x[i] - x[i+1])) - ((y[i+1] - y[i+2]) / (x[i+1] - x[i+2])));
	}

	// cout << endl;
	// cout << endl;
	// cout << "Array de constantes" << endl;
	// for (int i = 0; i < dim; i++) {
	// 	cout << vec_cons[i] << endl;
	// }

	Vec constantes(dim, vec_cons);
	EqSolver sistema(A, constantes);
	Vec K_n(dim);
	//cout << "Matriz após eliminação de gauss" << endl;
	K_n = sistema.BandedSolver();

	//K_n.Print();

	K[0] = 0;
	K[N-1] = 0;

	for(int i = 1; i <= dim; i++) {
		K[i] = K_n[i-1];
	}

	delete[] matriz;

	// cout << endl;
	// cout << endl;
	// cout << "Array de K's" << endl;
	// for (int i = 0; i < N; i++) {
	// 	cout << K[i] << endl;
	// }

}

double Spline3Interpolator::Interpolate(double fx) {

// detect in wich segment is x

	int i = 0;

	// for (i = 0; i < N; i++) {
	// 	if ((fx - x[i]) < 0.)
	// 		break;
	// } //upper bound returned

	// if (i == 0 || i == N - 1) // out of range
	// 	return 0.;

	//cout << "x = " << fx << " " << x[i] << " " << x[i+1] << endl;

//retrieve segment interpolator and return function value

	if(fx <= x[0] || fx >= x[N-1]) {
		return 0;
	}

	int lower_index = 0;
	for (int i = 0; i < N; i++) {
		if (fx > x[i] && fx < x[i+1]) {
			lower_index = i;
		}
		if (fx == x[i])
			return y[i];
	}

	i = lower_index;

	double f;

	f = K[i] / 6. * ( pow((fx - x[i+1]), 3) / (x[i] - x[i+1]) - (fx - x[i+1]) * (x[i] - x[i+1]) )
	  - K[i+1] / 6. * ( pow((fx - x[i]), 3) / (x[i] - x[i+1]) - (fx - x[i]) * (x[i] - x[i+1]) )
	  + (y[i] * (fx - x[i+1]) - y[i+1] * (fx - x[i])) / (x[i] - x[i+1]);

	return f;

}

void Spline3Interpolator::Draw() {

	cFCgraphics G;

	TGraph *g = new TGraph(N,x,y);
	g->SetMarkerStyle(20);
	g->SetMarkerColor(kMagenta);
	g->SetMarkerSize(1);
	TPad *pad1 = G.CreatePad("pad1");

	FInterpolator_f->SetLineColor(1);
	FInterpolator_f->SetLineWidth(4);
	FInterpolator_f->SetTitle("Spline 3");
	G.AddObject(FInterpolator_f,"pad1");

	if (F0) {
	 	F0->SetLineColor(kBlue);
		F0->SetLineWidth(4);
		F0->SetLineStyle(2);
		G.AddObject(F0,"pad1", "same");
	}
	G.AddObject(g,"pad1","P");

	G.AddObject(pad1);
	G.Draw();

    // TGraph* g1 = new TGraph(FInterpolator_f);
    // g1->SetLineWidth(4);
    // g1->SetLineColor(420);
    // TGraph* g2 = new TGraph(N, x, y);
    // g2->SetMarkerStyle(39);
    // g2->SetMarkerColor(kMagenta);

    // TPad* pad1 = G.CreatePad("Pad1");
    // G.AddObject(g1, "Pad1", "AC");
    // G.AddObject(g2, "Pad1", "P");
    // G.DrawPad("Pad1");
    // G.DumpPad("Pad1");
}

void Spline3Interpolator::Print(string FILE) {
	cFCgraphics G;
G.Print(FILE);
}

void Spline3Interpolator::SetFunction(TF1* f) {
	F0 = f;
}
