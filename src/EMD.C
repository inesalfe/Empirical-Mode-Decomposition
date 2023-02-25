#include "EMD.h"
using namespace std;

// double round_double (double x, double precision) {
//
// 	double temp = pow(10,precision);
//
// 	return round(x*temp)/temp;
// }

double FindZero(Point a, Point b) {  //b.X() > a.X()

	return ((b.Y()-a.Y())*a.X()-a.Y()*(b.X()-a.X()))/(b.Y()-a.Y());
}

double* GetX(vector <Point> a) {
	double* xs = new double[a.size()];

	for (int i = 0; i < a.size(); i++) {
		xs[i] = a[i].X();
	}
	return xs;
}

double* GetY(vector <Point> a) {
	double* ys = new double[a.size()];

	for (int i = 0; i < a.size(); i++) {
		ys[i] = a[i].Y();
	}
	return ys;
}

void Print(vector<Point> vec) {
	for (int i = 0; i < vec.size(); i++) {
		vec[i].Print();
	}
}

vector<Point> Sum(vector< vector<Point> > vec_in) {

	vector<Point> sum_out;

	vector<int> sizes;

	for (int i = 0; i < vec_in.size(); i++)
	sizes.push_back(vec_in[i].size());

	int standart_size = sizes[0];

	for (int i = 0; i < vec_in.size(); i++) {
		if (vec_in[i].size() != standart_size) {
			cout << "ERROR [vector<Point> Sum(vector<vector<Point>>): Trying to obtain the sum of vectors with different sizes." << endl;
			exit(0);
		}
	}

	double sum = 0;

	for (int j = 0; j < standart_size; j++) {
		sum = 0;
		for (int i = 0; i < vec_in.size(); i++) {
			sum = sum + vec_in[i][j].Y();
		}
		sum_out.push_back(Point(vec_in[0][j].X(), sum));
	}

	return sum_out;
}

double FindMaximumY (vector < vector <Point> > a) {

	double result = (double)a[0][0].Y();

	for (int i1 = 0; i1 < a.size(); i1++) {
		for (int i2 = 0; i2 < a[i1].size(); i2++) {
			if ((double)result < (double)a[i1][i2].Y())
			result = (double)a[i1][i2].Y();
		}
	}

	return result;
}

double FindMinimumY (vector < vector <Point> > a) {

	double result = (double)a[0][0].Y();

	for (int i1 = 0; i1 < a.size(); i1++) {
		for (int i2 = 0; i2 < a[i1].size(); i2++) {
			if ((double)result > (double)a[i1][i2].Y())
			result = (double)a[i1][i2].Y();
		}
	}

	return result;
}

double FindMaximumY (vector <Point> a) {

	double result = (double)a[0].Y();

	for (int i2 = 0; i2 < a.size(); i2++) {
		if ((double)result < (double)a[i2].Y())
		result = (double)a[i2].Y();
	}

	return result;
}

double FindMinimumY (vector <Point> a) {

	double result = (double)a[0].Y();

	for (int i2 = 0; i2 < a.size(); i2++) {
		if ((double)result > (double)a[i2].Y())
		result = (double)a[i2].Y();
	}

	return result;
}

double GetMeanY(vector <Point> a) {
	double result = 0;

	for (int i = 0; i < a.size(); i++) {
		result += a[i].Y();
	}

	return result/a.size();
}

// double GetUpperLimitY(double tolerance, vector < vector < Point > > a) {
//
// 	int N = 0; //numero total de pontos
//
// 	for (int i1 = 0; i1 < a.size(); i1++) {
// 		for (int i2 = 0; i2 < a[i1].size(); i2++)
// 		N++;
// 	}
//
// 	int k = -1;
// 	int c = -1;
// 	int b = -1;
//
// 	for (int i1 = 0; i1 < a.size(); i1++) {
// 		b = 0;
// 		c++;
// 		for (int i2 = 0; i2 < a[i1].size(); i2++) {
// 			k++;
// 			b++;
// 			if (double(k/double(N)) > tolerance)
// 			break;
// 		}
// 	}
//
// 	vector <Point> temp(a.size());
//
// 	for (int i = 0; i < a.size(); i++) {
// 		temp[i] = a[i][b];
// 	}
//
// 	double solution = temp[0].Y();
//
// 	for (int i2 = 0; i2 < temp.size(); i2++) {
// 		if ((double)solution < (double)temp[i2].Y())
// 		solution = (double)temp[i2].Y();
// 	}
//
// 	return solution;
// }

// vector < int > EMD::FindThreshold() const {
//
// 	vector <double> corr(GetNumberOfIMFs());
//
// 	for (int i = 0; i < GetNumberOfIMFs(); i++) {
// 		corr[i] = GetCorr(i);
// 	}
//
// 	double average_corr = 0;
//
// 	for (int i = 0; i < GetNumberOfIMFs(); i++) {
// 		average_corr += corr[i];
// 	}
//
// 	average_corr = average_corr/GetNumberOfIMFs();
// 	vector < int > draw;
//
// 	for (int i = 0; i < GetNumberOfIMFs(); i++) {
// 		if (corr[i] > average_corr)
// 			draw.push_back(i);
// 	}
//
// 	return draw;
// }

