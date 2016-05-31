// -*- C++ -*-
//
// Package:    V2Analyzer
// Class:      V2Analyzer
// 
/**\class V2Analyzer V2Analyzer.cc Flow/V2Analyzer/src/V2Analyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Sang Eon Park,,,
//         Created:  Mon May 30 11:27:47 CEST 2016
// $Id$
//
//


// system include files
#include "Flow/V2Analyzer/interface/V2Analyzer.h"




//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
V2Analyzer::V2Analyzer(const edm::ParameterSet& iConfig)

{
    //    nHitCut_ = iConfig.getParameter<int>("nHitCut");
    dxySigCut_ = iConfig.getParameter<double>("dxySigCut");
    dzSigCut_ = iConfig.getParameter<double>("dzSigCut");
    etaCutMin_ = iConfig.getParameter<double>("etaCutMin");
    etaCutMax_ = iConfig.getParameter<double>("etaCutMax");
    NTrkMin_ = iConfig.getParameter<int>("NTrkMin");
    NTrkMax_ = iConfig.getParameter<int>("NTrkMax");
    
    trackSrc_ = iConfig.getParameter<edm::InputTag>("trackSrc");
    vertexSrc_ = iConfig.getParameter<std::string>("vertexSrc");
   //now do what ever initialization is needed

}


V2Analyzer::~V2Analyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
V2Analyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    using namespace std;

    edm::Handle<reco::VertexCollection> vertices;
    iEvent.getByLabel(vertexSrc_,vertices);
    double bestvz=-999.9, bestvx=-999.9, bestvy=-999.9;
    double bestvzError=-999.9, bestvxError=-999.9, bestvyError=-999.9;
    const reco::Vertex & vtx = (*vertices)[0];
    bestvz = vtx.z(); bestvx = vtx.x(); bestvy = vtx.y();
    bestvzError = vtx.zError(); bestvxError = vtx.xError(); bestvyError = vtx.yError();

    //vertices selection
    if(bestvz < -15.0 || bestvz>15.0) return;

//    cout << "test: " << bestvz << bestvx << bestvy << bestvzError << bestvxError << bestvyError;
    
    
    edm::Handle<reco::TrackCollection> tracks;
    iEvent.getByLabel(trackSrc_, tracks);

    int N_pos = 0;
    int N_neg = 0;
    int N_tot = 0;

    int nTracks = 0;
    int nTracks_pos = 0;
    int nTracks_neg = 0;

    //define the flow vectors 
    TComplex Q2_pos(0,0);
    TComplex Q2_neg(0,0);
    TComplex Q2(0,0);
//    double cos_sum=0.0;
//    double sin_sum=0.0;

   

    for( reco::TrackCollection::const_iterator cand = tracks->begin(); cand != tracks->end(); cand++){

	double eta = cand->eta();
	double charge = (double)cand->charge();
	double pt = cand->pt();
	double phi = cand->phi();

	//highPurity
	if(!cand->quality(reco::TrackBase::highPurity)) continue;

	//DCA
	math::XYZPoint bestvtx(bestvx,bestvy,bestvz);
	double dzbest = cand->dz(bestvtx);
	double dxybest = cand->dxy(bestvtx);
	double dzerror = sqrt(cand->dzError()*cand->dzError()+bestvzError*bestvzError);
	double dxyerror = sqrt(cand->d0Error()*cand->d0Error()+bestvxError*bestvyError);
	double dzos = dzbest/dzerror;
	double dxyos = dxybest/dxyerror;
	if( dzSigCut_ <= fabs(dzos) || dxySigCut_ <= fabs(dxyos) ) continue;

	//ptError
	if(fabs(cand->ptError())/cand->pt() > 0.1 ) continue;

	if(fabs(eta)<2.4 && pt > 0.4){
	    nTracks++;
	    if(charge>0){
		nTracks_pos++;
	    }
	    else{
		nTracks_neg++;
	    }
	}

	if(2.4<=fabs(eta) || pt < 0.3 || pt > 3.0 ) continue;



	TComplex e(1,2*phi,1);
	
	Q2 += e;
	N_tot++;
	
	
	if(charge>0){
	    N_pos++;
	    Q2_pos += e;
	}
	if(charge<0){
	    N_neg++;
	    Q2_neg += e;
	}
	
    }


    /*
    int Npairs = 0;
    for( reco::TrackCollection::const_iterator cand1 = tracks->begin(); cand1 != tracks->end(); cand1++){

	double eta1 = cand1->eta();
//	double charge1 = (double)cand1->charge();
	double pt1 = cand1->pt();
	double phi1 = cand1->phi();

	//highPurity
	if(!cand1->quality(reco::TrackBase::highPurity)) continue;

	//DCA
	math::XYZPoint bestvtx(bestvx,bestvy,bestvz);
	double dzbest1 = cand1->dz(bestvtx);
	double dxybest1 = cand1->dxy(bestvtx);
	double dzerror1 = sqrt(cand1->dzError()*cand1->dzError()+bestvzError*bestvzError);
	double dxyerror1 = sqrt(cand1->d0Error()*cand1->d0Error()+bestvxError*bestvyError);
	double dzos1 = dzbest1/dzerror1;
	double dxyos1 = dxybest1/dxyerror1;
	if( dzSigCut_ <= fabs(dzos1) || dxySigCut_ <= fabs(dxyos1) ) continue;

	//ptError
	if(fabs(cand1->ptError())/cand1->pt() > 0.1 ) continue;
	if(2.4<=fabs(eta1) || pt1 < 0.3 || pt1 > 3.0 ) continue;
	
	for( reco::TrackCollection::const_iterator cand2 = tracks->begin(); cand2 != tracks->end(); cand2++){

	     double eta2 = cand2->eta();
//	     double charge2 = (double)cand2->charge();
	     double pt2 = cand2->pt();
	     double phi2 = cand2->phi();

	     //highPurity
	     if(!cand2->quality(reco::TrackBase::highPurity)) continue;

	     //DCA
	     math::XYZPoint bestvtx(bestvx,bestvy,bestvz);
	     double dzbest2 = cand2->dz(bestvtx);
	     double dxybest2 = cand2->dxy(bestvtx);
	     double dzerror2 = sqrt(cand2->dzError()*cand2->dzError()+bestvzError*bestvzError);
	     double dxyerror2 = sqrt(cand2->d0Error()*cand2->d0Error()+bestvxError*bestvyError);
	     double dzos2 = dzbest2/dzerror2;
	     double dxyos2 = dxybest2/dxyerror2;
	     if( dzSigCut_ <= fabs(dzos2) || dxySigCut_ <= fabs(dxyos2) ) continue;

	     //ptError
	     if(fabs(cand2->ptError())/cand2->pt() > 0.1 ) continue;
	     if(2.4<=fabs(eta2) || pt2 < 0.3 || pt2 > 3.0 ) continue;

	     if(cand1 == cand2) continue;
	     cos_sum += cos(2*(phi1-phi2));
	     Npairs++;
	}
	 
    }
    */
    
    if( nTracks < NTrkMin_ || nTracks >= NTrkMax_ ) return;
    
    int N_diff = N_pos - N_neg;
    double ach = (double)N_diff/N_tot;
    asym_Dist->Fill(ach);
    NTrkHist->Fill(nTracks);

    double wt_pos = 1.0;
    double wt_neg = 1.0;
    double wt = 1.0;

 
    double evt_avg_pos = (Q2_pos.Rho2()-N_pos)/(N_pos*(N_pos-1.0));
    double evt_avg_neg = (Q2_neg.Rho2()-N_neg)/(N_neg*(N_neg-1.0));
    double evt_avg = (Q2.Rho2()-N_tot)/(N_tot*(N_tot-1.0));
    /*
    cout << "numerator : " << cos_sum*cos_sum+sin_sum*sin_sum-N_tot << endl;
    cout << "denom : " << N_tot*(N_tot-1.0) << endl;
    cout << "evt_avg : " << evt_avg << endl;
    if(evt_avg < -0.008){
	cout << "exist------------------------" <<endl;
    }
    */

    /*
    c2Hist->Fill(evt_avg);
    c2Hist_pos->Fill(evt_avg_pos);
    c2Hist_neg->Fill(evt_avg_neg);
    */
    for(Int_t i=0;i<5;i++){
	 if(Bins[i] < ach && ach <= Bins[i+1]){
	     ach_hist[i]->Fill(ach);
	     c2_pos[i]->Fill(evt_avg_pos);
	     c2_neg[i]->Fill(evt_avg_neg);
	     c2_tot[i]->Fill(evt_avg);
	 }
    }
    
       

    // cout << "sum_wt_pos" << sum_wt_pos << endl;
    //cout << "sum_wt_neg" << sum_wt_neg << endl;

}


