#include "RiceStyle.h"
using namespace std;

void rebinasym(){

	TFile *f = new TFile("~/Summer2016/rootfiles/v2Cumulant_pPb_185_220_25bins/Merged.root");
	
	TH1D* c2_pos[25][2];
	TH1D* c2_neg[25][2];
	TH1D* ach_hist[25];


	TH1D* temp_c2_pos_cos;
	TH1D* temp_c2_neg_cos;
	TH1D* temp_c2_pos_sin;
	TH1D* temp_c2_neg_sin;
	TH1D* temp_ach_hist;


	const int nbin = 9; 
	double binning[nbin] = {1,2,2,3,9,3,2,2,1};

	for (Int_t i = 0; i < 25; i++){

		ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));	
		c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
		c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));
		c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
		c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));
		
	}


	TFile *rebinned = new TFile(Form("~/Summer2016/rootfiles/v2Cumulant_pPb_185_220_25bins/Rebinned_%d.root",nbin),"RECREATE");

	int num = 0;

	for (int i = 0; i < nbin; ++i)
	{
		temp_c2_pos_cos = new TH1D(Form("c2pos_%d_cos",i),"c2 Distribution",2000,-1,1);
		temp_c2_pos_sin = new TH1D(Form("c2pos_%d_sin",i),"c2 Distribution",2000,-1,1);
		temp_c2_neg_cos = new TH1D(Form("c2neg_%d_cos",i),"c2 Distribution",2000,-1,1);
		temp_c2_neg_sin = new TH1D(Form("c2neg_%d_sin",i),"c2 Distribution",2000,-1,1);
		temp_ach_hist = new TH1D(Form("ach_%d",i+1),Form("ach_%d",i+1),1000,-0.4,0.4);

		for(int j=0; j<binning[i]; j++){
			temp_c2_pos_cos -> Add(c2_pos[num][0],1.0);
			temp_c2_pos_sin -> Add(c2_pos[num][1],1.0);
			temp_c2_neg_cos -> Add(c2_neg[num][0],1.0);
			temp_c2_neg_sin -> Add(c2_neg[num][1],1.0);
			temp_ach_hist -> Add(ach_hist[num],1.0);
			num++;
		}
		temp_c2_pos_cos->Write();
		temp_c2_pos_sin->Write();
		temp_c2_neg_cos->Write();
		temp_c2_neg_sin->Write();
		temp_ach_hist->Write();
	}
	rebinned->Close();

}
