#include "RiceStyle.h"

void achdist_Appletoapple()
{   

   TH1D* achdist[100];
   TH1D* NtrkDist[100];

   f = new TFile("~/Summer2016/rootfiles/appletoapple/ALICE.root");

   achdist[0] = (TH1D*)f->Get("demo/ChargeAsym");
   achdist[0]->SetName("h_0");
   NtrkDist[0] = (TH1D*)f->Get("demo/NTrkHist");

   f = new TFile("~/Summer2016/rootfiles/appletoapple/STAR.root");

   achdist[1] = (TH1D*)f->Get("demo/ChargeAsym");
   achdist[1]->SetName("h_1");
   NtrkDist[1] = (TH1D*)f->Get("demo/NTrkHist");

   TFile *histlist = new TFile("~/Summer2016/achdistribution/ALICE_and_STAR.root","RECREATE");

   achdist[0]->Write();
   achdist[1]->Write();


   cout << "Mean Ntrk ALICE : " << NtrkDist[0]->GetMean() << endl;   
   cout << "Mean Ntrk STAR : " << NtrkDist[1]->GetMean() << endl;      
   

   histlist->Close();


}