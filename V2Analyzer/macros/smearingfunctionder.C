#include "RiceStyle.h"

void smearingfunctionder()
{   

   TH1D* genAch[15];
   TH1D* recoAch[15];
   TH1D* smearingAch[15][4];
   TH1D* NTrkHist[15]; 
   TH2D* genrecoach[15];
   gStyle->SetLegendFont(42);
   TF1* smearingfit[15][4];
   TF1* genfit[15];
   TF1* recofit[15];
   for(int i=0; i<14;i++){

      for (int j = 0; j < 4; ++j){
         smearingfit[i][j] = new TF1(Form("smearingfit_%d_%d",i,j),"[0]*exp(-0.5*(x-[1])*(x-[1])/([2]*[2]))/sqrt(2*pi*[2]*[2])", -1, 1);
      }
   }




   TCanvas *c1 = new TCanvas("c1","show profile",1,1,600,600);
   TCanvas *c2 = new TCanvas("c2","show profile",2,2,1200,1200);
   TCanvas *c3 = new TCanvas("c3","show profile",1,2,600,1200);
   c3->Divide(1,2);


   c2->Divide(2,2);

   //int N[7] = {90,120,150,185,260,300,400};
   int N[9] = {90,120,150,185,220,260,300,400,500};
   int Ncent[7] = {30,40,50,60,70,80,90};


   double x[14];
   double y[14];
   double yerr[14];
   double xerr[14];

   double smearingmean[14];


   double smearingwidth;


   for(int i=0;i<14;i++){


      if(i<8){
         f = new TFile(Form("../../../rootfiles/closure/final/closure_mult_%d.root",N[i]));
      }
      else{
         f = new TFile(Form("../../../rootfiles/closure/final/closure_cent_%d.root",Ncent[i-8]));
      }

     // cout << "ive reached : " << i << endl;


      genAch[i] = (TH1D*)f->Get("demo/GenChargeAsym");
      recoAch[i] = (TH1D*)f->Get("demo/RecoChargeAsym");
      genrecoach[i] = (TH2D*)f->Get("demo/genrecoach");
      NTrkHist[i] =(TH1D*)f->Get("demo/NTrkHist"); 



      genAch[i]->Rebin(20);
      recoAch[i]->Rebin(20);


      genAch[i]->Scale(1.0/genAch[i]->Integral());
      recoAch[i]->Scale(1.0/recoAch[i]->Integral());

      //cout << "ive reached : " << i << endl;

      genfit[i] = new TF1(Form("genfit_%d",i),"gaus", -1, 1);
      recofit[i] = new TF1(Form("recofit_%d",i),"gaus", -1, 1);
      genfit[i]->SetParameters(0.1,0,0.05);
      recofit[i]->SetParameters(0.1,0,0.05);


      genAch[i]->Fit(genfit[i],"RN0");
      recoAch[i]->Fit(recofit[i],"RN0");

      //cout << "this importnat point : " << i << endl;

      

      if(i==1){
         c3->cd(1);
         genAch[i]->Draw();
         genfit[i]->Draw("Same");
         c3->cd(2);
         recoAch[i]->Draw();
         recofit[i]->Draw("Same");
      }




      double genwidth = genfit[i]->GetParameter(2);
      double recowidth = recofit[i]->GetParameter(2);
      TAxis *yaxis = genrecoach[i]->GetYaxis();

      double ach_low=-genwidth;
      double ach_high=0.0;
      double sum_smearingwidth=0.0;
      double sum_stdev = 0.0;
      double var_smearingwidth=0.0;
      double var_stdev = 0.0;

      double smearing_prediction;
      smearing_prediction = sqrt(recowidth*recowidth-genwidth*genwidth);

      //cout << "point2 : " << i << endl;
      double smearingmean_temp = 0.0;


      for (int j=0;j<4;j++){
         double mean;


         

         //cout << "point3 : " << i <<" "<< j<< endl;




         smearingAch[i][j] = genrecoach[i]->ProjectionX(Form("smearingdist_%f_%f",ach_low,ach_high),yaxis->FindBin(ach_low),yaxis->FindBin(ach_high));
         
         //cout << "point3-prime : " << i <<" "<< j<< endl;


         smearingAch[i][j]->Rebin(20);

         //cout << "point3-prime1 : " << i <<" "<< j<< endl;

         smearingAch[i][j]->Scale(1.0/smearingAch[i][j]->Integral());

         //cout << "point3-prime2 : " << i <<" "<< j<< endl;

         mean = smearingAch[i][j]->GetMean();

         //cout << "point3-prime3 : " << mean <<" "<< smearing_prediction<< endl;

         smearingfit[i][j]->SetParameters(0.1,mean,smearing_prediction);

         //cout << "point4 : " << i <<" "<< j<< endl;


         smearingAch[i][j]->Fit(smearingfit[i][j],"RN0","",-0.5,0.5);
         double smearingwidth_temp = smearingfit[i][j]->GetParameter(2);
         double stdev_temp = smearingAch[i][j]->GetStdDev();
         double err_temp = smearingfit[i][j]->GetParError(2);
         double stderr_temp = smearingAch[i][j]->GetStdDevError();
         smearingmean_temp += smearingfit[i][j]->GetParameter(1);
         sum_smearingwidth+=smearingwidth_temp;
         sum_stdev += stdev_temp; 

         var_smearingwidth += err_temp*err_temp;
         var_stdev += stderr_temp*stderr_temp;


         //cout << "point5 : " << i <<" "<< j<< endl;


         ach_low += (genwidth*0.5);
         ach_high += (genwidth*0.5);
         
         if(i==8){
            c2->cd(j+1);
            smearingAch[i][j]->Draw();
            smearingfit[i][j]->Draw("same");
            TLatex* text4 = makeLatex(Form("smearing mean : %f",smearingfit[i][j]->GetParameter(1)),0.70,0.71) ;
            text4->Draw("same");

         }
         


      }




      //smearingwidth = sum_stdev/4.0;
      smearingwidth = sum_smearingwidth/4.0;

      //cout << "sum smearingwidth : " << sum_smearingwidth << endl;

      //cout << "smearing widdth : " << smearingwidth << endl;

      x[i] = NTrkHist[i]->GetMean();
      smearingmean[i]=smearingmean_temp/4.0;


      y[i] = smearingwidth;
      yerr[i] = sqrt(var_smearingwidth);
      xerr[i] = NTrkHist[i]->GetMeanError();
      //yerr[i] = sqrt(var_stdev);


   }
   for(i=0;i<14;i++){
      if(i<8){
         cout << N[i] << "-" << N[i+1] << " : " << smearingmean[i] << endl;
      }
      else{
         cout << Ncent[i-8] << "-" << Ncent[i-7] << "% : " << smearingmean[i] << endl;
      }
   }
   c1->cd();

   TGraphErrors* smearing_fuc = new TGraphErrors(10,x,y,xerr,yerr);

   TH1D* base1 = makeHist("base1", "", "N^{offline}_{trk}", "#sigma_{smearing}", 6000,0, 6000, kBlack);
   TH1D* base2 = makeHist("base2", "", "Observed A_{ch}", "v_{2}(-) - v_{2}(+)", 1000, -0.2, 0.2, kBlack);

   fixedFontHist1D(base1,1.1,1.3);

   base1->GetYaxis()->SetRangeUser(0.0, 0.05);
   base1->GetXaxis()->SetRangeUser(0, 1500);
   base1->GetXaxis()->SetTitleColor(kBlack);
   base1->GetYaxis()->SetTitleOffset(1.5);
   base1->GetYaxis()->SetTitleSize(base1->GetYaxis()->GetTitleSize()*1.4);
   base1->GetXaxis()->SetTitleSize(base1->GetXaxis()->GetTitleSize()*1.4);
   base1->GetYaxis()->SetLabelSize(base1->GetYaxis()->GetLabelSize()*1.5);
   base1->GetXaxis()->SetLabelSize(base1->GetXaxis()->GetLabelSize()*1.4);
   base1->GetXaxis()->SetNdivisions(8,5,0);
   base1->GetYaxis()->SetNdivisions(4,6,0);

   fixedFontHist1D(base2,1.1,1.25);

   base2->GetYaxis()->SetRangeUser(-0.015, 0.015);
   base2->GetXaxis()->SetRangeUser(-0.1,0.1);
   base2->GetXaxis()->SetTitleColor(kBlack);
   base2->GetYaxis()->SetTitleOffset(1.23);
   base2->GetYaxis()->SetTitleSize(base2->GetYaxis()->GetTitleSize()*1.4);
   base2->GetXaxis()->SetTitleSize(base2->GetXaxis()->GetTitleSize()*1.4);
   base2->GetYaxis()->SetLabelSize(base2->GetYaxis()->GetLabelSize()*1.5);
   base2->GetXaxis()->SetLabelSize(base2->GetXaxis()->GetLabelSize()*1.4);
   base2->GetXaxis()->SetNdivisions(8,18,0);
   base2->GetYaxis()->SetNdivisions(4,6,0);

   gPad->SetTicks();
   gPad->SetLeftMargin(0.13);
   gPad->SetBottomMargin(0.13);
   gPad->SetRightMargin(0.05);
   gStyle->SetPadBorderMode(0.1);
   gStyle->SetOptTitle(0);

   base1->Draw();



   TF1 *myfit = new TF1("myfit","[0]*(1/sqrt(x)) + [1]", 0, 1200);
   myfit->SetParameters(0.4,0.002);

   smearing_fuc->Fit(myfit,"RN0");



   TLatex* text1 = makeLatex(Form("Data : y=%.4f/#sqrt{x}+%.4f",myfit->GetParameter(0),myfit->GetParameter(1)),0.50,0.65) ;
   TLatex* text2 = makeLatex("Hydjet : y=0.3875/#sqrt{x}+0.0021",0.50,0.58) ;
   TLatex* text3 = makeLatex("EPOS : y=0.3261/#sqrt{x}+0.0042",0.50,0.51) ;

   text1->Draw("Same");

   text2->Draw("Same");

   text3->Draw("Same");







   smearing_fuc->SetMarkerStyle(8);
   smearing_fuc->SetMarkerSize(1.3);
   smearing_fuc->SetMarkerColor(kBlue);
   smearing_fuc->SetLineColor(kBlue);
   myfit->SetLineColor(kBlue);
   myfit->SetLineStyle(2);



   f = new TFile("../../../rootfiles/smearing_width_vs_Ntrk.root");
   TGraphErrors* EPOS;
   TGraphErrors* Hydjet;

   Hydjet=(TGraphErrors*)f->Get("Graph;1"); 
   EPOS=(TGraphErrors*)f->Get("Graph;2"); 

   EPOS->SetMarkerStyle(21);
   EPOS->SetMarkerSize(1.3);
   EPOS->SetMarkerColor(kRed);
   EPOS->Draw("Psame");

   Hydjet->SetMarkerStyle(34);
   Hydjet->SetMarkerSize(1.3);
   Hydjet->SetMarkerColor(kBlack);
   Hydjet->Draw("Psame");
   myfit->Draw("PSame");
   smearing_fuc->Draw("Psame");

   TLegend *w4 = new TLegend(0.7,0.72,0.9,0.85);
   w4->SetLineColor(kWhite);
   w4->SetFillColor(0);
   w4->SetTextSize(23);
   w4->SetTextFont(45);
   w4->AddEntry(smearing_fuc, "Data","P");    

   w4->AddEntry(Hydjet, "Hydjet ","P");    
   w4->AddEntry(EPOS, "EPOS ","P");
   w4->Draw("same");



   c1->Print("~/Summer2016/smearingfunction_stdev.gif");
   c2->Print("~/Summer2016/smearingfit_eachbin.pdf");

   cout << "Mean x!!!!!!!!!: " << x[0] << endl;

   cout << "Par0 : " << myfit->GetParameter(0) << "par1 : " << myfit->GetParameter(1) << endl;


}










