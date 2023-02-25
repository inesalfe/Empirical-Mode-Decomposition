#ifndef _FCmatrixBAND_
#define _FCmatrixBAND_
#include "FCmatrix.h"
#include "FCmatrixFull.h"

class FCmatrixBanded : public FCmatrix {    //vector<Vec> = lower_dig, mid_dig, up_dig

public:

//constructors
	FCmatrixBanded();
	FCmatrixBanded(double **, int); //matrix mxn
	FCmatrixBanded(double *, int);
	FCmatrixBanded(vector<Vec>);

//get
	int* GetDim() const;

//copy constructor
	FCmatrixBanded(const FCmatrixBanded&);

//inherited methods
	Vec& operator[] (int i);  //get diagonal i
	Vec GetRow(int i) const;
	Vec GetCol(int i) const;
	double Determinant() const;
	void Print() const;
	int GetRowMax(int j) const;
	int GetColMax(int j) const;
	void swapRows(int,int);

//operators
	FCmatrixBanded operator+(const FCmatrix&); // add 2 matrices of any kind
	FCmatrixBanded operator-(const FCmatrix&); // sub 2 matrices of any kind
	FCmatrixFull operator*(const FCmatrix&); // mul 2 matrices of any kind
	FCmatrixBanded operator*(double); // mul matrix of any kind by scalar
	Vec operator*(const Vec&); // mul matrix by Vec
	friend FCmatrixBanded operator*(double, FCmatrixBanded&);

private:
	
	int dim;
};

#endif