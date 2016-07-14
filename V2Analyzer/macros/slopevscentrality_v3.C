#include "RiceStyle.h"

using namespace std;

void slopevscentrality_v3(){
	TFile *f;
	TH1D* c2_pos[5][2];
	TH1D* c2_neg[5][2];
	TH1D* ach_hist[5];
	TH1D* cbinHist;
	TGraphErrors* gr_diff;
	TF1* fit1;

	double x_centrality[6] = {35, 45, 55, 65, 75, 85};
	double PbPb_centrality_yval[6];
	double PbPb_centrality_ystaterr[6];
	double statErr[6];


	double variance_pos = 0.0;
	double variance_neg = 0.0;
	double variance_diff = 0.0;
	double err_neg[5];
	double err_pos[5];
	double err_diff[5];
	double cmean;
	double errmean;
	double sum;

	for (int n = 0; n <6; ++n)
	{
		
		f = new TFile(Form("../../../rootfiles/slope_vs_centrality_v3/%d/cent_Merged_%d.root",n,n));

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
		double r;
		for(Int_t i=0; i<5; i++){


			x[i]=ach_hist[i]->GetMean();

			cmean = c2_pos[i][0] -> GetMean();
			v2_pos[i] = sqrt(cmean);
			errmean = c2_pos[i][0] -> GetMeanError();
			variance_pos = (errmean*errmean)/(4*cmean);


			cmean = c2_neg[i][0] -> GetMean();
			v2_neg[i] = sqrt(cmean);
			errmean = c2_neg[i][0] -> GetMeanError();
			variance_neg = (errmean*errmean)/(4*cmean);

			v2_diff[i] = (v2_neg[i] - v2_pos[i])/(v2_neg[i] + v2_pos[i]);

			sum = v2_pos[i] + v2_neg[i];

			variance_diff = (4*v2_neg[i]*v2_neg[i]*variance_pos)/(sum*sum*sum*sum)+(4*v2_pos[i]*v2_pos[i]*variance_neg)/(sum*sum*sum*sum);


//error calculation

			err_pos[i] = sqrt(variance_pos);
			err_neg[i] = sqrt(variance_neg);
			err_diff[i] = sqrt(variance_diff);

		}


		gr_diff = new TGraphErrors(5,x,v2_diff,NULL, err_diff);
		fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.09, 0.09);
		gr_diff->Fit(fit1);
		r = fit1->GetParameter(1);
		PbPb_centrality_ystaterr[n] = fit1->GetParError(1);
		PbPb_centrality_yval[n] = r;
		cout << r << endl;

	}

	TGraphErrors* PbPbslope_centrality = new TGraphErrors(6,x_centrality,PbPb_centrality_yval,NULL,PbPb_centrality_ystaterr);
	PbPbslope_centrality -> SetMarkerStyle(25);
	PbPbslope_centrality -> SetMarkerColor(kRed);


	TH1D* base = new TH1D("base","base",100,0,100);
	base->GetYaxis()->SetRangeUser(0.00,0.4);
	base->GetXaxis()->SetTitle("Centrality(%)");
	base->GetYaxis()->SetTitle("slope parameter(normalized v3)");
	base->SetStats(0);
	base->GetYaxis()->SetTitleOffset(1.4);
	base->GetXaxis()->SetTitleOffset(1.1);


	TCanvas* c3 = new TCanvas("c3","c3",1,1,600,600);

	PbPbslope_centrality->SetFillStyle(0);
	PbPbslope_centrality->SetFillColor(0);


	gStyle->SetOptTitle(0);


	TLegend* leg = new TLegend(.45,.65,.85,.85);
	leg->SetLineColor(kWhite);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->AddEntry(PbPbslope_centrality, "CMS, Pb-Pb at #sqrt{s_{NN}}=5.02TeV","p");


	//leg->AddEntry(gr_neg, "neg","p");

	
	c3->cd();
	base->Draw("");
	PbPbslope_centrality->Draw("PSame");


	leg->DrawClone("PSame");


    //Define a linear function





}
