#include "RiceStyle.h"

using namespace std;

void figure6_generate(){

	TFile *f;
	const int NAchBins = 7;

	TGraphErrors* graph_list[100];

	double corrfactor_cent[6] = {0.641, 0.644, 0.655, 0.673, 0.701, 0.631};
	double corrfactor_ntrk[8] = {0.689, 0.687, 0.677, 0.675, 0.673, 0.666, 0.662, 0.653};

	int low_cent[6] = {30,40,50,60,70,80};
	int upp_cent[6] = {40,50,60,70,80,90};

	int low_ntrk[8] = {90,120,150,185,220,260,300,400};
	int upp_ntrk[8] = {120,150,185,220,260,300,400,500};

	//containers for SP
	TH1D* ach_hist[NAchBins];
	TH1D* NTrkHist;


	TH1D* c2_pos_case1[NAchBins][4][2];
	TH1D* c2_neg_case1[NAchBins][4][2];
	TH1D* c2_tot_case1[NAchBins][4][2];

	TH1D* c2_pos_case2[NAchBins][4][2];
	TH1D* c2_neg_case2[NAchBins][4][2];
	TH1D* c2_tot_case2[NAchBins][4][2];

	TH1D* c2_pos[NAchBins][4];
	TH1D* c2_neg[NAchBins][4];
	
	//containers for pt
	TH1D* pt_pos[NAchBins];
	TH1D* pt_neg[NAchBins];

	double PbPb_v2_ntrk_yval[10];
	double PbPb_v2_ntrk_yerr[10];
	double PbPb_v2_ntrk_xval[10];



	double PbPb_v2_cent_yval[10];
	double PbPb_v2_cent_yerr[10];
	double PbPb_v2_cent_xval[10];

	double PbPb_pt_ntrk_yval[10];
	double PbPb_pt_ntrk_yerr[10];
	double PbPb_pt_ntrk_xval[10];

	double PbPb_pt_cent_yval[10];
	double PbPb_pt_cent_yerr[10];
	double PbPb_pt_cent_xval[10];



	for (int num = 0; num < 8; ++num)
	{
		double numerator;
		double denominator;
		double q0,q1,q2,q3;
		double v2_pos_sample[NAchBins][10];
		double v2_neg_sample[NAchBins][10];
		double v2_diff_sample[NAchBins][10];
		double v2_pos[NAchBins];
		double v2_neg[NAchBins];
		double v2_diff[NAchBins];
		double err_pos[NAchBins];
		double err_neg[NAchBins];
		double err_diff[NAchBins];
		double x[NAchBins];
		TGraphErrors* graph;
		TF1* fit;

		
		
		for (int m = 0; m < 10; ++m)
		{
			f = new TFile(Form("../../../rootfiles/FinalResult_Temp/MainResult/v2/PbPb/%d/leaveout%d.root",low_ntrk[num],m+1));
			
			//copy files for error calculation
			for (Int_t i = 0; i < NAchBins; i++)
			{

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
				for (int j = 0; j < 4; ++j)
				{

					c2_pos[i][j] =  new TH1D(*c2_pos_case1[i][j][0]);
					c2_pos[i][j] -> Add(c2_pos_case2[i][j][0],1.);

					c2_neg[i][j] =  new TH1D(*c2_neg_case1[i][j][0]);
					c2_neg[i][j] -> Add(c2_neg_case2[i][j][0],1.);

				}

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

		f = new TFile(Form("../../../rootfiles/FinalResult_Temp/MainResult/v2/PbPb/%d/Merged.root",low_ntrk[num]));

		NTrkHist = (TH1D*)f->Get("demo/NTrkHist");
		PbPb_v2_ntrk_xval[num] = NTrkHist->GetMean();
		for (Int_t i = 0; i < NAchBins; i++)
		{
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

			}
		}

		for (int i = 0; i < NAchBins; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{

				c2_pos[i][j] =  new TH1D(*c2_pos_case1[i][j][0]);
				c2_pos[i][j] -> Add(c2_pos_case2[i][j][0],1.);

				c2_neg[i][j] =  new TH1D(*c2_neg_case1[i][j][0]);
				c2_neg[i][j] -> Add(c2_neg_case2[i][j][0],1.);

			}

		}
		for(Int_t i=0; i<NAchBins; i++){

//x coordinates
			x[i]=ach_hist[i]->GetMean();
			x[i]*=corrfactor_ntrk[num];

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
			variance_pos *= 0.9;
			variance_neg *= 0.9;

			variance_diff = (4*v2_neg[i]*v2_neg[i]*variance_pos)/(sum*sum*sum*sum)+(4*v2_pos[i]*v2_pos[i]*variance_neg)/(sum*sum*sum*sum);

			//variance_diff *= 0.9;
			err_pos[i] = sqrt(variance_pos);
			err_neg[i] = sqrt(variance_neg);
			err_diff[i] = sqrt(variance_diff);

		}
		graph = new TGraphErrors(NAchBins,x,v2_diff,NULL,err_diff);
		fit = new TF1("Linear fitting", "[0]+x*[1]", -0.15, 0.15);
		graph->Fit(fit,"RN0");
		PbPb_v2_ntrk_yval[num] = fit->GetParameter(1);
		PbPb_v2_ntrk_yerr[num] = fit->GetParError(1);
	}

	graph_list[0] = new TGraphErrors(8,PbPb_v2_ntrk_xval,PbPb_v2_ntrk_yval,NULL,PbPb_v2_ntrk_yerr);

	for (int num = 0; num < 8; ++num)
	{
		double x[NAchBins];
		double ptavg_pos[NAchBins];
		double ptavg_neg[NAchBins];
		double ptavg_diff[NAchBins];
		double ptavg_pos_err[NAchBins];
		double ptavg_neg_err[NAchBins];
		double ptavg_diff_err[NAchBins];
		TGraphErrors* graph;
		TF1* fit;

		f = new TFile(Form("../../../rootfiles/FinalResult_Temp/MainResult/v2/PbPb/%d/Merged.root",low_ntrk[num]));
		NTrkHist = (TH1D*)f->Get("demo/NTrkHist");
		PbPb_pt_ntrk_xval[num] = NTrkHist->GetMean();

		for (Int_t i = 0; i < NAchBins; i++){

			ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));
			pt_pos[i] = (TH1D*)f->Get(Form("demo/pt_pos_%d",i+1));
			pt_neg[i] = (TH1D*)f->Get(Form("demo/pt_neg_%d",i+1));

		}

		for(Int_t i=0; i<NAchBins; i++){


			x[i]=ach_hist[i]->GetMean();
			x[i] *= corrfactor_ntrk[num];

			ptavg_pos[i]=pt_pos[i]->GetMean();
			ptavg_neg[i]=pt_neg[i]->GetMean();
			ptavg_pos_err[i]=pt_pos[i]->GetMeanError();

			variance_pos = ptavg_pos_err[i]*ptavg_pos_err[i];

			ptavg_neg_err[i]=pt_neg[i]->GetMeanError();

			variance_neg = ptavg_neg_err[i]*ptavg_neg_err[i];

			ptavg_diff[i] = (ptavg_neg[i] - ptavg_pos[i])/(ptavg_neg[i] + ptavg_pos[i]);

			sum = ptavg_pos[i] + ptavg_neg[i];
			variance_diff = (4*ptavg_neg[i]*ptavg_neg[i]*variance_pos)/(sum*sum*sum*sum)+(4*ptavg_pos[i]*ptavg_pos[i]*variance_neg)/(sum*sum*sum*sum);

			ptavg_diff_err[i] = sqrt(variance_diff);
			cout << ptavg_neg_err[i] << endl;


		}	
		graph = new TGraphErrors(NAchBins,x,ptavg_diff,NULL,ptavg_diff_err);
		fit = new TF1("Linear fitting", "[0]+x*[1]", -0.15, 0.15);
		graph->Fit(fit,"RN0");
		PbPb_pt_ntrk_yval[num] = fit->GetParameter(1);
		PbPb_pt_ntrk_yerr[num] = fit->GetParError(1);

	}

	graph_list[2] = new TGraphErrors(8,PbPb_pt_ntrk_xval,PbPb_pt_ntrk_yval,NULL,PbPb_pt_ntrk_yerr);




	for (int num = 0; num < 2; ++num)
	{

		double numerator;
		double denominator;
		double q0,q1,q2,q3;
		double v2_pos_sample[100][10];
		double v2_neg_sample[100][10];
		double v2_diff_sample[100][10];
		double v2_pos[100];
		double v2_neg[100];
		double v2_diff[100];
		double err_pos[100];
		double err_neg[100];
		double err_diff[100];
		double x[100];
		TGraphErrors* graph;
		TF1* fit;

		for (int m = 0; m < 10; ++m)
		{
			
			f = new TFile(Form("../../../rootfiles/FinalResult_Temp/MainResult/v2/PbPb/centrality/%d/leaveout%d.root",low_cent[num],m+1));
			
			//copy files for error calculation
			for (Int_t i = 0; i < NAchBins; i++)
			{

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
				for (int j = 0; j < 4; ++j)
				{

					c2_pos[i][j] =  new TH1D(*c2_pos_case1[i][j][0]);
					c2_pos[i][j] -> Add(c2_pos_case2[i][j][0],1.);

					c2_neg[i][j] =  new TH1D(*c2_neg_case1[i][j][0]);
					c2_neg[i][j] -> Add(c2_neg_case2[i][j][0],1.);

				}

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

		f = new TFile(Form("../../../rootfiles/FinalResult_Temp/MainResult/v2/PbPb/centrality/%d/Merged.root",low_cent[num]));

		NTrkHist = (TH1D*)f->Get("demo/NTrkHist");
		PbPb_v2_cent_xval[num] = NTrkHist->GetMean();
		for (Int_t i = 0; i < NAchBins; i++)
		{
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

			}
		}

		for (int i = 0; i < NAchBins; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{

				c2_pos[i][j] =  new TH1D(*c2_pos_case1[i][j][0]);
				c2_pos[i][j] -> Add(c2_pos_case2[i][j][0],1.);

				c2_neg[i][j] =  new TH1D(*c2_neg_case1[i][j][0]);
				c2_neg[i][j] -> Add(c2_neg_case2[i][j][0],1.);

			}

		}
		for(Int_t i=0; i<NAchBins; i++){

//x coordinates
			x[i]=ach_hist[i]->GetMean();
			x[i]*=corrfactor_cent[num];

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
			variance_pos *= 0.9;
			variance_neg *= 0.9;

			variance_diff = (4*v2_neg[i]*v2_neg[i]*variance_pos)/(sum*sum*sum*sum)+(4*v2_pos[i]*v2_pos[i]*variance_neg)/(sum*sum*sum*sum);

			//variance_diff *= 0.9;
			err_pos[i] = sqrt(variance_pos);
			err_neg[i] = sqrt(variance_neg);
			err_diff[i] = sqrt(variance_diff);

		}
		graph = new TGraphErrors(NAchBins,x,v2_diff,NULL,err_diff);
		fit = new TF1("Linear fitting", "[0]+x*[1]", -0.15, 0.15);
		graph->Fit(fit,"RN0");
		PbPb_v2_cent_yval[num] = fit->GetParameter(1);
		PbPb_v2_cent_yerr[num] = fit->GetParError(1);
	}

	graph_list[1] = new TGraphErrors(2,PbPb_v2_cent_xval,PbPb_v2_cent_yval,NULL,PbPb_v2_cent_yerr);


	for (int num = 0; num < 2; ++num)
	{
		double x[NAchBins];
		double ptavg_pos[NAchBins];
		double ptavg_neg[NAchBins];
		double ptavg_diff[NAchBins];
		double ptavg_pos_err[NAchBins];
		double ptavg_neg_err[NAchBins];
		double ptavg_diff_err[NAchBins];
		TGraphErrors* graph;
		TF1* fit;

		f = new TFile(Form("../../../rootfiles/FinalResult_Temp/MainResult/v2/PbPb/centrality/%d/Merged.root",low_cent[num]));
		NTrkHist = (TH1D*)f->Get("demo/NTrkHist");
		PbPb_pt_cent_xval[num] = NTrkHist->GetMean();

		for (Int_t i = 0; i < NAchBins; i++){

			ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));
			pt_pos[i] = (TH1D*)f->Get(Form("demo/pt_pos_%d",i+1));
			pt_neg[i] = (TH1D*)f->Get(Form("demo/pt_neg_%d",i+1));

		}

		for(Int_t i=0; i<NAchBins; i++){


			x[i]=ach_hist[i]->GetMean();
			x[i] *= corrfactor_cent[num];

			ptavg_pos[i]=pt_pos[i]->GetMean();
			ptavg_neg[i]=pt_neg[i]->GetMean();
			ptavg_pos_err[i]=pt_pos[i]->GetMeanError();

			variance_pos = ptavg_pos_err[i]*ptavg_pos_err[i];

			ptavg_neg_err[i]=pt_neg[i]->GetMeanError();

			variance_neg = ptavg_neg_err[i]*ptavg_neg_err[i];

			ptavg_diff[i] = (ptavg_neg[i] - ptavg_pos[i])/(ptavg_neg[i] + ptavg_pos[i]);

			sum = ptavg_pos[i] + ptavg_neg[i];
			variance_diff = (4*ptavg_neg[i]*ptavg_neg[i]*variance_pos)/(sum*sum*sum*sum)+(4*ptavg_pos[i]*ptavg_pos[i]*variance_neg)/(sum*sum*sum*sum);

			ptavg_diff_err[i] = sqrt(variance_diff);
			cout << ptavg_neg_err[i] << endl;


		}	
		graph = new TGraphErrors(NAchBins,x,ptavg_diff,NULL,ptavg_diff_err);
		fit = new TF1("Linear fitting", "[0]+x*[1]", -0.15, 0.15);
		graph->Fit(fit,"RN0");
		PbPb_pt_cent_yval[num] = fit->GetParameter(1);
		PbPb_pt_cent_yerr[num] = fit->GetParError(1);

	}

	graph_list[3] = new TGraphErrors(2,PbPb_pt_cent_xval,PbPb_pt_cent_yval,NULL,PbPb_pt_cent_yerr);




}