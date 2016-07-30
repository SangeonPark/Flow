#include "RiceStyle.h"
using namespace std;

void ntrkratiotable(){

	TH1D* ntrkdist[2][3];
	TH1D* ntrkratio[3];


	for (int i = 0; i < 3; ++i)
	{
		f = new TFile(Form("~/Summer2016/rootfiles/MC/EPOS_PbPb_Ntrk_%d.root",i));
		ntrkdist[0][i] = (TH1D*)f->Get("demo/NTrkHist");

	}
	for (int i = 0; i < 3; ++i)
	{
		f = new TFile(Form("~/Summer2016/rootfiles/MC/Hydjet_PbPb_Ntrk_%d.root",i));
		ntrkdist[1][i] = (TH1D*)f->Get("demo/NTrkHist");
	}

	TFile *weight = new TFile("~/Summer2016/Flow/V2Analyzer/data/NTRKreweight.root","RECREATE");


	for(int i = 0; i<3 ; ++i)
	{
		double N_epos;
		double N_hydjet;
		TH1D *epos = (TH1D*) ntrkdist[0][i]->Clone(Form("table_%d",i));
		TH1D *hydjet = (TH1D*) ntrkdist[1][i]->Clone();


		N_epos = epos->GetEntries();
		N_hydjet = hydjet->GetEntries();
		epos->Scale(1/N_epos);
		hydjet->Scale(1/N_hydjet);

		epos->Divide(hydjet);
		
		epos->Write();
		//TH2D* ratio = new TH2D(*ptetadist[0][i]);
		//ratio -> Divide(ptetadist[1][i]);
		//ratio -> SetTitle("table_wow;;;"); 
		//ratio -> Write();

	}
	weight->Close();

}