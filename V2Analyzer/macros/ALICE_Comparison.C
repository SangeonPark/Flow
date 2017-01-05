#include "RiceStyle.h"
using namespace std;

void ALICE_Comparison(){

	TFile *f = new TFile("~/Summer2016/rootfiles/FinalResult_0104/ALICE_Merged.root");


	const int NAchBins = 7;
	const double correction = 0.731;

	TH1D* c2_pos[NAchBins][2];
	TH1D* c2_neg[NAchBins][2];

	TH1D* ach_hist[NAchBins];
	double x[NAchBins];
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


	double x_alice[8] = {-0.07,-0.05,-0.03,-0.01,0.01,0.03,0.05,0.07};
	double v2_pos_alice[8] = {0.0995,0.0985+0.0005/4,0.098+0.0005/4,0.0975+0.0005*2/3,0.0975+0.0005/6,0.0975,0.097+0.0005/2,0.097+0.0005/2+0.0001};
	double v2_neg_alice[8] = {0.097-0.0005/5,0.097+0.0005/4,0.097+0.0005/2,0.0975,0.0975+0.0005/2,0.098+0.0005/4,0.0985+0.0001,0.0985+0.0005*2/3};
	double v2_diff_alice[8];
	for (int i = 0; i < 8; ++i)
	{
		v2_diff_alice[i] = (v2_neg_alice[i]-v2_pos_alice[i])/(v2_neg_alice[i]+v2_pos_alice[i]);


	}
	

	double x[NAchBins];
	double v2_pos[NAchBins];
	double v2_neg[NAchBins];
	double err_pos[NAchBins];
	double err_neg[NAchBins];
	double v2_diff[NAchBins];
	double err_diff[NAchBins];
	for (Int_t i = 0; i < NAchBins; i++){
		ach_hist[i] = (TH1D*)f->Get(Form("demo_n3/ach_%d",i+1));
		c2_pos[i][0] = (TH1D*)f->Get(Form("demo_n3/c2pos_%d_cos",i));
		c2_pos[i][1] = (TH1D*)f->Get(Form("demo_n3/c2pos_%d_sin",i));
		c2_neg[i][0] = (TH1D*)f->Get(Form("demo_n3/c2neg_%d_cos",i));
		c2_neg[i][1] = (TH1D*)f->Get(Form("demo_n3/c2neg_%d_sin",i));
		
	}
	for(Int_t i=0; i<NAchBins; i++){

		x[i]=ach_hist[i]->GetMean();
		x[i] *= correction; 

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
		sum = v2_pos[i] + v2_neg[i];
		variance_diff = (4*v2_neg[i]*v2_neg[i]*variance_pos)/(sum*sum*sum*sum)+(4*v2_pos[i]*v2_pos[i]*variance_neg)/(sum*sum*sum*sum);

	//error bars
		err_pos[i] = sqrt(variance_pos);
		err_neg[i] = sqrt(variance_neg);
		err_diff[i] = sqrt(variance_diff);


	}


	gStyle->SetLegendFont(42);
	TH1D* base = new TH1D("base","base",1,-0.2,0.2);
	//pPb
	base->GetYaxis()->SetRangeUser(0.10, 0.11);
	base->GetXaxis()->SetTitle("Observed A_{ch}");
	base->GetYaxis()->SetTitle("v_{2}{SP}");
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

	TH1D* base2 = new TH1D("base2","base2",1,-0.2,0.2);
	base2->GetYaxis()->SetRangeUser(-0.05, 0.05);
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

	cout << v2_pos[0] << endl;


	TGraphErrors *gr_pos = new TGraphErrors(7,x,v2_pos,NULL,err_pos);
	TGraphErrors *gr_neg = new TGraphErrors(7,x,v2_neg,NULL,err_neg);
	TGraphErrors *gr_diff = new TGraphErrors(7,x,v2_diff,NULL,err_diff);

	
	TGraph *gr_pos_alice = new TGraph(8,x_alice,v2_pos_alice);
	TGraph *gr_neg_alice = new TGraph(8,x_alice,v2_neg_alice);
	TGraph *gr_diff_alice = new TGraph(8,x_alice,v2_diff_alice);

	TCanvas* c1 = new TCanvas("c1","c1");
	TCanvas* c2 = new TCanvas("c2","c2");
	gr_neg -> SetMarkerStyle(20);
	gr_neg -> SetMarkerColor(kBlue);
	gr_pos -> SetMarkerStyle(34);	
	gr_pos -> SetMarkerColor(kRed);




	c1->cd();
	base->Draw("");
	gr_pos->Draw("PSame");
	gr_neg->Draw("PSame");
	//text_a->Draw("Same");
	//text_b->Draw("Same");


    //Define a linear function
	TF1* fit1 = new TF1("f1", "[0]+x*[1]", -0.2, 0.2);
	TF1* fit2 = new TF1("f2", "[0]+x*[1]", -0.2, 0.2);

	fit1->SetLineColor(kRed);
	fit1->SetLineStyle(2);
	fit2->SetLineColor(kBlue);
	fit2->SetLineStyle(2);
	gr_diff->Fit(fit1,"RN0");
	gr_diff_alice->Fit(fit2,"RN0");

	c2->cd();

	base2->Draw("");

	TLatex* text2 = makeLatex(Form("CMS Intercept(Red) : %f #pm %f",fit1->GetParameter(0),fit1->GetParError(0)),0.45,0.25) ;
	TLatex* text1 = makeLatex(Form("CMS slope(Red) : %.4f #pm %.4f",fit1->GetParameter(1),fit1->GetParError(1)),0.45,0.25) ;
	TLatex* text3 = makeLatex(Form("ALICE Intercept(Blue) : %f #pm %f",fit2->GetParameter(0),fit2->GetParError(0)),0.45,0.35) ;
	TLatex* text4 = makeLatex(Form("ALICE slope(Blue) : %.4f #pm %.4f",fit2->GetParameter(1),fit2->GetParError(1)),0.45,0.30) ;
	text1->SetTextFont(42);
	text2->SetTextFont(42);
	text3->SetTextFont(42);
	text4->SetTextFont(42);
	gr_diff->Draw("PSame");

	gr_diff_alice -> SetMarkerStyle(24);

	gr_diff_alice->Draw("PSame");

	text1->DrawClone("Same");
	text4->DrawClone("Same");


	fit1->DrawClone("Same");
	fit2->DrawClone("Same");

	TFile *rebinned = new TFile("~/Summer2016/root_forgraphs/figure_alicecomparison.root","RECREATE");
	gr_diff->Write();
	gr_diff_alice->Write();
	fit1->Write();
	fit2->Write();
	rebinned->Close();



	c2->Print("~/Summer2016/comparison_ALICE_ver2.pdf");
	c2->Print("~/Summer2016/comparison_ALICE_ver2.gif");

}
