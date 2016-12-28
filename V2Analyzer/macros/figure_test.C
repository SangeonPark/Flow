#include "RiceStyle.h"

using namespace std;

void figure_test(){

	TFile* f;
	const int NAchBins = 7;
	const double correction = 1.0;


	//185-220 correction
	//const double correction = 0.675;

	
	//30-40% correction
	//const double correction = 0.641;



	TH1D* c2_pos_case1[100][4][2];
	TH1D* c2_neg_case1[100][4][2];
	TH1D* c2_tot_case1[100][4][2];

	TH1D* c2_pos_case2[100][4][2];
	TH1D* c2_neg_case2[100][4][2];
	TH1D* c2_tot_case2[100][4][2];


	TH1D* ach_hist[100];
	TH1D* c2_pos[100][4];
	TH1D* c2_neg[100][4];

	double x[NAchBins];
	double v2_pos[NAchBins];
	double v2_neg[NAchBins];
	double err_pos[NAchBins];
	double err_neg[NAchBins];
	double v2_diff[NAchBins];
	double err_diff[NAchBins];

	double numerator;
	double denominator;
	double q0,q1,q2,q3;

	double esquared;

	double v2_pos_sample[100][10];
	double v2_neg_sample[100][10];
	double v2_diff_sample[100][10];


	for (int m = 0; m < 10; ++m)
	{
		f = new TFile(Form("~/Summer2016/rootfiles/FinalResult_ver3/leaveout%d.root",m+1));
		for (Int_t i = 0; i < NAchBins; i++){
			for(Int_t j = 0 ; j < 4; j++){

				c2_tot_case1[i][j][0] = (TH1D*)f->Get(Form("demo_n15/c2tot_%d_%d_cos_case1",i,j));
				c2_tot_case1[i][j][1] = (TH1D*)f->Get(Form("demo_n15/c2tot_%d_%d_sin_case1",i,j));
				c2_pos_case1[i][j][0] = (TH1D*)f->Get(Form("demo_n15/c2pos_%d_%d_cos_case1",i,j));
				c2_pos_case1[i][j][1] = (TH1D*)f->Get(Form("demo_n15/c2pos_%d_%d_sin_case1",i,j));
				c2_neg_case1[i][j][0] = (TH1D*)f->Get(Form("demo_n15/c2neg_%d_%d_cos_case1",i,j));
				c2_neg_case1[i][j][1] = (TH1D*)f->Get(Form("demo_n15/c2neg_%d_%d_sin_case1",i,j));

				c2_tot_case2[i][j][0] = (TH1D*)f->Get(Form("demo_n15/c2tot_%d_%d_cos_case2",i,j));
				c2_tot_case2[i][j][1] = (TH1D*)f->Get(Form("demo_n15/c2tot_%d_%d_sin_case2",i,j));
				c2_pos_case2[i][j][0] = (TH1D*)f->Get(Form("demo_n15/c2pos_%d_%d_cos_case2",i,j));
				c2_pos_case2[i][j][1] = (TH1D*)f->Get(Form("demo_n15/c2pos_%d_%d_sin_case2",i,j));
				c2_neg_case2[i][j][0] = (TH1D*)f->Get(Form("demo_n15/c2neg_%d_%d_cos_case2",i,j));
				c2_neg_case2[i][j][1] = (TH1D*)f->Get(Form("demo_n15/c2neg_%d_%d_sin_case2",i,j));

			}
		}

		for (int i = 0; i < NAchBins; ++i)
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

		for(Int_t i=0; i<NAchBins; i++){

			
//positive
			q0 = c2_pos[i][0]->GetMean();
			q1 = c2_pos[i][1]->GetMean();
			q2 = c2_pos[i][2]->GetMean();
			q3 = c2_pos[i][3]->GetMean();

			numerator = q0;
			denominator = sqrt((q1*q2)/q3);
			v2_pos_sample[i][m] = numerator/denominator;

//negative
			q0 = c2_neg[i][0]->GetMean();
			q1 = c2_neg[i][1]->GetMean();
			q2 = c2_neg[i][2]->GetMean();
			q3 = c2_neg[i][3]->GetMean();
			numerator = q0;
			denominator = sqrt((q1*q2)/q3);
			v2_neg_sample[i][m] = numerator/denominator;

			v2_diff_sample[i][m] = (v2_neg_sample[i][m] - v2_pos_sample[i][m])/(v2_neg_sample[i][m] + v2_pos_sample[i][m]);


		}



	}

	f = new TFile("~/Summer2016/rootfiles/FinalResult_ver3/Merged.root");


	for (Int_t i = 0; i < NAchBins; i++){

		ach_hist[i] = (TH1D*)f->Get(Form("demo_n15/ach_%d",i+1));
		
		for(Int_t j = 0 ; j < 4; j++){
			
			c2_tot_case1[i][j][0] = (TH1D*)f->Get(Form("demo_n15/c2tot_%d_%d_cos_case1",i,j));
			c2_tot_case1[i][j][1] = (TH1D*)f->Get(Form("demo_n15/c2tot_%d_%d_sin_case1",i,j));
			c2_pos_case1[i][j][0] = (TH1D*)f->Get(Form("demo_n15/c2pos_%d_%d_cos_case1",i,j));
			c2_pos_case1[i][j][1] = (TH1D*)f->Get(Form("demo_n15/c2pos_%d_%d_sin_case1",i,j));
			c2_neg_case1[i][j][0] = (TH1D*)f->Get(Form("demo_n15/c2neg_%d_%d_cos_case1",i,j));
			c2_neg_case1[i][j][1] = (TH1D*)f->Get(Form("demo_n15/c2neg_%d_%d_sin_case1",i,j));

			c2_tot_case2[i][j][0] = (TH1D*)f->Get(Form("demo_n15/c2tot_%d_%d_cos_case2",i,j));
			c2_tot_case2[i][j][1] = (TH1D*)f->Get(Form("demo_n15/c2tot_%d_%d_sin_case2",i,j));
			c2_pos_case2[i][j][0] = (TH1D*)f->Get(Form("demo_n15/c2pos_%d_%d_cos_case2",i,j));
			c2_pos_case2[i][j][1] = (TH1D*)f->Get(Form("demo_n15/c2pos_%d_%d_sin_case2",i,j));
			c2_neg_case2[i][j][0] = (TH1D*)f->Get(Form("demo_n15/c2neg_%d_%d_cos_case2",i,j));
			c2_neg_case2[i][j][1] = (TH1D*)f->Get(Form("demo_n15/c2neg_%d_%d_sin_case2",i,j));

			//c2_pos_case2[i][j][0] ->Sumw2();
			//c2_neg_case2[i][j][0] ->Sumw2(); 

		}
	}

	for (int i = 0; i < NAchBins; ++i)
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



	
	
	for(Int_t i=0; i<NAchBins; i++){
		
//x coordinates
		x[i]=ach_hist[i]->GetMean();
		x[i]*=correction;

//positive
		q0 = c2_pos[i][0]->GetMean();
		q1 = c2_pos[i][1]->GetMean();
		q2 = c2_pos[i][2]->GetMean();
		q3 = c2_pos[i][3]->GetMean();


		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_pos[i] = numerator/denominator;

//negative
		q0 = c2_neg[i][0]->GetMean();
		q1 = c2_neg[i][1]->GetMean();
		q2 = c2_neg[i][2]->GetMean();
		q3 = c2_neg[i][3]->GetMean();
		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_neg[i] = numerator/denominator;

//difference
		v2_diff[i] = (v2_neg[i]-v2_pos[i])/(v2_neg[i]+v2_pos[i]);


//error bars
		double variance_pos = 0.0;
		double variance_neg = 0.0;
		double variance_diff = 0.0;
		double sum;

		for (int k = 0; k < 10; ++k)
		{
			variance_pos += (v2_pos_sample[i][k]-v2_pos[i])*(v2_pos_sample[i][k]-v2_pos[i]);
			variance_neg += (v2_neg_sample[i][k]-v2_neg[i])*(v2_neg_sample[i][k]-v2_neg[i]);
			variance_diff += (v2_diff_sample[i][k]-v2_diff[i])*(v2_diff_sample[i][k]-v2_diff[i]);
		}
		sum = v2_pos[i] + v2_neg[i];
		variance_pos *= 0.9;
		variance_neg *= 0.9;
		variance_diff *= 0.9;
		//variance_diff = (4*v2_neg[i]*v2_neg[i]*variance_pos)/(sum*sum*sum*sum)+(4*v2_pos[i]*v2_pos[i]*variance_neg)/(sum*sum*sum*sum);

		err_pos[i] = sqrt(variance_pos);
		err_neg[i] = sqrt(variance_neg);
		err_diff[i] = sqrt(variance_diff);
		
	}
	

	TGraphErrors *gr_pos = new TGraphErrors(NAchBins,x,v2_pos,NULL,err_pos);
	TGraphErrors *gr_neg = new TGraphErrors(NAchBins,x,v2_neg,NULL,err_neg);
	TGraphErrors *gr_diff = new TGraphErrors(NAchBins,x,v2_diff,NULL,err_diff);

/*
	gr_pos->RemovePoint(0);
	gr_pos->RemovePoint(5);

	gr_neg->RemovePoint(0);
	gr_neg->RemovePoint(5);

	gr_diff->RemovePoint(0);
	gr_diff->RemovePoint(5);
*/




	gStyle->SetLegendFont(42);
	TH1D* base = new TH1D("base","base",1,-0.20,0.20);
	//pPb
	//base->GetYaxis()->SetRangeUser(0.065, 0.075);
	base->GetYaxis()->SetRangeUser(0.03, 0.04);

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

	TH1D* base2 = new TH1D("base2","base2",1,-0.2,0.2);
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

	

 //   TCanvas* c1 = new TCanvas("c1","c1");
 //   TCanvas* c2 = new TCanvas("c2","c2");
	TCanvas* c3 = new TCanvas("c3","c3",1,1,1200,600);
	c3->Divide(2,1,0.01,0.01);

	gr_neg -> SetMarkerStyle(20);
	gr_neg -> SetMarkerColor(kBlue);
	gr_pos -> SetMarkerStyle(34);	
	gr_pos -> SetMarkerColor(kRed);




	TLatex* text_a = makeLatex("CMS PbPb #sqrt{s_{NN}}=5.02TeV",0.25,0.85) ;
	//TLatex* text_b = makeLatex("185 #leq N_{trk}^{offline} < 220",0.25,0.80) ;
	TLatex* text_b = makeLatex("30-40%",0.25,0.80) ;

	TLatex* text_c = makeLatex("0.3 < p_{T} < 3.0 GeV/c",0.25,0.75) ;
	TLatex* text_d = makeLatex("|#Delta#eta| > 2",0.25,0.70) ;

	text_a->SetTextFont(42);
	text_b->SetTextFont(42);
	text_c->SetTextFont(42);
	text_d->SetTextFont(42);



	TLegend* leg = new TLegend(0.76,0.80,0.94,.88);
	leg->SetLineColor(kWhite);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->AddEntry(gr_pos, "v_{2}^{#plus}{2}","p");
	leg->AddEntry(gr_neg , "v_{2}^{#minus}{2}","p");



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

	fit1->SetLineColor(kRed);
	fit1->SetLineStyle(2);
	gr_diff->Fit(fit1,"RN0");



	c3->cd(2);



	TLatex* text2 = makeLatex(Form("Intercept : %f #pm %f",fit1->GetParameter(0),fit1->GetParError(0)),0.45,0.30) ;
	TLatex* text1 = makeLatex(Form("slope : %.4f #pm %.4f",fit1->GetParameter(1),fit1->GetParError(1)),0.45,0.25) ;
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

	TLegend* leg2 = new TLegend(0.25,0.68,0.5,0.78);
	leg2->SetLineColor(kWhite);
	leg2->SetFillColor(0);
	leg2->SetFillStyle(0);
	leg2->AddEntry(fit1, "Linear fit","l");
	leg2->AddEntry(gr_diff , "data","p");
	leg2->DrawClone("Same");

	//SaveCanvas(c3,"pics",Form("30-40SP"));


}
