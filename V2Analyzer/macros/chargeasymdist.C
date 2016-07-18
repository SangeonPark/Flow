#include "RiceStyle.h"
using namespace std;

void chargeasymdist(){

	TFile *f;
	TH1D* c2_pos[5][2];
	TH1D* c2_neg[5][2];

	TH1D* ach_hist[5];
	double x[5];

	double v2_pos[5];
	double v2_neg[5];
	double v2_diff[5];
	double err_neg[5];
	double err_pos[5];
	double err_diff[5];
	double cmean;
	double errmean;
	double sum;
	double variance_pos;
	double variance_neg;
	double variance_diff;


	f = new TFile("../../../rootfiles/v2Cumulant_pPb/Merged.root");


	gStyle->SetLegendFont(42);
	TH1D* base;
	base = (TH1D*)f->Get("demo/ChargeAsym");


	base->GetXaxis()->SetRangeUser(-0.15,0.15);
	base->GetXaxis()->SetTitle("Observed A_{ch}");
	base->GetYaxis()->SetTitle("Counts");
	base->GetXaxis()->CenterTitle();
	base->GetYaxis()->CenterTitle();
	base->SetTitleSize  (0.040,"X");
	base->SetTitleOffset(1.4,"X");
	base->SetTitleFont  (42,"X");
	base->SetLabelOffset(0.006,"X");
	base->SetLabelSize  (0.040,"X");
	base->SetLabelFont  (42   ,"X");

	base->SetTitleSize  (0.040,"Y");
	base->SetTitleOffset(2.2,"Y");
	base->SetTitleFont  (42,"Y");
	base->SetLabelOffset(0.006,"Y");
	base->SetLabelSize  (0.040,"Y");
	base->SetLabelFont  (42   ,"Y");
	base->SetLineWidth(0);

	TCanvas* c3 = MakeCanvas("c3","c3");
	TLatex* text_a = makeLatex("CMS pPb #sqrt{s_{NN}}=5.02TeV",0.23,0.85) ;
	TLatex* text_b = makeLatex("185 #leq N_{trk}^{offline} < 260",0.23,0.80) ;
	TLatex* text_c = makeLatex("0.3 < p_{T} < 3 GeV/c",0.23,0.75) ;
	TLatex* text_d = makeLatex("|#Delta#eta| > 2",0.23,0.80) ;

	text_a->SetTextFont(42);
	text_b->SetTextFont(42);
	text_c->SetTextFont(42);
	text_d->SetTextFont(42);


	gStyle->SetOptTitle(0);

	//leg->AddEntry(gr_neg, "neg","p");

	
	c3->cd();
	base->Draw("");

	text_a->DrawClone("Same");
	text_b->DrawClone("Same");
	text_c->DrawClone("Same");
//	text_d->DrawClone("Same");

    //Define a linear function
	SaveCanvas(c3,"pics","charge_asymmetry_distribution_pPb");
}