#ifndef _DERIVATOR_
#define _DERIVATOR_
#include "Func1D.h"
#include "TF1.h"

//double factorial(double);

//double combinations(double, double);

class Derivator : public Func1D {
public:
	Derivator(TF1 *fp = NULL, double xnew = 0, double hnew = 0.00001);
	~Derivator() {;}
// Get
	double GetDerivative1() const; // central difference
	double GetDerivative1F() const; // forward difference
	double GetDerivative1B() const; // backward difference
	double GetDerivative2() const;
	double GetDerivative3() const;
// Set
	void SetX(double);
	void SetStep(double);
private:
	double x0;
	double h; //step
};

#endif