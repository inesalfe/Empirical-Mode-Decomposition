#ifndef _FCMATRIX_
#define _FCMATRIX_
#include <vector>
#include <string>
#include "Vec.h"

class FCmatrix {
public:
	FCmatrix();
	FCmatrix(double**, int, int);   //matrix mxn
	FCmatrix(double*, int, int);
	FCmatrix(vector<Vec>);
	FCmatrix(const FCmatrix&);
//operators
	virtual Vec& operator[] (int i) = 0;
//methods
	virtual Vec GetRow(int i) const = 0;
	virtual Vec GetCol(int i) const = 0;

	virtual double Determinant() const = 0;

	virtual void Print() const;

	virtual int* GetDim() const = 0;
	vector<Vec> GetM() const;
	string GetClassname() const;

	void SetM(vector<Vec>);
//row max element index
	virtual int GetRowMax(int j) const = 0;
//row max element index (sclaed by s,from j on)
	virtual int GetColMax(int j) const = 0;
	virtual void swapRows(int,int) =  0;
	~FCmatrix();
protected:
	vector<Vec> M;
	string classname;
};
#endif