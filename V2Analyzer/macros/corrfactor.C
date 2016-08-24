#include "RiceStyle.h"

using namespace std;

void corrfactor(){

	TFile *f;

	const int NAchBins = 7;
	const double correction = 1.0;

	double r;

	TH2D* recogenach;


	f = new TFile("../../../rootfiles/closure/Merged.root");



	recogenach = (TH2D*)f->Get(Form("demo/genrecoach"));
	r = recogenach->GetCorrelationFactor();

	cout <<"answer is:" << r << endl;





}
