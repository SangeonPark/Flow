#include "RiceStyle.h"

using namespace std;

void v2v3_ach(){


	double x[5]={-0.0672281, -0.0268681, 5.3189e-05, 0.0269401, 0.0679959};


	double v2_diff[5] = {-0.0013951, -0.000448778, -0.00026506, 0.000454593, 0.000900035};
	double err_v2_diff[5] = {0.000170232, 0.000162984, 0.000114969, 0.000150978, 0.00013698};
	double v3_diff[5] = {-0.000935386, -0.000170658, -2.8693e-05, 0.000563132, 0.000701194};
	double err_v3_diff[5] = {0.000393865, 0.000262631, 0.000272847, 0.000275732, 0.000312574};

	TH1D* base = new TH1D("base","base",100,-0.1,0.1);
	base->GetYaxis()->SetRangeUser(-0.004, 0.004);
	base->GetXaxis()->SetTitle("Observed A_{ch}");
	base->GetYaxis()->SetTitle("#Delta v_{n}");


	TGraphErrors *gr_v2_diff = new TGraphErrors(5,x,v2_diff,NULL,err_v2_diff);
	TGraphErrors *gr_v3_diff = new TGraphErrors(5,x,v3_diff,NULL,err_v3_diff);


 //   TCanvas* c1 = new TCanvas("c1","c1");
 //   TCanvas* c2 = new TCanvas("c2","c2");
	TCanvas* c3 = new TCanvas("c3","c3",1,1,720,600);
	c3->SetLeftMargin(0.2);

	gr_v2_diff -> SetMarkerStyle(20);
	gr_v2_diff -> SetMarkerColor(kBlue);
	gr_v3_diff -> SetMarkerStyle(34);
	gr_v3_diff -> SetMarkerColor(kRed);
	gr_v2_diff->SetFillStyle(0);
	gr_v2_diff->SetFillColor(0);
	gr_v3_diff->SetFillStyle(0);
	gr_v3_diff->SetFillColor(0);

	base->GetYaxis()->SetTitleOffset(1.8);
	base->GetXaxis()->SetTitleOffset(1.4);
	base->GetYaxis()->SetNdivisions(505); 
	base->GetXaxis()->SetNdivisions(505); 
	base->SetStats(0);
	gStyle->SetOptTitle(0);

	TLegend* leg = new TLegend(.70,.70,.85,.85);
	leg->SetLineColor(kWhite);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->AddEntry(gr_v2_diff, "v2","p");
	leg->AddEntry(gr_v3_diff, "v3","p");

	
	c3->cd();
	base->Draw("");
	gr_v2_diff->Draw("PSame");
	gr_v3_diff->Draw("PSame");
	leg->DrawClone("Same");


    //Define a linear function
	TF1* fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.09, 0.09);
	fit1->SetLineColor(kBlue);
	fit1->SetLineStyle(2);
	gr_v2_diff->Fit(fit1);

	TF1* fit2 = new TF1("Linear fitting case 2", "[0]+x*[1]", -0.09, 0.09);
	fit2->SetLineColor(kRed);
	fit2->SetLineStyle(2);
	gr_v3_diff->Fit(fit2);




	TLatex* text1 = makeLatex(Form("slope v_{2} = %f #pm %f",fit1->GetParameter(1),fit1->GetParError(1)),0.25,0.8) ;
	TLatex* text2 = makeLatex(Form("slope v_{3} = %f #pm %f",fit2->GetParameter(1),fit2->GetParError(1)),0.25,0.7) ;


	text1->DrawClone("Same");
	fit1->DrawClone("Same");
	text2->DrawClone("Same");
	fit2->DrawClone("Same");

	TF1 *fa1 = new TF1("fa1","0",-10,10); 
	fa1->SetLineColor(kBlack);
	fa1->SetLineWidth(1);
	fa1->DrawClone("Same");


}
