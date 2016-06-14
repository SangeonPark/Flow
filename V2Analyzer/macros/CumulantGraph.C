#include "RiceStyle.h"

using namespace std;

void CumulantGraph(){

	TFile *f = new TFile("../../../rootfiles/CumulantMethodpPb.root");
	TH1D* c2_pos[5][2];
	TH1D* c2_neg[5][2];

	TH1D* ach_hist[5];

	for (Int_t i = 0; i < 5; i++){
		ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

		c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
		c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));


		c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
		c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));
		
	}

	double x[5];

	double v2_pos[5];
	double v2_neg[5];
	double v2_diff[5];

/*
	double err_neg[5];
	double err_pos[5];
	double err_diff_case1[5];
*/


	double cmean;	 


	for(Int_t i=0; i<5; i++){

		x[i]=ach_hist[i]->GetMean();

//positive
		cmean = c2_pos[i][0] -> GetMean();
		v2_pos[i] = sqrt(cmean);

		cmean = c2_neg[i][0] -> GetMean();
		v2_neg[i] = sqrt(cmean);

		v2_diff[i] = v2_neg[i] - v2_pos[i];

	}

	TGraph *gr_pos = new TGraph(5,x,v2_pos);
	TGraph *gr_neg = new TGraph(5,x,v2_neg);
	TGraph *gr_diff = new TGraph(5,x,v2_diff);

	TH1D* base = new TH1D("base","base",100,-0.1,0.1);
	base->GetYaxis()->SetRangeUser(0.06,0.09);
	base->GetXaxis()->SetTitle("Observed A_{ch}");
	base->GetYaxis()->SetTitle("v_{2}");
	base->SetStats(0);
	base->GetYaxis()->SetTitleOffset(1.4);
	base->GetXaxis()->SetTitleOffset(1.1);

	gr_neg -> SetMarkerStyle(20);
	gr_neg -> SetMarkerColor(kBlue);
	gr_pos -> SetMarkerStyle(28);
	gr_pos -> SetMarkerColor(kRed);

	TCanvas* c3 = new TCanvas("c3","c3",1,1,1200,600);
	c3->Divide(2,1,0.01,0.01);

	gr_pos->SetFillStyle(0);
	gr_pos->SetFillColor(0);
	gr_neg->SetFillStyle(0);
	gr_neg->SetFillColor(0);

	gStyle->SetOptTitle(0);

	TLatex* text_a = makeLatex("p-Pb #sqrt{s_{NN}}=5.02TeV",0.15,0.8) ;
	TLatex* text_b = makeLatex("N_{trk}^{offline} [220,260)",0.15,0.7) ;
	TLatex* text_c = makeLatex("0.3 < p_{T} < 3.0 GeV/c",0.15,0.6) ;

	TLegend* leg = new TLegend(.60,.70,.80,.85);
	leg->SetLineColor(kWhite);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->AddEntry(gr_pos, "pos","p");
	leg->AddEntry(gr_neg, "neg","p");

	
	c3->cd(1);
	base->Draw("");
	gr_pos->Draw("PSame");
	gr_neg->Draw("PSame");
	text_a->DrawClone("Same");
	text_b->DrawClone("Same");
	text_c->DrawClone("Same");
//	leg->DrawClone("Same");


    //Define a linear function
	TF1* fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.09, 0.09);
	fit1->SetLineColor(kRed);
	fit1->SetLineStyle(2);
	gr_diff->Fit(fit1);

	c3->cd(2);
	gr_diff->GetYaxis()->SetRangeUser(-0.004,0.004);
	gr_diff->GetXaxis()->SetLimits(-0.1,0.1);
	gr_diff->GetXaxis()->SetTitle("A_{ch}");
	gr_diff->GetYaxis()->SetTitle("v_{2}(-) - v_{2}(+)");
	gr_diff->GetYaxis()->SetTitleOffset(1.1);
	gr_diff->GetXaxis()->SetTitleOffset(1.1);

	TLatex* text1 = makeLatex(Form("slope r = %f #pm %f",fit1->GetParameter(1),fit1->GetParError(1)),0.15,0.8) ;
	
	gr_diff->Draw("A*");
	text1->DrawClone("Same");
	fit1->DrawClone("Same");

}
