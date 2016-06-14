#include "RiceStyle.h"

using namespace std;

void SPGraph(){

	TFile *f = new TFile("../../../rootfiles/SPmethodpPb.root");
	TH1D* c2_pos_case1[5][4][2];
	TH1D* c2_neg_case1[5][4][2];
	TH1D* c2_tot_case1[5][4][2];

	TH1D* c2_pos_case2[5][4][2];
	TH1D* c2_neg_case2[5][4][2];
	TH1D* c2_tot_case2[5][4][2];

	TH1D* ach_hist[5];

	TH1D* c2_pos[5][4];
	TH1D* c2_neg[5][4];

	for (Int_t i = 0; i < 5; i++){
		ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));
		
		for(Int_t j = 0 ; j < 4; j++){
			

			c2_pos_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_cos_case1",i,j));
			c2_pos_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_sin_case1",i,j));
			c2_neg_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_cos_case1",i,j));
			c2_neg_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_sin_case1",i,j));
			c2_pos_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_cos_case2",i,j));
			c2_pos_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_sin_case2",i,j));
			c2_neg_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_cos_case2",i,j));
			c2_neg_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_sin_case2",i,j));

		}

	}

	for (int i = 0; i < 5; ++i)
	{
		for(int j = 0; j < 4; j++){

			c2_pos[i][j] =  new TH1D(*c2_pos_case1[i][j][0]);
			c2_pos[i][j] -> Add(c2_pos_case2[i][j][0],1.);

			c2_neg[i][j] = new TH1D(*c2_neg_case1[i][j][0]);
			c2_neg[i][j] -> Add(c2_neg_case2[i][j][0],1.);


		}
		
	}
	double x[5];

	double v2_pos[5];
	double v2_neg[5];

	double v2_diff[5];



	double numerator;
	double denominator;
	double q0,q1,q2,q3;

	
	
	for(Int_t i=0; i<5; i++){
		

		x[i]=ach_hist[i]->GetMean();



//positive
		q0 = c2_pos[i][0]->GetMean();
		q1 = c2_pos[i][1]->GetMean();
		q2 = c2_pos[i][2]->GetMean();
		q3 = c2_pos[i][3]->GetMean();

		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_pos[i] = numerator/denominator;



//negative
		q0 = c2_neg[i][0]->GetMean();
		q1 = c2_neg[i][1]->GetMean();
		q2 = c2_neg[i][2]->GetMean();
		q3 = c2_neg[i][3]->GetMean();
		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_neg[i] = numerator/denominator;


		v2_diff[i] = v2_neg[i]-v2_pos[i];

		
	}	

	TGraph *gr_pos = new TGraph(5,x,v2_pos);
	TGraph *gr_neg = new TGraph(5,x,v2_neg);
	TGraph *gr_diff = new TGraph(5,x,v2_diff);

	TH1D* base = new TH1D("base","base",100,-0.1,0.1);
	base->GetYaxis()->SetRangeUser(0.02,0.15);
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
