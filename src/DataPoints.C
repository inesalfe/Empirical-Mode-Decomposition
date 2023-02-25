#include <iostream>
#include "DataPoints.h"
#include "TGraph.h"
#include "cFCgraphics.h"
using namespace std;

DataPoints::DataPoints() {
	N = 0;
	x = NULL;
	y = NULL;
}

DataPoints::DataPoints(int fN, double* fx, double* fy) : N(fN) {
	x = new double[N];
	y = new double[N];
	for (int i=0; i < N; i++) {
		x[i] = fx[i];
		y[i] = fy[i];
	}
}

DataPoints::~DataPoints() {
	delete [] x;
	delete [] y;
}

void DataPoints::Draw() {
	cFCgraphics G;

	TGraph *g = new TGraph(N,x,y);
	g->SetMarkerStyle(1);
	g->SetMarkerColor(kRed);
	g->SetMarkerSize(0.1);
	TPad *pad1 = G.CreatePad("pad1");
	G.AddObject(g,"pad1","AP");
	G.AddObject(pad1);
	G.Draw();
}

// função criada por mim

void DataPoints::Print() {
	for(int i = 0; i < N; i++) {
		cout << "(" << x[i] << ", " << y[i] << ")" << endl;
	}
}
