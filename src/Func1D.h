#ifndef _FUNC1D_
#define _FUNC1D_
#include "TF1.h"

class Func1D {
public:
	Func1D(TF1 *fp = NULL);
	~Func1D();

	// Set
	void SetFunction (TF1*);

	void Draw() const;
	double Evaluate(double x) const;
protected:
	TF1 *p;
};

#endif