#include "RiceStyle.h"

void getsmearingfromfn()
{   


   TH1D* NTrkHist[15];
   TH1D* NTrkHist_cent[15]; 


   TF1* smearingfunction = new TF1("smearingfunction","0.430355*(1/sqrt(x)) + 0.00192817",0,1200);


   int N[9] = {90,120,150,185,220,260,300,400,500};
   int Ncent[6] = {30,40,50,60,70,80};
   double x[14];
   double x_cent[14];
   double y[14];
   double yerr[14];


   for(int i=0;i<8;i++){

      if(i==4){
         f = new TFile("../../../rootfiles/crosscheck/PbPb/v2/ntrk/220_260/Merged.root");


      }
      else{

         f = new TFile(Form("../../../rootfiles/closure/fctder_%d.root",N[i]));
         //f = new TFile(Form("../../../rootfiles/crosscheck/PbPb/v2/ntrk/%d_%d/Merged.root",N[i],N[i+1]));

      } 

      NTrkHist[i] =(TH1D*)f->Get("demo/NTrkHist"); 

      x[i] = NTrkHist[i]->GetMean();
      cout << x[i] << " " << endl;



   }

   cout << "E_E_E_E_E_E" << endl;

   for(int i=0;i<6;i++){
      if(i==1){

         f = new TFile("../../../rootfiles/crosscheck/PbPb/v2/40_50/Merged.root");



      }

      else if(i==4){
         f = new TFile("../../../rootfiles/crosscheck/PbPb/v2/70_80/Merged.root");
      }
      else if(i==5){
         f = new TFile("../../../rootfiles/crosscheck/PbPb/v2/80_90/Merged.root");

      }
      else{

         f = new TFile(Form("../../../rootfiles/closure/fctdercent_%d.root",Ncent[i]));

      } 

      NTrkHist_cent[i] =(TH1D*)f->Get("demo/NTrkHist"); 

      x_cent[i] = NTrkHist_cent[i]->GetMean();
      cout << x_cent[i] << " " << endl;



   }


}










