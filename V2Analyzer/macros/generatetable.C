#include "RiceStyle.h"
using namespace std;

void generatetable(){

	TH2D* ptetadist[2][3];
	TH2D* ptetaratio[3];


	for (int i = 0; i < 3; ++i)
	{
		f = new TFile(Form("~/Summer2016/rootfiles/MC/EPOS_PbPb_pteta_%d.root",i));
		ptetadist[0][i] = (TH2D*)f->Get("demo/pt_eta_distribution");

	}
	for (int i = 0; i < 3; ++i)
	{
		f = new TFile(Form("~/Summer2016/rootfiles/MC/Hydjet_PbPb_pteta_%d.root",i));
		ptetadist[1][i] = (TH2D*)f->Get("demo/pt_eta_distribution");
	}

	TFile *weight = new TFile("~/Summer2016/Flow/V2Analyzer/data/MCweight.root","RECREATE");


	for(int i = 0; i<3 ; ++i)
	{
		double N_epos;
		double N_hydjet;
		TH2D *epos = (TH2D*) ptetadist[0][i]->Clone(Form("table_%d",i));
		TH2D *hydjet = (TH2D*) ptetadist[1][i]->Clone();
		epos->Rebin2D(20,20);
		hydjet->Rebin2D(20,20);


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