// ------------ method called once each job just before starting event loop  ------------
void 
V2Analyzer::beginJob()    
{
    edm::Service<TFileService> fs;
    TH1D::SetDefaultSumw2();

//    track_Data = fs->make<TNtuple>("track_Data","track_Data","pt:eta:phi:charge:dzos:dxyos:nhit");
    asym_Dist = fs->make<TH1D>("ChargeAsym","Distribution of Charge Asymmetry",21,-0.4,0.4);
    NTrkHist = fs->make<TH1D>("NTrkHist","NTrack",1000,0,500);

    //list of c2 histograms
    c2_tot[0] = fs->make<TH1D>("c2Hist_1","c2 Distribution1",1000,-1,1);
    c2_pos[0] = fs->make<TH1D>("c2Hist_pos_1","c2 Distribution for positive charges1",1000,-1,1);
    c2_neg[0] = fs->make<TH1D>("c2Hist_neg_1","c2 Distribution for negative charges1",1000,-1,1);

    c2_tot[1] = fs->make<TH1D>("c2Hist2","c2 Distribution2",1000,-1,1);
    c2_pos[1] = fs->make<TH1D>("c2Hist_pos2","c2 Distribution for positive charges2",1000,-1,1);
    c2_neg[1] = fs->make<TH1D>("c2Hist_neg2","c2 Distribution for negative charges2",1000,-1,1);

    c2_tot[2] = fs->make<TH1D>("c2Hist3","c2 Distribution3",1000,-1,1);
    c2_pos[2] = fs->make<TH1D>("c2Hist_pos3","c2 Distribution for positive charges3",1000,-1,1);
    c2_neg[2] = fs->make<TH1D>("c2Hist_neg3","c2 Distribution for negative charges3",1000,-1,1);

    c2_tot[3] = fs->make<TH1D>("c2Hist4","c2 Distribution4",1000,-1,1);
    c2_pos[3]= fs->make<TH1D>("c2Hist_pos4","c2 Distribution for positive charges4",1000,-1,1);
    c2_neg[3] = fs->make<TH1D>("c2Hist_neg4","c2 Distribution for negative charges4",1000,-1,1);

    c2_tot[4] = fs->make<TH1D>("c2Hist5","c2 Distribution5",1000,-1,1);
    c2_pos[4] = fs->make<TH1D>("c2Hist_pos5","c2 Distribution for positive charges5",1000,-1,1);
    c2_neg[4] = fs->make<TH1D>("c2Hist_neg5","c2 Distribution for negative charges5",1000,-1,1);

    ach_hist[0] = fs->make<TH1D>("ach_1","ach_1",1000,Bins[0],Bins[1]);
    ach_hist[1] = fs->make<TH1D>("ach_2","ach_2",1000,Bins[1],Bins[2]);
    ach_hist[2] = fs->make<TH1D>("ach_2","ach_3",1000,Bins[2],Bins[3]);
    ach_hist[3] = fs->make<TH1D>("ach_3","ach_4",1000,Bins[3],Bins[4]);
    ach_hist[4] = fs->make<TH1D>("ach_3","ach_5",1000,Bins[4],Bins[5]);


    

}

