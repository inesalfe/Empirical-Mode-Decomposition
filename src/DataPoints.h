#ifndef __DATAPOINTS__
#define __DATAPOINTS__

//#include "cFCgraphics.h"

class DataPoints {

public:

	DataPoints();
	DataPoints(int fN, double* fx, double* fy);
	virtual ~DataPoints();
	// para que serve esta função abaixo???
	virtual double Interpolate(double x) {return 0.;}
	virtual void Draw();
	//virtual void Print(string FILE = "");

	// funções criada por mim

	virtual void Print();

protected:

	int N; // number of data points
	double *x, *y; // arrays
	//cFCgraphics G;

};

#endif
