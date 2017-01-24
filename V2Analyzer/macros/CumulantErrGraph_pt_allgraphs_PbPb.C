#include "RiceStyle.h"
using namespace std;

void CumulantErrGraph_pt_allgraphs_PbPb(){

	TFile *f;

	const int NAchBins = 7;
	//const double correction = 0.7463;
	//const double correction = 1.0;

	
	TH1D* pt_pos[100];
	TH1D* pt_neg[100];
	TH1D* ach_hist[100];
	double x[NAchBins];
	double ptavg_pos[NAchBins];
	double ptavg_neg[NAchBins];
	double ptavg_diff[NAchBins];
	double ptavg_pos_err[NAchBins];
	double ptavg_neg_err[NAchBins];
	double ptavg_diff_err[NAchBins];
	double variance_pos,variance_neg,variance_diff,sum;






	int mult_start[5] = {120,150,185,220,260}; 
	int mult_end[5] = {150,185,220,260,300};
	double correction[5] = {0.698,0.694,0.687,0.684,0.676};
	int mult_index[5] = {2,3,4,5,6};

	double setrange_low[5] = {0.75, 0.755, 0.76 ,0.762, 0.766};
	double setrange_upp[5] = {0.77,0.775, 0.775 ,0.775,  0.78};

	double range_start = 0.06;
	double range_end = 0.072;

	int num = 2;

	range_start = setrange_low[num];
	range_end = setrange_upp[num];

	int num_temp=3; 
	int temp_index[4] = {1,2,3,4};



	//f = new TFile("~/Summer2016/rootfiles/FinalResult_0106/Main_PbPb_Merged.root");

	f = new TFile("~/Summer2016/rootfiles/v2_varybin_temp.root");



	for (Int_t i = 0; i < NAchBins; i++){
		/*

		ach_hist[i] = (TH1D*)f->Get(Form("demo_n%d/ach_%d",mult_index[num],i+1));
		pt_pos[i] = (TH1D*)f->Get(Form("demo_n%d/pt_pos_%d",mult_index[num],i+1));
		pt_neg[i] = (TH1D*)f->Get(Form("demo_n%d/pt_neg_%d",mult_index[num],i+1));
		*/
		cout << temp_index[num_temp] << endl;

		ach_hist[i] = (TH1D*)f->Get(Form("demo_n%d/ach_%d",temp_index[num_temp],i+1));
		pt_pos[i] = (TH1D*)f->Get(Form("demo_n%d/pt_pos_%d",temp_index[num_temp],i+1));
		pt_neg[i] = (TH1D*)f->Get(Form("demo_n%d/pt_neg_%d",temp_index[num_temp],i+1));


	}
	for(Int_t i=0; i<NAchBins; i++){
		

		x[i]=ach_hist[i]->GetMean();
		x[i] *= correction[num];

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
		
		

	}	
	gStyle->SetLegendFont(42);
	TH1D* base = new TH1D("base","base",1,-0.10,0.10);
	//pPb
	//base->GetYaxis()->SetRangeUser(0.065, 0.075);
	base->GetYaxis()->SetRangeUser(range_start, range_end);

	//PbPb
	//base->GetYaxis()->SetRangeUser(0.093, 0.103);
	base->GetXaxis()->SetTitle("Corrected A_{ch}");
	base->GetYaxis()->SetTitle("<p_{T}>");
	base->GetXaxis()->CenterTitle();
	base->GetYaxis()->CenterTitle();
	base->SetTitleSize  (0.040,"X");
	base->SetTitleOffset(1.4,"X");
	base->SetTitleFont  (42,"X");
	base->SetLabelOffset(0.006,"X");
	base->SetLabelSize  (0.040,"X");
	base->SetLabelFont  (42   ,"X");

	base->SetTitleSize  (0.040,"Y");
	base->SetTitleOffset(2.2,"Y");
	base->SetTitleFont  (42,"Y");
	base->SetLabelOffset(0.006,"Y");
	base->SetLabelSize  (0.040,"Y");
	base->SetLabelFont  (42   ,"Y");
	base->SetLineWidth(0);

	TH1D* base2 = new TH1D("base2","base2",1,-0.10,0.10);
	base2->GetYaxis()->SetRangeUser(-0.03, 0.03);
	base2->GetXaxis()->SetTitle("Corrected A_{ch}");
	base2->GetYaxis()->SetTitle(" (<p_{T}>^{#minus} #minus <p_{T}>^{#plus})/(<p_{T}>^{#minus} #plus <p_{T}>^{#plus}) ");
	base2->GetXaxis()->CenterTitle();
	base2->GetYaxis()->CenterTitle();
	base2->SetTitleSize  (0.040,"X");
	base2->SetTitleOffset(1.4,"X");
	base2->SetTitleFont  (42,"X");
	base2->SetLabelOffset(0.006,"X");
	base2->SetLabelSize  (0.040,"X");
	base2->SetLabelFont  (42   ,"X");
	base2->SetTitleSize  (0.040,"Y");
	base2->SetTitleOffset(2.0,"Y");
	base2->SetTitleFont  (42,"Y");
	base2->SetLabelOffset(0.006,"Y");
	base2->SetLabelSize  (0.040,"Y");
	base2->SetLabelFont  (42   ,"Y");
	base2->SetLineWidth(0);

	TFile *rebinned = new TFile(Form("~/Summer2016/root_forgraphs/pt_PbPb_%d_%d.root",mult_start[num],mult_end[num]),"RECREATE");


	TGraphErrors *gr_pos = new TGraphErrors(NAchBins,x,ptavg_pos,NULL,ptavg_pos_err);
	TGraphErrors *gr_neg = new TGraphErrors(NAchBins,x,ptavg_neg,NULL,ptavg_neg_err);
	TGraphErrors *gr_diff = new TGraphErrors(NAchBins,x,ptavg_diff,NULL,ptavg_diff_err);
/*
	if(num==0){
		gr_pos->RemovePoint(0);
		gr_pos->RemovePoint(5);
		gr_neg->RemovePoint(0);
		gr_neg->RemovePoint(5);
		gr_diff->RemovePoint(0);
		gr_diff->RemovePoint(5);

	}
*/
	gr_pos->Write();
	gr_neg->Write();
	gr_diff->Write();



 //   TCanvas* c1 = new TCanvas("c1","c1");
 //   TCanvas* c2 = new TCanvas("c2","c2");
	TCanvas* c3 = new TCanvas("c3","c3",1,1,1200,600);
	c3->Divide(2,1,0.01,0.01);

	gr_neg -> SetMarkerStyle(20);
	gr_neg -> SetMarkerColor(kBlue);
	gr_pos -> SetMarkerStyle(34);	
	gr_pos -> SetMarkerColor(kRed);




	TLatex* text_a = makeLatex("CMS PbPb #sqrt{s_{NN}}=5.02TeV",0.25,0.85) ;
	//TLatex* text_b = makeLatex("185 #leq N_{trk}^{offline} < 220",0.25,0.80) ;
	TLatex* text_b = makeLatex(Form("%d #leq N^{offline}_{trk} < %d",mult_start[num],mult_end[num]),0.25,0.80) ;

	TLatex* text_c = makeLatex("0.3 < p_{T} < 3.0 GeV/c",0.25,0.75) ;
	TLatex* text_d = makeLatex("|#Delta#eta| > 1",0.25,0.70) ;

	text_a->SetTextFont(42);
	text_b->SetTextFont(42);
	text_c->SetTextFont(42);
	text_d->SetTextFont(42);



	TLegend* leg = new TLegend(0.76,0.80,0.94,.88);
	leg->SetLineColor(kWhite);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->AddEntry(gr_pos, "v_{2}^{#plus}{2}","p");
	leg->AddEntry(gr_neg , "v_{2}^{#minus}{2}","p");



	c3->cd(1);
	base->Draw("");
	gr_pos->Draw("PSame");
	gr_neg->Draw("PSame");
	text_a->DrawClone("Same");
	text_b->DrawClone("Same");
	text_c->DrawClone("Same");
	text_d->DrawClone("Same");

	leg->DrawClone("Same");


    //Define a linear function
	TF1* fit1 = new TF1("f1", "[0]+x*[1]", -0.13, 0.13);

	fit1->SetLineColor(kRed);
	fit1->SetLineStyle(2);
	gr_diff->Fit(fit1,"RN0");
	fit1->Write();


	rebinned->Close();

	c3->cd(2);



	TLatex* text2 = makeLatex(Form("Intercept : %f #pm %f",fit1->GetParameter(0),fit1->GetParError(0)),0.45,0.30) ;
	TLatex* text1 = makeLatex(Form("slope : %.4f #pm %.4f",fit1->GetParameter(1),fit1->GetParError(1)),0.45,0.25) ;
	text1->SetTextFont(42);
	text2->SetTextFont(42);
	base2->Draw("");
	fit1->DrawClone("Same");
	gr_diff->SetMarkerStyle(20);
	gr_diff->Draw("PSame");

	text_a->DrawClone("Same");
	text_b->DrawClone("Same");
	

	text1->DrawClone("Same");
	text2->DrawClone("Same");

	

	TF1 *fa1 = new TF1("fa1","0",-10,10); 
	fa1->SetLineColor(kBlack);
	fa1->SetLineWidth(0);
	fa1->DrawClone("Same");

	TLegend* leg2 = new TLegend(0.25,0.68,0.5,0.78);
	leg2->SetLineColor(kWhite);
	leg2->SetFillColor(0);
	leg2->SetFillStyle(0);
	leg2->AddEntry(fit1, "Linear fit","l");
	leg2->AddEntry(gr_diff , "data","p");
	leg2->DrawClone("Same");

	cout << mult_start[num] << endl;
	cout << mult_end[num] << endl;

	c3->Print(Form("~/Summer2016/pics/pt_PbPb_%d_%d_binning_%d.pdf",mult_start[num],mult_end[num],temp_index[num_temp]));
	c3->Print(Form("~/Summer2016/pics/pt_PbPb_%d_%d_binning_%d.gif",mult_start[num],mult_end[num],temp_index[num_temp]));




}
