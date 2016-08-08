#include "RiceStyle.h"

void recogenach()
{   

   TH1D* ChargeAsym;
   TH1D* genAch;
   TH1D* genAchtemp[5];
   TH1D* recoAch;
   TH1D* recoAchtemp[5];


   TCanvas *c1 = new TCanvas("c1","show profile",1,1,1200,600);
   c1->Divide(2,1,0.01,0.01);

   TCanvas *c2 = new TCanvas("c2","show profile",1,1,1200,600);
   c2->Divide(2,1,0.01,0.01);
   c1->cd(1);

   f = new TFile("../../../rootfiles/MC/EPOS_newefftable_0.root");


   for (Int_t i = 0; i < 5; i++){

      genAchtemp[i] = (TH1D*)f->Get(Form("demo/gen_ach_%d",i+1));
      recoAchtemp[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));


   }

   genAch = (TH1D*)f->Get("demo/gen_ach_1");
   recoAch = (TH1D*)f->Get("demo/ach_1");


   for(i = 1; i< 5; i++){

      genAch -> Add(genAchtemp[i],1.0);
      recoAch -> Add(recoAchtemp[i],1.0);
   }

   recoAch->GetXaxis()->SetRangeUser(-0.25,0.25);
   recoAch->GetYaxis()->SetRangeUser(0,600);

   recoAch->GetXaxis()->SetTitle("A_{ch}");
   recoAch->GetYaxis()->SetTitle(" Counts ");
   recoAch->GetXaxis()->CenterTitle();
   recoAch->GetYaxis()->CenterTitle();
   recoAch->SetTitleOffset(1.8,"Y");

   recoAch->SetMarkerStyle(20);
   recoAch->SetMarkerColor(kBlue);
   recoAch->SetMarkerSize (1);
   recoAch->SetLineStyle(1);
   recoAch->SetLineWidth(1);   

   genAch->SetMarkerStyle(25);
   genAch->SetMarkerColor(kRed);
   genAch->SetMarkerSize (1);
   genAch->SetLineStyle(1);
   genAch->SetLineWidth(1); 

   recoAch->Rebin(10);
   genAch->Rebin(10);


   TLatex* text_a = makeLatex("EPOS",0.25,0.85) ;


   recoAch->Draw();
   genAch->Draw("same");
   text_a->Draw("same");


   c2->cd(1);

   TH1D* ratio_EPOS = (TH1D*) genAch->Clone();

   ratio_EPOS->Divide(recoAch);

   ratio_EPOS->SetMarkerStyle(20);
   ratio_EPOS->SetMarkerColor(kBlack);
   ratio_EPOS->SetMarkerSize (1);
   ratio_EPOS->SetLineStyle(1);
   ratio_EPOS->SetLineWidth(1); 
   ratio_EPOS->Draw();
   


   c1->cd(2);

   f = new TFile("../../../rootfiles/MC/Hydjet_newefftable_0.root");


   for (Int_t i = 0; i < 5; i++){

      genAchtemp[i] = (TH1D*)f->Get(Form("demo/gen_ach_%d",i+1));
      recoAchtemp[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));


   }

   genAch = (TH1D*)f->Get("demo/gen_ach_1");
   recoAch = (TH1D*)f->Get("demo/ach_1");


   for(i = 1; i< 5; i++){

      genAch -> Add(genAchtemp[i],1.0);
      recoAch -> Add(recoAchtemp[i],1.0);
   }

   recoAch->GetXaxis()->SetRangeUser(-0.25,0.25);
   recoAch->GetYaxis()->SetRangeUser(0,600);

   recoAch->GetXaxis()->SetTitle("A_{ch}");
   recoAch->GetYaxis()->SetTitle(" Counts ");
   recoAch->GetXaxis()->CenterTitle();
   recoAch->GetYaxis()->CenterTitle();
   recoAch->SetTitleOffset(1.8,"Y");

   recoAch->SetMarkerStyle(20);
   recoAch->SetMarkerColor(kBlue);
   recoAch->SetMarkerSize (1);
   recoAch->SetLineStyle(1);
   recoAch->SetLineWidth(1);   

   genAch->SetMarkerStyle(25);
   genAch->SetMarkerColor(kRed);
   genAch->SetMarkerSize (1);
   genAch->SetLineStyle(1);
   genAch->SetLineWidth(1); 

   recoAch->Rebin(10);
   genAch->Rebin(10);


   TLatex* text_b = makeLatex("Hydjet",0.25,0.85) ;


   recoAch->Draw();
   genAch->Draw("same");
   text_b->Draw("same");

   TH1D* ratio_Hydjet = (TH1D*) genAch->Clone();
   ratio_Hydjet->Divide(recoAch);

   c2->cd(2);
   ratio_Hydjet->SetMarkerStyle(20);
   ratio_Hydjet->SetMarkerColor(kBlack);
   ratio_Hydjet->SetMarkerSize (1);
   ratio_Hydjet->SetLineStyle(1);
   ratio_Hydjet->SetLineWidth(1);   

   ratio_Hydjet->Draw();

   




}