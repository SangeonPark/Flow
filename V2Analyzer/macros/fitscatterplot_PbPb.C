#include "RiceStyle.h"
using namespace std;

void fitscatterplot_PbPb(){

	TCanvas* C = new TCanvas("fitscatterplot","EPOS Hydjet Scatterplot",1800,1200);
  //TCanvas* C2 = new TCanvas("EPOSoverHydjet","EPOS divided by Hydjet",1500,1000);
	//C->SetCanvasSize(120,1000);
	// Number of PADS
	const Int_t Nx = 3;
	const Int_t Ny = 2;

    // Margins
	Float_t lMargin = 0.12;
	Float_t rMargin = 0.05;
	Float_t bMargin = 0.15;
	Float_t tMargin = 0.05;

	//CanvasPartition(C,Nx,Ny,lMargin,rMargin,bMargin,tMargin);
	C->Divide(Nx,Ny);

	TH2D* histlist[2][3];
	TProfile *profilelist[2][3];
	

	for (int i = 0; i < 3; ++i)
	{
		f = new TFile(Form("../../../rootfiles/MC/EPOS_PbPb_Ntrk_%d.root",i));

		histlist[0][i] = (TH2D*)f->Get("demo/scatterHist_effcorr");
    histlist[0][i]->Rebin2D(20,1);
    profilelist[0][i] = histlist[0][i]->ProfileX();

  }
  for (int i = 0; i < 3; ++i)
  {
    f = new TFile(Form("../../../rootfiles/MC/Hydjet_PbPb_Ntrk_%d.root",i));
    
    histlist[1][i] = (TH2D*)f->Get("demo/scatterHist_effcorr");
    histlist[1][i]->Rebin2D(20,1);
    profilelist[1][i] = histlist[1][i]->ProfileX();


  }  
  TLatex* textlist[2][3]; 
  textlist[0][0] = makeLatex("EPOS 200 #leq N_{trk}^{offline} < 400",0.25,0.85);
  textlist[0][1] = makeLatex("EPOS 400 #leq N_{trk}^{offline} < 800",0.25,0.85);
  textlist[0][2] = makeLatex("EPOS 800 #leq N_{trk}^{offline} < 1500",0.25,0.85);
  textlist[1][0] = makeLatex("Hydjet 200 #leq N_{trk}^{offline} < 400",0.25,0.85);
  textlist[1][1] = makeLatex("Hydjet 400 #leq N_{trk}^{offline} < 800",0.25,0.85);
  textlist[1][2] = makeLatex("Hydjet 800 #leq N_{trk}^{offline} < 1500",0.25,0.85);
  int n = 1;


  for (Int_t i=0;i<2;i++) {
    for (Int_t j=0;j<3;j++) {
     C->cd(n);
     gPad->SetLogz(1);
     n++;





     TLatex *text1 = (TLatex*) textlist[i][j]->Clone();

		 //axis range	
     profilelist[i][j]->GetYaxis()->SetRangeUser(-0.25,0.25);
     profilelist[i][j]->GetXaxis()->SetRangeUser(-0.25,0.25);

     TF1* fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.07, 0.07);
     fit1->SetLineColor(kBlue);
     fit1->SetLineStyle(1);
     fit1->SetLineWidth(3);
     profilelist[i][j]->Fit(fit1,"RN0");

     TF1* fit2 = new TF1("just comparing","0.0+0.761*x",-0.2,0.2);	
     fit2->SetLineColor(kRed);
     fit2->SetLineStyle(1);
     fit2->SetLineWidth(2);

			/*
			TF1 *fit1 = profilelist[i][j]->GetListOfFunctions()->FindObject("pol1");

			if(fit1){
				fit1->SetLineColor(4); // 4 = "blue"
				fit1->SetLineWidth(3);
      			fit1->SetLineStyle(2); // 2 = "- - -"
      		}
      		*/
      		





         // Format for y axis
            profilelist[i][j]->GetYaxis()->SetTitle("A_{ch}");

      		profilelist[i][j]->GetYaxis()->SetLabelFont(43);
      		profilelist[i][j]->GetYaxis()->SetLabelSize(16);
      		profilelist[i][j]->GetYaxis()->SetLabelOffset(0.02);
      		profilelist[i][j]->GetYaxis()->SetTitleFont(43);
      		profilelist[i][j]->GetYaxis()->SetTitleSize(16);
      		profilelist[i][j]->GetYaxis()->SetTitleOffset(3.5);

      		profilelist[i][j]->GetYaxis()->CenterTitle();
      		profilelist[i][j]->GetYaxis()->SetNdivisions(505);

         // TICKS Y Axis
      		//profilelist[i][j]->GetYaxis()->SetTickLength(xFactor*0.04/yFactor);

         // Format for x axis
      		profilelist[i][j]->GetXaxis()->SetLabelFont(43);
      		profilelist[i][j]->GetXaxis()->SetLabelSize(16);
      		profilelist[i][j]->GetXaxis()->SetLabelOffset(0.02);
      		profilelist[i][j]->GetXaxis()->SetTitleFont(43);
      		profilelist[i][j]->GetXaxis()->SetTitleSize(16);
      		profilelist[i][j]->GetXaxis()->SetTitleOffset(3);
      		profilelist[i][j]->GetXaxis()->CenterTitle();
      		profilelist[i][j]->GetXaxis()->SetNdivisions(505);

		 //Marker
      		profilelist[i][j]->SetMarkerStyle(20);
          profilelist[i][j]->SetMarkerSize(1);
          profilelist[i][j]->SetLineStyle(1);
          profilelist[i][j]->SetLineWidth(1);	

         // TICKS X Axis
      		//profilelist[i][j]->GetXaxis()->SetTickLength(yFactor*0.06/xFactor);
         profilelist[i][j]->Draw();
          //histlist[i][j]->Draw("colz");




          text1->DrawClone("same");

          TF1 *fa1 = new TF1("fa1","0",-10,10); 
          fa1->SetLineColor(kBlack);
          fa1->SetLineWidth(1);
          fa1->DrawClone("Same");

          TLatex* text2 = makeLatex(Form("slope : %.3f #pm %.3f",fit1->GetParameter(1),fit1->GetParError(1)),0.55,0.25) ;
          TLatex* text3 = makeLatex(Form("Intercept : %f #pm %f",fit1->GetParameter(0),fit1->GetParError(0)),0.55,0.20) ;

          text2->DrawClone("same");
          //text3->DrawClone("same");
          fit1->Draw("Same");
          //fit2->Draw("Same");


        }
      }
      C->cd();
      SaveCanvas(C,"pics","MC_Hydjet_EPOS_PbPb_Ntrk");



    }

    void CanvasPartition(TCanvas *C,const Int_t Nx = 2,const Int_t Ny = 2,
     Float_t lMargin = 0.15, Float_t rMargin = 0.05,
     Float_t bMargin = 0.15, Float_t tMargin = 0.05)
    {
     if (!C) return;

   // Setup Pad layout:
     Float_t vSpacing = 0.0;
     Float_t vStep  = (1.- bMargin - tMargin - (Ny-1) * vSpacing) / Ny;

     Float_t hSpacing = 0.0;
     Float_t hStep  = (1.- lMargin - rMargin - (Nx-1) * hSpacing) / Nx;

     Float_t vposd,vposu,vmard,vmaru,vfactor;
     Float_t hposl,hposr,hmarl,hmarr,hfactor;

     for (Int_t i=0;i<Nx;i++) {

      if (i==0) {
       hposl = 0.0;
       hposr = lMargin + hStep;
       hfactor = hposr-hposl;
       hmarl = lMargin / hfactor;
       hmarr = 0.0;
     } else if (i == Nx-1) {
       hposl = hposr + hSpacing;
       hposr = hposl + hStep + rMargin;
       hfactor = hposr-hposl;
       hmarl = 0.0;
       hmarr = rMargin / (hposr-hposl);
     } else {
       hposl = hposr + hSpacing;
       hposr = hposl + hStep;
       hfactor = hposr-hposl;
       hmarl = 0.0;
       hmarr = 0.0;
     }

     for (Int_t j=0;j<Ny;j++) {

       if (j==0) {
        vposd = 0.0;
        vposu = bMargin + vStep;
        vfactor = vposu-vposd;
        vmard = bMargin / vfactor;
        vmaru = 0.0;
      } else if (j == Ny-1) {
        vposd = vposu + vSpacing;
        vposu = vposd + vStep + tMargin;
        vfactor = vposu-vposd;
        vmard = 0.0;
        vmaru = tMargin / (vposu-vposd);
      } else {
        vposd = vposu + vSpacing;
        vposu = vposd + vStep;
        vfactor = vposu-vposd;
        vmard = 0.0;
        vmaru = 0.0;
      }

      C->cd(0);

      char name[16];
      sprintf(name,"pad_%i_%i",i,j);
      TPad *pad = (TPad*) gROOT->FindObject(name);
      if (pad) delete pad;
      pad = new TPad(name,"",hposl,vposd,hposr,vposu);
      pad->SetLeftMargin(hmarl);
      pad->SetRightMargin(hmarr);
      pad->SetBottomMargin(vmard);
      pad->SetTopMargin(vmaru);

      pad->SetFrameBorderMode(0);
      pad->SetBorderMode(0);
      pad->SetBorderSize(0);

      pad->Draw();
    }
  }
}
