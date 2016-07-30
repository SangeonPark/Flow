#include "RiceStyle.h"

using namespace std;

void fig1(){

	TH1D* ChargeAsym;
	
	TH2D* h2;

	f = new TFile("../../../rootfiles/v2Cumulant_pPb/Merged.root");
	ChargeAsym = (TH1D*)f->Get("demo/ChargeAsym");

	TH1D *h1 = (TH1D*) ChargeAsym->Clone("h1");

	f = new TFile("../../../rootfiles/MC/EPOS_Merged.root");
	h2 = (TH2D*)f->Get("demo/scatterHist_effcorr");
	TH2D *copy = (TH2D*) h2->Clone("h2");
	TProfile *prof = copy->ProfileX();

	TF1* fit1 = new TF1("f1", "[0]+x*[1]", -0.08, 0.08);
	prof->Fit(fit1,"RN0");

	TFile *rebinned = new TFile("~/Summer2016/root_forgraphs/figure1.root","RECREATE");
	h1->Write();
	prof->Write();
	fit1->Write();
	rebinned->Close();
}

















