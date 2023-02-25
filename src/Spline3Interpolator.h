#ifndef __SPLINE3INTERPOLATOR__
#define __SPLINE3INTERPOLATOR__

#include "DataPoints.h"
#include "TF1.h"
using namespace std;

class Spline3Interpolator : public DataPoints {

public:

	Spline3Interpolator(int N = 0, double * x = NULL, double * y = NULL, double xmin = 0, double xmax = 0);
	Spline3Interpolator(const Spline3Interpolator&);
	~Spline3Interpolator();
	double Interpolate(double x);
	void Draw();
	TF1* GetFInterpolator(){return (TF1*)FInterpolator_f->Clone();}
	void SetFunction (TF1*);
	void Print(string FILE = ""); // print results

private:

	void SetCurvatureLines();
	double FInterpolator(double *fx, double *par) {
		return Interpolate(fx[0]);
	}
	TF1* FInterpolator_f;
	double* K; //2nd derivatives
	TF1* F0;
};

#endif
