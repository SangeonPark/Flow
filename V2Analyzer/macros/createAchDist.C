#include "RiceStyle.h"

void createAchDist()
{   
   /*
   TH1D* achdist[6];
   TH1D* achdisttemp[6][7];
   int ntrklist[7] = {90,120,150,185,220,260,300};
   */

   TH1D* achdist[6];
   int centralitylist[7] = {30,40,50,60,70,80,90}
   gStyle->SetLegendFont(42);


   for (int i = 0; i < 6; ++i)
   {
      cout << i << endl;

      //f = new TFile(Form("~/Summer2016/rootfiles/crosscheck/v2_pPb_%d_%d_AchCorrected/Merged.root",ntrklist[i],ntrklist[i+1]));
      f = new TFile(Form("~/Summer2016/rootfiles/crosscheck/PbPb/%d_%d/Merged.root",centralitylist[i],centralitylist[i+1]));
      /*

      for (Int_t j = 0; j < 7; j++){

         achdisttemp[i][j] = (TH1D*)f->Get(Form("demo/ach_%d",j+1));

      }

      achdist[i] = (TH1D*)f->Get("demo/ach_1");

      for(j = 1; j< 7; j++){
         achdist[i] -> Add(achdisttemp[i][j],1.0);
      }
      */

      achdist[i] = (TH1D*)f->Get(Form("demo/ChargeAsym"));

      achdist[i]->SetName(Form("h_%d",i));
      
   }

   cout << "nice" << endl;



   TFile *histlist = new TFile("~/Summer2016/achdistribution/achdist_PbPb_6ranges.root","RECREATE");

   for (int i = 0; i < 6; ++i)
   {
      achdist[i]->Write();      
   
   }

   histlist->Close();


}