#include "RiceStyle.h"

using namespace std;

void selfcorr_SP_new(){

	const int NAchBins = 7;

	TFile *f = new TFile("../../../rootfiles/selfcorrelation/SP/selfcortest_new_30.root");
	TH1D* c2_pos_case1[100][4][2];
	TH1D* c2_neg_case1[100][4][2];
	TH1D* c2_tot_case1[100][4][2];

	TH1D* c2_pos_case2[100][4][2];
	TH1D* c2_neg_case2[100][4][2];
	TH1D* c2_tot_case2[100][4][2];

	TH1D* ach_hist[100];
	TH1D* ach_otherside[100];


	TH1D* c2_pos[100][4];
	TH1D* c2_neg[100][4];




	for (Int_t i = 0; i < NAchBins; i++){

		ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));
		ach_otherside[i] = (TH1D*)f->Get(Form("demo/ach_otherside_%d",i+1));

		
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
/*
	for (int i = 0; i < 5; ++i)
	{
		for(int j = 0; j < 4; j++){

			c2_pos[i][j] =  new TH1D(*c2_pos_case1[i][j][0]);
			c2_pos[i][j] -> Add(c2_pos_case2[i][j][0],1.);

			c2_neg[i][j] = new TH1D(*c2_neg_case1[i][j][0]);
			c2_neg[i][j] -> Add(c2_neg_case2[i][j][0],1.);


		}
		
	}
*/
	double x[NAchBins];
	double x_otherside[NAchBins];

	double v2_pos_poseta[NAchBins];
	double v2_neg_poseta[NAchBins];
	double v2_diff_poseta[NAchBins];

	double v2_pos_negeta[NAchBins];
	double v2_neg_negeta[NAchBins];
	double v2_diff_negeta[NAchBins];

	double numerator;
	double denominator;
	double q0,q1,q2,q3;

	
	
	for(Int_t i=0; i<NAchBins; i++){
		

		x[i]=ach_hist[i]->GetMean();
		x_otherside[i]=ach_otherside[i]->GetMean();



// positive eta region
//positive
		q0 = c2_pos_case1[i][0][0]->GetMean();
		q1 = c2_pos_case1[i][1][0]->GetMean();
		q2 = c2_pos_case1[i][2][0]->GetMean();
		q3 = c2_pos_case1[i][3][0]->GetMean();

		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_pos_poseta[i] = numerator/denominator;



//negative
		q0 = c2_neg_case1[i][0][0]->GetMean();
		q1 = c2_neg_case1[i][1][0]->GetMean();
		q2 = c2_neg_case1[i][2][0]->GetMean();
		q3 = c2_neg_case1[i][3][0]->GetMean();
		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_neg_poseta[i] = numerator/denominator;


		v2_diff_poseta[i] = v2_neg_poseta[i]-v2_pos_poseta[i];

// negative eta region
//positive
		q0 = c2_pos_case2[i][0][0]->GetMean();
		q1 = c2_pos_case2[i][1][0]->GetMean();
		q2 = c2_pos_case2[i][2][0]->GetMean();
		q3 = c2_pos_case2[i][3][0]->GetMean();

		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_pos_negeta[i] = numerator/denominator;



//negative
		q0 = c2_neg_case2[i][0][0]->GetMean();
		q1 = c2_neg_case2[i][1][0]->GetMean();
		q2 = c2_neg_case2[i][2][0]->GetMean();
		q3 = c2_neg_case2[i][3][0]->GetMean();
		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_neg_negeta[i] = numerator/denominator;


		v2_diff_negeta[i] = v2_neg_negeta[i]-v2_pos_negeta[i];
		
	}	



	TGraph *gr_pos_poseta = new TGraph(NAchBins,x,v2_pos_poseta);
	TGraph *gr_neg_poseta = new TGraph(NAchBins,x,v2_neg_poseta);
	TGraph *gr_diff_poseta = new TGraph(NAchBins,x,v2_diff_poseta);

	TGraph *gr_pos_negeta = new TGraph(NAchBins,x_otherside,v2_pos_poseta);
	TGraph *gr_neg_negeta = new TGraph(NAchBins,x_otherside,v2_neg_poseta);
	TGraph *gr_diff_negeta = new TGraph(NAchBins,x_otherside,v2_diff_poseta);

	gStyle->SetLegendFont(42);
	TH1D* base = new TH1D("base","base",1,-0.15,0.15);
	//pPb
	base->GetYaxis()->SetRangeUser(0.095, 0.105);

	//PbPb
	//base->GetYaxis()->SetRangeUser(0.093, 0.103);
	base->GetXaxis()->SetTitle("Observed A_{ch}");
	base->GetYaxis()->SetTitle("v_{2}{2}");
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

	TH1D* base2 = new TH1D("base2","base2",1,-0.15,0.15);
	base2->GetYaxis()->SetRangeUser(-0.005, 0.005);
	base2->GetXaxis()->SetTitle("Observed A_{ch}");
	base2->GetYaxis()->SetTitle(" (v^{#minus}_{2} #minus v^{#plus}_{2})/(v^{#minus}_{2} #plus v^{#plus}_{2}) ");
	base2->GetXaxis()->CenterTitle();
	base2->GetYaxis()->CenterTitle();
	base2->SetTitleSize  (0.040,"X");
	base2->SetTitleOffset(1.4,"X");
	base2->SetTitleFont  (42,"X");
	base2->SetLabelOffset(0.006,"X");
	base2->SetLabelSize  (0.040,"X");
	base2->SetLabelFont  (42   ,"X");
	base2->SetTitleSize  (0.040,"Y");
	base2->SetTitleOffset(2.0,"Y");
	base2->SetTitleFont  (42,"Y");
	base2->SetLabelOffset(0.006,"Y");
	base2->SetLabelSize  (0.040,"Y");
	base2->SetLabelFont  (42   ,"Y");
	base2->SetLineWidth(0);

	gr_neg_poseta -> SetMarkerStyle(20);
	gr_neg_poseta -> SetMarkerColor(kBlue);
	gr_pos_poseta -> SetMarkerStyle(28);
	gr_pos_poseta -> SetMarkerColor(kRed);

	gr_neg_negeta -> SetMarkerStyle(20);
	gr_neg_negeta -> SetMarkerColor(kBlue);
	gr_pos_negeta -> SetMarkerStyle(28);
	gr_pos_negeta -> SetMarkerColor(kRed);
	
	TCanvas* c1 = new TCanvas("c1","c1",1,1,1200,600);
	c1->Divide(2,1,0.01,0.01);
	TCanvas* c2 = new TCanvas("c2","c2",1,1,1200,600);
	c2->Divide(2,1,0.01,0.01);

	gr_pos_poseta->SetFillStyle(0);
	gr_pos_poseta->SetFillColor(0);
	gr_neg_poseta->SetFillStyle(0);
	gr_neg_poseta->SetFillColor(0);
	gr_pos_negeta->SetFillStyle(0);
	gr_pos_negeta->SetFillColor(0);
	gr_neg_negeta->SetFillStyle(0);
	gr_neg_negeta->SetFillColor(0);

	gStyle->SetOptTitle(0);

