#include "EMD.h"

int main () {

	// ----------------- EXERCICIO 1 (senos) -----------------

	TF1 *senos = new TF1("senos","tan(2*pi*x)",0,4);
	double *x_senos = new double[400];
	double *y_senos = new double[400];
	vector <Point> Data_senos;

	for (int i = 0; i < 400; i++) {
		x_senos[i] = i*0.01;
		y_senos[i] = senos->Eval(x_senos[i]);
		Data_senos.push_back(Point(x_senos[i], y_senos[i]));
	}

	EMD sin(Data_senos);

	sin.FindIMFs();

	sin.PrintData();
	//sin.Draw("ABCDEFGHIJK");

	// ----------------- EXERCICIO 2 (sunspots) -----------------

	vector<Vec> Vec_x_y = FCtools::ReadFile_v("sunspots.dat");
	int number_points = Vec_x_y.size();

	double * x = new double [number_points];
	double * y = new double [number_points];

	vector<Point> Data;

	for (int i = 0; i < number_points; i++) {
		Data.push_back(Point(Vec_x_y[i][0], Vec_x_y[i][1]));
		x[i] = Vec_x_y[i][0];
		y[i] = Vec_x_y[i][1];
	}

	EMD sun(Data);

	sun.FindIMFs();
  sun.Draw("ABCDEFGHIJK");
	sun.PrintData();

	delete[] x;
	delete[] y;
	delete[] x_senos;
	delete[] y_senos;
	delete senos;

	return 0;

}
