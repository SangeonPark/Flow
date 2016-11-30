#include "RiceStyle.h"

void getsmearingfromfn()
{   


   TH1D* NTrkHist[16];
   TH1D* NTrkHist_cent[16]; 


   TF1* smearingfunction = new TF1("smearingfunction","0.407811*(1/sqrt(x)) + 0.00275936",0,1200);


   int N[9] = {90,120,150,185,220,260,300,400,500};
   int Ncent[7] = {30,40,50,60,70,80,90};
   double x[14];
   double x_cent[14];
   double y[14];
   double yerr[14];


   for(int i=0;i<14;i++){
      if(i<8){
         //f = new TFile(Form("../../../rootfiles/closure/final/closure_mult_%d.root",N[i]));
         f = new TFile(Form("../../../rootfiles/crosscheck/PbPb/v2/ntrk/%d_%d/Merged.root",N[i],N[i+1]));
      }
      else{
         //f = new TFile(Form("../../../rootfiles/closure/final/closure_cent_%d.root",Ncent[i-8]));
         f = new TFile(Form("../../../rootfiles/crosscheck/PbPb/v2/%d_%d/Merged.root",Ncent[i-8],Ncent[i-7]));
      }

      NTrkHist[i] =(TH1D*)f->Get("demo/NTrkHist"); 

      x[i] = NTrkHist[i]->GetMean();
      if(i<8){
         cout << N[i] << "-" << N[i+1] << " : " << smearingfunction->Eval(x[i]) << endl;
      }
      else{
         cout << Ncent[i-8] << "-" << Ncent[i-7] << "% : " << smearingfunction->Eval(x[i]) << endl;


      }



   }



}










