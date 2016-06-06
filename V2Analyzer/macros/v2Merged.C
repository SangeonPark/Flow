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

void v2Merged(){

	TFile *f = new TFile("../../../rootfiles/PbPbcrabData.root");
	TH1D* c2_pos_case1[5][5][2];
	TH1D* c2_neg_case1[5][5][2];
	TH1D* c2_tot_case1[5][5][2];

	TH1D* c2_pos_case2[5][4][2];
	TH1D* c2_neg_case2[5][4][2];
	TH1D* c2_tot_case2[5][4][2];

	TH1D* ach_hist[5];

	TH1D* c2_pos[5][4];
	TH1D* c2_neg[5][4];

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
	/*
	TCanvas* c4 = new TCanvas("c4","c4");
	TCanvas* c5 = new TCanvas("c5","c5");
	TCanvas* c6 = new TCanvas("c6","c6");

	c4->cd();
	c2_pos[0][0]->DrawClone();
	c5->cd();
	c2_pos_case1[0][0][0]->DrawClone();

	c6->cd();
	c2_pos_case2[0][0][0]->DrawClone(); */

	double x[5];
	/*
	double v2_pos_case1[5];
	double err_pos_case1[5];

	double v2_neg_case1[5];
	double err_neg_case1[5];

	double v2_tot_case1[5];
	double err_tot_case1[5];
	
	double v2_pos_case2[5];
	double err_pos_case2[5];

	double v2_neg_case2[5];
	double err_neg_case2[5];

	double v2_tot_case2[5];
	double err_tot_case2[5];
	
	double v2_diff_case1[5];
	double err_diff_case1[5];

	double v2_diff_case2[5];
	double err_diff_case2[5];
	*/

	double v2_pos[5];
	double v2_neg[5];
	double err_pos[5];
	double err_neg[5];
	double v2_diff[5];
	double err_diff[5];



	double numerator;
	double denominator;
	double q0,q1,q2,q3;
	double e0,e1,e2,e3;
	double grad0,grad1,grad2,grad3;
	double esquared;
	
	
	for(Int_t i=0; i<5; i++){
		
		cout << i << "th term" << endl;

		x[i]=ach_hist[i]->GetMean();

		cout << "x : " << x[i] <<endl;



//positive
		q0 = c2_pos[i][0]->GetMean();
		q1 = c2_pos[i][1]->GetMean();
		q2 = c2_pos[i][2]->GetMean();
		q3 = c2_pos[i][3]->GetMean();

		cout << q0 << " " << q1 << " " << q2 << " " << q3 << endl;

		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_pos[i] = numerator/denominator;

		e0 = c2_pos[i][0]->GetMeanError();
		e1 = c2_pos[i][1]->GetMeanError();
		e2 = c2_pos[i][2]->GetMeanError();
		e3 = c2_pos[i][3]->GetMeanError();

		grad0 = 1/sqrt(q1*q2/q3);
		grad1 = -0.5*( (q0*sqrt(q3)) / (q1*sqrt(q1*q2)) );
		grad2 = -0.5*( (q0*sqrt(q3)) / (q2*sqrt(q1*q2)) );
		grad3 = q0/(2*sqrt(q1*q2*q3));

		esquared = grad0*grad0*e0*e0+grad1*grad1*e1*e1+grad2*grad2*e2*e2+grad3*grad3*e3*e3;
		err_pos[i] = sqrt(esquared);

		cout << "v2pos : " << v2_pos[i] << endl;
		cout << "errpos : " << err_pos[i] << endl;


//negative
		q0 = c2_neg[i][0]->GetMean();
		q1 = c2_neg[i][1]->GetMean();
		q2 = c2_neg[i][2]->GetMean();
		q3 = c2_neg[i][3]->GetMean();
		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_neg[i] = numerator/denominator;

		e0 = c2_neg[i][0]->GetMeanError();
		e1 = c2_neg[i][1]->GetMeanError();
		e2 = c2_neg[i][2]->GetMeanError();
		e3 = c2_neg[i][3]->GetMeanError();

		grad0 = 1/sqrt(q1*q2/q3);
		grad1 = -0.5*( (q0*sqrt(q3)) / (q1*sqrt(q1*q2)) );
		grad2 = -0.5*( (q0*sqrt(q3)) / (q2*sqrt(q1*q2)) );
		grad3 = q0/(2*sqrt(q1*q2*q3));

		esquared = grad0*grad0*e0*e0+grad1*grad1*e1*e1+grad2*grad2*e2*e2+grad3*grad3*e3*e3;
		err_neg[i] = sqrt(esquared);


		v2_diff[i] = v2_neg[i]-v2_pos[i];
		cout << "difference : " << v2_diff[i] <<endl;
		err_diff[i] = sqrt(err_neg[i]*err_neg[i]+err_pos[i]*err_pos[i]);

		
	}

	TH1D* base = new TH1D("base","base",100,-0.1,0.1);
	base->GetYaxis()->SetRangeUser(0.096,0.102);
	
	/*
	TGraphErrors *gr_pos_case1 = new TGraphErrors(5,x,v2_pos_case1,NULL,err_pos_case1);
	TGraphErrors *gr_neg_case1 = new TGraphErrors(5,x,v2_neg_case1,NULL,err_neg_case1);
	TGraphErrors *gr_tot_case1 = new TGraphErrors(5,x,v2_tot_case1,NULL,err_tot_case1);
	TGraphErrors *gr_pos_case2 = new TGraphErrors(5,x,v2_pos_case2,NULL,err_pos_case2);
	TGraphErrors *gr_neg_case2 = new TGraphErrors(5,x,v2_neg_case2,NULL,err_neg_case2);
	TGraphErrors *gr_tot_case2 = new TGraphErrors(5,x,v2_tot_case2,NULL,err_tot_case2);
	
	TGraphErrors *gr_diff_case1 = new TGraphErrors(5,x,v2_diff_case1,NULL,err_diff_case1);
	TGraphErrors *gr_diff_case2 = new TGraphErrors(5,x,v2_diff_case2,NULL,err_diff_case2); */

	TGraphErrors *gr_pos = new TGraphErrors(5,x,v2_pos,NULL,err_pos);
	TGraphErrors *gr_neg = new TGraphErrors(5,x,v2_neg,NULL,err_neg);
	TGraphErrors *gr_diff = new TGraphErrors(5,x,v2_diff,NULL,err_diff);


    /*
    gr_pos_case1->GetYaxis()->SetRangeUser(0.095,0.115);
    gr_pos_case1->GetXaxis()->SetLimits(-0.1,0.1);
    gr_neg_case1->GetYaxis()->SetRangeUser(0.095,0.115);
    gr_neg_case1->GetXaxis()->SetLimits(-0.1,0.1);
    gr_tot_case1->GetYaxis()->SetRangeUser(0.095,0.115);
    gr_tot_case1->GetXaxis()->SetLimits(-0.1,0.1);
    gr_pos_case2->GetYaxis()->SetRangeUser(0.095,0.115);
    gr_pos_case2->GetXaxis()->SetLimits(-0.1,0.1);
    gr_neg_case2->GetYaxis()->SetRangeUser(0.095,0.115);
    gr_neg_case2->GetXaxis()->SetLimits(-0.1,0.1);
    gr_tot_case2->GetYaxis()->SetRangeUser(0.095,0.115);
    gr_tot_case2->GetXaxis()->SetLimits(-0.1,0.1); */
/*
    gr_pos_case1 -> SetName("positive tracks case1");
    gr_neg_case1 -> SetName("negative tracks case1");
    gr_tot_case1 -> SetName("total tracks case1");
    gr_pos_case1 -> SetTitle("positive tracks case1");
    gr_neg_case1 -> SetTitle("negative tracks case1");
    gr_tot_case1 -> SetTitle("total tracks case1");

    gr_diff_case1 -> SetTitle("difference case1");

    gr_pos_case2 -> SetName("positive tracks case2");
    gr_neg_case2 -> SetName("negative tracks case2");
    gr_tot_case2 -> SetName("total tracks case2");
    gr_pos_case2 -> SetTitle("positive tracks case2");
    gr_neg_case2 -> SetTitle("negative tracks case2");
    gr_tot_case2 -> SetTitle("total tracks case2");

    gr_diff_case2 -> SetTitle("difference case2"); */

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

//  c2->Divide(2,1,0,0);
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
