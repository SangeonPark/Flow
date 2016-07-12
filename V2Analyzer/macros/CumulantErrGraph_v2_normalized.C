#include "RiceStyle.h"

using namespace std;

void CumulantErrGraph_v2_normalized(){

	TFile *f;
	TH1D* c2_pos[5][2];
	TH1D* c2_neg[5][2];

	TH1D* ach_hist[5];
	double x[5];

	double v2_pos[5];
	double v2_neg[5];
	double v2_diff[5];
	double err_neg[5];
	double err_pos[5];
	double err_diff[5];
	double cmean;
	double errmean;
	double sum;
	double variance_pos;
	double variance_neg;
	double variance_diff;


	f = new TFile("../../../rootfiles/v2Cumulant_PbPb/Merged.root");


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
	for(i=0;i<5;i++){
		cout << x[i] << ", ";
	}	
	cout << endl << "v2" << endl;
	for(i=0;i<5;i++){
		cout << v2_diff[i] << ", ";
	}
	cout << endl << "v2 error" <<endl;
	for(i=0;i<5;i++){
		cout << err_diff[i] << ", ";
	}		

	TH1D* base = new TH1D("base","base",100,-0.1,0.1);
//PbPb
	//base->GetYaxis()->SetRangeUser(0.094, 0.10);
//p-Pb 
	base->GetYaxis()->SetRangeUser(0.065, 0.075);

	base->GetXaxis()->SetTitle("Observed A_{ch}");
	base->GetYaxis()->SetTitle("v_{2}");

	TGraphErrors *gr_pos = new TGraphErrors(5,x,v2_pos,NULL,err_pos);
	TGraphErrors *gr_neg = new TGraphErrors(5,x,v2_neg,NULL,err_neg);
	TGraphErrors *gr_diff = new TGraphErrors(5,x,v2_diff,NULL,err_diff);

 //   TCanvas* c1 = new TCanvas("c1","c1");
 //   TCanvas* c2 = new TCanvas("c2","c2");
	TCanvas* c3 = new TCanvas("c3","c3",1,1,1200,600);
	c3->Divide(2,1,0.01,0.01);

	gr_neg -> SetMarkerStyle(20);
	gr_neg -> SetMarkerColor(kBlue);
	gr_pos -> SetMarkerStyle(28);
	gr_pos -> SetMarkerColor(kRed);
	gr_pos->SetFillStyle(0);

	gr_pos->SetFillColor(0);
	gr_neg->SetFillStyle(0);
	gr_neg->SetFillColor(0);

	base->GetYaxis()->SetTitleOffset(1.4);
	base->GetXaxis()->SetTitleOffset(1.1);
	base->GetYaxis()->SetNdivisions(505); 
	base->GetXaxis()->SetNdivisions(505); 
	base->SetStats(0);
	gStyle->SetOptTitle(0);

	TLatex* text_a = makeLatex("p-Pb #sqrt{s_{NN}}=5.02TeV",0.15,0.82) ;
	TLatex* text_b = makeLatex("N_{trk}^{offline} [185, 260)",0.15,0.74) ;
	TLatex* text_c = makeLatex("0.3 < p_{T} < 3.0 GeV/c",0.15,0.66) ;
	TLatex* text_d = makeLatex("-2.4 < #eta < 2.4",0.15,0.58) ;


	TLegend* leg = new TLegend(.60,.70,.80,.85);
	leg->SetLineColor(kWhite);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->AddEntry(gr_pos, "pos","p");
	leg->AddEntry(gr_neg , "neg","p");


	
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
	TF1* fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.09, 0.09);
	fit1->SetLineColor(kRed);
	fit1->SetLineStyle(2);
	gr_diff->Fit(fit1);

	c3->cd(2);
	gr_diff->GetYaxis()->SetRangeUser(-0.02,0.02);
	gr_diff->GetXaxis()->SetLimits(-0.1,0.1);
	gr_diff->GetXaxis()->SetTitle("A_{ch}");
	gr_diff->GetYaxis()->SetTitle("#frac{v_{2}(-) - v_{2}(+)}{v_{2}(-) + v_{2}(+)}");
	gr_diff->GetYaxis()->SetTitleOffset(1.1);
	gr_diff->GetXaxis()->SetTitleOffset(1.1);
	gr_diff->GetYaxis()->SetNdivisions(505); 
	gr_diff->GetXaxis()->SetNdivisions(505); 



	TLatex* text1 = makeLatex(Form("slope r = %f #pm %f",fit1->GetParameter(1),fit1->GetParError(1)),0.15,0.8) ;
	
	gr_diff->Draw("A*");
	

	text1->DrawClone("Same");
	fit1->DrawClone("Same");

	TF1 *fa1 = new TF1("fa1","0",-10,10); 
	fa1->SetLineColor(kBlack);
	fa1->SetLineWidth(1);
	fa1->DrawClone("Same");


}
