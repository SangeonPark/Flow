#include "RiceStyle.h"
using namespace std;

void RebinProfile_PbPb(){

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
  TH2D* histlist_temp[2][3];

  TProfile *profilelist[2][3];

  double newbins[8] = {-0.12,-0.075,-0.045,-0.015,0.015,0.045,0.075,0.12};


  for (int i = 0; i < 3; ++i)
  {
    f = new TFile(Form("../../../rootfiles/MC/EPOS_PbPb_Ntrk_%d.root",i));

    histlist_temp[0][i] = (TH2D*)f->Get("demo/scatterHist_noeffcorr");

    histlist[0][i] = new TH2D("rebin","rebin",7,newbins,1000,-0.3,0.3); 

    TAxis *xaxis = histlist_temp[0][i]->GetXaxis();
    TAxis *yaxis = histlist_temp[0][i]->GetYaxis();
    for (int k=1; k<=yaxis->GetNbins();k++) {
      for (int l=1; l<=xaxis->GetNbins();l++) {
        histlist[0][i]->Fill(xaxis->GetBinCenter(l),yaxis->GetBinCenter(k),histlist_temp[0][i]->GetBinContent(l,k));
      }
    }


    profilelist[0][i] = histlist[0][i]->ProfileX();

  }
  for (int i = 0; i < 3; ++i)
  {
    f = new TFile(Form("../../../rootfiles/MC/Hydjet_PbPb_Reweighted_%d.root",i));
    
    histlist_temp[1][i] = (TH2D*)f->Get("demo/scatterHist_effcorr");

    histlist[1][i] = new TH2D("rebin","rebin",7,newbins,1000,-0.3,0.3); 


    TAxis *xaxis = histlist_temp[1][i]->GetXaxis();
    TAxis *yaxis = histlist_temp[1][i]->GetYaxis();
    for (int k=1; k<=yaxis->GetNbins();k++) {
      for (int l=1; l<=xaxis->GetNbins();l++) {
        histlist[1][i]->Fill(xaxis->GetBinCenter(l),yaxis->GetBinCenter(k),histlist_temp[1][i]->GetBinContent(l,k));
      }
    }



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
     profilelist[i][j]->GetXaxis()->SetRangeUser(-0.3,0.3);

     TF1* fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.105, 0.105);
     fit1->SetLineColor(kBlue);
     fit1->SetLineStyle(1);
     fit1->SetLineWidth(2);
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
      SaveCanvas(C,"pics","Rebinned_MC_7_bins_ver7");



    }
