#include "Derivator.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <iostream>
using namespace std;

using namespace std;

/*double factorial(double n) {

	double solution = n;

	for (int i = 1; i < n; ++i)
	{
		solution *= (n - i);
	}

	return solution;
}

double combinations(double n, double r) { //C(n,r)

	if (r > n) 
	{
		cout << "ERROR [double combinations(double, double)] : In C(n,r), r mustn't be larger than n." << endl;
		exit(1);
	}

	return factorial(n)/(factorial(r)*factorial(n-r));
}*/

Derivator::Derivator(TF1 *fp, double xnew, double hnew) : Func1D(fp) {
	x0 = xnew;
	
	if (hnew <= 0) {
		cout << "ERROR [Derivator::Derivator (TF1*,double,double)]: The step provided must be larger than 0." << endl;
		exit(1);
	}

	h = hnew;
}

// Get
double Derivator::GetDerivative1() const {

	double a = Evaluate(x0-2*h);
	double b = Evaluate(x0-h);
	double c = Evaluate(x0+h);
	double d = Evaluate(x0+2*h);

	return ((a+8*c)-(8*b+d))/(12*h);
}

double Derivator::GetDerivative1F() const {

	double c = Evaluate(x0+h);
	double d = Evaluate(x0+2*h);
	double fx = Evaluate(x0);

	return (-d + 4*c -3*fx)/(2*h);
}

double Derivator::GetDerivative1B() const {

	double a = Evaluate(x0-2*h);
	double b = Evaluate(x0-h);
	double fx = Evaluate(x0);

	return (a - 4*b + 3 *fx)/(2*h);
}

double Derivator::GetDerivative2() const {

	double a = Evaluate(x0-2*h);
	double b = Evaluate(x0-h);
	double c = Evaluate(x0+h);
	double d = Evaluate(x0+2*h);
	double fx = Evaluate(x0);
	//return (c - 2*fx + b)/(h*h);   // three point formula
	
	return (-a + 16*b - 30*fx + 16*c - d)/(12*h*h);   ////five point formula
}

double Derivator::GetDerivative3() const {

	cout << "NOTE [double Derivator::GetDerivative3() const]: The step was changed to 1E-2, in order to provide an accurate value." << endl;
	double h = 1E-2;
	double a, b, c, d, e, f;
	a = Evaluate(x0-3*h);
	b = Evaluate(x0-2*h);
	c = Evaluate(x0-h);
	d = Evaluate(x0+h);
	e = Evaluate(x0+2*h);
	f = Evaluate(x0+3*h);
	return 1/(8*h*h*h)*(a-8*b+13*c-13*d+8*e-f);
}
/*

double Derivator::GetDerivative3() const {  // -1/2 // 1 // 0 // -1 // 1/2

	double a = Evaluate(x0-2*h);
	double b = Evaluate(x0-h);
	double c = Evaluate(x0+h);
	double d = Evaluate(x0+2*h);
	double e = Evaluate(x0-3*h);
	double f = Evaluate(x0+3*h);

	return 1/(8*h*h*h)*(e - 8*a + 13*b - 13*c + 8*d - f);
}*/

/*double Derivator::GetDerivativeN(int n) const {

	double solution = 0;
	int a = -1;

	for (int i = 0; i < n + 1; ++i)
	{
		if (i % 2 != 0)
			a = 1;
		else
			a = -1;

		solution += a*combinations(n,i)*Evaluate(x0 + i*h);
	}

	solution = solution/pow(h,n);

	return solution;
}*/

// Set
void Derivator::SetX(double xnew) {
	x0 = xnew;
}

void Derivator::SetStep(double hnew) {

	if (hnew <= 0) {
		cout << "ERROR [void Derivator::SetStep(double)]: The step provided must be larger than 0." << endl;
		exit(1);
	}

	h = hnew;
}