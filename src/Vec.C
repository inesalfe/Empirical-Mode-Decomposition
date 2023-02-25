#include "Vec.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <cmath>
using namespace std;

void Vec::Print() const {

	cout << "(";
	for (int i = 0; i < N; ++i)
	{
		cout << " " << entries[i] << " ";

		if (i != N-1)
			cout << ",";
	}
	cout << ")" << endl;
}

//trocar numero na posição a pela posição b
void Vec::swap(int a, int b) {

	if (a > N-1 || b > N-1)
	{
		cout << "ERROR: Não é possível trocar posições não existentes no vetor." << endl;
		return;
	}

	if (a < 0 || b < 0)
	{
		cout << "ERROR: Não é possível trocar posições negativas no vetor." << endl;
		return;
	}

	if (a == b)
		return;

	double temp = entries[a];

	entries[a] = entries[b];
	entries[b] = temp;

}

Vec Vec::operator-() {

	double *a = new double[N];

	for (int i = 0; i < N; ++i)
	{
		a[i] = -entries[i];	
	}

	return Vec(N,a);
}

Vec Vec::operator+() {

	double *a = new double[N];

	for (int i = 0; i < N; ++i)
	{
		a[i] = entries[i];	
	}

	return Vec(N,a);
}

Vec& Vec::operator=(const Vec& a) {

	N = a.size();
	(*this).SetEntries(N,a.GetEntries());

	return *this;
}

Vec Vec::operator+(const Vec& a) const {

	if (N != a.size())
	{
		cout << "ERROR: Não é possível somar vetores de comprimento diferente." << endl;
		
		return (*this);
	}

	double *sum = new double [N];

	for (int i = 0; i < N; i++)
	{
		sum[i] = entries[i] + (a.GetEntries())[i];
	}

	Vec ans(N,sum);

	delete[] sum;

	return ans;

}

Vec Vec::operator-(const Vec& a) const {

	if (N != a.size())
	{
		cout << "ERROR: Não é possível subtrair vetores de comprimento diferente." << endl;
		
		return (*this);
	}

	double *dif = new double [N];

	for (int i = 0; i < N; ++i)
	{
		dif[i] = ((*this).GetEntries())[i] - (a.GetEntries())[i];
	}

	Vec ans(N,dif);

	delete[] dif;

	return ans;

}

Vec& Vec::operator-=(const Vec& a) {

	if (N != a.size())
	{
		cout << "ERROR: Não é possível subtrair vetores de comprimento diferente." << endl;
		
		return (*this);
	}

	double *dif = new double [N];

	for (int i = 0; i < N; ++i)
	{
		dif[i] = ((*this).GetEntries())[i] - (a.GetEntries())[i];
	}

	(*this).SetEntries(N,dif);

	delete[] dif;

	return *this;

}

Vec& Vec::operator+=(const Vec& a) {

	if (N != a.size())
	{
		cout << "ERROR: Não é possível somar vetores de comprimento diferente." << endl;
		
		return (*this);
	}

	double *sum = new double [N];

	for (int i = 0; i < N; ++i)
	{
		sum[i] = ((*this).GetEntries())[i] + (a.GetEntries())[i];
	}

	(*this).SetEntries(N,sum);

	delete[] sum;

	return *this;

}

double Vec::operator[](int i) const {

	if ( i < 0 || i > N - 1)
	{
		cout << "ERROR: Não existe nenhuma posição " << i << " no vetor." << endl;
		return 0;
	}

	return ((*this).GetEntries())[i];
}

double& Vec::operator[](int i) {

	if ( i < 0 || i > N - 1)
	{
		cout << "ERROR: Não existe nenhuma posição " << i << " no vetor." << endl;
		exit(1);
	}

	return ((*this).GetEntries())[i];
}

Vec Vec::operator*(const Vec& a) const {

	if (N != a.size())
	{
		cout << "ERROR: Não é possível multiplicar vetores de comprimento diferente." << endl;
		
		return (*this);
	}

	double *mult = new double [N];

	for (int i = 0; i < N; ++i)
	{
		mult[i] = entries[i] * (a.GetEntries())[i];
	}

	Vec ans(N,mult);

	delete[] mult;

	return ans;
}