//	TLatex* text_a = makeLatex("CMS PbPb #sqrt{s_{NN}}=5.02TeV",0.25,0.85) ;
	TLatex* text_a = makeLatex("30-40% centrality",0.25,0.85) ;
//	TLatex* text_c = makeLatex("0.3 < p_{T} < 3 GeV/c",0.25,0.75) ;
	TLatex* text_b = makeLatex("A_{ch} in -2.4 < #eta < 0",0.25,0.80) ;
	TLatex* text_d = makeLatex("v_{2} in -2.4 < #eta < 0",0.25,0.75) ;
	TLatex* text_c = makeLatex("v_{2} in 0 < #eta < 2.4",0.25,0.75) ;
	TLatex* text_e = makeLatex("A_{ch} in 0 < #eta < 2.4",0.25,0.80) ;



	text_a->SetTextFont(42);
	text_b->SetTextFont(42);
	text_c->SetTextFont(42);
	text_d->SetTextFont(42);
	text_e->SetTextFont(42);


	TLegend* leg = new TLegend(0.76,0.80,0.94,.88);
	leg->SetLineColor(kWhite);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->AddEntry(gr_pos_poseta, "v_{2}^{#plus}{2}","p");
	leg->AddEntry(gr_neg_poseta , "v_{2}^{#minus}{2}","p");

	TLegend* leg2 = new TLegend(0.76,0.80,0.94,.88);
	leg2->SetLineColor(kWhite);
	leg2->SetFillColor(0);
	leg2->SetFillStyle(0);
	leg2->AddEntry(gr_pos_negeta, "v_{2}^{#plus}{2}","p");
	leg2->AddEntry(gr_neg_negeta , "v_{2}^{#minus}{2}","p");

	
	c1->cd(1);
	base->Draw("");
	gr_pos_poseta->Draw("PSame");
	gr_neg_poseta->Draw("PSame");

	text_a->DrawClone("Same");
	text_b->DrawClone("Same");
	text_c->DrawClone("Same");
	//text_d->DrawClone("Same");

	//leg->DrawClone("Same");

	//text_a->DrawClone("Same");
	//text_b->DrawClone("Same");
	//text_c->DrawClone("Same");
	leg->DrawClone("Same");


    //Define a linear function
	TF1* fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.15, 0.15);
	fit1->SetLineColor(kRed);
	fit1->SetLineStyle(2);
	gr_diff_poseta->Fit(fit1,"RN0");

	c1->cd(2);
