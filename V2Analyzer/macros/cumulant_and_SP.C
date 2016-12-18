#include "RiceStyle.h"

using namespace std;

void cumulant_and_SP(){

	TFile *f;

	const int NAchBins = 7;
	const double correction = 1;


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


	double numerator;
	double denominator;
	double q0,q1,q2,q3;

	double esquared;

	double v2_pos_sample[100][10];
	double v2_neg_sample[100][10];
	double v2_diff_sample[100][10];

	for (int m = 0; m < 10; ++m)
	{
		f = new TFile(Form("../../../rootfiles/FinalResult_Temp/MainResult/v2/PbPb/centrality/30/leaveout%d.root",m+1));
		for (Int_t i = 0; i < NAchBins; i++){
			for(Int_t j = 0 ; j < 4; j++){

				c2_tot_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_cos_case1",i,j));
				c2_tot_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_sin_case1",i,j));
				c2_pos_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_cos_case1",i,j));
				c2_pos_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_sin_case1",i,j));
				c2_neg_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_cos_case1",i,j));
				c2_neg_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_sin_case1",i,j));

				c2_tot_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_cos_case2",i,j));
				c2_tot_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_sin_case2",i,j));
				c2_pos_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_cos_case2",i,j));
				c2_pos_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_sin_case2",i,j));
				c2_neg_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_cos_case2",i,j));
				c2_neg_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_sin_case2",i,j));

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

	f = new TFile("../../../rootfiles/FinalResult_Temp/MainResult/v2/PbPb/centrality/30/Merged.root");


	for (Int_t i = 0; i < NAchBins; i++){

		ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));
		
		for(Int_t j = 0 ; j < 4; j++){
			
			c2_tot_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_cos_case1",i,j));
			c2_tot_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_sin_case1",i,j));
			c2_pos_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_cos_case1",i,j));
			c2_pos_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_sin_case1",i,j));
			c2_neg_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_cos_case1",i,j));
			c2_neg_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_sin_case1",i,j));

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
			//variance_diff += (v2_diff_sample[i][k]-v2_diff[i])*(v2_diff_sample[i][k]-v2_diff[i]);
		}
		sum = v2_pos[i] + v2_neg[i];
		variance_diff = (4*v2_neg[i]*v2_neg[i]*variance_pos)/(sum*sum*sum*sum)+(4*v2_pos[i]*v2_pos[i]*variance_neg)/(sum*sum*sum*sum);
		variance_pos *= 0.9;
		variance_neg *= 0.9;
		variance_diff *= 0.9;
		err_pos[i] = sqrt(variance_pos);
		err_neg[i] = sqrt(variance_neg);
		err_diff[i] = sqrt(variance_diff);
		
	}

	TGraphErrors* diff_list[5];

	diff_list[0] = new TGraphErrors(NAchBins,x,v2_diff,NULL,err_diff);



	f = new TFile("~/Summer2016/rootfiles/systematics_redo/v2_Cumulant_30.root");


	for (Int_t i = 0; i < NAchBins; i++){
		ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

		c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
		c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));

		c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
		c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));
		
	}
	for(Int_t i=0; i< NAchBins; i++){

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

	diff_list[1] = new TGraphErrors(NAchBins,x,v2_diff,NULL,err_diff);






	///plotting

	gStyle->SetLegendFont(42);


	TH1D* base2 = new TH1D("base2","base2",1,-0.15,0.15);
	base2->GetYaxis()->SetRangeUser(-0.04, 0.04);
	base2->GetXaxis()->SetTitle("Observed A_{ch}");
	base2->GetYaxis()->SetTitle(" #frac{ v_{2}^{#minus} #minus v_{2}^{#plus} }{ v_{2}^{#minus} #plus v_{2}^{#plus} } ");
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
	TCanvas* c3 = new TCanvas("c3","c3",1,1,600,600);




	TLatex* text_a = makeLatex("CMS PbPb #sqrt{s_{NN}}=5.02TeV",0.25,0.85) ;
	TLatex* text_b = makeLatex("30-40%",0.25,0.80) ;
	TLatex* text_c = makeLatex("0.3 < p_{T} < 3 GeV/c",0.25,0.75) ;
	TLatex* text_d = makeLatex("|#Delta#eta| > 2",0.25,0.70) ;

	text_a->SetTextFont(42);
	text_b->SetTextFont(42);
	text_c->SetTextFont(42);
	text_d->SetTextFont(42);



    //Define a linear function
	TF1* fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.15, 0.15);
	fit1->SetLineColor(kRed);
	fit1->SetLineStyle(2);
	diff_list[0]->Fit(fit1,"N0");



	TF1* fit2 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.15, 0.15);
	fit2->SetLineColor(kBlue);
	fit2->SetLineStyle(2);
	diff_list[1]->Fit(fit2,"N0");

/*
	TF1* fit3 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.15, 0.15);
	fit3->SetLineColor(kBlack);
	fit3->SetLineStyle(2);
	diff_list[2]->Fit(fit3,"N0");
*/

	TLatex* text1 = makeLatex(Form("SP slope : %.3f #pm %.3f",fit1->GetParameter(1),fit1->GetParError(1)),0.45,0.25) ;	
	TLatex* text2 = makeLatex(Form("Cumulant slope : %.3f #pm %.3f",fit2->GetParameter(1),fit2->GetParError(1)),0.45,0.30) ;
//	TLatex* text3= makeLatex(Form("default slope : %.3f #pm %.3f",fit3->GetParameter(1),fit3->GetParError(1)),0.45,0.35) ;


	text1->SetTextFont(42);
	text2->SetTextFont(42);

	//text3->SetTextFont(42);
	base2->Draw("fit2");
	fit1->SetLineWidth(3);

	fit2->SetLineWidth(3);

	//fit3->SetLineWidth(3);



	fit1->DrawClone("Same");
	fit2->DrawClone("Same");
	//fit3->DrawClone("Same");


	diff_list[0]->SetMarkerStyle(20);
	diff_list[0]->Draw("PSame");

	diff_list[1]->SetMarkerStyle(20);
	diff_list[1]->Draw("PSame");

	//diff_list[2]->SetMarkerStyle(20);
	//diff_list[2]->Draw("PSame");

	text_a->DrawClone("Same");
	text_b->DrawClone("Same");
	

	text1->DrawClone("Same");
	text2->DrawClone("Same");
//		text3->DrawClone("Same");


	

	TF1 *fa1 = new TF1("fa1","0",-10,10); 
	fa1->SetLineColor(kBlack);
	fa1->SetLineWidth(0);
	fa1->DrawClone("Same");

	TLegend* leg2 = new TLegend(0.25,0.64,0.55,0.78);
	leg2->SetLineColor(kWhite);
	leg2->SetFillColor(0);
	leg2->SetFillStyle(0);
	leg2->AddEntry(fit1, "SP","l");
	leg2->AddEntry(fit2 , "Cumulant","l");
	//leg2->AddEntry(fit3 , "default","l");

	leg2->DrawClone("Same");
	SaveCanvas(c3,"pics","cumulant_and_sp");

	TFile *rebinned = new TFile("~/Summer2016/root_forgraphs/Cumualnt_and_SP.root","RECREATE");
	diff_list[0]->Write();
	diff_list[1]->Write();
	rebinned->Close();




}
