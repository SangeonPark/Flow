#include "RiceStyle.h"

void Nposnegdist()
{
   //example illustrating how to fit a 2-d histogram of type y=f(x)
   //Author: Rene Brun

   // generate a 2-d histogram using a TCutG

   TCanvas *c1 = new TCanvas("c1","show profile",1,1,1200,600);
   c1->Divide(2,1,0.01,0.01);
   TFile *f;

   f = new TFile("../../../rootfiles/MC/EPOS_PbPb_pteta_0.root");
   
   TH2D* h_epos_pos_temp = (TH2D*)f->Get("demo/Npos_scatterHist_noeffcorr");
   TH2D* h_epos_pos = h_epos_pos_temp->Clone();

   h_epos_pos->Rebin2D(5,1);


   TH2D* h_epos_neg_temp = (TH2D*)f->Get("demo/Nneg_scatterHist_noeffcorr");
   TH2D* h_epos_neg = h_epos_neg_temp->Clone();


   h_epos_neg->Rebin2D(5,1);

//  TLatex* text_a = makeLatex("EPOS",0.25,0.85) ;
//   TLatex* text_b = makeLatex("EPOS",0.7,0.85) ;
   f = new TFile("../../../rootfiles/MC/Hydjet_PbPb_pteta_0.root");
   
   TH2D* h_hydjet_pos_temp = (TH2D*)f->Get("demo/Npos_scatterHist_noeffcorr");

   TH2D* h_hydjet_pos = h_hydjet_pos_temp->Clone();

   h_hydjet_pos->Rebin2D(5,1);


   TH2D* h_hydjet_neg_temp = (TH2D*)f->Get("demo/Nneg_scatterHist_noeffcorr");


   TH2D* h_hydjet_neg = h_hydjet_neg_temp->Clone();

   h_hydjet_neg->Rebin2D(5,1);




   c1->cd(1);

   //use a TProfile to convert the 2-d to 1-d problem
   TProfile *prof_epos_pos_temp = h_epos_pos->ProfileX();

   TProfile* prof_epos_pos = prof_epos_pos_temp->Clone();

   TProfile *prof_hydjet_pos_temp = h_hydjet_pos->ProfileX();

   TProfile* prof_hydjet_pos = prof_hydjet_pos_temp->Clone();


   TProfile *prof_epos_neg_temp = h_epos_neg->ProfileX();

   TProfile* prof_epos_neg = prof_epos_neg_temp->Clone();



   TProfile *prof_hydjet_neg_temp= h_hydjet_neg->ProfileX();

   TProfile* prof_hydjet_neg = prof_hydjet_neg_temp->Clone();


   TH1D* base = new TH1D("base","base",1,0,400);
   base->GetYaxis()->SetRangeUser(0, 400);




   //prof->Fit("pol1");
   prof_epos_pos->GetYaxis()->SetRangeUser(0,400);
   prof_epos_pos->GetXaxis()->SetRangeUser(0,400);
   prof_hydjet_pos->GetYaxis()->SetRangeUser(0,400);
   prof_hydjet_pos->GetXaxis()->SetRangeUser(0,400);

   prof_epos_pos->SetMarkerStyle(20);
   prof_epos_pos->SetMarkerColor(kBlue);
   prof_epos_pos->SetMarkerSize (1);
   prof_epos_pos->SetLineStyle(1);
   prof_epos_pos->SetLineWidth(1);   

   prof_hydjet_pos->SetMarkerStyle(22);
   prof_hydjet_pos->SetMarkerColor(kRed);
   prof_hydjet_pos->SetMarkerSize (1);
   prof_hydjet_pos->SetLineStyle(1);
   prof_hydjet_pos->SetLineWidth(1); 

   TF1* fit1 = new TF1("f1", "[0]+x*[1]", 80, 300);
   fit1->SetLineColor(kBlue);
   fit1->SetLineStyle(1);
   fit1->SetLineWidth(3);
   prof_epos_pos->Fit(fit1,"RN0");

   TF1* fit2 = new TF1("f2", "[0]+x*[1]", 80, 300);
   fit2->SetLineColor(kRed);
   fit2->SetLineStyle(1);
   fit2->SetLineWidth(3);
   prof_hydjet_pos->Fit(fit2,"RN0");


   TLatex* epos = makeLatex(Form("EPOS slope : %.3f #pm %.3f",fit1->GetParameter(1),fit1->GetParError(1)),0.55,0.25) ;
   TLatex* hydjet = makeLatex(Form("Hydjet slope : %.3f #pm %.3f",fit2->GetParameter(1),fit2->GetParError(1)),0.55,0.20) ;


//base->Draw();
//   prof_epos_pos->Draw();
//   prof_hydjet_pos->Draw("same");
   h_epos_pos->Draw("samecolz");
   //h_hydjet_pos->Draw("samecolz");


   fit1->Draw("same");
   fit2->Draw("same");
   epos->Draw("same");
   hydjet->Draw("same");







/*
   prof->SetYTitle("A_{ch}");
   prof -> GetXaxis() -> CenterTitle();
   prof -> GetYaxis() -> CenterTitle();
   prof->SetLabelOffset(0.006,"Y");
   prof->SetTitleOffset(1.800,"Y");
   prof->SetMarkerStyle(20);
   prof->SetMarkerColor(kBlack);
   prof->SetMarkerSize (0.3);
   prof->SetMarkerStyle(1);
   prof->SetLineStyle(1);
   prof->SetLineWidth(1);   
   prof->Fit("pol1");
   TF1 *fit1 = prof->GetListOfFunctions()->FindObject("pol1");
   TLatex* text2 = makeLatex(Form("slope : %.3f #pm %.3f",fit1->GetParameter(1),fit1->GetParError(1)),0.55,0.25) ;


   if(fit1)
   {
      fit1->SetLineColor(4); 
      fit1->SetLineWidth(3);
      fit1->SetLineStyle(1);
   }

   text_a->Draw("Same");
   text2->Draw("Same");
   TF1 *fa1 = new TF1("fa1","0",-10,10); 
   fa1->SetLineColor(kBlack);
   fa1->SetLineWidth(1);
   fa1->DrawClone("Same"); */



/*original
   h2->Rebin2D(5,8);
   c1->cd(1);
   c1->cd(1)->SetRightMargin(0.12);


   h2 -> GetXaxis()->CenterTitle();
   h2 -> GetYaxis()->CenterTitle();
   h2->Draw("colz");
   text_a->Draw("Same");

   */


   c1->cd(2);

   prof_epos_neg->GetYaxis()->SetRangeUser(0,400);
   prof_epos_neg->GetXaxis()->SetRangeUser(0,400);
   prof_hydjet_neg->GetYaxis()->SetRangeUser(0,400);
   prof_hydjet_neg->GetXaxis()->SetRangeUser(0,400);

   prof_epos_neg->SetMarkerStyle(20);
   prof_epos_neg->SetMarkerColor(kBlue);
   prof_epos_neg->SetMarkerSize (1);
   prof_epos_neg->SetLineStyle(1);
   prof_epos_neg->SetLineWidth(1);   

   prof_hydjet_neg->SetMarkerStyle(22);
   prof_hydjet_neg->SetMarkerColor(kRed);
   prof_hydjet_neg->SetMarkerSize (1);
   prof_hydjet_neg->SetLineStyle(1);
   prof_hydjet_neg->SetLineWidth(1);   

   TF1* fit3 = new TF1("f3", "[0]+x*[1]", 80, 300);
   fit3->SetLineColor(kBlue);
   fit3->SetLineStyle(1);
   fit3->SetLineWidth(3);
   prof_epos_neg->Fit(fit3,"RN0");

   TF1* fit4 = new TF1("f4", "[0]+x*[1]", 80, 300);
   fit4->SetLineColor(kRed);
   fit4->SetLineStyle(1);
   fit4->SetLineWidth(3);
   prof_hydjet_neg->Fit(fit4,"RN0");

//   prof_epos_neg->DrawClone("");
//   prof_hydjet_neg->DrawClone("same");

  // base->Draw();

   h_epos_neg->Draw("samecolz");
   //h_hydjet_neg->Draw("samecolz");

   fit3->Draw("same");

   fit4->Draw("same");


   TLatex* epos_neg = makeLatex(Form("EPOS slope : %.3f #pm %.3f",fit3->GetParameter(1),fit3->GetParError(1)),0.55,0.25) ;
   TLatex* hydjet_neg = makeLatex(Form("Hydjet slope : %.3f #pm %.3f",fit4->GetParameter(1),fit4->GetParError(1)),0.55,0.20) ;
   epos_neg->Draw("same");
   hydjet_neg->Draw("same");

   SaveCanvas(c1,"pics","NscatterhistHydjet_noeffcor");






   //prof->Draw();   

}

