#include "RiceStyle.h"

using namespace std;

void figure6_ntrk(){

	TFile *f;

	const int NAchBins = 7;
	double correctionlist[10] = {0.704,0.698,0.694,0.687,0.684,0.676,0.673,0.662,0.645,0.663};
	//double correctionlist[10] = {1,1,1,1,1,1,1,1,1,1};

	TH1D* c2_pos[NAchBins][2];
	TH1D* c2_neg[NAchBins][2];
	TH1D* ach_hist[NAchBins];
	TH1D* pt_pos[NAchBins];

	TH1D* pt_neg[NAchBins];

	TGraphErrors* gr_diff;
	TF1* fit1;

	double x_val[10];

	double v2_PbPb_centrality_yval[10];
	double v2_PbPb_centrality_ystaterr[10];
	double v2_statErr[10];

	double pt_yval[10];
	double pt_yerr[10];
	
	double narrow_yval[10];
	double narrow_yerr[10];
	


	double variance_pos = 0.0;
	double variance_neg = 0.0;
	double variance_diff = 0.0;
	double err_neg[NAchBins];
	double err_pos[NAchBins];
	double err_diff[NAchBins];
	double cmean;
	double errmean;
	double sum;

	int v2_index[10] = {1,2,3,4,5,6,7,8,9,10};

	TGraphErrors* graph_list[3];

	f = new TFile("~/Summer2016/rootfiles/FinalResult_0106/Main_PbPb_Merged.root");


	for (int n = 0; n <10; ++n)
	{
		NTrkHist = (TH1D*)f->Get(Form("demo_n%d/NTrkHist",v2_index[n]));
		x_val[n] = NTrkHist->GetMean();



		for (Int_t i = 0; i < NAchBins; i++){
			ach_hist[i] = (TH1D*)f->Get(Form("demo_n%d/ach_%d",v2_index[n],i+1));

			c2_pos[i][0] = (TH1D*)f->Get(Form("demo_n%d/c2pos_%d_cos",v2_index[n],i));
			c2_pos[i][1] = (TH1D*)f->Get(Form("demo_n%d/c2pos_%d_sin",v2_index[n],i));


			c2_neg[i][0] = (TH1D*)f->Get(Form("demo_n%d/c2neg_%d_cos",v2_index[n],i));
			c2_neg[i][1] = (TH1D*)f->Get(Form("demo_n%d/c2neg_%d_sin",v2_index[n],i));

		}

		double x[NAchBins];
		double v2_pos[NAchBins];
		double v2_neg[NAchBins];
		double v2_diff[NAchBins];
		double r;
		for(Int_t i=0; i<NAchBins; i++){


			x[i]=ach_hist[i]->GetMean();
			x[i] *= correctionlist[n];

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
		
		fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.2, 0.2);
		gr_diff->Fit(fit1);
		r = fit1->GetParameter(1);
		v2_PbPb_centrality_ystaterr[n] = fit1->GetParError(1);
		cout << "v2err: " << v2_PbPb_centrality_ystaterr[n] << endl;
		v2_PbPb_centrality_yval[n] = r;

	}


	graph_list[0] = new TGraphErrors(10,x_val,v2_PbPb_centrality_yval,NULL,v2_PbPb_centrality_ystaterr);

	for (int n = 0; n <10; ++n)
	{
		double x[NAchBins];
		double ptavg_pos[NAchBins];
		double ptavg_neg[NAchBins];
		double ptavg_diff[NAchBins];
		double ptavg_pos_err[NAchBins];
		double ptavg_neg_err[NAchBins];
		double ptavg_diff_err[NAchBins];
		TGraphErrors* graph;
		TF1* fit;



		for (Int_t i = 0; i < NAchBins; i++){

			ach_hist[i] = (TH1D*)f->Get(Form("demo_n%d/ach_%d",v2_index[n],i+1));
			pt_pos[i] = (TH1D*)f->Get(Form("demo_n%d/pt_pos_%d",v2_index[n],i+1));
			pt_neg[i] = (TH1D*)f->Get(Form("demo_n%d/pt_neg_%d",v2_index[n],i+1));

		}

		for(Int_t i=0; i<NAchBins; i++){


			x[i]=ach_hist[i]->GetMean();
			x[i] *= correctionlist[n];

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
		graph = new TGraphErrors(NAchBins,x,ptavg_diff,NULL,ptavg_diff_err);
		fit = new TF1("Linear fitting", "[0]+x*[1]", -0.15, 0.15);
		graph->Fit(fit,"RN0");
		pt_yval[n] = fit->GetParameter(1);
		pt_yerr[n] = fit->GetParError(1);

	}

	graph_list[1] = new TGraphErrors(10,x_val,pt_yval,NULL,pt_yerr);


/*
	f = new TFile("~/Summer2016/rootfiles/FinalResult_0104/Narrowpt_PbPb_Merged.root");


	for (int n = 0; n <10; ++n)
	{
		

		for (Int_t i = 0; i < NAchBins; i++){
			ach_hist[i] = (TH1D*)f->Get(Form("demo_n%d/ach_%d",v2_index[n],i+1));

			c2_pos[i][0] = (TH1D*)f->Get(Form("demo_n%d/c2pos_%d_cos",v2_index[n],i));
			c2_pos[i][1] = (TH1D*)f->Get(Form("demo_n%d/c2pos_%d_sin",v2_index[n],i));


			c2_neg[i][0] = (TH1D*)f->Get(Form("demo_n%d/c2neg_%d_cos",v2_index[n],i));
			c2_neg[i][1] = (TH1D*)f->Get(Form("demo_n%d/c2neg_%d_sin",v2_index[n],i));

		}

		double x[NAchBins];
		double v2_pos[NAchBins];
		double v2_neg[NAchBins];
		double v2_diff[NAchBins];
		double r;
		for(Int_t i=0; i<NAchBins; i++){


			x[i]=ach_hist[i]->GetMean();
			x[i] *= correctionlist[n];

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
		
		fit1 = new TF1("Linear fitting case 1", "[0]+x*[1]", -0.2, 0.2);
		gr_diff->Fit(fit1);
		r = fit1->GetParameter(1);
		narrow_yerr[n] = fit1->GetParError(1);
		narrow_yval[n] = r;

	}


	graph_list[2] = new TGraphErrors(10,x_val,narrow_yval,NULL,narrow_yerr);
*/


	TFile *rebinned = new TFile("~/Summer2016/root_forgraphs/figure6_ntrk.root","RECREATE");
	graph_list[0]->Write();
	graph_list[1]->Write();
//	graph_list[2]->Write();

	rebinned->Close();



	graph_list[0] -> SetMarkerStyle(24);
	graph_list[0] -> SetMarkerColor(kBlue);
	graph_list[0] -> SetLineColor(kBlue);
	graph_list[1] -> SetMarkerStyle(25);
	graph_list[1] -> SetMarkerColor(kRed);
	graph_list[1] -> SetLineColor(kRed);
//	graph_list[2] -> SetMarkerStyle(kCircle);
//	graph_list[2] -> SetMarkerColor(kBlack);
//	graph_list[2] -> SetLineColor(kBlack);



	gStyle->SetLegendFont(42);	gStyle->SetOptTitle(0);
	TH1D* base = new TH1D("base","base",1,80,1000);
	base->GetYaxis()->SetRangeUser(0.00,0.15);
	base->GetXaxis()->SetTitle("ntrk");
	base->GetYaxis()->SetTitle("Slope parameter(normalized v_{n})");
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

	TCanvas* c3 = new TCanvas("c3","c3",1,1,600,600);
	TLatex* text_a = makeLatex("CMS PbPb #sqrt{s_{NN}}=5.02TeV",0.25,0.84) ;
	TLatex* text_b = makeLatex("185 #leq N_{trk}^{offline} < 260",0.25,0.80) ;
	TLatex* text_c = makeLatex("0.3 < p_{T} < 3 GeV/c",0.25,0.78) ;
	TLatex* text_d = makeLatex("|#Delta#eta| > 2",0.25,0.72) ;

	text_a->SetTextFont(42);
	text_b->SetTextFont(42);
	text_c->SetTextFont(42);
	text_d->SetTextFont(42);


	TLegend* leg = new TLegend(0.7,0.78,0.88,.88);
	leg->SetLineColor(kWhite);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->AddEntry(graph_list[0], "v2","p");	
	leg->AddEntry(graph_list[1], "pt","p");
	//leg->AddEntry(graph_list[2], "v2(narrowpt)","p");



	//leg->AddEntry(gr_neg, "neg","p");
		gPad->SetLogx(1);

	
	c3->cd();
	base->Draw("");

	text_a->Draw("");
	text_c->Draw("");
	text_d->Draw("");

	graph_list[0]->Draw("PSame");
	graph_list[1]->Draw("PSame");
	//graph_list[2]->Draw("PSame");



	leg->DrawClone("PSame");
	//SaveCanvas(c3,"pics","slope_vs_cent_v2_v3_superposition_PbPb_ver3");


    //Define a linear function





}