Vec Vec::operator*(const double a) const {

	double *mult = new double [N];

	for (int i = 0; i < N; ++i)
	{
		mult[i] = entries[i] * a;
	}

	Vec ans(N,mult);

	delete[] mult;

	return ans;
}

int Vec::size() const {

	return N;
}

double Vec::dot(const Vec& a) const {

	if (N != a.size())
	{
		cout << "ERROR: Não é possível obter o produto interno de vetores de comprimento diferente." << endl;
		
		return 0;
	}

	double dprod;

	for (int i = 0; i < N; ++i)
	{
		dprod = dprod + entries[i]*((a.GetEntries())[i]);
	}

	return dprod;
}

double* Vec::GetEntries() const {

	return entries;
}

void Vec::SetEntries(int number, double* a) {

	N = number;

	delete[] entries;

	entries = new double[number];

	for (int i = 0; i < number; ++i)
	{
		entries[i] = a[i];
	}
}

//select = 0 ->  ascendente // otherwise, -> descendente
void Vec::bubbleSort(int init, int end, int select) {

	if(init < 0 || init > end || end > N-1)
	{
		cout << "ERROR: Vec::bubbleSort;" << endl;
		return;
	}

   if (select == 0)
   {
	   for (int i = init; i < end + init; i++) {     
	       // Last i elements are already in place    
	       for (int j = init; j < end + init-i; j++) {
	           
	           if (entries[j] > entries[j+1]) {
	           	double temp;

	           	temp = entries[j];
	           	entries[j] = entries[j+1];
	           	entries[j+1] = temp;
	           }
	       }
	    }
	}
	else
	{
		for (int i = init; i < end + init; i++) {     
      // Last i elements are already in place    
	      for (int j = init; j < end + init-i; j++) {
	           
	           if (entries[j] < entries[j+1]) {
	           	double temp;

	           	temp = entries[j];
	           	entries[j] = entries[j+1];
	           	entries[j+1] = temp;
	           }
	       }
	    }
	}
}

//select = 0 ->  ascendente // otherwise, -> descendente
void Vec::fabs_bubbleSort(int init, int end, int select) {

	if(init < 0 || init > end || end > N-1)
	{
		cout << "ERROR: Vec::fabs_bubbleSort;" << endl;
		return;
	}

   if (select == 0)
   {
	   for (int i = init; i < end + init; i++) {     
	       // Last i elements are already in place    
	       for (int j = init; j < end + init - i; j++) {
	           
	           if (fabs(entries[j]) > fabs(entries[j+1])) {
	           	double temp;

	           	temp = entries[j];
	           	entries[j] = entries[j+1];
	           	entries[j+1] = temp;
	           }
	       }
	    }
	}
	else
	{
		for (int i = init; i < end + init; i++) {     
      // Last i elements are already in place    
	      for (int j = init; j < end + init - i; j++) {
	           
	           if (fabs(entries[j]) < fabs(entries[j+1])) {
	           	double temp;

	           	temp = entries[j];
	           	entries[j] = entries[j+1];
	           	entries[j+1] = temp;
	           }
	       }
	    }
	}
}

Vec::Vec(int number) {

	N = number;

	if (number == 0)
		entries = NULL;
	else
	{
		entries = new double[number];

		for (int i = 0; i < N; ++i)
		{
			entries[i] = 0;
		}
	}
}

Vec::Vec(int number, double value) {

	N = number;
	entries = new double[number];

	for (int i = 0; i < N; ++i)
	{
		entries[i] = value;
	}
}

Vec::Vec(int number, double *values) {

	N = number;
	entries = new double[number];

	for (int i = 0; i < N; ++i)
	{
		entries[i] = values[i];
	}
}

Vec::Vec(const Vec& a) {

	N = a.size();
	entries = new double[N];

	double *x = a.GetEntries();

	for (int i=0; i<N; ++i) {
	  entries[i] = x[i];
	}

	//delete x;
}

Vec::~Vec(){
  delete [] entries;
}

// -------------------------------------------------- friend functions

Vec operator* (double a, Vec& b) {

	return b*a;
}
