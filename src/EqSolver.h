#ifndef __EQSOLVER__
#define __EQSOLVER__
#include <vector>
#include "Vec.h"
#include "FCmatrix.h"
#include "FCmatrixFull.h"
#include "FCmatrixBanded.h"

class EqSolver {

public:

	EqSolver();
	EqSolver(const FCmatrix&, const Vec&); // matriz M e vector de constantes
	~EqSolver();

	// set
	void SetConstants(const Vec&);
	void SetMatrix(const FCmatrix&);

	void Print();

	Vec GaussEliminationSolver();	
	Vec LUdecompositionSolver();
	FCmatrixFull GetU();

	Vec BandedSolver();
	FCmatrixBanded GetD();

	Vec JacobiIterator(double tol = 1.E-4);

	bool GetSwapped() const;

private:

	void LUdecomposition(FCmatrix& matrix_input, vector<int> index);
	void GaussElimination(FCmatrix&, Vec&);

	FCmatrix *M; //matriz de coeffs
	Vec b; //vector de constantes
	bool swapped;

};

#endif