EMD::EMD() {
	// cout << endl;
	// cout << "[EMD] Welcome. Before decomposing your signal, please provide one with 'SetSignal()'." << endl << endl;
	// cout << "To decompose your signal into IMFs, please do:" << endl;
	// cout << "> FindIMFs();" << endl;
	// cout << "To get the IMFs, do: > GetIMFs()" << endl;

	for (int i = 0; i < 3; i++) {
		envelope.push_back(new TF1());
	}

	IMFs_found = false;
}

EMD::EMD(vector <Point> input) {
	// cout << endl;
	// cout << "[EMD] Welcome. To decompose your signal into IMFs, please do:" << endl;
	// cout << "> FindIMFs();" << endl;
	// cout << "To get the IMFs, do: > GetIMFs()" << endl;
	s = input;
	N = s.size();
	residue = s;

	for (int i = 0; i < 3; i++) {
		envelope.push_back(new TF1());
	}
	IMFs_found = false;
}

EMD::EMD(int Nnew, double* x, double* y) {
	N = Nnew;

	for (int i = 0; i < N; ++i)
	{
		s.push_back(Point(x[i],y[i]));
	}

	residue = s;

	for (int i = 0; i < 3; i++) {
		envelope.push_back(new TF1());
	}
	IMFs_found = false;
}

EMD::EMD(const EMD& a) {

	N = a.N;
	s = a.s;
	for (int i = 0; i < 3; i++) {
		envelope.push_back(a.envelope[i]);
	}
	residue = a.residue;
	IMF = a.IMF;
	detail = a.detail;
	IMFs_found = a.IMFs_found;
}

EMD::~EMD() {

	// vectors clean themselves up when they go out of scope

	for (int i = 0; i < envelope.size(); ++i)
	{
		delete envelope[i];
	}
}

void EMD::Clear() {   // doesn't clear envelopes
	s.clear();
	for (int i = 0; i < IMF.size(); i++) {
		IMF[i].clear();
	}
	IMF.clear();
	residue.clear();
	detail.clear();
	Amp0.clear();
	N = 0;
	IMFs_found = false;
}

void EMD::SetSignal(vector <Point> input) {
	s.clear();
	s = input;
	N = s.size();
	residue = s;
	IMFs_found = false;
}

void EMD::SetSignal(int Nnew, double* x, double* y) {
	N = Nnew;
	s.clear();

	for (int i = 0; i < N; ++i)
	{
		s.push_back(Point(x[i],y[i]));
	}

	residue = s;
	IMFs_found = false;
}

vector < vector <Point> > EMD::GetIMFs() const {
	if (IMFs_found == false)
		cout << "WARNING [vector<vector<Point>> EMD::GetIMFs() const]: 'FindIMFs()' hasn't been used yet." << endl;
	return IMF;
}

int EMD::GetN() const {
	return N;
}

vector <Point> EMD::GetIMF(int i) const {
	if (i < 0 || i > GetNumberOfIMFs() - 1) {
		cout << "ERROR [vector <Point> EMD::GetIMF(int) const]: There is no IMF number " << i << "." << endl;
		exit(1);
	}
	if (IMFs_found == false)
		cout << "WARNING [vector <Point> EMD::GetIMF(int) const]: 'FindIMFs()' hasn't been used yet." << endl;
	return IMF[i];
}

int EMD::GetNumberOfIMFs() const {
	if (IMFs_found == false)
		cout << "WARNING [int EMD::GetNumberOfIMFs() const]: 'FindIMFs()' hasn't been used yet." << endl;
	return IMF.size();
}

double EMD::GetCorr(int i) const {
	if (i < 0 || i > GetNumberOfIMFs() - 1) {
		cout << "ERROR [double EMD::GetCorr(int) const]: There is no IMF number " << i << "." << endl;
		exit(1);
	}
	if (IMFs_found == false)
		cout << "WARNING [double EMD::GetCorr(int) const]: 'FindIMFs()' hasn't been used yet." << endl;

	vector <Point> IMF = GetIMF(i);

	double sum1 = 0;
	double sum2 = 0;
	double sum3 = 0;

	for (int i1 = 0; i1 < N; i1++) {
		sum1 += s[i1].Y()*IMF[i1].Y();
		sum2 += s[i1].Y()*s[i1].Y();
		sum3 += IMF[i1].Y()*IMF[i1].Y();
	}

	return sum1/(sqrt(sum2*sum3));
}

vector<Point> EMD::GetMax(vector<Point> s_in) const{

	vector<Point> max;

	int count = 0;
	double iqual_y = s_in[0].Y();
	for(int i = 0; i < s_in.size(); i++) {
		if (s_in[i].Y() == iqual_y)
		count ++;
	}

	if (count == s_in.size())
	return max;

	double prev;
	double pos;
	int i = 0;
	int j = 1;
	while(j < s_in.size()+1) {
		if (j == s_in.size())
		pos = s_in[s_in.size()-2].Y();
		else
		pos = s_in[j].Y();

		if (s_in[i].Y() > pos) {
			if (i == 0)
			//prev = -DBL_MAX;
			prev = s_in[1].Y();
			else
			prev = s_in[i-1].Y();

			if (s_in[i].Y() > prev) {
				for (int k = i; k < j; k++)
				max.push_back(s_in[k]);
			}
			i = j;
			j = i+1;
		}
		else if (s_in[i].Y() == pos)
		j++;
		else {
			i = j;
			j = i+1;
		}
	}

	if (s_in[i].Y() > s_in[i-1].Y())
	for (int k = i; k < s_in.size(); k++)
	max.push_back(s_in[k]);

	return max;
}

