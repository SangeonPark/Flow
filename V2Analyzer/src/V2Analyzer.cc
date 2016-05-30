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

    int nTracks = 0;
    int nTracks_pos = 0;
    int nTracks_neg = 0;

    //define the flow vectors 
    TComplex Q2_pos(0,0);
    TComplex Q2_neg(0,0);


    for( reco::TrackCollection::const_iterator cand = tracks->begin(); cand != tracks->end(); cand++){

	double eta = cand->eta();
	double charge = (double)cand->charge();
	double pt = cand->pt();
	double phi = cand->phi();

	//highPurity
	if(!cand->quality(reco::TrackBase::highPurity)) continue;

	//trkNHits cut
/*	int nhit = cand->numberOfValidHits();
	if(nhit <= nHitCut_) continue; */
     
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

	if(2.4<=fabs(eta) || pt <= 0.3) continue;
	
	TComplex e(1,2*phi,1);
	
	if(charge>0){
	    N_pos++;
	    Q2_pos += e;
	}
	if(charge<0){
	    N_neg++;
	    Q2_neg += e;
	}

//	double data[7]={pt,eta,phi,charge,dzos,dxyos,(double)nhit};
//	track_Data->Fill(pt,eta,phi,charge,dzos,dxyos);
    }

    if( nTracks < NTrkMin_ || nTracks >= NTrkMax_ ) return;
    
    int N_tot = N_pos + N_neg;
    int N_diff = N_pos - N_neg;
    double ach = (double)N_diff/N_tot;
    asym_Dist->Fill(ach);
    NTrkHist->Fill(nTracks);

    double wt_pos = (nTracks_pos)*(nTracks_pos-1);
    double wt_neg = (nTracks_neg)*(nTracks_neg-1);
    double wt = 1.0;

    double evt_avg_pos = (Q2_pos.Rho2()-nTracks_pos)/(nTracks_pos*(nTracks_pos-1));
    double evt_avg_neg = (Q2_neg.Rho2()-nTracks_neg)/(nTracks_neg*(nTracks_neg-1));

    double evt_wtd_pos = wt_pos * evt_avg_pos;
    double evt_wtd_neg = wt_neg * evt_avg_neg;
 
    sum_wt += wt;
    sum_wt_pos += wt_pos;
    sum_wt_neg += wt_neg;
    sum_wtdavg_pos += evt_wtd_pos;
    sum_wtdavg_neg += evt_wtd_neg;



}


// ------------ method called once each job just before starting event loop  ------------
void 
V2Analyzer::beginJob()    
{
    edm::Service<TFileService> fs;
    TH1D::SetDefaultSumw2();
    sum_wt = 0.0;
    sum_wt_pos = 0.0;
    sum_wt_neg = 0.0;
    sum_wtdavg_pos = 0.0;
    sum_wtdavg_neg = 0.0;
//    track_Data = fs->make<TNtuple>("track_Data","track_Data","pt:eta:phi:charge:dzos:dxyos:nhit");
    asym_Dist = fs->make<TH1D>("ChargeAsym","Distribution of Charge Asymmetry",21,-0.4,0.4);
    NTrkHist = fs->make<TH1D>("NTrkHist","NTrack",1000,0,500);
//    C2Hist = fs->make<TH1D>("C2Hist","C2 Histogram", 

    asym_Dist->SetMarkerStyle(21);
    asym_Dist->SetMarkerSize(0.8);
    asym_Dist->SetStats(0);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
V2Analyzer::endJob() 
{
    double c2_pos = sum_wtdavg_pos/sum_wt_pos;
    double c2_neg = sum_wtdavg_neg/sum_wt_neg;
    double v2_pos = sqrt(c2_pos);
    double v2_neg = sqrt(c2_neg);
    std::cout<<c2_pos<<std::endl;
    std::cout<<c2_neg<<std::endl;
    std::cout<<v2_pos<<std::endl;
    std::cout<<v2_neg;
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
