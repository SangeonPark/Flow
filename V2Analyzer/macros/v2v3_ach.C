#include "RiceStyle.h"

using namespace std;

void v2v3_ach(){


	double x_pPb[5]={-0.0675987, -0.026866, 8.25199e-05, 0.0269863, 0.068599};
	double x_PbPb[5]= {-0.066403, -0.0268031, 9.10135e-05, 0.0269368, 0.0673906};

	double y_pPb[5]={-0.00999897, -0.00507546, 0.00102101, 0.00431005, 0.0111284};
	double err_pPb[5]={0.000582847, 0.000618996, 0.000515639, 0.000601981, 0.000543659};

	double y_PbPb[5] = {-0.00648909, 0.00776142, 0.0122597, 0.0100027, 0.0185398};
	double err_PbPb[5] = {0.00601675, 0.00597722, 0.00492338, 0.005926, 0.00539414};

	TH1D* base = new TH1D("base","base",100,-0.1,0.1);
	base->GetYaxis()->SetRangeUser(-0.03, 0.06);
	base->GetXaxis()->SetTitle("Observed A_{ch}");
	base->GetYaxis()->SetTitle("#frac{v_{n}(-) - v_{n}(+)}{v_{n}(-) + v_{n}(+)}");


	TGraphErrors *gr_v2_diff = new TGraphErrors(5,x_pPb,y_pPb,NULL,err_pPb);
	TGraphErrors *gr_v3_diff = new TGraphErrors(5,x_PbPb,y_PbPb,NULL,err_PbPb);

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
	base->GetYaxis()->SetRangeUser(-0.05,0.05);
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
	TLatex* text3 = makeLatex("N_{trk}^{offline} v2: [185, 260) v3: [185, 300) " ,0.45,0.20) ;
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