vector<Point> EMD::GetMin(vector<Point> s_in) const{

	vector<Point> min;

	int count = 0;
	double iqual_y = s_in[0].Y();
	for(int i = 0; i < s_in.size(); i++) {
		if (s_in[i].Y() == iqual_y)
		count ++;
	}

	if (count == s_in.size())
	return min;

	double prev;
	double pos;
	int i = 0;
	int j = 1;
	while(j < s_in.size()+1) {
		if (j == s_in.size())
		pos = s_in[s_in.size()-2].Y();
		else
		pos = s_in[j].Y();

		if (s_in[i].Y() < pos) {
			if (i == 0)
			//prev = -DBL_MAX;
			prev = s_in[1].Y();
			else
			prev = s_in[i-1].Y();

			if (s_in[i].Y() < prev) {
				for (int k = i; k < j; k++)
				min.push_back(s_in[k]);
			}
			i = j;
			j = i+1;
		}
		else if (s_in[i].Y() == pos)
		j++;
		else {
			i = j;
			j = i+1;
		}
	}

	if (s_in[i].Y() < s_in[i-1].Y())
	for (int k = i; k < s_in.size(); k++)
	min.push_back(s_in[k]);

	return min;
}

void EMD::SetEMax(vector <Point> s_in) {

	vector<Point> max_spline;
	vector<Point> max = GetMax(s_in);

	if (max[0] == s_in[0]) {
		if(max[0].Y() >= max[1].Y()) {
			for (int i = 0; i < max.size()-1; i++)
			max_spline.push_back(max[i]);
		}
		else {
			for (int i = 1; i < max.size()-1; i++)
			max_spline.push_back(max[i]);
		}
	}
	else {
		for (int i = 0; i < max.size()-1; i++)
		max_spline.push_back(max[i]);
	}
	if (max[max.size()-1] == s_in[N-1]) {
		if(max[max.size()-1].Y() >= max[max.size()-2].Y()) {
			max_spline.push_back(max[max.size()-1]);
		}
	}
	else {
		max_spline.push_back(max[max.size()-1]);
	}

	double * x = new double [max_spline.size()+2];
	double * y = new double [max_spline.size()+2];

	for (int i = 1; i < max_spline.size()+1; i++) {
		x[i] = max_spline[i-1].X();
		y[i] = max_spline[i-1].Y();
	}

	if (max[0] == s_in[0] && max[0].Y() >= max[1].Y()) {
		y[0] = y[2];
		x[0] = 2*x[1]-x[2];
	}
	else {
		y[0] = y[1];
		x[0] = 2*s[0].X()-x[1];
	}
	if (max[max.size()-1] == s_in[N-1] && max[max.size()-1].Y() >= max[max.size()-2].Y()) {
		y[max_spline.size()+1] = y[max_spline.size()-1];
		x[max_spline.size()+1] = 2*x[max_spline.size()]-x[max_spline.size()-1];
	}
	else {
		y[max_spline.size()+1] = y[max_spline.size()];
		x[max_spline.size()+1] = 2*s[N-1].X()-x[max_spline.size()];
	}

	Spline3Interpolator INTER3(max_spline.size()+2, x, y, s[0].X(), s[N-1].X());

	delete[] x;
	delete[] y;

	TF1 * func_out = new TF1(*(INTER3.GetFInterpolator()));
	func_out->SetNpx(10000);

	*(envelope[0]) = *func_out;
}

void EMD::SetEMin(vector <Point> s_in) {

	vector<Point> min_spline;
	vector<Point> min = GetMin(s_in);

	if (min[0] == s_in[0]) {
		if(min[0].Y() <= min[1].Y()) {
			for (int i = 0; i < min.size()-1; i++)
			min_spline.push_back(min[i]);
		}
		else {
			for (int i = 1; i < min.size()-1; i++)
			min_spline.push_back(min[i]);
		}
	}
	else {
		for (int i = 0; i < min.size()-1; i++)
		min_spline.push_back(min[i]);
	}
	if (min[min.size()-1] == s_in[N-1]) {
		if(min[min.size()-1].Y() <= min[min.size()-2].Y()) {
			min_spline.push_back(min[min.size()-1]);
		}
	}
	else {
		min_spline.push_back(min[min.size()-1]);
	}

	double * x = new double [min_spline.size()+2];
	double * y = new double [min_spline.size()+2];

	for (int i = 1; i < min_spline.size()+1; i++) {
		x[i] = min_spline[i-1].X();
		y[i] = min_spline[i-1].Y();
	}

	if (min[0] == s_in[0] && min[0].Y() <= min[1].Y()) {
		y[0] = y[2];
		x[0] = 2*x[1]-x[2];
	}
	else {
		y[0] = y[1];
		x[0] = 2*s[0].X()-x[1];
	}
	if (min[min.size()-1] == s_in[N-1] && min[min.size()-1].Y() <= min[min.size()-2].Y()) {
		y[min_spline.size()+1] = y[min_spline.size()-1];
		x[min_spline.size()+1] = 2*x[min_spline.size()]-x[min_spline.size()-1];
	}
	else {
		y[min_spline.size()+1] = y[min_spline.size()];
		x[min_spline.size()+1] = 2*s[N-1].X()-x[min_spline.size()];
	}

	Spline3Interpolator INTER3(min_spline.size()+2, x, y, s[0].X(), s[N-1].X());

	delete[] x;
	delete[] y;

	TF1 * func_out = new TF1(*(INTER3.GetFInterpolator()));
	func_out->SetNpx(10000);

	*(envelope[1]) = *func_out;
}

