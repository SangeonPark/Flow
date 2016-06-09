#include "RiceStyle.h"

using namespace std;

void v2ErrGraph(){

	TFile* f;
	TH1D* c2_pos_case1[5][5][2];
	TH1D* c2_neg_case1[5][5][2];
	TH1D* c2_tot_case1[5][5][2];
	TH1D* c2_pos_case2[5][4][2];
	TH1D* c2_neg_case2[5][4][2];
	TH1D* c2_tot_case2[5][4][2];
	TH1D* ach_hist[5];

	double x[5];
	double v2_pos_case1[5];
	double err_pos_case1[5];

	double v2_neg_case1[5];
	double err_neg_case1[5];



	double v2_pos_case2[5];
	double err_pos_case2[5];

	double v2_neg_case2[5];
	double err_neg_case2[5];


	double v2_diff_case1[5];
	double err_diff_case1[5];

	double v2_diff_case2[5];
	double err_diff_case2[5];

	double v2_pos_case1_sample[5][10];
	double v2_neg_case1_sample[5][10];
	double v2_pos_case2_sample[5][10];
	double v2_neg_case2_sample[5][10];
	double v2_diff_case1_sample[5][10];
	double v2_diff_case2_sample[5][10];



	double numerator;
	double denominator;
	double q0,q1,q2,q3;



	for (int n = 0; n < 10; ++n)
	{
		f = new TFile(Form("../../../rootfiles/errcalcpPb/leaveout%d.root",n+1));

		for (Int_t i = 0; i < 5; i++){
			for(Int_t j = 0 ; j < 5; j++){

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

		for(Int_t i=0; i<5; i++){

//case1 positive
			q0 = c2_pos_case1[i][0][0]->GetMean();
			q1 = c2_pos_case1[i][1][0]->GetMean();
			q2 = c2_pos_case1[i][2][0]->GetMean();
			q3 = c2_pos_case1[i][3][0]->GetMean();


			numerator = q0;
			denominator = sqrt((q1*q2)/q3);
			v2_pos_case1_sample[i][n] = numerator/denominator;


//case1 negative
			q0 = c2_neg_case1[i][0][0]->GetMean();
			q1 = c2_neg_case1[i][1][0]->GetMean();
			q2 = c2_neg_case1[i][2][0]->GetMean();
			q3 = c2_neg_case1[i][3][0]->GetMean();
			numerator = q0;
			denominator = sqrt((q1*q2)/q3);
			v2_neg_case1_sample[i][n] = numerator/denominator;

//case2 positive
			q0 = c2_pos_case2[i][0][0]->GetMean();
			q1 = c2_pos_case2[i][1][0]->GetMean();
			q2 = c2_pos_case2[i][2][0]->GetMean();
			q3 = c2_pos_case2[i][3][0]->GetMean();

			numerator = q0;
			denominator = sqrt((q1*q2)/q3);
			v2_pos_case2_sample[i][n] = numerator/denominator;


//case2 negative
			q0 = c2_neg_case2[i][0][0]->GetMean();
			q1 = c2_neg_case2[i][1][0]->GetMean();
			q2 = c2_neg_case2[i][2][0]->GetMean();
			q3 = c2_neg_case2[i][3][0]->GetMean();
			numerator = q0;
			denominator = sqrt((q1*q2)/q3);
			v2_neg_case2_sample[i][n] = numerator/denominator;

			v2_diff_case1_sample[i][n] = v2_neg_case1_sample[i][n] - v2_pos_case1_sample[i][n];
			v2_diff_case2_sample[i][n] = v2_neg_case2_sample[i][n] - v2_pos_case2_sample[i][n];
		}

	}


	f = new TFile("../../../rootfiles/v2pPb3filesmerged.root");


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




	for(Int_t i=0; i<5; i++){

//x coordinates
		x[i]=ach_hist[i]->GetMean();


//case1 positive
		q0 = c2_pos_case1[i][0][0]->GetMean();
		q1 = c2_pos_case1[i][1][0]->GetMean();
		q2 = c2_pos_case1[i][2][0]->GetMean();
		q3 = c2_pos_case1[i][3][0]->GetMean();
		
		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_pos_case1[i] = numerator/denominator;




//case1 negative
		q0 = c2_neg_case1[i][0][0]->GetMean();
		q1 = c2_neg_case1[i][1][0]->GetMean();
		q2 = c2_neg_case1[i][2][0]->GetMean();
		q3 = c2_neg_case1[i][3][0]->GetMean();
		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_neg_case1[i] = numerator/denominator;

//case2 positive
		q0 = c2_pos_case2[i][0][0]->GetMean();
		q1 = c2_pos_case2[i][1][0]->GetMean();
		q2 = c2_pos_case2[i][2][0]->GetMean();
		q3 = c2_pos_case2[i][3][0]->GetMean();

		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_pos_case2[i] = numerator/denominator;


//case2 negative
		q0 = c2_neg_case2[i][0][0]->GetMean();
		q1 = c2_neg_case2[i][1][0]->GetMean();
		q2 = c2_neg_case2[i][2][0]->GetMean();
		q3 = c2_neg_case2[i][3][0]->GetMean();
		numerator = q0;
		denominator = sqrt((q1*q2)/q3);
		v2_neg_case2[i] = numerator/denominator;

		v2_diff_case1[i] = (v2_neg_case1[i] - v2_pos_case1[i]);
		v2_diff_case2[i] = (v2_neg_case2[i] - v2_pos_case2[i]);


//error bars
		double variance_pos_case1 = 0.0;
		double variance_pos_case2 = 0.0;		
		double variance_neg_case1 = 0.0;
		double variance_neg_case2 = 0.0;
		double variance_diff_case1 = 0.0;
		double variance_diff_case2 = 0.0;

		for (int k = 0; k < 10; ++k)
		{
			variance_pos_case1 += (v2_pos_case1_sample[i][k]-v2_pos_case1[i])*(v2_pos_case1_sample[i][k]-v2_pos_case1[i]);
			variance_pos_case2 += (v2_pos_case2_sample[i][k]-v2_pos_case2[i])*(v2_pos_case2_sample[i][k]-v2_pos_case2[i]);
			variance_neg_case1 += (v2_neg_case1_sample[i][k]-v2_neg_case1[i])*(v2_neg_case1_sample[i][k]-v2_neg_case1[i]);
			variance_neg_case2 += (v2_neg_case2_sample[i][k]-v2_neg_case2[i])*(v2_neg_case2_sample[i][k]-v2_neg_case2[i]);
			variance_diff_case1 += (v2_diff_case1_sample[i][k]-v2_diff_case1[i])*(v2_diff_case1_sample[i][k]-v2_diff_case1[i]);
			variance_diff_case2 += (v2_diff_case2_sample[i][k]-v2_diff_case2[i])*(v2_diff_case2_sample[i][k]-v2_diff_case2[i]);
		}
		variance_pos_case1 *= 0.9;
		variance_pos_case2 *= 0.9;
		variance_neg_case1 *= 0.9;
		variance_neg_case2 *= 0.9;
		variance_diff_case1 *= 0.9;
		variance_diff_case2 *= 0.9;

		err_pos_case1[i] = sqrt(variance_pos_case1);
		err_pos_case2[i] = sqrt(variance_pos_case2);
		err_neg_case1[i] = sqrt(variance_neg_case1);
		err_neg_case2[i] = sqrt(variance_neg_case2);
		err_diff_case1[i] = sqrt(variance_diff_case1);
		err_diff_case2[i] = sqrt(variance_diff_case2);

	}

	TH1D* base = new TH1D("base","base",100,-0.1,0.1);
	base->GetYaxis()->SetRangeUser(0.06,0.075);
	base->GetXaxis()->SetTitle("Observed A_{ch}");
	base->GetYaxis()->SetTitle("v_{2}");
	base->SetStats(0);
	base->GetYaxis()->SetTitleOffset(1.4);
	base->GetXaxis()->SetTitleOffset(1.1);


	TGraphErrors *gr_pos_case1 = new TGraphErrors(5,x,v2_pos_case1,NULL,err_pos_case1);
	TGraphErrors *gr_neg_case1 = new TGraphErrors(5,x,v2_neg_case1,NULL,err_neg_case1);
	TGraphErrors *gr_pos_case2 = new TGraphErrors(5,x,v2_pos_case2,NULL,err_pos_case2);
	TGraphErrors *gr_neg_case2 = new TGraphErrors(5,x,v2_neg_case2,NULL,err_neg_case2);

	TGraphErrors *gr_diff_case1 = new TGraphErrors(5,x,v2_diff_case1,NULL,err_diff_case1);
	TGraphErrors *gr_diff_case2 = new TGraphErrors(5,x,v2_diff_case2,NULL,err_diff_case2);


	gr_neg_case1 -> SetMarkerStyle(20);
	gr_neg_case1 -> SetMarkerColor(kBlue);
	gr_pos_case1 -> SetMarkerStyle(28);
	gr_pos_case1 -> SetMarkerColor(kRed);

	TLegend* leg = new TLegend(.60,.70,.80,.85);
	leg->SetLineColor(kWhite);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->AddEntry(gr_pos_case1, "pos","p");
	leg->AddEntry(gr_neg_case1, "neg","p");

	gr_neg_case2 -> SetMarkerStyle(20);
	gr_neg_case2 -> SetMarkerColor(kBlue);
	gr_pos_case2 -> SetMarkerStyle(28);
	gr_pos_case2 -> SetMarkerColor(kRed);

	TLegend* leg2 = new TLegend(.60,.70,.80,.85);
	leg2->SetLineColor(kWhite);
	leg2->SetFillColor(0);
	leg2->SetFillStyle(0);
	leg2->AddEntry(gr_pos_case2, "pos","p");
	leg2->AddEntry(gr_neg_case2, "neg","p");

	TLatex* text_a = makeLatex("pPb #sqrt{s_{NN}}=5.02TeV",0.15,0.8) ;
	TLatex* text_b = makeLatex("N_{trk}^{offline} [185,220)",0.15,0.7) ;
	TLatex* text_c = makeLatex("0.3 < p_{T} < 3.0 GeV/c",0.15,0.6) ;




	gr_pos_case1 -> SetName("positive tracks case1");
	gr_neg_case1 -> SetName("negative tracks case1");
	gr_pos_case1 -> SetTitle("positive tracks case1");
	gr_neg_case1 -> SetTitle("negative tracks case1");

	gr_diff_case1 -> SetTitle("difference case1");

	gr_pos_case2 -> SetName("positive tracks case2");
	gr_neg_case2 -> SetName("negative tracks case2");
	gr_pos_case2 -> SetTitle("positive tracks case2");
	gr_neg_case2 -> SetTitle("negative tracks case2");

	gr_diff_case2 -> SetTitle("difference case2");

/*
    TCanvas* c1 = new TCanvas("c1","c1");
    TCanvas* c2 = new TCanvas("c2","c2");
    TCanvas* c3 = new TCanvas("c3","c3");
    TCanvas* c4 = new TCanvas("c4","c4");
    */

    TCanvas* c5 = new TCanvas("c5","c5",1,1,1200,600);
    c5->Divide(2,1,0.01,0.01);
    TCanvas* c6 = new TCanvas("c6","c6",1,1,1200,600);
    c6->Divide(2,1,0.01,0.01);

    base->GetYaxis()->SetNdivisions(510); 
    base->GetXaxis()->SetNdivisions(505); 

    
    c5->cd(1);
    base->SetTitle("p going side");
    base->DrawClone("");

    gr_pos_case1->Draw("PSame");
    gr_neg_case1->Draw("PSame");
    text_a->DrawClone("Same");
    text_b->DrawClone("Same");
    text_c->DrawClone("Same");
    leg->DrawClone("Same");



    c6->cd(1);
    base->SetTitle("Pb going side");
    base->DrawClone("");

    gr_pos_case2->Draw("PSame");
    gr_neg_case2->Draw("PSame");
    text_a->DrawClone("Same");
    text_b->DrawClone("Same");
    text_c->DrawClone("Same");
    leg2->DrawClone("Same");


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
    c5->cd(2);
    gr_diff_case1->GetYaxis()->SetRangeUser(-0.002,0.003);
    gr_diff_case1->GetXaxis()->SetLimits(-0.1,0.1);
    gr_diff_case1->GetXaxis()->SetTitle("A_{ch}");
    gr_diff_case1->GetYaxis()->SetTitle("v_{2}(-) - v_{2}(+)");
    gr_diff_case1->GetYaxis()->SetTitleOffset(1.5);
    gr_diff_case1->GetXaxis()->SetTitleOffset(1.1);
    gr_diff_case1->GetYaxis()->SetNdivisions(505); 
    gr_diff_case1->GetXaxis()->SetNdivisions(505); 


    TLatex* text1 = new TLatex(-0.09, 0.0025, Form("slope r = %f #pm %f",fit1->GetParameter(1),fit1->GetParError(1))) ;
    
    gr_diff_case1->Draw("A*");
    text1->DrawClone("Same");
    fit1->DrawClone("Same");

    c6->cd(2);

    TLatex* text2 = new TLatex(-0.09, 0.0025, Form("slope r = %f #pm %f",fit2->GetParameter(1),fit2->GetParError(1))) ;
    gr_diff_case2->GetYaxis()->SetRangeUser(-0.002,0.003);
    gr_diff_case2->GetXaxis()->SetLimits(-0.1,0.1);
    gr_diff_case2->GetXaxis()->SetTitle("A_{ch}");
    gr_diff_case2->GetYaxis()->SetTitle("v_{2}(-) - v_{2}(+)");
    gr_diff_case2->GetYaxis()->SetTitleOffset(1.5);
    gr_diff_case2->GetXaxis()->SetTitleOffset(1.1);
    gr_diff_case2->GetYaxis()->SetNdivisions(505); 
    gr_diff_case2->GetXaxis()->SetNdivisions(505); 

    
    gr_diff_case2->Draw("A*");
    text2->DrawClone("Same");
    fit2->DrawClone("Same");
    
    cout << "slope case1 : " << fit1->GetParameter(1) << endl;
    cout << "slope case2 : " << fit2->GetParameter(1) << endl;

    
}
