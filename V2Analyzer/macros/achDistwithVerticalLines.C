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


   for (int i = 3; i < 4; ++i)
   {
      cout << i << endl;

      f = new TFile(Form("~/Summer2016/rootfiles/crosscheck/pPb/v2/%d_%d/Merged.root",ntrklist[i],ntrklist[i+1]));
      //f = new TFile(Form("~/Summer2016/rootfiles/crosscheck/PbPb/v2/ntrk/%d_%d/Merged.root",centralitylist[i],centralitylist[i+1]));
      
      cout << "yeah" << endl;

      for (Int_t j = 0; j < 7; j++){

         achdisttemp[i][j] = (TH1D*)f->Get(Form("demo/ach_%d",j+1));

      }

      achdist[i] = (TH1D*)f->Get("demo/ach_1");

      for(j = 1; j< 7; j++){
         achdist[i] -> Add(achdisttemp[i][j],1.0);
      }
      


      achdist[i]->SetName(Form("h_%d",i));
      
   }
   achdist[3]->GetXaxis()->SetRangeUser(-0.25, 0.25);
   //achdist[3]->SetMarkerColor(kBlue);

   TLine *l1 = new TLine(-0.09,0,-0.09,40000);
   TLine *l2 = new TLine(-0.05,0,-0.05,55000);
   TLine *l3 = new TLine(-0.015,0,-0.015,60000);
   TLine *l4 = new TLine(0.015,0,0.015,60000);
   TLine *l5 = new TLine(0.05,0,0.05,55000);
   TLine *l6 = new TLine(0.09,0,0.09,40000);

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
   l1->Draw("same");
   l2->Draw("same");
   l3->Draw("same");
   l4->Draw("same");
   l5->Draw("same");
   l6->Draw("same");
   SaveCanvas(c1,"pics","achwithverticallines");

}