double EMD::Get_Mean_Function(double * x, double * par) const {
	return (envelope[0]->EvalPar(x,par) + envelope[1]->EvalPar(x,par))/2;
}

void EMD::SetMean(vector <Point> s_in) {
	SetEMax(s_in);
	SetEMin(s_in);

	TF1 * mean = new TF1("Mean", this, &EMD::Get_Mean_Function,s[0].X(),s[N-1].X(),0);
	mean->SetNpx(10000);

	*(envelope[2]) = *mean;
}

// ------------------------------------------

TF1* EMD::GetEMax(vector <Point> s_in) const {

	vector<Point> max_spline;
	vector<Point> max = GetMax(s_in);

	if (max[0] == s_in[0]) {
		if(max[0].Y() >= max[1].Y()) {
			for (int i = 0; i < max.size()-1; i++)
			max_spline.push_back(max[i]);
		}
		else {
			for (int i = 1; i < max.size()-1; i++)
			max_spline.push_back(max[i]);
		}
	}
	else {
		for (int i = 0; i < max.size()-1; i++)
		max_spline.push_back(max[i]);
	}
	if (max[max.size()-1] == s_in[N-1]) {
		if(max[max.size()-1].Y() >= max[max.size()-2].Y()) {
			max_spline.push_back(max[max.size()-1]);
		}
	}
	else {
		max_spline.push_back(max[max.size()-1]);
	}

	double * x = new double [max_spline.size()+2];
	double * y = new double [max_spline.size()+2];

	for (int i = 1; i < max_spline.size()+1; i++) {
		x[i] = max_spline[i-1].X();
		y[i] = max_spline[i-1].Y();
	}

	if (max[0] == s_in[0] && max[0].Y() >= max[1].Y()) {
		y[0] = y[2];
		x[0] = 2*x[1]-x[2];
	}
	else {
		y[0] = y[1];
		x[0] = 2*s[0].X()-x[1];
	}
	if (max[max.size()-1] == s_in[N-1] && max[max.size()-1].Y() >= max[max.size()-2].Y()) {
		y[max_spline.size()+1] = y[max_spline.size()-1];
		x[max_spline.size()+1] = 2*x[max_spline.size()]-x[max_spline.size()-1];
	}
	else {
		y[max_spline.size()+1] = y[max_spline.size()];
		x[max_spline.size()+1] = 2*s[N-1].X()-x[max_spline.size()];
	}

	Spline3Interpolator INTER3(max_spline.size()+2, x, y, s[0].X(), s[N-1].X());

	delete[] x;
	delete[] y;

	TF1 * func_out = new TF1(*(INTER3.GetFInterpolator()));
	func_out->SetNpx(10000);

	return func_out;
}

TF1* EMD::GetEMin(vector <Point> s_in) const {

	vector<Point> min_spline;
	vector<Point> min = GetMin(s_in);

	if (min[0] == s_in[0]) {
		if(min[0].Y() <= min[1].Y()) {
			for (int i = 0; i < min.size()-1; i++)
			min_spline.push_back(min[i]);
		}
		else {
			for (int i = 1; i < min.size()-1; i++)
			min_spline.push_back(min[i]);
		}
	}
	else {
		for (int i = 0; i < min.size()-1; i++)
		min_spline.push_back(min[i]);
	}
	if (min[min.size()-1] == s_in[N-1]) {
		if(min[min.size()-1].Y() <= min[min.size()-2].Y()) {
			min_spline.push_back(min[min.size()-1]);
		}
	}
	else {
		min_spline.push_back(min[min.size()-1]);
	}

	double * x = new double [min_spline.size()+2];
	double * y = new double [min_spline.size()+2];

	for (int i = 1; i < min_spline.size()+1; i++) {
		x[i] = min_spline[i-1].X();
		y[i] = min_spline[i-1].Y();
	}

	if (min[0] == s_in[0] && min[0].Y() <= min[1].Y()) {
		y[0] = y[2];
		x[0] = 2*x[1]-x[2];
	}
	else {
		y[0] = y[1];
		x[0] = 2*s[0].X()-x[1];
	}
	if (min[min.size()-1] == s_in[N-1] && min[min.size()-1].Y() <= min[min.size()-2].Y()) {
		y[min_spline.size()+1] = y[min_spline.size()-1];
		x[min_spline.size()+1] = 2*x[min_spline.size()]-x[min_spline.size()-1];
	}
	else {
		y[min_spline.size()+1] = y[min_spline.size()];
		x[min_spline.size()+1] = 2*s[N-1].X()-x[min_spline.size()];
	}

	Spline3Interpolator INTER3(min_spline.size()+2, x, y, s[0].X(), s[N-1].X());

	delete[] x;
	delete[] y;

	TF1 * func_out = new TF1(*(INTER3.GetFInterpolator()));
	func_out->SetNpx(10000);

	return func_out;
}

