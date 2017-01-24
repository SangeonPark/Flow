#include "RiceStyle.h"

void achDistwithVerticalLines()
{   

   TH1D* achdist[6];
   TH1D* achdisttemp[6][7];
   int ntrklist[7] = {90,120,150,185,220,260,300};

//   TH1D* achdist[6];
//   int centralitylist[7] = {30,40,50,60,70,80,90}
   gStyle->SetLegendFont(42);
   TCanvas* c1 = new TCanvas("c1","c1",1,1,600,600);


   //f = new TFile("~/Summer2016/rootfiles/FinalResult_0106/Main_PbPb_Merged.root");
      f = new TFile("~/Summer2016/rootfiles/FinalResult_0106/Main_pPb_Merged.root");


   achdist[3] = (TH1D*)f->Get("demo_n3/ChargeAsym");
  // achdist[3]->Rebin(5);

   achdist[3]->GetXaxis()->SetRangeUser(-0.25, 0.25);
  // achdist[3]->GetYaxis()->SetRangeUser(0, 500000);

   //achdist[3]->SetMarkerColor(kBlue);

 /*  TLine *l1 = new TLine(-0.07,0,-0.07,300000);
   TLine *l2 = new TLine(-0.03,0,-0.03,400000);
   TLine *l3 = new TLine(-0.01,0,-0.01,450000);
   TLine *l4 = new TLine(0.01,0,0.01,450000);
   TLine *l5 = new TLine(0.03,0,0.03,400000);
   TLine *l6 = new TLine(0.07,0,0.07,300000);
*/
   TLine *l1 = new TLine(-0.085,0,-0.085,300000);
   TLine *l2 = new TLine(-0.05,0,-0.05,400000);
   TLine *l3 = new TLine(-0.025,0,-0.025,450000);
   TLine *l4 = new TLine(0.025,0,0.025,450000);
   TLine *l5 = new TLine(0.05,0,0.05,400000);
   TLine *l6 = new TLine(0.085,0,0.085,300000);
   l1->SetLineColor(kBlue);
   l1->SetLineStyle(2);
   l1->SetLineWidth(3);

   l2->SetLineColor(kBlue);
   l2->SetLineStyle(2);
   l2->SetLineWidth(3);

   l3->SetLineColor(kBlue);
   l3->SetLineStyle(2);
   l3->SetLineWidth(3);

   l4->SetLineColor(kBlue);
   l4->SetLineStyle(2);
   l4->SetLineWidth(3);

   l5->SetLineColor(kBlue);
   l5->SetLineStyle(2);
   l5->SetLineWidth(3);

   l6->SetLineColor(kBlue);
   l6->SetLineStyle(2);
   l6->SetLineWidth(3);



   achdist[3]->Draw();
   achdist[3]->GetXaxis()->SetTitle("Observed A_{ch}");
   achdist[3]->GetYaxis()->SetTitle("Count");
   achdist[3]->GetXaxis()->CenterTitle();
   achdist[3]->GetYaxis()->CenterTitle();
   achdist[3]->SetTitleSize  (0.040,"X");
   achdist[3]->SetTitleOffset(1.4,"X");
   achdist[3]->SetTitleFont  (42,"X");
   achdist[3]->SetLabelOffset(0.006,"X");
   achdist[3]->SetLabelSize  (0.040,"X");
   achdist[3]->SetLabelFont  (42   ,"X");

   achdist[3]->SetTitleSize  (0.040,"Y");
   achdist[3]->SetTitleOffset(2.2,"Y");
   achdist[3]->SetTitleFont  (42,"Y");
   achdist[3]->SetLabelOffset(0.006,"Y");
   achdist[3]->SetLabelSize  (0.040,"Y");
   achdist[3]->SetLabelFont  (42   ,"Y");
   achdist[3]->SetLineWidth(0);
   TLatex* text_a = makeLatex("CMS PbPb #sqrt{s_{NN}}=5.02TeV",0.23,0.87) ;

   TLatex* text_b = makeLatex("30-40%",0.23,0.82) ;

   TLatex* text_c = makeLatex("0.3 < p_{T} < 3.0 GeV/c",0.23,0.75) ;

   text_a->SetTextFont(42);

   text_b->SetTextFont(42);

   text_c->SetTextFont(42);

   text_a->DrawClone("Same");
   text_b->DrawClone("Same");
   //text_c->DrawClone("Same");


   l1->Draw("same");
   l2->Draw("same");
   l3->Draw("same");
   l4->Draw("same");
   l5->Draw("same");
   l6->Draw("same");
   SaveCanvas(c1,"pics","achwithverticallines");

}