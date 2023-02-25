#ifndef _FCmatrixFULL_
#define _FCmatrixFULL_

#include "FCmatrix.h"
#include "Vec.h"
#include <vector>

class FCmatrixFull : public FCmatrix {
public:
//constructors
	FCmatrixFull();
	FCmatrixFull(double **, int, int); //matrix mxn
	FCmatrixFull(double *, int, int);
	FCmatrixFull(vector<Vec>);
//copy constructors
	FCmatrixFull(const FCmatrixFull&);
//operators
	Vec& operator[] (int) ;
	FCmatrixFull operator+(const FCmatrix&); // add 2 matrices of any kind
	FCmatrixFull operator-(const FCmatrix&); // sub 2 matrices of any kind
	FCmatrixFull operator*(const FCmatrix&); // mul 2 matrices of any kind
	FCmatrixFull operator*(double lambda); // mul matrix of any kind by scalar
	Vec operator*(const Vec&); // mul matrix by Vec
	friend FCmatrixFull operator*(double, FCmatrixFull&);
// virtual inherited
	Vec GetRow(int i) const; // retrieve row i
	Vec GetCol(int i) const; // retrieve column i
	int GetRowMax(int) const; //returns index of column with biggest absolute value
	int GetColMax(int) const; //returns index of row with biggest absolute value
	double Determinant() const;
	void Print() const;
	void swapRows(int,int);
	int* GetDim() const;
	FCmatrixFull GetInvert() const;
	~FCmatrixFull();
private:
	int *rowindices; // row indices (0,1,2,...)
};
#endif