TF1* EMD::GetMean() const {

	TF1 * mean = new TF1("Mean", this, &EMD::Get_Mean_Function,s[0].X(),s[N-1].X(),0);
	mean->SetNpx(10000);

	return mean;
}

vector <Point> EMD::GetDetail(vector <Point> a) const {

	vector <Point> detailnew(N);

	double x;
	double y;
	for (int i = 0; i < N; ++i)
	{
		x = s[i].X();
		y = a[i].Y() - envelope[2]->Eval(x);
		detailnew[i] = Point(x,y);
	}

	return detailnew;
}

vector <Point> EMD::GetSignal() const {
	return s;
}

vector <Point> EMD::GetResidue() const {
	if (IMFs_found == false)
		cout << "WARNING [vector <Point> EMD::GetResidue() const]: 'FindIMFs()' hasn't been used yet." << endl;
	return residue;
}

vector <double> EMD::GetVariation() const {

	vector <double> var(N);
	vector <double> amp = GetAmplitude();

	for (int i = 0; i < N; ++i)
	{
		var[i] = fabs((envelope[2]->Eval(residue[i].X()))/amp[i]);
	}

	return var;
}

vector <double> EMD::GetAmplitude() const {

	vector <double> amp(N);

	for (int i = 0; i < N; ++i)
	{
		amp[i] = (envelope[0]->Eval(residue[i].X()) - envelope[1]->Eval(residue[i].X()))/2;
	}

	return amp;
}

bool EMD::IsIMF() const {

	vector <double> var = GetVariation();

	int count = 0;

	for (int i = 0; i < N; i++)
	{
		if (var[i] >= 0.5) {
			return false;
		}
		else if (var[i] < 0.05) {
			count++;
		}
	}

	double taxa = count/double(N);

	if (taxa < 0.95)
	return false;
	else
	return true;
}

bool EMD::ContinueCycle() const {

	// Ver se a amplitude é muito pequena (aproximadamente constante)

	double ave = 0;
	double ave0 = 0;

	for (int i = 0; i < N; i++) {
		ave += residue[i].Y();
		ave0 += Amp0[i];
	}

	ave = ave / double(N);
	ave0 = ave0 /double(N);

	int teste = 1;

	for (int i = 0; i < N; i++) {
		if (fabs(residue[i].Y()-ave) > 0.1*ave0)
		teste = 0;
	}

	if (teste == 1)
	return false;

	// Ver se possui no máximo 3 extremos locais

	vector <Point> max = GetMax(residue);
	vector <Point> min = GetMin(residue);

	int nextremos = max.size() + min.size() - 2;
	//Por causa do mirroring, os extremos do intervalo vão sempre ser
	//ou um máximo ou um mínimo. Para não os contar neste critério,
	//retiramos 2 ao número de extremos total do resíduo.

	if(nextremos < 4)
	return false;

	return true;
}

void EMD::SiftingProcess() {

	SetMean(detail);

	while (!IsIMF()) {

		detail = GetDetail(detail);

		SetMean(detail);
	}
}

void EMD::FindIMFs() {

	IMFs_found = true;

	IMF.clear();
	residue = s;

	SetMean(residue);

	Amp0 = GetAmplitude();

	while(ContinueCycle()) {

		detail = GetDetail(residue);

		SiftingProcess();

		IMF.push_back(detail);

		for (int i = 0; i < N; i++)   // computing residue
		{
			residue[i].Y() = residue[i].Y() - detail[i].Y();
		}

		SetMean(residue);
	}
}

vector <Point> EMD::GetFrequency(vector <Point> a) const {

	vector <double> zeros;
	int j = 1;

	for (int i = 0; i < a.size(); i++) {
		if (a[i].Y() == 0) {
			zeros.push_back(a[i].X());
		}

		if (i == a.size() - 1)
		break;

		if (a[i].Y()*a[j].Y() < 0)
		zeros.push_back(FindZero(a[i],a[j]));

		j++;
	}

	double T = 0;

	vector <Point> frequency(zeros.size()+1);

	for (int i = 1; i < zeros.size(); i++) {
		T = fabs(2*(zeros[i] - zeros[i-1]));
		frequency[i] = Point((zeros[i] + zeros[i-1])/2,1/T);
	}

	frequency[0] = Point(2*s[0].X()-frequency[1].X(),frequency[1].Y());
	frequency[zeros.size()] = Point(2*s[N-1].X()-frequency[zeros.size()-1].X(),frequency[zeros.size()-1].Y());

	Spline3Interpolator INTER3(frequency.size(), GetX(frequency), GetY(frequency), s[0].X(), s[N-1].X());

	TF1 * func_out = new TF1(*(INTER3.GetFInterpolator()));
	func_out->SetNpx(10000);

	vector <Point> output(N);

	for (int i = 0; i < N; i++) {
		output[i] = Point(s[i].X(),fabs(func_out->Eval(s[i].X())));
	}

	delete func_out;

	return output;
}

