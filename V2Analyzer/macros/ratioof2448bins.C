#include "RiceStyle.h"

using namespace std;

void ratioof2448bins(){

	TFile *f;
	TH1D* c2_pos[5][2];
	TH1D* c2_neg[5][2];

	TH1D* ach_hist[5];
	double x[5];

	double v2_pos[5];
	double v2_neg[5];
	double v2_pos_24[5];
	double v2_neg_24[5];
	double v2_pos_48[5];
	double v2_neg_48[5];
	double v2_pos_ratio[5];
	double v2_neg_ratio[5];
	double v2_diff[5];
	double err_neg[5];
	double err_pos[5];
	double err_neg_24[5];
	double err_pos_24[5];
	double err_diff[5];
	double err_pos_ratio[5];
	double err_neg_ratio[5];
	double cmean;
	double v2_pos_sample[5][10];
	double v2_neg_sample[5][10];
	double v2_diff_sample[5][10];


	for (int n = 0; n < 10; ++n){
		f = new TFile(Form("../../../rootfiles/errcalc_v2Cumulant_24bins_pPb/leaveout%d.root",n+1));


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
			v2_pos_sample[i][n] = sqrt(cmean);

			cmean = c2_neg[i][0] -> GetMean();
			v2_neg_sample[i][n] = sqrt(cmean);

			v2_diff_sample[i][n] = v2_neg_sample[i][n] - v2_pos_sample[i][n];

		}

	}
	
	f = new TFile("../../../rootfiles/sampling_v2Cumulant_24bins_pPb/v2Cumulant_24bins_Merged.root");

	for (Int_t i = 0; i < 5; i++){
		ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

		c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
		c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));

		c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
		c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));
		
	}
	for(Int_t i=0; i<5; i++){

		x[i]=ach_hist[i]->GetMean();

//v2 positive
		cmean = c2_pos[i][0] -> GetMean();
		v2_pos[i] = sqrt(cmean);

//negative
		cmean = c2_neg[i][0] -> GetMean();
		v2_neg[i] = sqrt(cmean);

		//difference
		v2_diff[i] = v2_neg[i] - v2_pos[i];

//error bars
		double variance_pos = 0.0;
		double variance_neg = 0.0;
		double variance_diff = 0.0;
		for (int k = 0; k < 10; ++k)
		{
			variance_pos += (v2_pos_sample[i][k]-v2_pos[i])*(v2_pos_sample[i][k]-v2_pos[i]);
			variance_neg += (v2_neg_sample[i][k]-v2_neg[i])*(v2_neg_sample[i][k]-v2_neg[i]);
			variance_diff += (v2_diff_sample[i][k]-v2_diff[i])*(v2_diff_sample[i][k]-v2_diff[i]);
		}
		variance_pos *= 0.9;
		variance_neg *= 0.9;
		variance_diff *= 0.9;
		err_pos[i] = sqrt(variance_pos);
		err_neg[i] = sqrt(variance_neg);
		err_diff[i] = sqrt(variance_diff);

		v2_pos_24[i] = v2_pos[i];
		v2_neg_24[i] = v2_neg[i];
		err_pos_24[i] = err_pos[i];
		err_neg_24[i] = err_neg[i];


	}	


	TGraphErrors *gr_pos_24 = new TGraphErrors(5,x,v2_pos,NULL,err_pos);
	TGraphErrors *gr_neg_24 = new TGraphErrors(5,x,v2_neg,NULL,err_neg);
	TGraphErrors *gr_diff_24 = new TGraphErrors(5,x,v2_diff,NULL,err_diff);


    //Define a linear function
	TF1* fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.09, 0.09);
	fit1->SetLineColor(kRed);
	fit1->SetLineStyle(2);
	gr_diff_24->Fit(fit1);


	for (int n = 0; n < 10; ++n){
		f = new TFile(Form("../../../rootfiles/errcalc_v2Cumulant_48bins_pPb/leaveout%d.root",n+1));


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
			v2_pos_sample[i][n] = sqrt(cmean);

			cmean = c2_neg[i][0] -> GetMean();
			v2_neg_sample[i][n] = sqrt(cmean);

			v2_diff_sample[i][n] = v2_neg_sample[i][n] - v2_pos_sample[i][n];

		}

	}
	
	f = new TFile("../../../rootfiles/sampling_v2Cumulant_48bins_pPb/v2Cumulant_48bins_Merged.root");

	for (Int_t i = 0; i < 5; i++){
		ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

		c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
		c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));

		c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
		c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));
		
	}
	for(Int_t i=0; i<5; i++){

		x[i]=ach_hist[i]->GetMean();

//v2 positive
		cmean = c2_pos[i][0] -> GetMean();
		v2_pos[i] = sqrt(cmean);

//negative
		cmean = c2_neg[i][0] -> GetMean();
		v2_neg[i] = sqrt(cmean);

		//difference
		v2_diff[i] = v2_neg[i] - v2_pos[i];

//error bars
		double variance_pos = 0.0;
		double variance_neg = 0.0;
		double variance_diff = 0.0;
		for (int k = 0; k < 10; ++k)
		{
			variance_pos += (v2_pos_sample[i][k]-v2_pos[i])*(v2_pos_sample[i][k]-v2_pos[i]);
			variance_neg += (v2_neg_sample[i][k]-v2_neg[i])*(v2_neg_sample[i][k]-v2_neg[i]);
			variance_diff += (v2_diff_sample[i][k]-v2_diff[i])*(v2_diff_sample[i][k]-v2_diff[i]);
		}
		variance_pos *= 0.9;
		variance_neg *= 0.9;
		variance_diff *= 0.9;
		err_pos[i] = sqrt(variance_pos);
		err_neg[i] = sqrt(variance_neg);
		err_diff[i] = sqrt(variance_diff);

		v2_pos_48[i] = v2_pos[i];
		v2_neg_48[i] = v2_neg[i];

		v2_pos_ratio[i] = v2_pos_24[i]/v2_pos_48[i];
		v2_neg_ratio[i] = v2_neg_24[i]/v2_neg_48[i];

		double variance = 0.0;
		variance += ((v2_pos_24[i]*v2_pos_24[i])/(v2_pos_48[i]*v2_pos_48[i]*v2_pos_48[i]*v2_pos_48[i]))*(err_pos[i]*err_pos[i]);
		variance += (err_pos_24[i]*err_pos_24[i])/(v2_pos_48[i]*v2_pos_48[i]);
		err_pos_ratio[i] = sqrt(variance);

		variance = 0.0;
		variance += ((v2_neg_24[i]*v2_neg_24[i])/(v2_neg_48[i]*v2_neg_48[i]*v2_neg_48[i]*v2_neg_48[i]))*(err_neg[i]*err_neg[i]);
		variance += (err_neg_24[i]*err_neg_24[i])/(v2_neg_48[i]*v2_neg_48[i]);
		err_neg_ratio[i] = sqrt(variance);



	}

	TGraphErrors *gr_pos_48 = new TGraphErrors(5,x,v2_pos,NULL,err_pos);
	TGraphErrors *gr_neg_48 = new TGraphErrors(5,x,v2_neg,NULL,err_neg);
	TGraphErrors *gr_diff_48 = new TGraphErrors(5,x,v2_diff,NULL,err_diff);


    //Define a linear function
	TF1* fit2 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.09, 0.09);
	fit2->SetLineColor(kRed);
	fit2->SetLineStyle(2);
	gr_diff_48->Fit(fit2);


	TH1D* base = new TH1D("base","base",100,-0.1,0.1);
	base->GetYaxis()->SetRangeUser(0.065,	0.075);
	base->GetXaxis()->SetTitle("Observed A_{ch}");
	base->GetYaxis()->SetTitle("v_{2}");
	TCanvas* c3 = new TCanvas("c3","c3",1,1,1200,600);
	c3->Divide(2,1,0.01,0.01);

	gr_neg_24 -> SetMarkerStyle(20);
	gr_neg_24 -> SetMarkerColor(kBlue);
	gr_pos_24 -> SetMarkerStyle(34);
	gr_pos_24 -> SetMarkerColor(kRed);
	gr_pos_24 -> SetFillStyle(0);
	gr_pos_24 -> SetFillColor(0);
	gr_neg_24 -> SetFillStyle(0);
	gr_neg_24 -> SetFillColor(0);

	gr_neg_48 -> SetMarkerStyle(20);
	gr_neg_48 -> SetMarkerColor(kYellow);
	gr_pos_48 -> SetMarkerStyle(34);
	gr_pos_48 -> SetMarkerColor(8);
	gr_pos_48 -> SetFillStyle(0);
	gr_pos_48 -> SetFillColor(0);
	gr_neg_48 -> SetFillStyle(0);
	gr_neg_48 -> SetFillColor(0);

	base->GetYaxis()->SetTitleOffset(1.4);
	base->GetXaxis()->SetTitleOffset(1.1);
	base->GetYaxis()->SetNdivisions(505); 
	base->GetXaxis()->SetNdivisions(505); 
	base->SetStats(0);
	gStyle->SetOptTitle(0);

	TLatex* text_a = makeLatex("p-Pb #sqrt{s_{NN}}=5.02TeV",0.15,0.82) ;
	TLatex* text_b = makeLatex("N_{trk}^{offline} [185, 260)",0.15,0.74) ;
	TLatex* text_c = makeLatex("0.3 < p_{T} < 3.0 GeV/c",0.15,0.66) ;
	TLatex* text_d = makeLatex("Cumulant Method",0.15,0.58) ;


	TLegend* leg = new TLegend(.60,.70,.80,.85);
	leg->SetLineColor(kWhite);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->AddEntry(gr_pos_24, "pos 24 bins","p");
	leg->AddEntry(gr_neg_24 ,"neg 24 bins","p");
	leg->AddEntry(gr_pos_48 ,"pos 48 bins","p");
	leg->AddEntry(gr_neg_48 ,"neg 48 bins","p");


	
	c3->cd(1);
	base->Draw("");
	gr_pos_24->Draw("PSame");
	gr_neg_24->Draw("PSame");
	gr_pos_48->Draw("PSame");
	gr_neg_48->Draw("PSame");

	text_a->DrawClone("Same");
	text_b->DrawClone("Same");
	text_c->DrawClone("Same");
	text_d->DrawClone("Same");

	leg->DrawClone("Same");






	TH1D* base2 = new TH1D("base2","base2",100,-0.1,0.1);
	base2->GetYaxis()->SetRangeUser(0.98,1.02);
	base2->GetXaxis()->SetTitle("Observed A_{ch}");
	base2->GetYaxis()->SetTitle("v_{2}(24bins) / v_{2}(48bins)");
	base2->GetYaxis()->SetTitleOffset(1.4);
	base2->GetXaxis()->SetTitleOffset(1.1);
	base2->GetYaxis()->SetNdivisions(506); 
	base2->GetXaxis()->SetNdivisions(505); 
	base2->SetStats(0);

	TGraphErrors *gr_pos_ratio = new TGraphErrors(5,x,v2_pos_ratio,NULL,err_pos_ratio);
	TGraphErrors *gr_neg_ratio = new TGraphErrors(5,x,v2_neg_ratio,NULL,err_neg_ratio);


	gr_pos_ratio -> SetMarkerStyle(20);
	gr_pos_ratio -> SetMarkerColor(kBlue);
	gr_pos_ratio -> SetFillStyle(0);
	gr_pos_ratio -> SetFillColor(0);

	gr_neg_ratio -> SetMarkerStyle(34);
	gr_neg_ratio -> SetMarkerColor(kRed);
	gr_neg_ratio -> SetFillStyle(0);
	gr_neg_ratio -> SetFillColor(0);

	TLegend* leg2 = new TLegend(.60,.70,.80,.85);
	leg2->SetLineColor(kWhite);
	leg2->SetFillColor(0);
	leg2->SetFillStyle(0);
	leg2->AddEntry(gr_pos_ratio, "pos ratio","p");
	leg2->AddEntry(gr_neg_ratio ,"neg ratio","p");


	c3->cd(2);
	base2->Draw("");
	gr_pos_ratio->Draw("PSame");
	gr_neg_ratio->Draw("PSame");
	leg2->DrawClone("Same");

}