/*	gr_diff_poseta->GetYaxis()->SetRangeUser(-0.004,0.004);
	gr_diff_poseta->GetXaxis()->SetLimits(-0.1,0.1);
	gr_diff_poseta->GetXaxis()->SetTitle("A_{ch}");
	gr_diff_poseta->GetYaxis()->SetTitle("v_{2}(-) - v_{2}(+)");
	gr_diff_poseta->GetYaxis()->SetTitleOffset(1.1);
	gr_diff_poseta->GetXaxis()->SetTitleOffset(1.1); */

	TLatex* text2 = makeLatex(Form("Intercept : %f #pm %f",fit1->GetParameter(0),fit1->GetParError(0)),0.45,0.25) ;
	TLatex* text1 = makeLatex(Form("slope : %.4f #pm %.4f",fit1->GetParameter(1),fit1->GetParError(1)),0.45,0.30) ;
	base2->Draw("");
	gr_diff_poseta->Draw("PSame");
	text1->DrawClone("Same");
	text2->DrawClone("Same");

	fit1->DrawClone("Same");

	c2->cd(1);
	base->Draw("");
	gr_pos_negeta->Draw("PSame");
	gr_neg_negeta->Draw("PSame");

	//text_a->DrawClone("Same");
	//text_b->DrawClone("Same");
	//text_c->DrawClone("Same");
//	leg->DrawClone("Same");

	text_a->DrawClone("Same");
	text_c->DrawClone("Same");
	//text_c->DrawClone("Same");
	text_e->DrawClone("Same");

	leg2->DrawClone("Same");
    //Define a linear function
	TF1* fit2 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.15, 0.15);
	fit2->SetLineColor(kRed);
	fit2->SetLineStyle(2);
	gr_diff_negeta->Fit(fit2,"RN0");

	c2->cd(2);
/*	gr_diff_negeta->GetYaxis()->SetRangeUser(-0.004,0.004);
	gr_diff_negeta->GetXaxis()->SetLimits(-0.1,0.1);
	gr_diff_negeta->GetXaxis()->SetTitle("A_{ch}");
	gr_diff_negeta->GetYaxis()->SetTitle("v_{2}(-) - v_{2}(+)");
	gr_diff_negeta->GetYaxis()->SetTitleOffset(1.1);
	gr_diff_negeta->GetXaxis()->SetTitleOffset(1.1); */

	TLatex* text3 = makeLatex(Form("Intercept : %f #pm %f",fit2->GetParameter(0),fit2->GetParError(0)),0.45,0.25) ;
	TLatex* text4 = makeLatex(Form("slope : %.4f #pm %.4f",fit2->GetParameter(1),fit2->GetParError(1)),0.45,0.30) ;
	base2->Draw("");
	gr_diff_negeta->Draw("PSame");
	text3->DrawClone("Same");
	text4->DrawClone("Same");

	fit2->DrawClone("Same");

	TCanvas* c3 = new TCanvas("c3","c3",1,1,600,600);
	TGraph *gr_ach = new TGraph(NAchBins,x,x_otherside);
	TH1D* base3 = new TH1D("base3","base3",1,-0.15,0.15);
	//pPb
	base3->GetYaxis()->SetRangeUser(-0.15, 0.15);

	//PbPb
	//base->GetYaxis()->SetRangeUser(0.093, 0.103);
	base3->GetXaxis()->SetTitle("A_{ch} eta < 0");
	base3->GetYaxis()->SetTitle("A_{ch} eta > 0");
	base3->GetXaxis()->CenterTitle();
	base3->GetYaxis()->CenterTitle();
	base3->SetTitleSize  (0.040,"X");
	base3->SetTitleOffset(1.4,"X");	
	base3->SetTitleFont  (42,"X");
	base3->SetLabelOffset(0.006,"X");
	base3->SetLabelSize  (0.040,"X");
	base3->SetLabelFont  (42   ,"X");

	base3->SetTitleSize  (0.040,"Y");
	base3->SetTitleOffset(2.2,"Y");
	base3->SetTitleFont  (42,"Y");
	base3->SetLabelOffset(0.006,"Y");
	base3->SetLabelSize  (0.040,"Y");
	base3->SetLabelFont  (42   ,"Y");
	base3->SetLineWidth(0);
	c3->cd();

	base3->Draw("");
	gr_ach->Draw("PSame");



	c1->Print("~/Summer2016/selfcorr_SP_new_30_case1.pdf");
	c1->Print("~/Summer2016/selfcorr_SP_new_30_case1.gif");


	c2->Print("~/Summer2016/selfcorr_SP_new_30_case2.pdf");
	c2->Print("~/Summer2016/selfcorr_SP_new_30_case2.gif");

	c3->Print("~/Summer2016/Achcorr_30.pdf");
	c3->Print("~/Summer2016/Achcorr_30.gif");
	


}
