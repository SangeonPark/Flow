#include "RiceStyle.h"
using namespace std;

void v2Merged(){

	TFile *f = new TFile("../../../rootfiles/CMW_AutoCorrelation_SP_PbPb_MB5_0119.root");
	TH1D* c2_pos_case1[100][4][2];
	TH1D* c2_neg_case1[100][4][2];
	TH1D* c2_tot_case1[100][4][2];

	TH1D* c2_pos_case2[100][4][2];
	TH1D* c2_neg_case2[100][4][2];
	TH1D* c2_tot_case2[100][4][2];

	TH1D* ach_hist[100];

	TH1D* c2_pos[100][4];
	TH1D* c2_neg[100][4];

	double x_alice[8] = {-0.07,-0.05,-0.03,-0.01,0.01,0.03,0.05,0.07};
	double v2_pos_alice[8] = {0.0995,0.0985+0.0005/4,0.098+0.0005/4,0.0975+0.0005*2/3,0.0975+0.0005/6,0.0975,0.097+0.0005/2,0.097+0.0005/2+0.0001};
	double v2_neg_alice[8] = {0.097-0.0005/5,0.097+0.0005/4,0.097+0.0005/2,0.0975,0.0975+0.0005/2,0.098+0.0005/4,0.0985+0.0001,0.0985+0.0005*2/3};
	double v2_diff_alice[8];


	//const double correction = 0.629;

	const double correction = 1.0;

	for (Int_t i = 0; i < 7; i++){
		ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));
		
		for(Int_t j = 0 ; j < 4; j++){
			
			c2_tot_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_cos_case1",i,j));
			c2_tot_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_sin_case1",i,j));
			c2_pos_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_cos_case1",i,j));
			c2_pos_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_sin_case1",i,j));
			c2_neg_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_cos_case1",i,j));
			c2_neg_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_sin_case1",i,j));

			//c2_pos_case1[i][j][0] -> Sumw2();
			//c2_neg_case1[i][j][0] -> Sumw2();
		}
		for(Int_t j=0; j<4; j++){
			c2_tot_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_cos_case2",i,j));
			c2_tot_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_sin_case2",i,j));
			c2_pos_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_cos_case2",i,j));
			c2_pos_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_sin_case2",i,j));
			c2_neg_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_cos_case2",i,j));
			c2_neg_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_sin_case2",i,j));

			//c2_pos_case2[i][j][0] ->Sumw2();
			//c2_neg_case2[i][j][0] ->Sumw2(); 

		}
	}

	for (int i = 0; i < 7; ++i)
	{
		c2_pos[i][0] =  new TH1D(*c2_pos_case1[i][0][0]);
		c2_pos[i][0] -> Add(c2_pos_case2[i][0][0],1.);
		
		c2_pos[i][1] =  new TH1D(*c2_pos_case1[i][1][0]);
		c2_pos[i][1] -> Add(c2_pos_case2[i][2][0],1.);

		c2_pos[i][2] =  new TH1D(*c2_pos_case1[i][2][0]);
		c2_pos[i][2] -> Add(c2_pos_case2[i][1][0],1.);

		c2_pos[i][3] =  new TH1D(*c2_pos_case1[i][3][0]);
		c2_pos[i][3] -> Add(c2_pos_case2[i][3][0],1.);

		c2_neg[i][0] =  new TH1D(*c2_neg_case1[i][0][0]);
		c2_neg[i][0] -> Add(c2_neg_case2[i][0][0],1.);
		
		c2_neg[i][1] =  new TH1D(*c2_neg_case1[i][1][0]);
		c2_neg[i][1] -> Add(c2_neg_case2[i][2][0],1.);

		c2_neg[i][2] =  new TH1D(*c2_neg_case1[i][2][0]);
		c2_neg[i][2] -> Add(c2_neg_case2[i][1][0],1.);

		c2_neg[i][3] =  new TH1D(*c2_neg_case1[i][3][0]);
		c2_neg[i][3] -> Add(c2_neg_case2[i][3][0],1.);




		
		
		
	}
	/*
	TCanvas* c4 = new TCanvas("c4","c4");
	TCanvas* c5 = new TCanvas("c5","c5");
	TCanvas* c6 = new TCanvas("c6","c6");

	c4->cd();
	c2_pos[0][0]->DrawClone();
	c5->cd();
	c2_pos_case1[0][0][0]->DrawClone();

	c6->cd();
	c2_pos_case2[0][0][0]->DrawClone(); */

	double x[7];
	/*
	double v2_pos_case1[5];
	double err_pos_case1[5];

	double v2_neg_case1[5];
	double err_neg_case1[5];

	double v2_tot_case1[5];
	double err_tot_case1[5];
	
	double v2_pos_case2[5];
	double err_pos_case2[5];

	double v2_neg_case2[5];
	double err_neg_case2[5];

	double v2_tot_case2[5];
	double err_tot_case2[5];
	
	double v2_diff_case1[5];
	double err_diff_case1[5];

	double v2_diff_case2[5];
	double err_diff_case2[5];
	*/

	double v2_pos[7];
	double v2_neg[7];
	double err_pos[7];
	double err_neg[7];
	double v2_diff[7];
	double err_diff[7];



	double numerator;
	double denominator;
	double q0,q1,q2,q3;
	double e0,e1,e2,e3;
	double grad0,grad1,grad2,grad3;
	double esquared;
	
	for (int i = 0; i < 8; ++i)
	{
		//v2_diff_alice[i] = (v2_neg_alice[i]-v2_pos_alice[i]);
		v2_diff_alice[i] = (v2_neg_alice[i]-v2_pos_alice[i])/(v2_neg_alice[i]+v2_pos_alice[i]);


	}
	
	for(Int_t i=0; i<7; i++){
		
		cout << i << "th term" << endl;

		x[i]=ach_hist[i]->GetMean();

		x[i] *= correction; 


		cout << "x : " << x[i] <<endl;



//positive
		q0 = c2_pos[i][0]->GetMean();
		q1 = c2_pos[i][1]->GetMean();
		q2 = c2_pos[i][2]->GetMean();
		q3 = c2_pos[i][3]->GetMean();

		cout << q0 << " " << q1 << " " << q2 << " " << q3 << endl;

		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_pos[i] = numerator/denominator;

		e0 = c2_pos[i][0]->GetMeanError();
		e1 = c2_pos[i][1]->GetMeanError();
		e2 = c2_pos[i][2]->GetMeanError();
		e3 = c2_pos[i][3]->GetMeanError();

		grad0 = 1/sqrt(q1*q2/q3);
		grad1 = -0.5*( (q0*sqrt(q3)) / (q1*sqrt(q1*q2)) );
		grad2 = -0.5*( (q0*sqrt(q3)) / (q2*sqrt(q1*q2)) );
		grad3 = q0/(2*sqrt(q1*q2*q3));

		esquared = grad0*grad0*e0*e0+grad1*grad1*e1*e1+grad2*grad2*e2*e2+grad3*grad3*e3*e3;
		err_pos[i] = sqrt(esquared);

		cout << "v2pos : " << v2_pos[i] << endl;
		cout << "errpos : " << err_pos[i] << endl;


//negative
		q0 = c2_neg[i][0]->GetMean();
		q1 = c2_neg[i][1]->GetMean();
		q2 = c2_neg[i][2]->GetMean();
		q3 = c2_neg[i][3]->GetMean();
		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_neg[i] = numerator/denominator;

		e0 = c2_neg[i][0]->GetMeanError();
		e1 = c2_neg[i][1]->GetMeanError();
		e2 = c2_neg[i][2]->GetMeanError();
		e3 = c2_neg[i][3]->GetMeanError();

		grad0 = 1/sqrt(q1*q2/q3);
		grad1 = -0.5*( (q0*sqrt(q3)) / (q1*sqrt(q1*q2)) );
		grad2 = -0.5*( (q0*sqrt(q3)) / (q2*sqrt(q1*q2)) );
		grad3 = q0/(2*sqrt(q1*q2*q3));

		esquared = grad0*grad0*e0*e0+grad1*grad1*e1*e1+grad2*grad2*e2*e2+grad3*grad3*e3*e3;
		err_neg[i] = sqrt(esquared);


		v2_diff[i] = (v2_neg[i]-v2_pos[i])/(v2_neg[i]+v2_pos[i]);
		//v2_diff[i] = (v2_neg[i]-v2_pos[i]);


		cout << "difference : " << v2_diff[i] <<endl;
		err_diff[i] = sqrt(err_neg[i]*err_neg[i]+err_pos[i]*err_pos[i]);

		
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
	//base2->GetYaxis()->SetTitle(" (v^{#minus}_{2} #minus v^{#plus}_{2})/(v^{#minus}_{2} #plus v^{#plus}_{2}) ");
	base2->GetYaxis()->SetTitle(" (v^{#minus}_{2} #minus v^{#plus}_{2}) ");
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

	gr_diff_alice->RemovePoint(7);
	gr_diff_alice->RemovePoint(0);


	TCanvas* c1 = new TCanvas("c1","c1");
	TCanvas* c2 = new TCanvas("c2","c2");
	gr_neg -> SetMarkerStyle(20);
	gr_neg -> SetMarkerColor(kBlue);
	gr_pos -> SetMarkerStyle(34);	
	gr_pos -> SetMarkerColor(kRed);
	TLatex* text_a = makeLatex("CMS, 40-50% centrality",0.25,0.85) ;
	TLatex* text_b = makeLatex("0.75 < p_{T} < 0.8",0.25,0.80) ;


	text_a->SetTextFont(42);
	text_b->SetTextFont(42);



	c1->cd();
	base->Draw("");
	gr_pos->Draw("PSame");
	gr_neg->Draw("PSame");
	text_a->Draw("Same");
	//text_b->Draw("Same");


    //Define a linear function
	TF1* fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.2, 0.2);
	TF1* fit2 = new TF1("Linear fitting case 2", "[0]+x*[1]", -0.2, 0.2);

	fit1->SetLineColor(kRed);
	fit1->SetLineStyle(2);
	fit2->SetLineColor(kBlue);
	fit2->SetLineStyle(2);
	gr_diff->Fit(fit1,"RN0");
	gr_diff_alice->Fit(fit2,"RN0");


//  c2->Divide(2,1,0,0);
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

//	gr_diff_alice->Draw("PSame");

	//text1->DrawClone("Same");
	//text2->DrawClone("Same");
	//text3->DrawClone("Same");
	//text4->DrawClone("Same");


	fit1->DrawClone("Same");
	fit2->DrawClone("Same");



	c1->Print("~/Summer2016/v2SPslope_ALICE.pdf");
	c1->Print("~/Summer2016/v2SPslope_ALICE.gif");
	c2->Print("~/Summer2016/v2SPdiffslope_ALICE.pdf");
	c2->Print("~/Summer2016/v2SPdiffslope_ALICE.gif");

}
