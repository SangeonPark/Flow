#include "RiceStyle.h"

void addinquad()
{   

   TH1D* genAch;
   TH1D* recoAch;
   TH1D* smearingAch;
   TH2D* genrecoach;
   gStyle->SetLegendFont(42);

   TF1 *genfit = new TF1("genfit","gaus", -1, 1);
   TF1 *recofit = new TF1("recofit","gaus", -1, 1);
   TF1 *smearingfit = new TF1("smearingfit","gaus", -1, 1);

   TCanvas *c1 = new TCanvas("c1","show profile",1,1,1800,600);
   c1->Divide(3,1);

   f = new TFile("../../../rootfiles/closure/addinquad_300.root");

   genAch = (TH1D*)f->Get("demo/GenChargeAsym");
   recoAch = (TH1D*)f->Get("demo/RecoChargeAsym");
   genrecoach = (TH2D*)f->Get("demo/genrecoach");

//   TAxis *xaxis = genrecoach->GetXaxis();
   TAxis *yaxis = genrecoach->GetYaxis();


   smearingAch = genrecoach->ProjectionX("smearingdist",yaxis->FindBin(-0.09),yaxis->FindBin(-0.07));


   genAch->Scale(1.0/genAch->Integral());
   recoAch->Scale(1.0/recoAch->Integral());

   genAch->Rebin(10);
   recoAch->Rebin(10);
   smearingAch->Rebin(10);


   smearingAch->Scale(1.0/smearingAch->Integral());


   genAch->Fit(genfit,"RN0");
   recoAch->Fit(recofit,"RN0");
   smearingAch->Fit(smearingfit,"RN0");

   genAch->GetXaxis()->SetRangeUser(-0.2,0.2);
   genAch->GetXaxis()->SetTitle("A_{ch}");
   genAch->GetYaxis()->SetTitle("Normalized Counts");
   genAch->GetXaxis()->CenterTitle();
   genAch->GetYaxis()->CenterTitle();
   genAch->SetTitleOffset(1.8,"Y");
   genAch->SetMarkerStyle(24);
   genAch->SetMarkerColor(kBlack);
   genAch->SetMarkerSize (1);
   genAch->SetLineStyle(1);
   genAch->SetLineWidth(1);

   recoAch->GetXaxis()->SetRangeUser(-0.2,0.2);
   recoAch->GetXaxis()->SetTitle("A_{ch}");
   recoAch->GetYaxis()->SetTitle("Normalized Counts");   
   recoAch->GetXaxis()->CenterTitle();
   recoAch->GetYaxis()->CenterTitle();
   recoAch->SetTitleOffset(1.8,"Y");
   recoAch->SetMarkerStyle(20);
   recoAch->SetMarkerColor(kRed);
   recoAch->SetMarkerSize (1);
   recoAch->SetLineStyle(1);
   recoAch->SetLineWidth(1); 

   smearingAch->GetXaxis()->SetRangeUser(-0.2,0.2);
   smearingAch->GetXaxis()->SetTitle("A_{ch}");
   smearingAch->GetYaxis()->SetTitle("Normalized Counts");   
   smearingAch->GetXaxis()->CenterTitle();
   smearingAch->GetYaxis()->CenterTitle();
   smearingAch->SetTitleOffset(1.8,"Y");
   smearingAch->SetMarkerStyle(20);
   smearingAch->SetMarkerColor(kBlue);
   smearingAch->SetMarkerSize (1);
   smearingAch->SetLineStyle(1);
   smearingAch->SetLineWidth(1); 


   c1->cd(1);
   genAch->Draw();
   genfit->SetLineColor(kBlack);
   genfit->SetLineStyle(2);
   genfit->Draw("same");
   double genwidth = genfit->GetParameter(2);
   double recowidth = recofit->GetParameter(2);
   double smearingwidth = smearingfit->GetParameter(2);

   TLatex* text1 = makeLatex(Form("width : %f",genfit->GetParameter(2)),0.25,0.80) ;
   text1->Draw("same");


   c1->cd(2);
   recoAch->Draw();
   recofit->SetLineColor(kBlack);
   recofit->SetLineStyle(2);
   recofit->Draw("same");   
   TLatex* text2 = makeLatex(Form("width : %f",recofit->GetParameter(2)),0.25,0.80) ;
   text2->Draw("same");

   c1->cd(3);
   smearingAch->Draw();
   smearingfit->SetLineColor(kBlack);
   smearingfit->SetLineStyle(2);
   smearingfit->Draw("same");   
   TLatex* text3 = makeLatex(Form("width : %f",smearingfit->GetParameter(2)),0.25,0.80) ;
   text3->Draw("same");

   cout << recowidth*recowidth << endl;

   cout << genwidth*genwidth << endl;

   cout << smearingwidth*smearingwidth << endl;

   cout << recowidth*recowidth-genwidth*genwidth-smearingwidth*smearingwidth << endl;



   SaveCanvas(c1,"pics","addinquad_1000_0");



}