// ------------ method called once each job just after ending the event loop  ------------
void
V2Analyzer::endJob() 
{
    using namespace std;
    /*
    cout<< "sum of weighted average" << sum_wtdavg_pos <<endl;
    cout << "sum of weights_positive : " << sum_wt_pos << endl;
    cout << "sum of weights_negative : " << sum_wt_neg << endl;
    cout << "sum of weights : " << sum_wt << endl;


    */

    double x[5];
    double v2_pos_val[5];
    double v2_neg_val[5];
    double v2_tot_val[5];
    double c2_pos_val[5];
    double c2_neg_val[5];
    double c2_tot_val[5];

    for(Int_t i=0; i<5; i++){
	x[i]=ach_hist[i]->GetMean();
	c2_pos_val[i]=c2_pos[i]->GetMean();
	c2_neg_val[i]=c2_neg[i]->GetMean();
	c2_tot_val[i]=c2_tot[i]->GetMean();
	v2_pos_val[i]=sqrt(c2_pos_val[i]);
	v2_neg_val[i]=sqrt(c2_neg_val[i]);
	v2_tot_val[i]=sqrt(c2_tot_val[i]);

    }  

    gr_pos = fs->make<TGraph>(5,x,v2_pos_val);
    gr_neg = fs->make<TGraph>(5,x,v2_neg_val);
    // v2graph->Add(gr_pos);
    //v2graph->Add(gr_neg);
    
}

// ------------ method called when starting to processes a run  ------------
void 
V2Analyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
V2Analyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
V2Analyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
V2Analyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
V2Analyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(V2Analyzer);