vector <Point> EMD::GetAmplitude(vector <Point> a) const {

	vector <Point> amp(N);

	TF1 *emax = new TF1(*(GetEMax(a)));
	TF1 *emin = new TF1(*(GetEMin(a)));

	for (int i = 0; i < N; ++i)
	{
		amp[i] = Point(a[i].X(),(emax->Eval(a[i].X()) - emin->Eval(a[i].X()))/2);
	}

	delete emax;
	delete emin;

	return amp;
}

void EMD::Draw(string options) {

	size_t found_A = options.find("A");
	size_t found_B = options.find("B");
	size_t found_C = options.find("C");
	size_t found_D = options.find("D");
	size_t found_E = options.find("E");
	size_t found_F = options.find("F");
	size_t found_G = options.find("G");
	size_t found_H = options.find("H");
	size_t found_I = options.find("I");
	size_t found_J = options.find("J");
	size_t found_K = options.find("K");

	if (found_A == string::npos && found_B == string::npos && found_C == string::npos && found_D == string::npos && found_E == string::npos && found_F == string::npos && found_G == string::npos && found_H == string::npos && found_I == string::npos && found_J == string::npos && found_K == string::npos) {
		cout << "ERROR [void EMD::Draw(string options)]: Option not available. Select one or more of this options: A,B,C,D,E,F,G,H,I,J,K." << endl;
		return;
	}

	if (IMFs_found == false)
		cout << "WARNING [void EMD::Draw(string options)]: 'FindIMFs()' hasn't been used yet." << endl;

	cFCgraphics G;

	if (found_A != string::npos) {

		TPad * pad = G.CreatePad("pad");
		TGraph * graph = new TGraph(N, GetX(GetSignal()), GetY(GetSignal()));
		graph->GetXaxis()->SetLimits(s[0].X(), s[N-1].X());
		graph->SetTitle("Original Signal; Time; Amplitude");
		graph->SetLineColor(1);
		graph->SetLineWidth(5);
		graph->SetMarkerSize(1);
		graph->SetMarkerStyle(20);
		graph->SetMarkerColor(kMagenta);
		G.AddObject(graph,"pad","ACP");
		G.DrawPad("pad");

		delete graph;
		delete pad;
	}

	if (found_B != string::npos) {

		TPad * pad = G.CreatePad("pad");

		SetMean(s);

		TGraph * signal = new TGraph(N, GetX(s), GetY(s));
		TF1 * max = new TF1(*(GetEMax(s)));
		TF1 * min = new TF1(*(GetEMin(s)));
		TF1 * mean = new TF1(*(GetMean()));

		signal->SetTitle("Original Signal | Envelopes | Mean; Time; Amplitude");
		signal->GetXaxis()->SetLimits(s[0].X(), s[N-1].X());
		signal->SetMarkerStyle(20);
		signal->SetMarkerColor(1);
		signal->SetMarkerSize(0.5);
		signal->SetLineColor(1);
		signal->SetLineWidth(5);
		G.AddObject(signal,"pad", "ACP");
		max->SetLineColor(kViolet+10);
		max->SetLineWidth(10);
		max->SetMarkerSize(1);
		G.AddObject(max,"pad");
		min->SetLineColor(kAzure+8);
		min->SetLineWidth(10);
		min->SetMarkerSize(1);
		G.AddObject(min,"pad");
		mean->SetLineColor(kPink+10);
		mean->SetLineWidth(10);
		mean->SetMarkerSize(1);
		G.AddObject(mean,"pad");
		G.DrawPad("pad");

		delete max;
		delete min;
		delete mean;
		delete pad;
	}

	if (found_C != string::npos) {

		TPad * pad = G.CreatePad("pad");

		vector < vector <Point> > imfs = GetIMFs();

		if (imfs.size() == 0)
		cout << "ERROR [void EMD::Draw(string options)]: There's no IMF to draw." << endl;
		else {
			vector<TGraph*> imfs_graphs;

			for (int i = 0; i < imfs.size(); i++) {
				imfs_graphs.push_back(new TGraph(N, GetX(imfs[i]), GetY(imfs[i])));
			}

			gStyle->SetPalette(kColorPrintableOnGrey);

			imfs_graphs[0]->SetTitle("All the IMFs; Time; Amplitude");
			imfs_graphs[0]->GetXaxis()->SetLimits(s[0].X(), s[N-1].X());
			imfs_graphs[0]->SetLineColor(1);
			imfs_graphs[0]->SetLineWidth(5);
			G.AddObject(imfs_graphs[0],"pad", "ACP");

			for (int i = 1; i < imfs.size(); i++) {
				imfs_graphs[i]->SetLineColor(TColor::GetColorPalette(100*i));
				imfs_graphs[i]->SetLineWidth(5);
				G.AddObject(imfs_graphs[i],"pad");
			}

			G.DrawPad("pad");
			for (int i = 0; i < imfs.size(); i++) {
				delete imfs_graphs[i];
			}
			delete pad;
		}
	}

	if (found_D != string::npos) {

		vector < vector <Point> > imfs = GetIMFs();
		string number_imf = "IMF  ";

		if (imfs.size() == 0)
		cout << "ERROR [void EMD::Draw(string options)]: There's no IMF to draw." << endl;
		else {
			for (int i = 0; i < imfs.size(); i++) {
				TPad * pad = G.CreatePad("pad");
				TGraph * graph = new TGraph(N, GetX(imfs[i]), GetY(imfs[i]));
				number_imf.replace(4,1,1,char(i+49));
				graph->SetTitle(number_imf.c_str());
				graph->GetXaxis()->SetLimits(s[0].X(), s[N-1].X());
				graph->GetXaxis()->SetTitle("Time");
				graph->GetYaxis()->SetTitle("Amplitude");
				graph->SetMarkerStyle(20);
				graph->SetMarkerColor(1);
				graph->SetMarkerSize(0.7);
				graph->SetLineColor(kRed);
				graph->SetLineWidth(8);
				G.AddObject(graph,"pad", "ACP");
				G.DrawPad("pad");
				delete graph;
				delete pad;
			}
		}
	}

	if (found_E != string::npos) {

		TPad * pad = G.CreatePad("pad");

		vector<Point> imfs_sum = Sum(IMF);

		TGraph * signal = new TGraph(N, GetX(s), GetY(s));
		signal->SetTitle("Original Signal and Sum of IMF's; Time; Amplitude");
		signal->GetXaxis()->SetLimits(s[0].X(), s[N-1].X());
		signal->SetMarkerStyle(20);
		signal->SetMarkerColor(1);
		signal->SetMarkerSize(0.5);
		signal->SetLineColor(kBlue);
		signal->SetLineWidth(5);
		G.AddObject(signal,"pad", "ACP");

		TGraph * imfs_sum_graph = new TGraph(N, GetX(imfs_sum), GetY(imfs_sum));
		imfs_sum_graph->SetMarkerStyle(20);
		imfs_sum_graph->SetMarkerColor(1);
		imfs_sum_graph->SetMarkerSize(0.5);
		imfs_sum_graph->SetLineColor(kRed);
		imfs_sum_graph->SetLineWidth(5);
		G.AddObject(imfs_sum_graph,"pad", "SAME");
		G.DrawPad("pad");

		delete signal;
		delete imfs_sum_graph;
		delete pad;
	}

	if (found_F != string::npos) {

		TPad * pad = G.CreatePad("pad");

		vector<Point> imfs_sum = Sum(IMF);
		vector<Point> imfs_res;
		for (int i = 0; i < N; i++)
		imfs_res.push_back(Point(imfs_sum[i].X(), imfs_sum[i].Y()+GetResidue()[i].Y()));

		TGraph * signal = new TGraph(N, GetX(s), GetY(s));
		signal->SetTitle("Original Sinal and Residue + Sum of IMF's; Time; Amplitude");
		signal->GetXaxis()->SetLimits(s[0].X(), s[N-1].X());
		signal->SetMarkerStyle(20);
		signal->SetMarkerColor(1);
		signal->SetMarkerSize(0.5);
		signal->SetLineColor(kBlue);
		signal->SetLineWidth(5);
		G.AddObject(signal,"pad", "ACP");

		TGraph * imfs_sum_graph = new TGraph(N, GetX(imfs_res), GetY(imfs_res));
		imfs_sum_graph->SetMarkerStyle(20);
		imfs_sum_graph->SetMarkerColor(1);
		imfs_sum_graph->SetMarkerSize(0.5);
		imfs_sum_graph->SetLineColor(kRed);
		imfs_sum_graph->SetLineWidth(5);
		G.AddObject(imfs_sum_graph,"pad", "SAME");
		G.DrawPad("pad");

		delete signal;
		delete imfs_sum_graph;
		delete pad;
	}

	if (found_G != string::npos) {

		TPad * pad = G.CreatePad("pad");

		TGraph * residue_graph = new TGraph(N, GetX(GetResidue()), GetY(GetResidue()));
		residue_graph->SetTitle("Final Residue; Time; Amplitude");
		residue_graph->GetXaxis()->SetLimits(s[0].X(), s[N-1].X());
		residue_graph->SetLineColor(kTeal+1);
		residue_graph->SetLineWidth(10);
		residue_graph->SetMarkerSize(1);
		G.AddObject(residue_graph,"pad", "ACP");
		G.DrawPad("pad");

		delete residue_graph;
		delete pad;
	}

	if (found_H != string::npos) {

		TPad * pad = G.CreatePad("pad");

		double * n_imfs = new double [GetNumberOfIMFs()];
		double * corr = new double [GetNumberOfIMFs()];

		for (int i = 0; i < GetNumberOfIMFs(); i++) {
			n_imfs[i] = i + 1;
			corr[i] = GetCorr(i);
		}

		TGraph * corr_graph = new TGraph(GetIMFs().size(),n_imfs,corr);
		corr_graph->SetTitle("Correlation Coeficient VS Number of IMF; IMF; Correlation");
		corr_graph->SetFillColor(kViolet+1);
		corr_graph->SetMarkerColor(kRed);
		G.AddObject(corr_graph,"pad","AB1");
		G.DrawPad("pad");

		delete corr_graph;
		delete pad;
		delete[] n_imfs;
		delete[] corr;
	}

	if (found_I != string::npos) {

		TPad * pad = G.CreatePad("pad");

		vector < vector <Point> > IMFs = GetIMFs();
		vector < vector <Point> > amplitudes;
		vector < vector <Point> > frequencies;

		for (int i = 0; i < IMFs.size(); i++) {
			amplitudes.push_back(GetAmplitude(IMFs[i]));
			frequencies.push_back(GetFrequency(IMFs[i]));
		}

		gStyle->SetPalette(kRainBow);

		TH2F *hilbert = new TH2F("hilbert", "Hilbert Spectrum", N, s[0].X(), s[N-1].X(), N/4, FindMinimumY(frequencies),FindMaximumY(frequencies));

		for (int i1 = 0; i1 < IMFs.size(); i1++) {
			for (int i2 = 0; i2 < N; i2++) {
				hilbert->Fill(s[i2].X(),frequencies[i1][i2].Y(),amplitudes[i1][i2].Y());
			}
		}

		hilbert->SetContour(255);
		hilbert->GetXaxis()->SetTitle("Time");
		hilbert->GetYaxis()->SetTitle("Frequency");
		hilbert->GetZaxis()->SetTitle("Amplitude");
		G.AddObject(hilbert,"pad","COLZ1");
		G.DrawPad("pad");

		delete pad;
		delete hilbert;
	}

	if (found_J != string::npos) {

		vector < vector <Point> > IMFs = GetIMFs();

		if (IMFs.size() == 0)
		cout << "ERROR [void EMD::Draw(string options)]: There's no IMF to draw." << endl;
		else {
			vector < vector <Point> > amplitudes;
			vector < vector <Point> > frequencies;
			string number_imf = "Hilbert Spectrum IMF  ";

			for (int i = 0; i < IMFs.size(); i++) {
				amplitudes.push_back(GetAmplitude(IMFs[i]));
				frequencies.push_back(GetFrequency(IMFs[i]));
			}

			gStyle->SetPalette(kRainBow);

			for (int i = 0; i < IMFs.size(); i++) {
				TPad * pad = G.CreatePad("pad");

				TH2F *hilbert = new TH2F("hilbert", "Hilbert Spectrum", N/3, s[0].X(), s[N-1].X(), N/4, FindMinimumY(frequencies[i]),FindMaximumY(frequencies[i]));

				for (int i2 = 0; i2 < N; i2++) {
					hilbert->Fill(s[i2].X(),frequencies[i][i2].Y(),amplitudes[i][i2].Y());
				}

				hilbert->SetContour(255);
				hilbert->GetXaxis()->SetTitle("Time");
				hilbert->GetYaxis()->SetTitle("Frequency");
				number_imf.replace(22,1,1,char(i+49));
				hilbert->SetTitle(number_imf.c_str());
				G.AddObject(hilbert,"pad","COLZ1");
				G.DrawPad("pad");
				delete hilbert;
				delete pad;
			}
		}
	}

	if (found_K != string::npos) {

		vector < vector <Point> > imfs = GetIMFs();

		if (imfs.size() == 0)
		cout << "ERROR [void EMD::Draw(string options)]: There's no IMF to draw." << endl;
		else {
			string number_imf = "IMF  ";
			TPad *pad = G.CreatePad("pad");

			for (int i = 0; i < imfs.size(); i++) {
				TGraph * graph = new TGraph(N, GetX(imfs[i]), GetY(imfs[i]));
				number_imf.replace(4,1,1,char(i+49));
				graph->SetTitle(number_imf.c_str());
				graph->GetXaxis()->SetLimits(s[0].X(), s[N-1].X());
				graph->GetXaxis()->SetTitle("Time");
				graph->GetYaxis()->SetTitle("Amplitude");
				graph->SetMarkerStyle(20);
				graph->SetMarkerColor(kBlue);
				graph->SetMarkerSize(0.7);
				graph->SetLineColor(1);
				graph->SetLineWidth(3);
				G.AddObject(new TGraph(*graph),"pad","ACP");
				G.AddObject(pad->Clone());
				delete graph;
			}
			G.Draw();
			delete pad;
		}
	}
}


