#include "RiceStyle.h"

using namespace std;

void slopevscentrality(){
	TFile *f;
	TH1D* c2_pos[5][2];
	TH1D* c2_neg[5][2];
	TH1D* ach_hist[5];
	TH1D* cbinHist;
	TGraphErrors* gr_diff;
	TF1* fit1;

	double x_centrality[6] = {35, 45, 55, 65, 75, 85};
	double y_slope[6];
	double statErr[6];

	double v2_pos_sample[5][10][6];
	double v2_neg_sample[5][10][6];
	double v2_diff_sample[5][10][6];
	double variance_pos = 0.0;
	double variance_neg = 0.0;
	double variance_diff = 0.0;
	double err_neg[5];
	double err_pos[5];
	double err_diff[5];
	double cmean;

	for(int k = 0;k < 6;k++){
		for (int n = 0; n < 10; ++n){

			f = new TFile(Form("../../../rootfiles/errcalc_slopevscentrality/bin%d/leaveout%d.root",k+1,n+1));

			for (Int_t i = 0; i < 5; i++){
				ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

				c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
				c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));

				c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
				c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));

			}
			for(Int_t i=0; i<5; i++){

//positive
				cmean = c2_pos[i][0] -> GetMean();
				v2_pos_sample[i][n][k] = sqrt(cmean);

				cmean = c2_neg[i][0] -> GetMean();
				v2_neg_sample[i][n][k] = sqrt(cmean);

				v2_diff_sample[i][n][k] = v2_neg_sample[i][n][k] - v2_pos_sample[i][n][k];

			}

		}

	}




	for (int n = 0; n <6; ++n)
	{

		f = new TFile(Form("../../../rootfiles/slope_vs_centrality/PbPb502_%d.root",n+1));
		for (Int_t i = 0; i < 5; i++){
			ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

			c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
			c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));


			c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
			c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));

		}

		cbinHist = (TH1D*)f->Get("demo/cbinHist");
		double x[5];
		double v2_pos[5];
		double v2_neg[5];
		double v2_diff[5];
		double r;
		for(Int_t i=0; i<5; i++){

			x[i]=ach_hist[i]->GetMean();

			cmean = c2_pos[i][0] -> GetMean();
			v2_pos[i] = sqrt(cmean);

			cmean = c2_neg[i][0] -> GetMean();
			v2_neg[i] = sqrt(cmean);

			v2_diff[i] = v2_neg[i] - v2_pos[i];


//error calculation
			variance_pos = 0.0;
			variance_neg = 0.0;
			variance_diff = 0.0;
			
			for (int k = 0; k < 10; ++k)
			{
				variance_pos += (v2_pos_sample[i][k][n]-v2_pos[i])*(v2_pos_sample[i][k][n]-v2_pos[i]);
				variance_neg += (v2_neg_sample[i][k][n]-v2_neg[i])*(v2_neg_sample[i][k][n]-v2_neg[i]);
				variance_diff += (v2_diff_sample[i][k][n]-v2_diff[i])*(v2_diff_sample[i][k][n]-v2_diff[i]);
			}
			variance_pos *= 0.9;
			variance_neg *= 0.9;
			variance_diff *= 0.9;
			err_pos[i] = sqrt(variance_pos);
			err_neg[i] = sqrt(variance_neg);

			variance_diff = err_pos[i]*err_pos[i]+err_neg[i]*err_neg[i];

			err_diff[i] = sqrt(variance_diff);


		}

		gr_diff = new TGraphErrors(5,x,v2_diff,NULL, err_diff);
		fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.09, 0.09);
		gr_diff->Fit(fit1);
		r = fit1->GetParameter(1);
		statErr[n] = fit1->GetParError(1);
		y_slope[n] = r;
		cout << y_slope[n] << endl;

	}

	double x_alice[] = {5,15,25,35,45,55,65,75};
	double y_alice[] = { 0.0188127, 0.0252774, 0.0290478, 0.0315681, 0.0313678, 0.0334533, 0.0326948, 0.027709 };
	double alice_statErrors[] = { 0.00276672, 0.00491256, 0.00542907, 0.00499819, 0.00427076, 0.00421142, 0.00436631, 0.00480683 };
	double alice_sysminus[] = { 0.003345731066792428, 0.005524736668946313, 0.006157316616294797, 0.00591162859559022, 0.0052989413797474684, 0.0053784097301432885, 0.0054547376184835876, 0.005548288155719744 };
	double alice_sysplus[] = { 0.003345731066792428, 0.005524736668946313, 0.006157316616294797, 0.00591162859559022, 0.0052989413797474684, 0.0053784097301432885, 0.0054547376184835876, 0.005548288155719744 };
	double xsysalice[] = {1,1,1,1,1,1,1,1};


	double x_star[] = {2.5,7.5,15.0,25.0,35.0,45.0,55.0,65.0,75.0};
	double y_star[] = {-0.033529,0.001979,0.015917,0.028232,0.031986,0.026516,0.028016,0.012459,-0.02195};
	double star_statErrors[] = { 0.0010554, 0.00701, 0.003874, 0.003091, 0.002903, 0.002921, 0.003657, 0.005119, 0.009593 };
	double star_sysminus[] = { 2.156594920238847, 1.1474282374074642, 0.41413973487218053, 0.40721102637330436, 0.46464817873311415, 0.48750025641018896, 1.2743975557101481, 0.6065696744810114, 0.9645708786812922 };
	double star_sysplus[] = { 3.152323796820371, 1.1348034014753392, 0.6881948851887814, 0.3091, 0.3775553601791398, 0.6362180836788593, 0.39244649316817704, 1.060086081410373, 4.931994052105091 };
	double xsysstar[] = {1,1,1,1,1,1,1,1,1};

	for(i=0;i<9;i++){
		star_sysminus[i]/=100;
		star_sysplus[i]/=100;
	}

	TGraphErrors* slopevscent = new TGraphErrors(6,x_centrality,y_slope,NULL,statErr);
	TGraphErrors* ALICE = new TGraphErrors(8,x_alice,y_alice,NULL,alice_statErrors);
	TGraphErrors* STAR = new TGraphErrors(9,x_star,y_star,NULL,star_statErrors);
	TGraphAsymmErrors* ALICE_sys = new TGraphAsymmErrors(8, x_alice, y_alice, xsysalice, xsysalice, alice_sysminus, alice_sysplus);
	TGraphAsymmErrors* STAR_sys = new TGraphAsymmErrors(9, x_star, y_star, xsysstar, xsysstar, star_sysminus, star_sysplus);


	slopevscent -> SetMarkerStyle(20);
	slopevscent -> SetMarkerColor(kBlack);

	ALICE -> SetMarkerStyle(28);
	ALICE -> SetMarkerColor(kRed);

	STAR -> SetMarkerStyle(22);
	STAR -> SetMarkerColor(kBlue);

	TH1D* base = new TH1D("base","base",100,0,100);
	base->GetYaxis()->SetRangeUser(0.00,0.06);
	base->GetXaxis()->SetTitle("Centrality(%)");
	base->GetYaxis()->SetTitle("slope parameter");
	base->SetStats(0);
	base->GetYaxis()->SetTitleOffset(1.4);
	base->GetXaxis()->SetTitleOffset(1.1);


	TCanvas* c3 = new TCanvas("c3","c3",1,1,600,600);

	slopevscent->SetFillStyle(0);
	slopevscent->SetFillColor(0);
	slopevscent->SetFillStyle(0);
	slopevscent->SetFillColor(0);

	gStyle->SetOptTitle(0);


	TLegend* leg = new TLegend(.45,.65,.85,.85);
	leg->SetLineColor(kWhite);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->AddEntry(slopevscent, "CMS, Pb-Pb at #sqrt{s_{NN}}=5.02TeV","p");
	leg->AddEntry(ALICE, "ALICE, Pb-Pb at #sqrt{s_{NN}}=2.76TeV","p");
	leg->AddEntry(STAR, "STAR, Au-Au at #sqrt{s_{NN}}=200GeV","p");

	//leg->AddEntry(gr_neg, "neg","p");

	
	c3->cd();
	base->Draw("");
	slopevscent->Draw("PSame");
	ALICE->Draw("PSame");
	STAR->Draw("PSame");


	ALICE_sys->SetFillColor(2);
	ALICE_sys->SetFillStyle(3001);

//	ALICE_sys->Draw("2Same");
	STAR_sys->SetFillColor(6);
	STAR_sys->SetFillStyle(3001);
//	STAR_sys->Draw("2Same");

	leg->DrawClone("PSame");


    //Define a linear function





}
