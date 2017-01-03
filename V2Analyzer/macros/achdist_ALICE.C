#include "RiceStyle.h"

void achdist_ALICE()
{   

   TH1D* achdist[100];
   TH1D* NtrkDist[100];

   f = new TFile("~/Summer2016/rootfiles/FinalResult_Cumulant/temp_Merged.root");

   achdist[0] = (TH1D*)f->Get("demo_n9/ChargeAsym");
   achdist[0]->SetName("h_0");
  
   TFile *histlist = new TFile("~/Summer2016/achdistribution/ALICE_noachweight.root","RECREATE");

   achdist[0]->Write();


   

   histlist->Close();


}