void EMD::PrintData() const {

	cout << endl << endl;

	cout << "---------------------------- DATA --------------------------- " << endl << endl;

	cout << "Number of points: " << N << endl;
	cout << "Time interval: [ " << s[0].X() << " , " << s[N-1].X() << " ]" << endl;

	cout << endl << " ----------------------- IMF's ------------------------------ " << endl;

	vector < vector <Point> > IMFs = GetIMFs();
	vector < vector <Point> > amplitudes;
	vector < vector <Point> > frequencies;

	cout << endl << "Number of IMFs: " << IMFs.size() << endl << endl;;

	for (int i = 0; i < IMFs.size(); i++) {
		amplitudes.push_back(GetAmplitude(IMFs[i]));
		frequencies.push_back(GetFrequency(IMFs[i]));
	}

	cout << "  ------------- Correlation Coefficients -------------------- " << endl;

	for (int i = 0; i < IMFs.size(); i++) {
		cout << "  IMF " << i+1 << ") " << GetCorr(i) << endl;
	}

	cout << "  ------------- Medium Frequency --------------------------- " << endl;

	for (int i = 0; i < IMFs.size(); i++) {
		cout << "  IMF " << i+1 << ") " << GetMeanY(frequencies[i]) << endl;
	}

	cout << "  ------------- Medium Amplitude --------------------------- " << endl;

	for (int i = 0; i < IMFs.size(); i++) {
		cout << "  IMF " << i+1 << ") " << GetMeanY(amplitudes[i]) << endl;
	}

	cout << endl << "------------------------------------------------------------- " << endl << endl;
}
