#include "RiceStyle.h"

using namespace std;

void slopevsntrk(){

	TFile *f;
	TH1D* c2_pos[5][2];
	TH1D* c2_neg[5][2];
	TH1D* ach_hist[5];
	TH1D* NTrkHist;
	TGraphErrors* gr_diff;
	TF1* fit1;


	double pPb_xval[4];
	double pPb_yval[4];
	double pPb_ystaterr[4];


	double PbPb_xval[8];
	double PbPb_yval[8];
	double PbPb_ystaterr[8];

	double PbPb_centrality_xval[4];
	double PbPb_centrality_yval[4];
	double PbPb_centrality_ystaterr[4];

	double variance_pos = 0.0;
	double variance_neg = 0.0;
	double variance_diff = 0.0;
	double err_neg[5];
	double err_pos[5];
	double err_diff[5];
	double cmean;
	double errmean;
	double sum;


	for (int n = 0; n <4; ++n)
	{
		
		f = new TFile(Form("../../../rootfiles/slope_vs_ntrk/pPb/Rebin/%d/Merged.root",n));
		NTrkHist = (TH1D*)f->Get("demo/NTrkHist");
		pPb_xval[n] = NTrkHist->GetMean();

		for (Int_t i = 0; i < 5; i++){
			ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

			c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
			c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));


			c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
			c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));

		}

		double x[5];
		double v2_pos[5];
		double v2_neg[5];
		double v2_diff[5];
		double r;
		for(Int_t i=0; i<5; i++){

			x[i]=ach_hist[i]->GetMean();

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

		gr_diff = new TGraphErrors(5,x,v2_diff,NULL, err_diff);
		fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.09, 0.09);
		gr_diff->Fit(fit1);
		r = fit1->GetParameter(1);
		pPb_ystaterr[n] = fit1->GetParError(1);
		pPb_yval[n] = r;
		cout << r << endl;

	}

	TGraphErrors* pPbslope = new TGraphErrors(4,pPb_xval,pPb_yval,NULL,pPb_ystaterr);





	for (int n = 0; n <4; ++n)
	{
		
		f = new TFile(Form("../../../rootfiles/slope_vs_ntrk/PbPb/Rebin/Merged_%d.root",n));
		NTrkHist = (TH1D*)f->Get("demo/NTrkHist");
		PbPb_xval[n] = NTrkHist->GetMean();
		for (Int_t i = 0; i < 5; i++){
			ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

			c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
			c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));


			c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
			c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));

		}

		double x[5];
		double v2_pos[5];
		double v2_neg[5];
		double v2_diff[5];
		double r;
		for(Int_t i=0; i<5; i++){


			x[i]=ach_hist[i]->GetMean();

			cmean = c2_pos[i][0] -> GetMean();
			v2_pos[i] = sqrt(cmean);
			errmean = c2_pos[i][0] -> GetMeanError();
			variance_pos = (errmean*errmean)/(4*cmean);


			cmean = c2_neg[i][0] -> GetMean();
			v2_neg[i] = sqrt(cmean);
			errmean = c2_neg[i][0] -> GetMeanError();
			variance_neg = (errmean*errmean)/(4*cmean);

			v2_diff[i] = v2_neg[i] - v2_pos[i];
			v2_diff[i] = (v2_neg[i] - v2_pos[i])/(v2_neg[i] + v2_pos[i]);

			sum = v2_pos[i] + v2_neg[i];

			variance_diff = (4*v2_neg[i]*v2_neg[i]*variance_pos)/(sum*sum*sum*sum)+(4*v2_pos[i]*v2_pos[i]*variance_neg)/(sum*sum*sum*sum);


//error calculation

			err_pos[i] = sqrt(variance_pos);
			err_neg[i] = sqrt(variance_neg);
			err_diff[i] = sqrt(variance_diff);


		}

		gr_diff = new TGraphErrors(5,x,v2_diff,NULL, err_diff);
		fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.09, 0.09);
		gr_diff->Fit(fit1);
		r = fit1->GetParameter(1);
		PbPb_ystaterr[n] = fit1->GetParError(1);
		PbPb_yval[n] = r;

	}


	TGraphErrors* PbPbslope = new TGraphErrors(4,PbPb_xval,PbPb_yval,NULL,PbPb_ystaterr);




	for (int n = 0; n <2; ++n)
	{
		
		f = new TFile(Form("../../../rootfiles/slope_vs_centrality/PbPb502_%d.root",n+1));
		NTrkHist = (TH1D*)f->Get("demo/NTrkHist");
		PbPb_centrality_xval[n] = NTrkHist->GetMean();
		for (Int_t i = 0; i < 5; i++){
			ach_hist[i] = (TH1D*)f->Get(Form("demo/ach_%d",i+1));

			c2_pos[i][0] = (TH1D*)f->Get(Form("demo/c2pos_%d_cos",i));
			c2_pos[i][1] = (TH1D*)f->Get(Form("demo/c2pos_%d_sin",i));


			c2_neg[i][0] = (TH1D*)f->Get(Form("demo/c2neg_%d_cos",i));
			c2_neg[i][1] = (TH1D*)f->Get(Form("demo/c2neg_%d_sin",i));

		}

		double x[5];
		double v2_pos[5];
		double v2_neg[5];
		double v2_diff[5];
		double r;
		for(Int_t i=0; i<5; i++){


			x[i]=ach_hist[i]->GetMean();

			cmean = c2_pos[i][0] -> GetMean();
			v2_pos[i] = sqrt(cmean);
			errmean = c2_pos[i][0] -> GetMeanError();
			variance_pos = (errmean*errmean)/(4*cmean);


			cmean = c2_neg[i][0] -> GetMean();
			v2_neg[i] = sqrt(cmean);
			errmean = c2_neg[i][0] -> GetMeanError();
			variance_neg = (errmean*errmean)/(4*cmean);

			v2_diff[i] = v2_neg[i] - v2_pos[i];
			v2_diff[i] = (v2_neg[i] - v2_pos[i])/(v2_neg[i] + v2_pos[i]);

			sum = v2_pos[i] + v2_neg[i];

			variance_diff = (4*v2_neg[i]*v2_neg[i]*variance_pos)/(sum*sum*sum*sum)+(4*v2_pos[i]*v2_pos[i]*variance_neg)/(sum*sum*sum*sum);


//error calculation

			err_pos[i] = sqrt(variance_pos);
			err_neg[i] = sqrt(variance_neg);
			err_diff[i] = sqrt(variance_diff);

		}
		cout << r << endl;
		cout << PbPb_centrality_xval[n] << endl;

		gr_diff = new TGraphErrors(5,x,v2_diff,NULL, err_diff);
		fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.09, 0.09);
		gr_diff->Fit(fit1);
		r = fit1->GetParameter(1);
		PbPb_centrality_ystaterr[n] = fit1->GetParError(1);
		PbPb_centrality_yval[n] = r;

	}
	TFile *rebinned = new TFile("~/Summer2016/root_forgraphs/figure3.root","RECREATE");

	TGraphErrors* PbPbslope_centrality = new TGraphErrors(2,PbPb_centrality_xval,PbPb_centrality_yval,NULL,PbPb_centrality_ystaterr);
	pPbslope->Write();
	PbPbslope->Write();
	PbPbslope_centrality->Write();
	rebinned->Close();


	PbPbslope -> SetMarkerStyle(24);
	PbPbslope -> SetMarkerColor(kBlue);
	pPbslope -> SetMarkerStyle(20);
	pPbslope -> SetMarkerColor(kBlue);

	PbPbslope_centrality -> SetMarkerStyle(24);
	PbPbslope_centrality -> SetMarkerColor(kRed);

	gStyle->SetLegendFont(42);	gStyle->SetOptTitle(0);

	TH1D* base = new TH1D("base","base",1,0,500);
	base->GetYaxis()->SetRangeUser(0.00,0.4);
	base->GetXaxis()->SetTitle("N_{trk}^{offline}");
	base->GetYaxis()->SetTitle("Slope parameter(normalized v_{2})");
	base->GetXaxis()->CenterTitle();
	base->GetYaxis()->CenterTitle();
	base->SetTitleSize  (0.040,"X");
	base->SetTitleOffset(1.4,"X");
	base->SetTitleFont  (42,"X");
	base->SetLabelOffset(0.006,"X");
	base->SetLabelSize  (0.040,"X");
	base->SetLabelFont  (42   ,"X");

	base->SetTitleSize  (0.040,"Y");
	base->SetTitleOffset(1.6,"Y");
	base->SetTitleFont  (42,"Y");
	base->SetLabelOffset(0.006,"Y");
	base->SetLabelSize  (0.040,"Y");
	base->SetLabelFont  (42   ,"Y");
	base->SetLineWidth(0);

	TCanvas* c3 = MakeCanvas("c3","c3");
	TLatex* text_a = makeLatex("CMS pPb #sqrt{s_{NN}}=5.02TeV",0.25,0.85) ;
	TLatex* text_b = makeLatex("185 #leq N_{trk}^{offline} < 260",0.25,0.80) ;
	TLatex* text_c = makeLatex("0.3 < p_{T} < 3 GeV/c",0.25,0.84) ;
	TLatex* text_d = makeLatex("|#Delta#eta| > 2",0.25,0.78) ;

	text_a->SetTextFont(42);
	text_b->SetTextFont(42);
	text_c->SetTextFont(42);
	text_d->SetTextFont(42);



	TLegend* leg = new TLegend(.70,.76,.93,.88);
	leg->SetLineColor(kWhite);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->AddEntry(pPbslope, "pPb","p");
	leg->AddEntry(PbPbslope, "PbPb","p");

	

	c3->cd();
	base->Draw("");
	text_c->DrawClone("");
	text_d->DrawClone("");
	pPbslope->Draw("PSame");
	PbPbslope->Draw("PSame");
//	PbPbslope_centrality->Draw("PSame");
	leg->DrawClone("PSame");
	SaveCanvas(c3,"pics","slope_vs_ntrk_pPb_PbPb_superposed");

}
