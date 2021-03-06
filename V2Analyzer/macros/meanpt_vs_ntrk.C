#include "RiceStyle.h"

using namespace std;

void meanpt_vs_ntrk(){

	TFile *f;
	const int NAchBins = 7;
//	double correctionlist_cent[6] = {0.6527, 0.7218, 0.7411, 0.7551, 0.7567, 0.6836};
//	double correctionlist_ntrk[7] = {0.7439,0.7520,0.7575,0.7463,0.7508,0.7374,0.7127};
//	double correctionlist_pPb[4] = {0.7520,0.7575,0.7463,0.7595};

	double correctionlist_cent[6] = {0.641, 0.644, 0.655, 0.673, 0.701, 0.631};
	double correctionlist_ntrk[8] = {0.689, 0.687, 0.677, 0.675, 0.673, 0.666, 0.662, 0.653}

	double correctionlist_pPb[4] = {1,1,1,1};



	int low_cent[6] = {30,40,50,60,70,80};
	int upp_cent[6] = {40,50,60,70,80,90};

	int low_pPb[4] = {120,150,185,220};
	int upp_pPb[4] = {150,185,220,260};
	
	int low_ntrk[8] = {90,120,150,185,220,260,300,400};
	int upp_ntrk[8] = {120,150,185,220,260,300,400,500};

	TH1D* pt_pos[100];
	TH1D* pt_neg[100];
	TH1D* ach_hist[100];

	TH1D* NTrkHist;
	TGraphErrors* gr_diff;
	TF1* fit1;


	double pPb_xval[4];
	double pPb_yval[4];
	double pPb_ystaterr[4];


	double PbPb_xval[8];
	double PbPb_yval[8];
	double PbPb_ystaterr[8];

	double PbPb_centrality_xval[6];
	double PbPb_centrality_yval[6];
	double PbPb_centrality_ystaterr[6];


	double err_neg[NAchBins];
	double err_pos[NAchBins];
	double err_diff[NAchBins];
	double cmean;
	double errmean;

/*
	for (int n = 0; n <4; ++n)
	{
		
		f = new TFile(Form("../../../rootfiles/crosscheck/pPb/v2/%d_%d/Merged.root",low_pPb[n],upp_pPb[n]));
		NTrkHist = (TH1D*)f->Get("demo/NTrkHist");
		pPb_xval[n] = NTrkHist->GetMean();

		for (Int_t i = 0; i < NAchBins; i++){
			ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

			c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
			c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));


			c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
			c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));

		}

		double x[NAchBins];
		double v2_pos[NAchBins];
		double v2_neg[NAchBins];
		double v2_diff[NAchBins];
		double r;
		for(Int_t i=0; i<NAchBins; i++){

			x[i]=ach_hist[i]->GetMean();
			x[i] *= correctionlist_pPb[n];

			cmean = c2_pos[i][0] -> GetMean();
			v2_pos[i] = sqrt(cmean);
			errmean = c2_pos[i][0] -> GetMeanError();
			variance_pos = (errmean*errmean)/(4*cmean);


			cmean = c2_neg[i][0] -> GetMean();
			v2_neg[i] = sqrt(cmean);
			errmean = c2_neg[i][0] -> GetMeanError();
			variance_neg = (errmean*errmean)/(4*cmean);

			v2_diff[i] = (v2_neg[i] - v2_pos[i])/(v2_neg[i] + v2_pos[i]);

			sum = v2_pos[i] + v2_neg[i];

			variance_diff = (4*v2_neg[i]*v2_neg[i]*variance_pos)/(sum*sum*sum*sum)+(4*v2_pos[i]*v2_pos[i]*variance_neg)/(sum*sum*sum*sum);


//error calculation

			err_pos[i] = sqrt(variance_pos);
			err_neg[i] = sqrt(variance_neg);
			err_diff[i] = sqrt(variance_diff);

		}

		gr_diff = new TGraphErrors(NAchBins,x,v2_diff,NULL, err_diff);
		fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.09, 0.09);
		gr_diff->Fit(fit1);
		r = fit1->GetParameter(1);
		pPb_ystaterr[n] = fit1->GetParError(1);
		pPb_yval[n] = r;
		cout << r << endl;

	}

	TGraphErrors* pPbslope = new TGraphErrors(4,pPb_xval,pPb_yval,NULL,pPb_ystaterr);
*/


	for (int n = 0; n <8; ++n)
	{
		
		f = new TFile(Form("../../../rootfiles/FinalResult_Temp/MainResult/v2/PbPb/%d/Merged.root",low_ntrk[n]));
		NTrkHist = (TH1D*)f->Get("demo/NTrkHist");
		PbPb_xval[n] = NTrkHist->GetMean();

		for (Int_t i = 0; i < NAchBins; i++){

			ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));
			pt_pos[i] = (TH1D*)f->Get(Form("demo/pt_pos_%d",i+1));
			pt_neg[i] = (TH1D*)f->Get(Form("demo/pt_neg_%d",i+1));

		}

		double x[NAchBins];
		double ptavg_pos[NAchBins];
		double ptavg_neg[NAchBins];
		double ptavg_diff[NAchBins];
		double ptavg_pos_err[NAchBins];
		double ptavg_neg_err[NAchBins];
		double ptavg_diff_err[NAchBins];

		double variance_pos,variance_neg,variance_diff,sum;
		double r;

		for(Int_t i=0; i<NAchBins; i++){


			x[i]=ach_hist[i]->GetMean();
			x[i] *= correctionlist_ntrk[n];

			ptavg_pos[i]=pt_pos[i]->GetMean();
			ptavg_neg[i]=pt_neg[i]->GetMean();
			ptavg_pos_err[i]=pt_pos[i]->GetMeanError();

			variance_pos = ptavg_pos_err[i]*ptavg_pos_err[i];

			ptavg_neg_err[i]=pt_neg[i]->GetMeanError();

			variance_neg = ptavg_neg_err[i]*ptavg_neg_err[i];

			ptavg_diff[i] = (ptavg_neg[i] - ptavg_pos[i])/(ptavg_neg[i] + ptavg_pos[i]);

			sum = ptavg_pos[i] + ptavg_neg[i];
			variance_diff = (4*ptavg_neg[i]*ptavg_neg[i]*variance_pos)/(sum*sum*sum*sum)+(4*ptavg_pos[i]*ptavg_pos[i]*variance_neg)/(sum*sum*sum*sum);

			ptavg_diff_err[i] = sqrt(variance_diff);
			cout << ptavg_neg_err[i] << endl;


		}

		gr_diff = new TGraphErrors(NAchBins,x,ptavg_diff,NULL,ptavg_diff_err);
		fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.15, 0.15);
		gr_diff->Fit(fit1,"RN0");
		r = fit1->GetParameter(1);
		PbPb_ystaterr[n] = fit1->GetParError(1);
		PbPb_yval[n] = r;

	}


	TGraphErrors* PbPbslope = new TGraphErrors(8,PbPb_xval,PbPb_yval,NULL,PbPb_ystaterr);




	for (int n = 0; n <6; ++n)
	{
		
		f = new TFile(Form("../../../rootfiles/FinalResult_Temp/MainResult/v2/PbPb/centrality/%d/Merged.root",low_cent[n]));
		NTrkHist = (TH1D*)f->Get("demo/NTrkHist");
		PbPb_centrality_xval[n] = NTrkHist->GetMean();
		for (Int_t i = 0; i < NAchBins; i++){

			ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));
			pt_pos[i] = (TH1D*)f->Get(Form("demo/pt_pos_%d",i+1));
			pt_neg[i] = (TH1D*)f->Get(Form("demo/pt_neg_%d",i+1));

		}

		double x[NAchBins];
		double ptavg_pos[NAchBins];
		double ptavg_neg[NAchBins];
		double ptavg_diff[NAchBins];
		double ptavg_pos_err[NAchBins];
		double ptavg_neg_err[NAchBins];
		double ptavg_diff_err[NAchBins];

		double variance_pos,variance_neg,variance_diff,sum;
		double r;

		for(Int_t i=0; i<NAchBins; i++){


			x[i]=ach_hist[i]->GetMean();
			x[i] *= correctionlist_cent[n];

			ptavg_pos[i]=pt_pos[i]->GetMean();
			ptavg_neg[i]=pt_neg[i]->GetMean();
			ptavg_pos_err[i]=pt_pos[i]->GetMeanError();

			variance_pos = ptavg_pos_err[i]*ptavg_pos_err[i];

			ptavg_neg_err[i]=pt_neg[i]->GetMeanError();

			variance_neg = ptavg_neg_err[i]*ptavg_neg_err[i];

			ptavg_diff[i] = (ptavg_neg[i] - ptavg_pos[i])/(ptavg_neg[i] + ptavg_pos[i]);

			sum = ptavg_pos[i] + ptavg_neg[i];
			variance_diff = (4*ptavg_neg[i]*ptavg_neg[i]*variance_pos)/(sum*sum*sum*sum)+(4*ptavg_pos[i]*ptavg_pos[i]*variance_neg)/(sum*sum*sum*sum);

			ptavg_diff_err[i] = sqrt(variance_diff);
			cout << ptavg_neg_err[i] << endl;


		}

		gr_diff = new TGraphErrors(NAchBins,x,ptavg_diff,NULL,ptavg_diff_err);
		fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.15, 0.15);
		gr_diff->Fit(fit1,"RN0");
		r = fit1->GetParameter(1);
		PbPb_centrality_ystaterr[n] = fit1->GetParError(1);
		PbPb_centrality_yval[n] = r;

	}
	TFile *rebinned = new TFile("~/Summer2016/root_forgraphs/figure6.root","RECREATE");

	TGraphErrors* PbPbslope_centrality = new TGraphErrors(2,PbPb_centrality_xval,PbPb_centrality_yval,NULL,PbPb_centrality_ystaterr);
	//pPbslope->Write();
	PbPbslope->Write();
	PbPbslope_centrality->Write();
	rebinned->Close();


	
	TH1D* base1 = makeHist("base1", "", "N^{offline}_{trk}", "r_{<pt>}", 6000,0, 6000, kBlack);
	TH1D* base2 = makeHist("base2", "", "Observed A_{ch}", "v_{2}(-) - v_{2}(+)", 1000, -0.2, 0.2, kBlack);

	fixedFontHist1D(base1,1.1,1.3);
	
	base1->GetYaxis()->SetRangeUser(0.00, 0.5);
	base1->GetXaxis()->SetRangeUser(60, 2000);
	base1->GetXaxis()->SetTitleColor(kBlack);
	base1->GetYaxis()->SetTitleOffset(1.23);
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

	TCanvas* c1 = new TCanvas("c1", "c1", 1, 1, 600,600);
	gPad->SetTicks();
	gPad->SetLeftMargin(0.13);
	gPad->SetBottomMargin(0.13);
	gPad->SetRightMargin(0.05);
	gStyle->SetPadBorderMode(0.1);
	gStyle->SetOptTitle(0);
	gPad->SetLogx(1);

	base1->Draw();

	TLatex* r33 = new TLatex(0.13,0.91, "CMS");
	r33->SetNDC();
	r33->SetTextSize(0.04);
	r33->Draw("same");

	TLatex* r44 = new TLatex(0.23,0.91, "Preliminary");
	r44->SetNDC();
	r44->SetTextSize(24);
	r44->SetTextFont(53);
	r44->Draw("same");

	TLatex* r22 = new TLatex(0.15, 0.83, "#sqrt{s_{NN}} = 5.02 TeV");
	r22->SetNDC();
	r22->SetTextSize(23);
	r22->SetTextFont(43);
	r22->SetTextColor(kBlack);
	r22->Draw("same");

	TLatex* r55 = new TLatex(0.15, 0.76, "185 #leq N^{offline}_{trk} < 260");
	r55->SetNDC();
	r55->SetTextSize(23);
	r55->SetTextFont(43);
	r55->SetTextColor(kBlack);
	//r55->Draw("same"); 

	TLatex* r66 = new TLatex(0.58, 0.83, "0.3 #leq p_{T} < 3.0 GeV/c");
	r66->SetNDC();
	r66->SetTextSize(23);
	r66->SetTextFont(43);
	r66->SetTextColor(kBlack);
	r66->Draw("same");

