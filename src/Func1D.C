#include "Func1D.h"
#include "cFCgraphics.h"
#include "TF1.h"
#include "TPad.h"

Func1D::Func1D (TF1 *fp) {
	p = new TF1();
	*p = *fp;
}

Func1D::~Func1D() {
	delete p;
}

void Func1D::SetFunction(TF1* newfunc) {
	*p = *newfunc;
}

void Func1D::Draw() const {
	cFCgraphics G;

	TPad *pad1 = G.CreatePad("pad1");
	pad1->SetTitle(p->GetExpFormula());
	G.AddObject(p,"pad1");
	G.DrawPad("pad1");
}

double Func1D::Evaluate(double x) const {
	return p->Eval(x);
}