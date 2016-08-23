#include "RiceStyle.h"

using namespace std;

void slopevscentrality_v2_v3_superposition(){

	TFile *f;
	const int NAchBins = 7;
	double correctionlist[6] = {0.5195, 0.6754, 0.7080, 0.7381, 0.7507, 0.7542};

	TH1D* c2_pos[NAchBins][2];
	TH1D* c2_neg[NAchBins][2];
	TH1D* ach_hist[NAchBins];
	TGraphErrors* gr_diff;
	TF1* fit1;

	double x_centrality[6] = {35, 45, 55, 65, 75, 85};
	double x_v3_cent[4] = {35, 45, 55, 65};

	double v2_PbPb_centrality_yval[6];
	double v2_PbPb_centrality_ystaterr[6];
	double v2_statErr[6];

	double v3_PbPb_centrality_yval[6];
	double v3_PbPb_centrality_ystaterr[6];
	double v3_statErr[6];


	double variance_pos = 0.0;
	double variance_neg = 0.0;
	double variance_diff = 0.0;
	double err_neg[NAchBins];
	double err_pos[NAchBins];
	double err_diff[NAchBins];
	double cmean;
	double errmean;
	double sum;

	int low[6] = {30,40,50,60,70,80};
	int upp[6] = {40,50,60,70,80,90};



	for (int n = 0; n <6; ++n)
	{
		
		f = new TFile(Form("../../../rootfiles/crosscheck/PbPb/v2/%d_%d/Merged.root",low[n],upp[n]));

		for (Int_t i = 0; i < NAchBins; i++){
			ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

			c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
			c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));


			c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
			c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));

		}

		double x[NAchBins];
		double v2_pos[NAchBins];
		double v2_neg[NAchBins];
		double v2_diff[NAchBins];
		double r;
		for(Int_t i=0; i<NAchBins; i++){


			x[i]=ach_hist[i]->GetMean();
			x[i] *= correctionlist[n];

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


		gr_diff = new TGraphErrors(NAchBins,x,v2_diff,NULL, err_diff);
		
		fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.2, 0.2);
		gr_diff->Fit(fit1);
		r = fit1->GetParameter(1);
		v2_PbPb_centrality_ystaterr[n] = fit1->GetParError(1);
		cout << "v2err: " << v2_PbPb_centrality_ystaterr[n] << endl;
		v2_PbPb_centrality_yval[n] = r;

	}


	TGraphErrors* v2_PbPbslope_centrality = new TGraphErrors(6,x_centrality,v2_PbPb_centrality_yval,NULL,v2_PbPb_centrality_ystaterr);



	for (int n = 0; n <4; ++n)
	{
		
		f = new TFile(Form("../../../rootfiles/crosscheck/PbPb/v3/%d_%d/Merged.root",low[n],upp[n]));

		for (Int_t i = 0; i < NAchBins; i++){
			ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

			c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
			c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));


			c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
			c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));

		}

		double x[NAchBins];
		double v2_pos[NAchBins];
		double v2_neg[NAchBins];
		double v2_diff[NAchBins];
		double r;
		for(Int_t i=0; i<NAchBins; i++){


			x[i]=ach_hist[i]->GetMean();
			x[i] *= correctionlist[n];

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


		gr_diff = new TGraphErrors(NAchBins,x,v2_diff,NULL, err_diff);
		fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.2, 0.2);
		gr_diff->Fit(fit1);
		r = fit1->GetParameter(1);
		v3_PbPb_centrality_ystaterr[n] = fit1->GetParError(1);
		cout << "v3err: " << v3_PbPb_centrality_ystaterr[n] << endl;

		v3_PbPb_centrality_yval[n] = r;
		cout << r << endl;

	}

	TGraphErrors* v3_PbPbslope_centrality = new TGraphErrors(4,x_v3_cent,v3_PbPb_centrality_yval,NULL,v3_PbPb_centrality_ystaterr);
	TFile *rebinned = new TFile("~/Summer2016/root_forgraphs/figure5.root","RECREATE");
	v2_PbPbslope_centrality->Write();
	v3_PbPbslope_centrality->Write();
	rebinned->Close();



	v2_PbPbslope_centrality -> SetMarkerStyle(24);
	v2_PbPbslope_centrality -> SetMarkerColor(kBlue);
	v2_PbPbslope_centrality -> SetLineColor(kBlue);
	v3_PbPbslope_centrality -> SetMarkerStyle(25);
	v3_PbPbslope_centrality -> SetMarkerColor(kRed);
	v3_PbPbslope_centrality -> SetLineColor(kRed);



	gStyle->SetLegendFont(42);	gStyle->SetOptTitle(0);
	TH1D* base = new TH1D("base","base",1,0,100);
	base->GetYaxis()->SetRangeUser(0.00,0.5);
	base->GetXaxis()->SetTitle("Centrality(%)");
	base->GetYaxis()->SetTitle("Slope parameter(normalized v_{n})");
	base->GetXaxis()->CenterTitle();
	base->GetYaxis()->CenterTitle();
	base->SetTitleSize  (0.040,"X");
	base->SetTitleOffset(1.4,"X");
	base->SetTitleFont  (42,"X");
	base->SetLabelOffset(0.006,"X");
	base->SetLabelSize  (0.040,"X");
	base->SetLabelFont  (42   ,"X");

	base->SetTitleSize  (0.040,"Y");
	base->SetTitleOffset(1.6,"Y");
	base->SetTitleFont  (42,"Y");
	base->SetLabelOffset(0.006,"Y");
	base->SetLabelSize  (0.040,"Y");
	base->SetLabelFont  (42   ,"Y");
	base->SetLineWidth(0);

	TCanvas* c3 = MakeCanvas("c3","c3");
	TLatex* text_a = makeLatex("CMS PbPb #sqrt{s_{NN}}=5.02TeV",0.25,0.84) ;
	TLatex* text_b = makeLatex("185 #leq N_{trk}^{offline} < 260",0.25,0.80) ;
	TLatex* text_c = makeLatex("0.3 < p_{T} < 3 GeV/c",0.25,0.78) ;
	TLatex* text_d = makeLatex("|#Delta#eta| > 2",0.25,0.72) ;

	text_a->SetTextFont(42);
	text_b->SetTextFont(42);
	text_c->SetTextFont(42);
	text_d->SetTextFont(42);


	TLegend* leg = new TLegend(0.80,0.78,0.98,.88);
	leg->SetLineColor(kWhite);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->AddEntry(v2_PbPbslope_centrality, "v2","p");	
	leg->AddEntry(v3_PbPbslope_centrality, "v3","p");


	//leg->AddEntry(gr_neg, "neg","p");

	
	c3->cd();
	base->Draw("");
	text_a->Draw("");
	text_c->Draw("");
	text_d->Draw("");

	v2_PbPbslope_centrality->Draw("PSame");
	v3_PbPbslope_centrality->Draw("PSame");



	leg->DrawClone("PSame");
	//SaveCanvas(c3,"pics","slope_vs_cent_v2_v3_superposition_PbPb_ver3");


    //Define a linear function





}
