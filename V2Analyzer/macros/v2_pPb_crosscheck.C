#include "RiceStyle.h"
using namespace std;

void v2_pPb_crosscheck(){

	TFile *f;

	const int NAchBins = 7;
	const int ntrkmin = 220;
	const int ntrkmax = 260;

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
	cout << ntrkmin << ntrkmax << endl; 
	TFile* file = new TFile(Form("~/Dropbox/CMWplottingMacros/dataPoints/Weischecks/vnasym_pPb_%d%d.root",ntrkmin,ntrkmax));
	TGraphErrors* gr1[3];
	gr1[0] = (TGraphErrors*) file->Get("v2vschasym_pos");
	gr1[1] = (TGraphErrors*) file->Get("v2vschasym_neg");
	gr1[2] = (TGraphErrors*) file->Get("v2vschasym_diff");

	gr1[1] -> SetMarkerStyle(24);
	gr1[0] -> SetMarkerStyle(28);




	f = new TFile(Form("~/Summer2016/rootfiles/crosscheck/pPb/v2/%d_%d/Merged.root",ntrkmin,ntrkmax));


	for (Int_t i = 0; i < NAchBins; i++){
		ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

		c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
		c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));

		c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
		c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));
		
	}
	for(Int_t i=0; i<NAchBins; i++){

		x[i]=ach_hist[i]->GetMean();

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
	for(i=0;i<NAchBins;i++){
		cout << x[i] << ", ";
	}	
	cout << endl << "v2" << endl;
	for(i=0;i<NAchBins;i++){
		cout << v2_diff[i] << ", ";
	}
	cout << endl << "v2 error" <<endl;
	for(i=0;i<NAchBins;i++){
		cout << err_diff[i] << ", ";
	}		
	gStyle->SetLegendFont(42);
	TH1D* base = new TH1D("base","base",1,-0.15,0.15);
	//pPb
	base->GetYaxis()->SetRangeUser(0.067, 0.073);

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
	base2->GetYaxis()->SetRangeUser(-0.03, 0.03);
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



	TGraphErrors *gr_pos = new TGraphErrors(NAchBins,x,v2_pos,NULL,err_pos);
	TGraphErrors *gr_neg = new TGraphErrors(NAchBins,x,v2_neg,NULL,err_neg);
	TGraphErrors *gr_diff = new TGraphErrors(NAchBins,x,v2_diff,NULL,err_diff);




 //   TCanvas* c1 = new TCanvas("c1","c1");
 //   TCanvas* c2 = new TCanvas("c2","c2");
	TCanvas* c3 = new TCanvas("c3","c3",1,1,1200,600);
	c3->Divide(2,1,0.01,0.01);

	gr_neg -> SetMarkerStyle(20);
	gr_neg -> SetMarkerColor(kBlue);
	gr_pos -> SetMarkerStyle(34);	
	gr_pos -> SetMarkerColor(kRed);




	TLatex* text_a = makeLatex("CMS pPb #sqrt{s_{NN}}=5.02TeV",0.25,0.85) ;
	TLatex* text_b = makeLatex(Form("%d #leq N_{trk}^{offline} < %d",ntrkmin,ntrkmax),0.25,0.80) ;
	TLatex* text_c = makeLatex("0.3 < p_{T} < 3 GeV/c",0.25,0.75) ;
	TLatex* text_d = makeLatex("|#Delta#eta| > 2",0.25,0.70) ;

	text_a->SetTextFont(42);
	text_b->SetTextFont(42);
	text_c->SetTextFont(42);
	text_d->SetTextFont(42);



	TLegend* leg = new TLegend(0.66,0.74,0.92,.88);
	leg->SetLineColor(kWhite);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->AddEntry(gr_pos, "v_{2}^{#plus}{2}","p");
	leg->AddEntry(gr_neg , "v_{2}^{#minus}{2}","p");
	leg->AddEntry(gr1[0] , "Crosscheck v_{2}^{#plus}{2}","p");
	leg->AddEntry(gr1[1] , "Crosscheck v_{2}^{#minus}{2}","p");




	c3->cd(1);
	base->Draw("");
	gr_pos->Draw("PSame");
	gr_neg->Draw("PSame");
	text_a->DrawClone("Same");
	text_b->DrawClone("Same");
	text_c->DrawClone("Same");
	text_d->DrawClone("Same");

	leg->DrawClone("Same");


    //Define a linear function
	TF1* fit1 = new TF1("f1", "[0]+x*[1]", -0.13, 0.13);
	TF1* fit2 = new TF1("f2", "[0]+x*[1]", -0.13, 0.13);


	fit1->SetLineColor(kBlack);
	fit1->SetLineStyle(2);

	fit2->SetLineColor(kRed);
	fit2->SetLineStyle(1);

	gr_diff->Fit(fit1,"N0");


	gr1[0] -> Draw("PSame");
	gr1[1] -> Draw("PSame");

	c3->cd(2);



	TLatex* text2 = makeLatex(Form("Intercept : %.3f #pm %.3f",fit1->GetParameter(0),fit1->GetParError(0)),0.43,0.29) ;
	TLatex* text1 = makeLatex(Form("slope : %.4f #pm %.4f",fit1->GetParameter(1),fit1->GetParError(1)),0.43,0.25) ;
	text1->SetTextFont(42);
	text2->SetTextFont(42);
	base2->Draw("");
	fit1->DrawClone("Same");

	gr_diff->SetMarkerStyle(20);
	gr_diff->Draw("PSame");

	text_a->DrawClone("Same");
	text_b->DrawClone("Same");
	

	text1->DrawClone("Same");
	text2->DrawClone("Same");

	

	TF1 *fa1 = new TF1("fa1","0",-10,10); 
	fa1->SetLineColor(kBlack);
	fa1->SetLineWidth(0);
	fa1->DrawClone("Same");

	TLegend* leg2 = new TLegend(0.25,0.64,0.6,0.78);
	leg2->SetLineColor(kWhite);
	leg2->SetFillColor(0);
	leg2->SetFillStyle(0);
	gr1[2] -> SetMarkerStyle(24);
	gr1[2] -> SetMarkerColor(kRed);
	leg2->AddEntry(fit1, "Linear fit","l");
	leg2->AddEntry(gr_diff , "data","p");
	leg2->AddEntry(fit2, "Linear fit to crosscheck","l");
	leg2->AddEntry(gr1[2] , "crosscheck","p");
	leg2->DrawClone("Same");

	gr1[2] -> SetMarkerStyle(24);
	gr1[2] -> SetMarkerColor(kRed);
	gr1[2] -> Draw("PSame");
	gr1[2]->Fit(fit2,"N0");

	fit2->Draw("Same");

	TLatex* text3 = makeLatex(Form("Crosscheck Intercept : %.3f #pm %.3f",fit2->GetParameter(0),fit2->GetParError(0)),0.43,0.21) ;
	TLatex* text4 = makeLatex(Form("Crosscheck slope : %.4f #pm %.4f",fit2->GetParameter(1),fit2->GetParError(1)),0.43,0.17) ;
	text3->SetTextFont(42);
	text4->SetTextFont(42);
	text3->Draw("Same");
	text4->Draw("Same");

	SaveCanvas(c3,"pics",Form("v2_pPb_%d_%d_crosscheck",ntrkmin,ntrkmax));




}
