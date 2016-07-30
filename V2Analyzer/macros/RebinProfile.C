#include "RiceStyle.h"
using namespace std;

void RebinProfile(){

	f = new TFile("../../../rootfiles/MC/EPOS_PbPb_Ntrk_0.root");

	TH2D* h2;
	h2 = (TH2D*)f->Get("demo/scatterHist_effcorr");



	TCanvas* C = new TCanvas("fitscatterplot","EPOS Hydjet Scatterplot",1800,1200);

	C->Divide(3,2);
	C->cd(1);

	double newbins[8] = {-0.3,-0.075,-0.045,-0.015,0.015,0.045,0.075,0.3};
	//double newbins[6] = {-0.3,-0.045,-0.015,0.015,0.045,0.3};
	TH2D* hnew = new TH2D("rebin","rebin",7,newbins,1000,-0.3,0.3); 

	TAxis *xaxis = h2->GetXaxis();
	TAxis *yaxis = h2->GetYaxis();
	for (int k=1; k<=yaxis->GetNbins();k++) {
		for (int l=1; l<=xaxis->GetNbins();l++) {
			hnew->Fill(xaxis->GetBinCenter(l),yaxis->GetBinCenter(k),h2->GetBinContent(l,k));
		}
	}

	TProfile *prof = hnew->ProfileX();

	TF1* fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.2, 0.2);
	fit1->SetLineColor(kBlue);
	fit1->SetLineStyle(1);
	fit1->SetLineWidth(3);
	prof->Fit(fit1,"RN0");

	TLatex* text2 = makeLatex(Form("slope : %.3f #pm %.3f",fit1->GetParameter(1),fit1->GetParError(1)),0.55,0.25) ;
	prof->Draw();

	text2->Draw("same");
	fit1->Draw("same");


	


/*
	for (Int_t i=0;i<2;i++) {
		for (Int_t j=0;j<3;j++) {


			h = (TH2D*)f->Get("demo/scatterHist_noeffcorr");
			h -> new TH2D(" ");


			corrTable[oc]->SetBinContent(eta+1, pt+1, c);

			

			double c1 = testload.getWeight(ptbins[pt], etabins[eta], ocbin[oc], "eff");
			double c2 = testload.getWeight(ptbins[pt], etabins[eta], ocbin[oc], "fak");
			double c = c1/(1-c2);

			if( oc == 0 && eta == 15 && pt == 20 ) cout << "1: " << c << endl;
			if( oc == 4 && eta == 15 && pt == 20 ) cout << "4: " << c << endl;
				//cout << "corr factor: " << c << endl; 
			corrTable[oc]->SetBinContent(eta+1, pt+1, c);


			c = c1/(1-c2);
			c2 = c3/(1-c1);
			c4 = c2/(1-c3);
			c5 = c6/(1-c7);

*/
		}

