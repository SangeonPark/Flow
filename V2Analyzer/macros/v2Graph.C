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

void v2Graph(){

    TFile *f = new TFile("../PbPbData.root");
    TH1D* c2_pos_case1[5][5][2];
    TH1D* c2_neg_case1[5][5][2];
    TH1D* c2_tot_case1[5][5][2];

    TH1D* c2_pos_case2[5][4][2];
    TH1D* c2_neg_case2[5][4][2];
    TH1D* c2_tot_case2[5][4][2];
    TH1D* ach_hist[5];

    for (Int_t i = 0; i < 5; i++){
	ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));
				    
	for(Int_t j = 0 ; j < 5; j++){
	    
	    c2_tot_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_cos_case1",i,j));
	    c2_tot_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_sin_case1",i,j));
	    c2_pos_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_cos_case1",i,j));
	    c2_pos_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_sin_case1",i,j));
	    c2_neg_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_cos_case1",i,j));
	    c2_neg_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_sin_case1",i,j));
	}
	for(Int_t j=0; j<4; j++){
	    c2_tot_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_cos_case2",i,j));
	    c2_tot_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_sin_case2",i,j));
	    c2_pos_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_cos_case2",i,j));
	    c2_pos_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_sin_case2",i,j));
	    c2_neg_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_cos_case2",i,j));
	    c2_neg_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_sin_case2",i,j));

	}
    }
 
    double x[5];
    double v2_pos_case1[5];
    double v2_neg_case1[5];
    double v2_tot_case1[5];
    double v2_pos_case2[5];
    double v2_neg_case2[5];
    double v2_tot_case2[5];
    double numerator;
    double denominator;
    double q0,q1,q2,q3;
    
    for(Int_t i=0; i<5; i++){
	x[i]=ach_hist[i]->GetMean();
	//case1 positive
	q0 = c2_pos_case1[i][0][0]->GetMean();
	q1 = c2_pos_case1[i][1][0]->GetMean();
	q2 = c2_pos_case1[i][2][0]->GetMean();
	q3 = c2_pos_case1[i][3][0]->GetMean();
	numerator = q0;
	denominator = sqrt((q1*q2)/q3);
	v2_pos_case1[i] = numerator/denominator;
	//case1 total
	q0 = c2_tot_case1[i][0][0]->GetMean();
	q1 = c2_tot_case1[i][1][0]->GetMean();
	q2 = c2_tot_case1[i][2][0]->GetMean();
	q3 = c2_tot_case1[i][3][0]->GetMean();
	numerator = q0;
	denominator = sqrt((q1*q2)/q3);
	v2_tot_case1[i] = numerator/denominator;
	//case1 negative
	q0 = c2_neg_case1[i][0][0]->GetMean();
	q1 = c2_neg_case1[i][1][0]->GetMean();
	q2 = c2_neg_case1[i][2][0]->GetMean();
	q3 = c2_neg_case1[i][3][0]->GetMean();
	numerator = q0;
	denominator = sqrt((q1*q2)/q3);
	v2_neg_case1[i] = numerator/denominator;
	//case2 positive
	q0 = c2_pos_case2[i][0][0]->GetMean();
	q1 = c2_pos_case2[i][1][0]->GetMean();
	q2 = c2_pos_case2[i][2][0]->GetMean();
	q3 = c2_pos_case2[i][3][0]->GetMean();
	numerator = q0;
	denominator = sqrt((q1*q2)/q3);
	v2_pos_case2[i] = numerator/denominator;
	//case2 total
	q0 = c2_tot_case2[i][0][0]->GetMean();
	q1 = c2_tot_case2[i][1][0]->GetMean();
	q2 = c2_tot_case2[i][2][0]->GetMean();
	q3 = c2_tot_case2[i][3][0]->GetMean();
	numerator = q0;
	denominator = sqrt((q1*q2)/q3);
	v2_tot_case2[i] = numerator/denominator;
	//case2 negative
	q0 = c2_neg_case2[i][0][0]->GetMean();
	q1 = c2_neg_case2[i][1][0]->GetMean();
	q2 = c2_neg_case2[i][2][0]->GetMean();
	q3 = c2_neg_case2[i][3][0]->GetMean();
	numerator = q0;
	denominator = sqrt((q1*q2)/q3);
	v2_neg_case2[i] = numerator/denominator;
    }
    TGraph *gr_pos_case1 = new TGraph(5,x,v2_pos_case1);
    TGraph *gr_neg_case1 = new TGraph(5,x,v2_neg_case1);
    TGraph *gr_tot_case1 = new TGraph(5,x,v2_tot_case1);
    TGraph *gr_pos_case2 = new TGraph(5,x,v2_pos_case2);
    TGraph *gr_neg_case2 = new TGraph(5,x,v2_neg_case2);
    TGraph *gr_tot_case2 = new TGraph(5,x,v2_tot_case2);

    gr_pos_case1 -> SetName("positive tracks case1");
    gr_neg_case1 -> SetName("negative tracks case1");
    gr_tot_case1 -> SetName("total tracks case1");
    gr_pos_case1 -> SetTitle("positive tracks case1");
    gr_neg_case1 -> SetTitle("negative tracks case1");
    gr_tot_case1 -> SetTitle("total tracks case1");

    gr_pos_case2 -> SetName("positive tracks case2");
    gr_neg_case2 -> SetName("negative tracks case2");
    gr_tot_case2 -> SetName("total tracks case2");
    gr_pos_case2 -> SetTitle("positive tracks case2");
    gr_neg_case2 -> SetTitle("negative tracks case2");
    gr_tot_case2 -> SetTitle("total tracks case2");

    TCanvas* c1 = new TCanvas("c1","c1");
     c1->Divide(3,2,0,0);
    c1->cd(1);
    gr_pos_case1->Draw("A*");

    c1->cd(2);
    gr_neg_case1->Draw("A*");

    c1->cd(3);
    gr_tot_case1->Draw("A*");

    c1->cd(4);
    gr_pos_case2->Draw("A*");

    c1->cd(5);
    gr_neg_case2->Draw("A*");

    c1->cd(6);
    gr_tot_case2->Draw("A*");

    
}
