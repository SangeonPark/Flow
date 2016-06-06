#include "RiceStyle.h"

using namespace std;

void v2Graph(){

	TFile *f = new TFile("../../../rootfiles/PbPbcrabData.root");
	TH1D* c2_pos_case1[5][5][2];
	TH1D* c2_neg_case1[5][5][2];
	TH1D* c2_tot_case1[5][5][2];

	TH1D* c2_pos_case2[5][4][2];
	TH1D* c2_neg_case2[5][4][2];
	TH1D* c2_tot_case2[5][4][2];
	TH1D* ach_hist[5];

	for (Int_t i = 0; i < 5; i++){
		ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

		for(Int_t j = 0 ; j < 5; j++){

			c2_tot_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_cos_case1",i,j));
			c2_tot_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_sin_case1",i,j));
			c2_pos_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_cos_case1",i,j));
			c2_pos_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_sin_case1",i,j));
			c2_neg_case1[i][j][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_cos_case1",i,j));
			c2_neg_case1[i][j][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_sin_case1",i,j));
		}
		for(Int_t j=0; j<4; j++){
			c2_tot_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_cos_case2",i,j));
			c2_tot_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2tot_%d_%d_sin_case2",i,j));
			c2_pos_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_cos_case2",i,j));
			c2_pos_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_%d_sin_case2",i,j));
			c2_neg_case2[i][j][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_cos_case2",i,j));
			c2_neg_case2[i][j][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_%d_sin_case2",i,j));

		}
	}

	double x[5];
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



	double numerator;
	double denominator;
	double q0,q1,q2,q3;
	double e0,e1,e2,e3;
	double grad0,grad1,grad2,grad3;
	double esquared;


	for(Int_t i=0; i<5; i++){
		x[i]=ach_hist[i]->GetMean();

		cout << i << "th term" << endl;


//case1 positive
		q0 = c2_pos_case1[i][0][0]->GetMean();
		q1 = c2_pos_case1[i][1][0]->GetMean();
		q2 = c2_pos_case1[i][2][0]->GetMean();
		q3 = c2_pos_case1[i][3][0]->GetMean();
		
		cout << "case1 : " << q0 << " " << q1 << " " << q2 << " " << q3 << endl;

		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_pos_case1[i] = numerator/denominator;

		e0 = c2_pos_case1[i][0][0]->GetMeanError();


		e1 = c2_pos_case1[i][1][0]->GetMeanError();
		e2 = c2_pos_case1[i][2][0]->GetMeanError();
		e3 = c2_pos_case1[i][3][0]->GetMeanError();
		grad0 = 1/sqrt(q1*q2/q3);

		grad1 = -0.5*( (q0*sqrt(q3)) / (q1*sqrt(q1*q2)) );
		grad2 = -0.5*( (q0*sqrt(q3)) / (q2*sqrt(q1*q2)) );
		grad3 = q0/(2*sqrt(q1*q2*q3));

		esquared = grad0*grad0*e0*e0+grad1*grad1*e1*e1+grad2*grad2*e2*e2+grad3*grad3*e3*e3;
		err_pos_case1[i] = sqrt(esquared);



	//case1 total
		q0 = c2_tot_case1[i][0][0]->GetMean();
		q1 = c2_tot_case1[i][1][0]->GetMean();
		q2 = c2_tot_case1[i][2][0]->GetMean();
		q3 = c2_tot_case1[i][3][0]->GetMean();
		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_tot_case1[i] = numerator/denominator;

		e0 = c2_tot_case1[i][0][0]->GetMeanError();
		e1 = c2_tot_case1[i][1][0]->GetMeanError();
		e2 = c2_tot_case1[i][2][0]->GetMeanError();
		e3 = c2_tot_case1[i][3][0]->GetMeanError();

		grad0 = 1/sqrt(q1*q2/q3);
		grad1 = -0.5*( (q0*sqrt(q3)) / (q1*sqrt(q1*q2)) );
		grad2 = -0.5*( (q0*sqrt(q3)) / (q2*sqrt(q1*q2)) );
		grad3 = q0/(2*sqrt(q1*q2*q3));

		esquared = grad0*grad0*e0*e0+grad1*grad1*e1*e1+grad2*grad2*e2*e2+grad3*grad3*e3*e3;
		err_tot_case1[i] = sqrt(esquared);




//case1 negative
		q0 = c2_neg_case1[i][0][0]->GetMean();
		q1 = c2_neg_case1[i][1][0]->GetMean();
		q2 = c2_neg_case1[i][2][0]->GetMean();
		q3 = c2_neg_case1[i][3][0]->GetMean();
		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_neg_case1[i] = numerator/denominator;

		e0 = c2_neg_case1[i][0][0]->GetMeanError();
		e1 = c2_neg_case1[i][1][0]->GetMeanError();
		e2 = c2_neg_case1[i][2][0]->GetMeanError();
		e3 = c2_neg_case1[i][3][0]->GetMeanError();

		grad0 = 1/sqrt(q1*q2/q3);
		grad1 = -0.5*( (q0*sqrt(q3)) / (q1*sqrt(q1*q2)) );
		grad2 = -0.5*( (q0*sqrt(q3)) / (q2*sqrt(q1*q2)) );
		grad3 = q0/(2*sqrt(q1*q2*q3));

		esquared = grad0*grad0*e0*e0+grad1*grad1*e1*e1+grad2*grad2*e2*e2+grad3*grad3*e3*e3;
		err_neg_case1[i] = sqrt(esquared);

//case2 positive
		q0 = c2_pos_case2[i][0][0]->GetMean();
		q1 = c2_pos_case2[i][1][0]->GetMean();
		q2 = c2_pos_case2[i][2][0]->GetMean();
		q3 = c2_pos_case2[i][3][0]->GetMean();
		cout << "case2 : " << q0 << " " << q1 << " " << q2 << " " << q3 << endl;		

		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_pos_case2[i] = numerator/denominator;

		e0 = c2_pos_case2[i][0][0]->GetMeanError();
		e1 = c2_pos_case2[i][1][0]->GetMeanError();
		e2 = c2_pos_case2[i][2][0]->GetMeanError();
		e3 = c2_pos_case2[i][3][0]->GetMeanError();

		grad0 = 1/sqrt(q1*q2/q3);
		grad1 = -0.5*( (q0*sqrt(q3)) / (q1*sqrt(q1*q2)) );
		grad2 = -0.5*( (q0*sqrt(q3)) / (q2*sqrt(q1*q2)) );
		grad3 = q0/(2*sqrt(q1*q2*q3));

		esquared = grad0*grad0*e0*e0+grad1*grad1*e1*e1+grad2*grad2*e2*e2+grad3*grad3*e3*e3;
		err_pos_case2[i] = sqrt(esquared);


//case2 total
		q0 = c2_tot_case2[i][0][0]->GetMean();
		q1 = c2_tot_case2[i][1][0]->GetMean();
		q2 = c2_tot_case2[i][2][0]->GetMean();
		q3 = c2_tot_case2[i][3][0]->GetMean();
		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_tot_case2[i] = numerator/denominator;

		e0 = c2_tot_case2[i][0][0]->GetMeanError();
		e1 = c2_tot_case2[i][1][0]->GetMeanError();
		e2 = c2_tot_case2[i][2][0]->GetMeanError();
		e3 = c2_tot_case2[i][3][0]->GetMeanError();

		grad0 = 1/sqrt(q1*q2/q3);
		grad1 = -0.5*( (q0*sqrt(q3)) / (q1*sqrt(q1*q2)) );
		grad2 = -0.5*( (q0*sqrt(q3)) / (q2*sqrt(q1*q2)) );
		grad3 = q0/(2*sqrt(q1*q2*q3));

		esquared = grad0*grad0*e0*e0+grad1*grad1*e1*e1+grad2*grad2*e2*e2+grad3*grad3*e3*e3;
		err_tot_case2[i] = sqrt(esquared);




//case2 negative
		q0 = c2_neg_case2[i][0][0]->GetMean();
		q1 = c2_neg_case2[i][1][0]->GetMean();
		q2 = c2_neg_case2[i][2][0]->GetMean();
		q3 = c2_neg_case2[i][3][0]->GetMean();
		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_neg_case2[i] = numerator/denominator;

		e0 = c2_neg_case2[i][0][0]->GetMeanError();

		e1 = c2_neg_case2[i][1][0]->GetMeanError();
		e2 = c2_neg_case2[i][2][0]->GetMeanError();
		e3 = c2_neg_case2[i][3][0]->GetMeanError();

		grad0 = 1/sqrt(q1*q2/q3);
		grad1 = -0.5*( (q0*sqrt(q3)) / (q1*sqrt(q1*q2)) );
		grad2 = -0.5*( (q0*sqrt(q3)) / (q2*sqrt(q1*q2)) );
		grad3 = q0/(2*sqrt(q1*q2*q3));

		esquared = grad0*grad0*e0*e0+grad1*grad1*e1*e1+grad2*grad2*e2*e2+grad3*grad3*e3*e3;
		err_neg_case2[i] = sqrt(esquared);
 
		cout << "x: " << x[i] << endl;

		cout << "v2 case1 " << v2_pos_case1[i] << endl;	
		cout << "v2 case2 " << v2_pos_case2[i] << endl; 



		v2_diff_case1[i] = v2_neg_case1[i] - v2_pos_case1[i];
		err_diff_case1[i] = sqrt(err_neg_case1[i]*err_neg_case1[i]+err_pos_case1[i]*err_pos_case1[i]);

		cout << "v2 value " << i << " "  <<  v2_pos_case1[i] << endl;
		cout << "error positive case1 " << i << " " <<err_pos_case1[i] << endl;
//	cout << err_diff_case1[i] << endl;


		v2_diff_case2[i] = (v2_neg_case2[i] - v2_pos_case2[i]);
		err_diff_case2[i] = sqrt(err_neg_case2[i]*err_neg_case2[i]+err_pos_case2[i]*err_pos_case2[i]);
//	cout << err_diff_case2[i] << endl;	



	}

	TH1D* base = new TH1D("base","base",100,-0.1,0.1);
	base->GetYaxis()->SetRangeUser(0.095,0.104);


	TGraphErrors *gr_pos_case1 = new TGraphErrors(5,x,v2_pos_case1,NULL,err_pos_case1);
	TGraphErrors *gr_neg_case1 = new TGraphErrors(5,x,v2_neg_case1,NULL,err_neg_case1);
	TGraphErrors *gr_tot_case1 = new TGraphErrors(5,x,v2_tot_case1,NULL,err_tot_case1);
	TGraphErrors *gr_pos_case2 = new TGraphErrors(5,x,v2_pos_case2,NULL,err_pos_case2);
	TGraphErrors *gr_neg_case2 = new TGraphErrors(5,x,v2_neg_case2,NULL,err_neg_case2);
	TGraphErrors *gr_tot_case2 = new TGraphErrors(5,x,v2_tot_case2,NULL,err_tot_case2);

	TGraphErrors *gr_diff_case1 = new TGraphErrors(5,x,v2_diff_case1,NULL,err_diff_case1);
	TGraphErrors *gr_diff_case2 = new TGraphErrors(5,x,v2_diff_case2,NULL,err_diff_case2);

    /*
    gr_pos_case1->GetYaxis()->SetRangeUser(0.095,0.115);
    gr_pos_case1->GetXaxis()->SetLimits(-0.1,0.1);
    gr_neg_case1->GetYaxis()->SetRangeUser(0.095,0.115);
    gr_neg_case1->GetXaxis()->SetLimits(-0.1,0.1);
    gr_tot_case1->GetYaxis()->SetRangeUser(0.095,0.115);
    gr_tot_case1->GetXaxis()->SetLimits(-0.1,0.1);
    gr_pos_case2->GetYaxis()->SetRangeUser(0.095,0.115);
    gr_pos_case2->GetXaxis()->SetLimits(-0.1,0.1);
    gr_neg_case2->GetYaxis()->SetRangeUser(0.095,0.115);
    gr_neg_case2->GetXaxis()->SetLimits(-0.1,0.1);
    gr_tot_case2->GetYaxis()->SetRangeUser(0.095,0.115);
    gr_tot_case2->GetXaxis()->SetLimits(-0.1,0.1); */


    

    gr_pos_case1 -> SetName("positive tracks case1");
    gr_neg_case1 -> SetName("negative tracks case1");
    gr_tot_case1 -> SetName("total tracks case1");
    gr_pos_case1 -> SetTitle("positive tracks case1");
    gr_neg_case1 -> SetTitle("negative tracks case1");
    gr_tot_case1 -> SetTitle("total tracks case1");

    gr_diff_case1 -> SetTitle("difference case1");

    gr_pos_case2 -> SetName("positive tracks case2");
    gr_neg_case2 -> SetName("negative tracks case2");
    gr_tot_case2 -> SetName("total tracks case2");
    gr_pos_case2 -> SetTitle("positive tracks case2");
    gr_neg_case2 -> SetTitle("negative tracks case2");
    gr_tot_case2 -> SetTitle("total tracks case2");

    gr_diff_case2 -> SetTitle("difference case2");


    TCanvas* c1 = new TCanvas("c1","c1");
    TCanvas* c2 = new TCanvas("c2","c2");
    TCanvas* c3 = new TCanvas("c3","c3");
    TCanvas* c4 = new TCanvas("c4","c4");

    
    c1->cd();
    base->SetTitle("case1");
    base->Draw("");
    gr_pos_case1 -> SetMarkerStyle(20);
	gr_pos_case1 -> SetMarkerColor(kBlue);
	gr_neg_case1 -> SetMarkerStyle(28);
	gr_neg_case1 -> SetMarkerColor(kRed);
    gr_pos_case1->Draw("PSame");
    gr_neg_case1->Draw("PSame");


    c4->cd();
        base->SetTitle("case2");

    base->Draw("");
    gr_pos_case2 -> SetMarkerStyle(20);
	gr_pos_case2 -> SetMarkerColor(kBlue);
	gr_neg_case2 -> SetMarkerStyle(28);
	gr_neg_case2 -> SetMarkerColor(kRed);
    gr_pos_case2->Draw("PSame");
    gr_neg_case2->Draw("PSame");

    //Define a linear function
    TF1* fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.09, 0.09);
    fit1->SetLineColor(kRed);
    fit1->SetLineStyle(2);
    gr_diff_case1->Fit(fit1);
    
    TF1* fit2 = new TF1("Linear fitting case 2", "[0]+x*[1]", -0.09, 0.09);
    fit2->SetLineColor(kRed);
    fit2->SetLineStyle(2);
    gr_diff_case2->Fit(fit2);

//    c2->Divide(2,1,0,0);
    c2->cd();
    gr_diff_case1->GetYaxis()->SetRangeUser(-0.002,0.003);
    gr_diff_case1->GetXaxis()->SetLimits(-0.1,0.1);
    gr_diff_case1->GetXaxis()->SetTitle("A_{ch}");
    gr_diff_case1->GetYaxis()->SetTitle("v_{2}(-) - v_{2}(+)");
    gr_diff_case1->GetYaxis()->SetTitleOffset(1.1);
    gr_diff_case1->GetXaxis()->SetTitleOffset(1.1);

    TLatex* text1 = new TLatex(-0.09, 0.0025, Form("slope r = %f #pm %f",fit1->GetParameter(1),fit1->GetParError(1))) ;
    
    gr_diff_case1->Draw("A*");
    text1->DrawClone("Same");
    fit1->DrawClone("Same");

    c3->cd();

    TLatex* text2 = new TLatex(-0.09, 0.0025, Form("slope r = %f #pm %f",fit2->GetParameter(1),fit2->GetParError(1))) ;
    gr_diff_case2->GetYaxis()->SetRangeUser(-0.002,0.003);
    gr_diff_case2->GetXaxis()->SetLimits(-0.1,0.1);
    gr_diff_case2->GetXaxis()->SetTitle("A_{ch}");
    gr_diff_case2->GetYaxis()->SetTitle("v_{2}(-) - v_{2}(+)");
    gr_diff_case2->GetYaxis()->SetTitleOffset(1.1);
    gr_diff_case2->GetXaxis()->SetTitleOffset(1.1);

    
    gr_diff_case2->Draw("A*");
    text2->DrawClone("Same");
    fit2->DrawClone("Same");
    
    cout << "slope case1 : " << fit1->GetParameter(1) << endl;
    cout << "slope case2 : " << fit2->GetParameter(1) << endl;

    
}
