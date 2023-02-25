#ifndef _VEC_
#define _VEC_
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Vec {
public:
	Vec(int number, double *values);
	Vec(int number, double value);
	Vec(int number = 0);
	Vec(const Vec&);
	int size() const ;
	double* GetEntries()  const ;
	void SetEntries(int ,double *);
	Vec& operator=(const Vec&);   
	Vec operator-(const Vec&) const;
	Vec& operator-=(const Vec&);
	Vec operator+(const Vec&) const; 
	Vec& operator+=(const Vec&);   
	Vec operator*(const Vec&) const;   
	Vec operator*(const double) const;
	friend Vec operator*(double, Vec&); 
	Vec operator-();               
	Vec operator+();               
	double operator[](int) const;
	double& operator[](int);        
	double dot(const Vec&) const;              
	void Print() const;                        
	void swap(int,int);  
	void bubbleSort(int,int,int); //(posicao inicial, posicao final, metodo [0->ascendente])
	void fabs_bubbleSort(int,int,int); //(posicao inicial, posicao final, metodo [0->ascendente])
	~Vec();
private:
	int N; //number of elements
	double *entries; //pointer to array of doubles
};

#endif