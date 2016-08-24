#include "RiceStyle.h"

void fitscatterplot()
{
   //example illustrating how to fit a 2-d histogram of type y=f(x)
   //Author: Rene Brun

   // generate a 2-d histogram using a TCutG
   TFile *f;
   f = new TFile("../../../rootfiles/closure/Merged.root");
   TH2D *h2 = new TH2D("h2","h2",1000,-0.3,0.3,1000,-0.3,0.3);

   TCanvas *c1 = new TCanvas("c1","show profile",1,1,1200,600);
   c1->Divide(2,1,0.01,0.01);

   h2 = (TH2D*)f->Get("demo/genrecoach");
//   h2->Rebin2D(5,1);

   c1->cd(2);

   //use a TProfile to convert the 2-d to 1-d problem
   TProfile *prof = h2->ProfileX();
   //prof->Fit("pol1");
   prof->GetYaxis()->SetRangeUser(-0.08,0.08);
   prof->GetXaxis()->SetRangeUser(-0.08,0.08);
   prof->SetYTitle("A_{ch}");
   prof -> GetXaxis() -> CenterTitle();
   prof -> GetYaxis() -> CenterTitle();
   prof->SetLabelOffset(0.006,"Y");
   prof->SetTitleOffset(1.800,"Y");
   prof->SetMarkerStyle(20);
   prof->SetMarkerColor(kBlack);
   prof->SetMarkerSize (0.3);
   prof->SetMarkerStyle(1);
   prof->SetLineStyle(1);
   prof->SetLineWidth(1);   
   prof->Fit("pol1","0");
   TF1 *fit1 = prof->GetListOfFunctions()->FindObject("pol1");
   TLatex* text2 = makeLatex(Form("slope : %.3f #pm %.3f",fit1->GetParameter(1),fit1->GetParError(1)),0.55,0.25) ;


   if(fit1)
   {
      fit1->SetLineColor(4); 
      fit1->SetLineWidth(3);
      fit1->SetLineStyle(1);
   }

  // text_a->Draw("Same");
   text2->Draw("Same");
   TF1 *fa1 = new TF1("fa1","0",-10,10); 
   fa1->SetLineColor(kBlack);
   fa1->SetLineWidth(1);
   fa1->DrawClone("Same");
   prof->DrawClone("Same");




   c1->cd(1);
   c1->cd(1)->SetRightMargin(0.12);


   h2 -> GetXaxis()->CenterTitle();
   h2 -> GetYaxis()->CenterTitle();
   h2 ->GetXaxis()->SetRangeUser(-0.1, 0.1);
   h2 ->GetYaxis()->SetRangeUser(-0.1, 0.1);


   h2->Draw("colz");

   prof->SetLineColor(kRed); 
   prof->SetLineWidth(5);


   prof->Draw("Same");

 //  text_a->Draw("Same");



   /*
   TH1D* ChargeAsym;


   f = new TFile("../../../rootfiles/closure/Merged.root");
   ChargeAsym = (TH1D*)f->Get("demo/ChargeAsym");
   ChargeAsym->GetXaxis()->SetRangeUser(-0.25,0.25);
   ChargeAsym->GetXaxis()->SetTitle("Observed A_{ch}");
   ChargeAsym->GetYaxis()->SetTitle(" Counts ");
   ChargeAsym->GetXaxis()->CenterTitle();
   ChargeAsym->GetYaxis()->CenterTitle();
   ChargeAsym->SetTitleOffset(1.8,"Y");



   c1->cd(1);
   ChargeAsym->Draw();





   //prof->Draw();   

   */

   SaveCanvas(c1,"pics",Form("fitscatterplot_profonscatter_nofit"));

}

