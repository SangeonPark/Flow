#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "TString.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TMath.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TLine.h"
#include "TAxis.h"

using namespace std;

void v2ErrMerged(){

	TFile* f;
	TH1D* c2_pos_case1[5][5][2];
	TH1D* c2_neg_case1[5][5][2];
	TH1D* c2_tot_case1[5][5][2];

	TH1D* c2_pos_case2[5][4][2];
	TH1D* c2_neg_case2[5][4][2];
	TH1D* c2_tot_case2[5][4][2];


	TH1D* ach_hist[5];

	TH1D* c2_pos[5][4];
	TH1D* c2_neg[5][4];

	double x[5];


	double v2_pos[5];
	double v2_neg[5];
	double err_pos[5];
	double err_neg[5];
	double v2_diff[5];
	double err_diff[5];



	double numerator;
	double denominator;
	double q0,q1,q2,q3;

	double esquared;

	double v2_pos_sample[5][10];
	double v2_neg_sample[5][10];


	for (int n = 0; n < 10; ++n)
	{
		f = new TFile(Form("../../../rootfiles/errcalc/leaveout%d.root",n+1));
		for (Int_t i = 0; i < 5; i++){
			for(Int_t j = 0 ; j < 5; j++){

				c2_tot_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_cos_case1",i,j));
				c2_tot_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_sin_case1",i,j));
				c2_pos_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_cos_case1",i,j));
				c2_pos_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_sin_case1",i,j));
				c2_neg_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_cos_case1",i,j));
				c2_neg_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_sin_case1",i,j));

			//c2_pos_case1[i][j][0] -> Sumw2();
			//c2_neg_case1[i][j][0] -> Sumw2();
			}
			for(Int_t j=0; j<4; j++){
				c2_tot_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_cos_case2",i,j));
				c2_tot_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_sin_case2",i,j));
				c2_pos_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_cos_case2",i,j));
				c2_pos_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_sin_case2",i,j));
				c2_neg_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_cos_case2",i,j));
				c2_neg_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_sin_case2",i,j));

			//c2_pos_case2[i][j][0] ->Sumw2();
			//c2_neg_case2[i][j][0] ->Sumw2(); 

			}
		}

		for (int i = 0; i < 5; ++i)
		{
			c2_pos[i][0] =  new TH1D(*c2_pos_case1[i][0][0]);
			c2_pos[i][0] -> Add(c2_pos_case2[i][0][0],1.);

			c2_pos[i][1] =  new TH1D(*c2_pos_case1[i][1][0]);
			c2_pos[i][1] -> Add(c2_pos_case2[i][2][0],1.);

			c2_pos[i][2] =  new TH1D(*c2_pos_case1[i][2][0]);
			c2_pos[i][2] -> Add(c2_pos_case2[i][1][0],1.);

			c2_pos[i][3] =  new TH1D(*c2_pos_case1[i][3][0]);
			c2_pos[i][3] -> Add(c2_pos_case2[i][3][0],1.);

			c2_neg[i][0] =  new TH1D(*c2_neg_case1[i][0][0]);
			c2_neg[i][0] -> Add(c2_neg_case2[i][0][0],1.);

			c2_neg[i][1] =  new TH1D(*c2_neg_case1[i][1][0]);
			c2_neg[i][1] -> Add(c2_neg_case2[i][2][0],1.);

			c2_neg[i][2] =  new TH1D(*c2_neg_case1[i][2][0]);
			c2_neg[i][2] -> Add(c2_neg_case2[i][1][0],1.);

			c2_neg[i][3] =  new TH1D(*c2_neg_case1[i][3][0]);
			c2_neg[i][3] -> Add(c2_neg_case2[i][3][0],1.);

		}

		for(Int_t i=0; i<5; i++){

	
//positive
			q0 = c2_pos[i][0]->GetMean();
			q1 = c2_pos[i][1]->GetMean();
			q2 = c2_pos[i][2]->GetMean();
			q3 = c2_pos[i][3]->GetMean();


			numerator = q0;
			denominator = sqrt((q1*q2)/q3);
			v2_pos_sample[i][n] = numerator/denominator;




//negative
			q0 = c2_neg[i][0]->GetMean();
			q1 = c2_neg[i][1]->GetMean();
			q2 = c2_neg[i][2]->GetMean();
			q3 = c2_neg[i][3]->GetMean();
			numerator = q0;
			denominator = sqrt((q1*q2)/q3);
			v2_neg_sample[i][n] = numerator/denominator;


		}



	}

	f = new TFile("../../../rootfiles/PbPbcrabData.root");


	for (Int_t i = 0; i < 5; i++){
		ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));
		
		for(Int_t j = 0 ; j < 5; j++){
			
			c2_tot_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_cos_case1",i,j));
			c2_tot_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_sin_case1",i,j));
			c2_pos_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_cos_case1",i,j));
			c2_pos_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_sin_case1",i,j));
			c2_neg_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_cos_case1",i,j));
			c2_neg_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_sin_case1",i,j));

			//c2_pos_case1[i][j][0] -> Sumw2();
			//c2_neg_case1[i][j][0] -> Sumw2();
		}
		for(Int_t j=0; j<4; j++){
			c2_tot_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_cos_case2",i,j));
			c2_tot_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_sin_case2",i,j));
			c2_pos_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_cos_case2",i,j));
			c2_pos_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_sin_case2",i,j));
			c2_neg_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_cos_case2",i,j));
			c2_neg_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_sin_case2",i,j));

			//c2_pos_case2[i][j][0] ->Sumw2();
			//c2_neg_case2[i][j][0] ->Sumw2(); 

		}
	}

	for (int i = 0; i < 5; ++i)
	{
		c2_pos[i][0] =  new TH1D(*c2_pos_case1[i][0][0]);
		c2_pos[i][0] -> Add(c2_pos_case2[i][0][0],1.);
		
		c2_pos[i][1] =  new TH1D(*c2_pos_case1[i][1][0]);
		c2_pos[i][1] -> Add(c2_pos_case2[i][2][0],1.);

		c2_pos[i][2] =  new TH1D(*c2_pos_case1[i][2][0]);
		c2_pos[i][2] -> Add(c2_pos_case2[i][1][0],1.);

		c2_pos[i][3] =  new TH1D(*c2_pos_case1[i][3][0]);
		c2_pos[i][3] -> Add(c2_pos_case2[i][3][0],1.);

		c2_neg[i][0] =  new TH1D(*c2_neg_case1[i][0][0]);
		c2_neg[i][0] -> Add(c2_neg_case2[i][0][0],1.);
		
		c2_neg[i][1] =  new TH1D(*c2_neg_case1[i][1][0]);
		c2_neg[i][1] -> Add(c2_neg_case2[i][2][0],1.);

		c2_neg[i][2] =  new TH1D(*c2_neg_case1[i][2][0]);
		c2_neg[i][2] -> Add(c2_neg_case2[i][1][0],1.);

		c2_neg[i][3] =  new TH1D(*c2_neg_case1[i][3][0]);
		c2_neg[i][3] -> Add(c2_neg_case2[i][3][0],1.);

	}



	
	
	for(Int_t i=0; i<5; i++){
		
//x coordinates
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



//error bars
		double variance_pos = 0.0;
		double variance_neg = 0.0;
		for (int k = 0; k < 10; ++k)
		{
			variance_pos += (v2_pos_sample[i][k]-v2_pos[i])*(v2_pos_sample[i][k]-v2_pos[i]);
			variance_neg += (v2_neg_sample[i][k]-v2_neg[i])*(v2_neg_sample[i][k]-v2_neg[i]);
		}
		variance_pos *= 0.9;
		variance_neg *= 0.9;
		err_pos[i] = sqrt(variance_pos);
		err_neg[i] = sqrt(variance_neg);



//difference
		v2_diff[i] = v2_neg[i]-v2_pos[i];
		err_diff[i] = sqrt(err_neg[i]*err_neg[i]+err_pos[i]*err_pos[i]);

		
	}

	TH1D* base = new TH1D("base","base",100,-0.1,0.1);
	base->GetYaxis()->SetRangeUser(0.095,0.105);

	TGraphErrors *gr_pos = new TGraphErrors(5,x,v2_pos,NULL,err_pos);
	TGraphErrors *gr_neg = new TGraphErrors(5,x,v2_neg,NULL,err_neg);
	TGraphErrors *gr_diff = new TGraphErrors(5,x,v2_diff,NULL,err_diff);

    TCanvas* c1 = new TCanvas("c1","c1");
    TCanvas* c2 = new TCanvas("c2","c2");

    gr_pos -> SetMarkerStyle(20);
	gr_pos -> SetMarkerColor(kBlue);
	gr_neg -> SetMarkerStyle(28);
	gr_neg -> SetMarkerColor(kRed);

    
    c1->cd();
    base->Draw("");
    gr_pos->Draw("PSame");
    gr_neg->Draw("PSame");

    //Define a linear function
    TF1* fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.09, 0.09);
    fit1->SetLineColor(kRed);
    fit1->SetLineStyle(2);
    gr_diff->Fit(fit1);

    c2->cd();
    gr_diff->GetYaxis()->SetRangeUser(-0.002,0.003);
    gr_diff->GetXaxis()->SetLimits(-0.1,0.1);
    gr_diff->GetXaxis()->SetTitle("A_{ch}");
    gr_diff->GetYaxis()->SetTitle("v_{2}(-) - v_{2}(+)");
    gr_diff->GetYaxis()->SetTitleOffset(1.1);
    gr_diff->GetXaxis()->SetTitleOffset(1.1);

    TLatex* text1 = new TLatex(-0.09, 0.0025, Form("slope r = %f #pm %f",fit1->GetParameter(1),fit1->GetParError(1))) ;
    
    gr_diff->Draw("A*");
    text1->DrawClone("Same");
    fit1->DrawClone("Same");

}