/*
	pPbslope->SetMarkerStyle(20);
	pPbslope->SetMarkerSize(1.5);
	pPbslope->SetMarkerColor(kRed);
	pPbslope->SetLineColor(kRed);
	pPbslope->Draw("Psame");
*/
	PbPbslope->SetMarkerStyle(25);
	PbPbslope->SetMarkerSize(1.5);
	PbPbslope->SetMarkerColor(kBlue);
	PbPbslope->SetLineColor(kBlue);
	PbPbslope->Draw("Psame");

	PbPbslope_centrality->SetMarkerStyle(25);
	PbPbslope_centrality->SetMarkerSize(1.5);
	PbPbslope_centrality->SetMarkerColor(kBlue);
	PbPbslope_centrality->SetLineColor(kBlue);
	PbPbslope_centrality->Draw("Psame");

	TLegend *w4 = new TLegend(0.7,0.17,0.9,0.3);
	w4->SetLineColor(kWhite);
	w4->SetFillColor(0);
	w4->SetTextSize(23);
	w4->SetTextFont(45);
	//w4->AddEntry(pPbslope, "pPb ","P");    
	w4->AddEntry(PbPbslope, "PbPb ","P");
	w4->Draw("same");


	c1->Print("~/Summer2016/pics/figure6.pdf");
	c1->Print("~/Summer2016/pics/figure6.gif");


	//SaveCanvas(c3,"pics","slope_vs_ntrk_pPb_PbPb_superposed");

}
