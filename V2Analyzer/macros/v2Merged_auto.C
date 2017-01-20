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



	

}
