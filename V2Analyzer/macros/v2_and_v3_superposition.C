#include "RiceStyle.h"

using namespace std;

void v2_and_v3_superposition(){

	TFile *f;
	const int NAchBins = 5;

	TH1D* c2_pos[NAchBins][2];
	TH1D* c2_neg[NAchBins][2];
	TH1D* ach_hist[NAchBins];
	double v2_pos[NAchBins];
	double v2_neg[NAchBins];
	double v2_diff[NAchBins];
	double err_neg[NAchBins];
	double err_pos[NAchBins];
	double err_diff[NAchBins];
	double cmean;
	double errmean;
	double sum;
	double variance_pos;
	double variance_neg;
	double variance_diff;

	double x_v2[NAchBins];
	double y_v2[NAchBins];
	double err_v2[NAchBins];

	double x_v3[NAchBins];
	double y_v3[NAchBins];
	double err_v3[NAchBins];


	f = new TFile("../../../rootfiles/slope_vs_centrality/PbPb502_1.root");

	for (Int_t i = 0; i < NAchBins; i++){
		ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

		c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
		c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));

		c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
		c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));
		
	}
	for(Int_t i=0; i<NAchBins; i++){

		x_v2[i]=ach_hist[i]->GetMean();

//v2 positive
		cmean = c2_pos[i][0] -> GetMean();
		v2_pos[i] = sqrt(cmean);

		errmean = c2_pos[i][0] -> GetMeanError();
		variance_pos = (errmean*errmean)/(4*cmean);

//negative
		cmean = c2_neg[i][0] -> GetMean();
		v2_neg[i] = sqrt(cmean);

		errmean = c2_neg[i][0] -> GetMeanError();
		variance_neg = (errmean*errmean)/(4*cmean);

		//difference
		v2_diff[i] = (v2_neg[i] - v2_pos[i])/(v2_neg[i] + v2_pos[i]);
		y_v2[i] = v2_diff[i];

		sum = v2_pos[i] + v2_neg[i];

		variance_diff = (4*v2_neg[i]*v2_neg[i]*variance_pos)/(sum*sum*sum*sum)+(4*v2_pos[i]*v2_pos[i]*variance_neg)/(sum*sum*sum*sum);


	//error bars

		err_pos[i] = sqrt(variance_pos);
		err_neg[i] = sqrt(variance_neg);
		err_diff[i] = sqrt(variance_diff);
		err_v2[i] = err_diff[i];

	}

	f = new TFile("../../../rootfiles/v3Cumulant_PbPb_cent_30_40/Merged.root");

	for (Int_t i = 0; i < NAchBins; i++){
		ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

		c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
		c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));

		c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
		c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));
		
	}
	for(Int_t i=0; i<NAchBins; i++){

		x_v3[i]=ach_hist[i]->GetMean();

//v2 positive
		cmean = c2_pos[i][0] -> GetMean();
		v2_pos[i] = sqrt(cmean);

		errmean = c2_pos[i][0] -> GetMeanError();
		variance_pos = (errmean*errmean)/(4*cmean);

//negative
		cmean = c2_neg[i][0] -> GetMean();
		v2_neg[i] = sqrt(cmean);

		errmean = c2_neg[i][0] -> GetMeanError();
		variance_neg = (errmean*errmean)/(4*cmean);

		//difference
		v2_diff[i] = (v2_neg[i] - v2_pos[i])/(v2_neg[i] + v2_pos[i]);
		y_v3[i] = v2_diff[i];

		sum = v2_pos[i] + v2_neg[i];

		variance_diff = (4*v2_neg[i]*v2_neg[i]*variance_pos)/(sum*sum*sum*sum)+(4*v2_pos[i]*v2_pos[i]*variance_neg)/(sum*sum*sum*sum);


	//error bars

		err_pos[i] = sqrt(variance_pos);
		err_neg[i] = sqrt(variance_neg);
		err_diff[i] = sqrt(variance_diff);
		err_v3[i] = err_diff[i];

	}



	

	TH1D* base = new TH1D("base","base",100,-0.1,0.1);
	base->GetYaxis()->SetRangeUser(-0.03, 0.06);
	base->GetXaxis()->SetTitle("Observed A_{ch}");
	base->GetYaxis()->SetTitle("#frac{v_{n}(-) - v_{n}(+)}{v_{n}(-) + v_{n}(+)}");


	TGraphErrors *gr_v2_diff = new TGraphErrors(5,x_v2,y_v2,NULL,err_v2);
	TGraphErrors *gr_v3_diff = new TGraphErrors(5,x_v3,y_v3,NULL,err_v3);

    //Define a linear function
	TF1* fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.09, 0.09);
	fit1->SetLineColor(kBlue);
	fit1->SetLineStyle(2);
	gr_v2_diff->Fit(fit1);

	TF1* fit2 = new TF1("Linear fitting case 2", "[0]+x*[1]", -0.09, 0.09);
	fit2->SetLineColor(kRed);
	fit2->SetLineStyle(2);
	gr_v3_diff->Fit(fit2);

 //   TCanvas* c1 = new TCanvas("c1","c1");
 //   TCanvas* c2 = new TCanvas("c2","c2");
	TCanvas* c3 = MakeCanvas("c3","c3");


	gr_v2_diff -> SetMarkerStyle(20);
	gr_v2_diff -> SetMarkerColor(kBlue);
	gr_v3_diff -> SetMarkerStyle(34);
	gr_v3_diff -> SetMarkerColor(kRed);
	gr_v2_diff->SetFillStyle(0);
	gr_v2_diff->SetFillColor(0);
	gr_v3_diff->SetFillStyle(0);
	gr_v3_diff->SetFillColor(0);

	gStyle->SetLegendFont(42);	gStyle->SetOptTitle(0);

	TH1D* base = new TH1D("base","base",1,-0.1,0.1);
	base->GetYaxis()->SetRangeUser(-0.03,0.03);
	base->GetXaxis()->SetTitle("Observed A_{ch}");
	base->GetYaxis()->SetTitle("normalized #Deltav_{n}");
	base->GetXaxis()->CenterTitle();
	base->GetYaxis()->CenterTitle();
	base->SetTitleSize  (0.040,"X");
	base->SetTitleOffset(1.4,"X");
	base->SetTitleFont  (42,"X");
	base->SetLabelOffset(0.006,"X");
	base->SetLabelSize  (0.040,"X");
	base->SetLabelFont  (42   ,"X");

	base->SetTitleSize  (0.040,"Y");
	base->SetTitleOffset(2.0,"Y");
	base->SetTitleFont  (42,"Y");
	base->SetLabelOffset(0.006,"Y");
	base->SetLabelSize  (0.040,"Y");
	base->SetLabelFont  (42   ,"Y");
	base->SetLineWidth(0);
	TLatex* text1 = makeLatex(Form("slope normalized v_{2} = %.3f #pm %.3f",fit1->GetParameter(1),fit1->GetParError(1)),0.45,0.30) ;
	TLatex* text2 = makeLatex(Form("slope normalized v_{3} = %.3f #pm %.3f",fit2->GetParameter(1),fit2->GetParError(1)),0.45,0.25) ;
	TLatex* text3 = makeLatex("30-40%" ,0.45,0.20) ;
	text1->SetTextFont(42);
	text2->SetTextFont(42);
	text3->SetTextFont(42);



	TLegend* leg = new TLegend(.25,.76,.48,.88);


	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->AddEntry(gr_v2_diff, "PbPb v2","p");
	leg->AddEntry(gr_v3_diff, "PbPb v3","p");
	

	c3->cd();
	
	base->Draw("");
	gr_v2_diff->Draw("PSame");
	gr_v3_diff->Draw("PSame");
	leg->DrawClone("Same");




	text1->DrawClone("Same");
	fit1->DrawClone("Same");
	text2->DrawClone("Same");
	fit2->DrawClone("Same");
	text3->DrawClone("Same");

	TF1 *fa1 = new TF1("fa1","0",-10,10); 
	fa1->SetLineColor(kBlack);
	fa1->SetLineWidth(1);
	fa1->DrawClone("Same");
	SaveCanvas(c3,"pics","v2v3_comparison");



}
