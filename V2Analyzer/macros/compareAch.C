#include "RiceStyle.h"

void compareAch()
{   

   TH1D* ChargeAsym;
   TH1D* weiAch;
   TH1D* myAch;
   TH1D* myAchtemp[7];
   gStyle->SetLegendFont(42);


   TCanvas *c1 = new TCanvas("c1","show profile",1,1,600,600);

   c1->cd();

   f = new TFile("../../../rootfiles/AchDistribution/chasymdihadroncorrelation_pPb_n185220_all_eff_v5.root");

   weiAch = (TH1D*)f->Get("corr_ana_pPb_pos/multchargeasym");


   f = new TFile("../../../rootfiles/AchDistribution/Merged.root");

   for (Int_t i = 0; i < 7; i++){

      myAchtemp[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));


   }

   myAch = (TH1D*)f->Get("demo/ach_1");

   for(i = 1; i< 7; i++){

      myAch -> Add(myAchtemp[i],1.0);
   }

   myAch->GetXaxis()->SetRangeUser(-0.25,0.25);
   myAch->GetYaxis()->SetRangeUser(0,600000);

   myAch->GetXaxis()->SetTitle("A_{ch}");
   myAch->GetYaxis()->SetTitle(" Counts ");
   myAch->GetXaxis()->CenterTitle();
   myAch->GetYaxis()->CenterTitle();
   myAch->SetTitleOffset(1.8,"Y");

   myAch->SetMarkerStyle(24);
   myAch->SetMarkerColor(kBlack);
   myAch->SetMarkerSize (1);
   myAch->SetLineStyle(1);
   myAch->SetLineWidth(1);   

   weiAch->SetMarkerStyle(20);
   weiAch->SetMarkerColor(kRed);
   weiAch->SetMarkerSize (1);
   weiAch->SetLineStyle(1);
   weiAch->SetLineWidth(1); 

   Double_t norm = 1;
   myAch->Scale(norm, "width");
   weiAch->Scale(norm,"width");

   //myAch->Rebin(10);
   //weiAch->Rebin(10);


   //TLatex* text_a = makeLatex("EPOS",0.25,0.85) ;
   TLegend* leg = new TLegend(0.76,0.80,0.94,.88);
   leg->SetLineColor(kWhite);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->AddEntry(myAch, "my Result","p");
   leg->AddEntry(weiAch , "Wei's Result","p");



   myAch->Draw();
   weiAch->Draw("same");
   leg->Draw("same");
   //text_a->Draw("same");

   SaveCanvas(c1,"pics","comparing_Ach_Distribution");



}