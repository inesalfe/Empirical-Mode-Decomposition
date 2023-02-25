#ifndef H_EMD_H
#define H_EMD_H

#include "Point.h"
#include "FCtools.h"
#include "Spline3Interpolator.h"
#include "cFCgraphics.h"
#include "TF1.h"
#include "TGraph.h"
#include "TH2F.h"
#include "TStyle.h"
#include "TColor.h"
#include <vector>
#include <string>
#include <iostream> // cout
#include <cstdlib> // exit
using namespace std;

// Auxiliary functions
// double round_double (double, double); //arredonda um número com a precisão dada
double FindZero(Point,Point); //faz uma reta entre dois pontos e determina o zero dessa reta
double* GetX(vector <Point>);
double* GetY(vector <Point>);
void Print(vector<Point>);
vector<Point> Sum(vector< vector<Point> >);
double FindMaximumY (vector < vector <Point> >);
double FindMinimumY (vector < vector <Point> >);
double FindMaximumY (vector <Point>);
double FindMinimumY (vector <Point>);
double GetMeanY(vector <Point>);
// double GetUpperLimitY(double, vector < vector < Point > >);

class EMD {
public:
//constructors and destructor
	EMD();
	EMD(int, double*, double*);
	EMD(vector <Point>);
	EMD(const EMD&);
	~EMD();

// 'Set' functions
	void SetSignal(vector <Point>);
	void SetSignal(int, double*, double*);

// 'Get' functions
	vector <Point> GetMax(vector <Point>) const; // returns maxima of a provided vector of Points
 	vector <Point> GetMin(vector <Point>) const; // returns minima of a provided vector of Points
  TF1 * GetEMax(vector <Point>) const; // returns envelope max of provided vector of Points
 	TF1 * GetEMin(vector <Point>) const; // returns envelope min of provided vector of Points
 	vector <Point> GetFrequency(vector <Point>) const; // returns approximate instantaneous frequency of a signal
 	vector <Point> GetAmplitude(vector <Point>) const; // returns amplitude of a signal without changing the envelopes

	TF1 * GetMean() const; // returns mean of envelopes currently stored
	vector < vector <Point> > GetIMFs() const; // returns IMFs found
	vector <Point> GetIMF(int) const; // returns a specific IMF between 0 and number of IMFS-1
	int GetNumberOfIMFs() const; // returns the number of IMFs found
	double GetCorr(int) const; // returns the correlation coefficient of a specific IMF between 0 and number of IMFS-1
	int GetN() const; // returns number of points of the original signal
	vector <Point> GetSignal() const; // returns the original signal

	vector <Point> GetResidue() const; // returns the residue stored
	// when used without stopping the normal cycle, it returns the final residue

//
	void FindIMFs();

// Other functions
	void PrintData() const; //prints relevant data
	void Draw(string); //draws different possible graphs
	void Clear(); //clears all vectors except the envelope vector

private:
	int N; //number of points
	vector <Point> s; //original (x,y) points of the signal
	vector <TF1*> envelope; //emax, emin, mean
	vector < vector <Point> > IMF;
	vector <Point> residue;
	vector <Point> detail;
	vector <double> Amp0; //initial amplitude (to compare with IMFs amplitude)
	bool IMFs_found;

// Auxiliary private functions
	bool IsIMF() const; //Rilling criteria
	bool ContinueCycle() const; //Criteria to stop finding IMFs
	void SiftingProcess();
	double Get_Mean_Function(double*, double*) const;
	vector <Point> GetDetail(vector <Point>) const;
	vector <double> GetVariation() const; //returns variation of current envelopes
	vector <double> GetAmplitude() const; //returns amplitude of current envelopes
	void SetEMax(vector <Point>); //sets envelope[0]
	void SetEMin(vector <Point>); //sets envelope[1]
	void SetMean(vector <Point>); //sets envelope[2] - first, it sets envelope [0] and [1]
};
#endif
