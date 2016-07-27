#include "RiceStyle.h"
using namespace std;

void genachdist(){

 TCanvas* C = new TCanvas("fitscatterplot","EPOS Hydjet Scatterplot",1500,500);
    //TCanvas* C2 = new TCanvas("EPOSoverHydjet","EPOS divided by Hydjet",1500,1000);
	     //C->SetCanvasSize(120,1000);
	// Number of PADS
 const Int_t Nx = 3;
 const Int_t Ny = 2;

    // Margins
 Float_t lMargin = 0.12;
 Float_t rMargin = 0.05;
 Float_t bMargin = 0.15;
 Float_t tMargin = 0.05;

	//CanvasPartition(C,Nx,Ny,lMargin,rMargin,bMargin,tMargin);
 C->Divide(Nx,Ny);

 TH2D* histlist[2][3];
 TH1D *profilelist[2][3];


 for (int i = 0; i < 3; ++i)
 {
  f = new TFile(Form("../../../rootfiles/MC/EPOS_PbPb_Ntrk_%d.root",i));

  histlist[0][i] = (TH2D*)f->Get("demo/scatterHist_noeffcorr");
  double n_entries; 
  n_entries = histlist[0][i]->GetEntries();
  cout << n_entries << endl;
  histlist[0][i]->Scale(1/n_entries);
  histlist[0][i]->Rebin2D(10,10);
  profilelist[0][i] = histlist[0][i]->ProjectionX();

}
for (int i = 0; i < 3; ++i)
{
  f = new TFile(Form("../../../rootfiles/MC/Hydjet_PbPb_Reweighted_%d.root",i));

  histlist[1][i] = (TH2D*)f->Get("demo/scatterHist_effcorr");
  double n_entries;
  n_entries = histlist[1][i]->GetEntries();
  histlist[1][i]->Scale(1/n_entries);
  histlist[1][i]->Rebin2D(10,10);
  profilelist[1][i] = histlist[1][i]->ProjectionX();


}  
TLatex* textlist[3]; 
textlist[0] = makeLatex("200 #leq N_{trk}^{offline} < 400",0.25,0.85);
textlist[1] = makeLatex("400 #leq N_{trk}^{offline} < 800",0.25,0.85);
textlist[2] = makeLatex("800 #leq N_{trk}^{offline} < 1500",0.25,0.85);

int n = 1;


for (Int_t j=0;j<3;j++) {
 C->cd(j+1);
 n++;


 TLatex *text1 = (TLatex*) textlist[j]->Clone();
 for(i=0;i<2;i++){

   //profilelist[i][j]->GetYaxis()->SetRangeUser(-0.25,0.25);
   //profilelist[i][j]->GetXaxis()->SetRangeUser(-0.25,0.25);



   profilelist[i][j]->GetYaxis()->SetLabelFont(43);
   profilelist[i][j]->GetYaxis()->SetLabelSize(16);
   profilelist[i][j]->GetYaxis()->SetLabelOffset(0.02);
   profilelist[i][j]->GetYaxis()->SetTitleFont(43);
   profilelist[i][j]->GetYaxis()->SetTitleSize(16);
   profilelist[i][j]->GetYaxis()->SetTitleOffset(5);

   profilelist[i][j]->GetYaxis()->CenterTitle();
   profilelist[i][j]->GetYaxis()->SetNdivisions(505);

   profilelist[i][j]->GetXaxis()->SetLabelFont(43);
   profilelist[i][j]->GetXaxis()->SetLabelSize(16);
   profilelist[i][j]->GetXaxis()->SetLabelOffset(0.02);
   profilelist[i][j]->GetXaxis()->SetTitleFont(43);
   profilelist[i][j]->GetXaxis()->SetTitleSize(16);
   profilelist[i][j]->GetXaxis()->SetTitleOffset(5);
   profilelist[i][j]->GetXaxis()->CenterTitle();
   profilelist[i][j]->GetXaxis()->SetNdivisions(505);

   if(i==0){
     profilelist[i][j]->SetMarkerStyle(20);
     profilelist[i][j]->SetMarkerSize(0.5);
     profilelist[i][j]->SetLineStyle(1);
     profilelist[i][j]->SetLineWidth(1);
          profilelist[i][j]->SetMarkerColor(kBlue);


   }
   if(i==1){

     profilelist[i][j]->SetMarkerStyle(20);
     profilelist[i][j]->SetMarkerSize(0.5);
     profilelist[i][j]->SetLineStyle(1);
     profilelist[i][j]->SetLineWidth(1);
     profilelist[i][j]->SetMarkerColor(kRed);

   }




 }	

 profilelist[0][j]->Draw();
 profilelist[1][j]->Draw("Same");




 text1->DrawClone("same");





}
}



