#include "RiceStyle.h"

void smearingfunctionder()
{   

   TH1D* genAch;
   TH1D* recoAch;
   TH1D* smearingAch;
   TH2D* genrecoach;
   gStyle->SetLegendFont(42);
   TF1 *genfit = new TF1("genfit","gaus", -1, 1);
   TF1 *recofit = new TF1("recofit","gaus", -1, 1);
   TF1 *smearingfit = new TF1("smearingfit","gaus", -1, 1);

   TCanvas *c1 = new TCanvas("c1","show profile",1,1,600,600);
   //c1->Divide(3,1);

   int N[12] = {60,90,120,155,190,230,270,360,450,650,950,1050};
   double x[12] = {90,120,150,185,220,260,300,400,500,700,1000,1100};
   double y[12];
   double yerr[12];

   double smearingwidth;

   int i;

   for(i=0;i<12;i++){

      const double ach_low=0.00;
      const double ach_high=0.06;

      f = new TFile(Form("../../../rootfiles/closure/functionder_%d.root",N[i]));

      genAch = (TH1D*)f->Get("demo/GenChargeAsym");
      recoAch = (TH1D*)f->Get("demo/RecoChargeAsym");
      genrecoach = (TH2D*)f->Get("demo/genrecoach");

      //TAxis *xaxis = genrecoach->GetXaxis();
      TAxis *yaxis = genrecoach->GetYaxis();
      smearingAch = genrecoach->ProjectionX("smearingdist",yaxis->FindBin(ach_low),yaxis->FindBin(ach_high));


      genAch->Scale(1.0/genAch->Integral());
      recoAch->Scale(1.0/recoAch->Integral());

      genAch->Rebin(10);
      recoAch->Rebin(10);
      smearingAch->Rebin(10);


      smearingAch->Scale(1.0/smearingAch->Integral());


      genAch->Fit(genfit,"RN0");
      recoAch->Fit(recofit,"RN0");
      smearingAch->Fit(smearingfit,"RN0");


      double smearingwidth = smearingfit->GetParameter(2);
      yerr[i] = smearingfit->GetParError(2);


      cout << smearingwidth << endl;
      y[i] = smearingwidth;
      cout << y[i] << endl;


   }
   TGraphErrors* smearing_fuc = new TGraphErrors(12,x,y,NULL,yerr);

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

   smearing_fuc->RemovePoint(0);


   TF1 *myfit = new TF1("myfit","[0]*(1/sqrt(x)) + [1]", 110, 1200);
   smearing_fuc->Fit(myfit);

   TLatex* text1 = makeLatex(Form("y=#frac{%.4f}{#sqrt{x}}+%.4f",myfit->GetParameter(0),myfit->GetParameter(1)),0.45,0.25) ;
   text1->Draw("Same");






   smearing_fuc->SetMarkerStyle(20);
   smearing_fuc->SetMarkerSize(1.5);
   smearing_fuc->SetMarkerColor(kRed);
   smearing_fuc->SetLineColor(kBlue);
   smearing_fuc->Draw("Psame");

   SaveCanvas(c1,"pics","smearing_function_der");










}