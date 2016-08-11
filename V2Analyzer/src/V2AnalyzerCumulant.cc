// -*- C++ -*-
//
// Package:    V2AnalyzerCumulant
// Class:      V2AnalyzerCumulant
// 
/**\class V2AnalyzerCumulant V2AnalyzerCumulant.cc Flow/V2Analyzer/src/V2AnalyzerCumulant.cc

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
#include "Flow/V2Analyzer/interface/V2AnalyzerBase.h"

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
 V2AnalyzerCumulant::V2AnalyzerCumulant(const edm::ParameterSet& iConfig)
 {

 	dxySigCut_ = iConfig.getParameter<double>("dxySigCut");
 	dzSigCut_ = iConfig.getParameter<double>("dzSigCut");
 	etaCutMin_ = iConfig.getParameter<double>("etaCutMin");
 	etaCutMax_ = iConfig.getParameter<double>("etaCutMax");
 	ptCutMin_ = iConfig.getParameter<double>("ptCutMin");
 	ptCutMax_ = iConfig.getParameter<double>("ptCutMax");
 	etaHFLow_ = iConfig.getParameter<double>("etaHFLow");
 	etaHFUpp_ = iConfig.getParameter<double>("etaHFUpp");
 	etaGap_ = iConfig.getParameter<double>("etaGap");
 	Nmin_ = iConfig.getParameter<int>("Nmin");
 	Nmax_ = iConfig.getParameter<int>("Nmax");
 	NEtaBins_ = iConfig.getParameter<int>("NEtaBins");
 	

 	trackSrc_ = iConfig.getParameter<edm::InputTag>("trackSrc");
 	vertexSrc_ = iConfig.getParameter<std::string>("vertexSrc");
 	towerSrc_ = iConfig.getParameter<edm::InputTag>("towerSrc");

 	doEffCorrection_ = iConfig.getParameter<bool>("doEffCorrection");
 	doAchEffCorrection_ = iConfig.getParameter<bool>("doAchEffCorrection");
 	reverseBeam_ = iConfig.getParameter<bool>("reverseBeam");
 	useCentrality_ = iConfig.getParameter<bool>("useCentrality");

 	centBins_ = iConfig.getUntrackedParameter<std::vector<double>>("centBins");
 	achBins_ = iConfig.getUntrackedParameter<std::vector<double>>("achBins");
 	efftablePath_ = iConfig.getParameter<std::string>("efftablePath");
 	efftableName_ = iConfig.getParameter<std::string>("efftableName");





//now do what ever initialization is needed

 }


 V2AnalyzerCumulant::~V2AnalyzerCumulant()
 {

// do anything here that needs to be done at desctruction time
// (e.g. close files, deallocate resources etc.)

 }


//
// member functions
//

// ------------ method called for each event  ------------
 void V2AnalyzerCumulant::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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

 	edm::Handle<reco::TrackCollection> tracks;
 	iEvent.getByLabel(trackSrc_, tracks);

 //centrality range selection

 	Handle<CaloTowerCollection> towers;
 	iEvent.getByLabel(towerSrc_, towers);



 	double etHFtowerSumPlus = 0.0;
 	double etHFtowerSumMinus = 0.0;
 	double etHFtowerSum = 0.0;

 	if( useCentrality_ ){

 		for( unsigned i = 0; i<towers->size(); ++ i){
 			const CaloTower & tower = (*towers)[ i ];
 			double eta = tower.eta();
 			bool isHF = tower.ietaAbs() > 29;
 			if(isHF && eta > 0){
 				etHFtowerSumPlus += tower.pt();
 			}
 			if(isHF && eta < 0){
 				etHFtowerSumMinus += tower.pt();
 			}
 		}
 		etHFtowerSum=etHFtowerSumPlus + etHFtowerSumMinus;

 		int bin = -1;
 		for(int j=0; j<200; j++){
 			if( etHFtowerSum >= centBins_[j] ){
 				bin = j; break;
 			}
 		}

 		int hiBin = bin;
 		cbinHist->Fill( hiBin );
 		if( hiBin < Nmin_ || hiBin >= Nmax_ ) return;

 	}



//variables for charge asymmetry calculation
 	double N_pos = 0.0;
 	double N_neg = 0.0;
 	double N_tot = 0.0;

//variables for charge asymmetry calculation of different eta range
 	double eta2_N_pos = 0.0;
 	double eta2_N_neg = 0.0;
 	double eta2_N_tot = 0.0;	

//NTrackOffline values
 	int nTracks = 0;
 	int nTracks_pos = 0;
 	int nTracks_neg = 0;

//define the flow vectors and weight

 	const int NBins = NEtaBins_;
 	double etarange = etaCutMax_ - etaCutMin_;
 	double Binsize = etarange/(double)NBins;

 	TComplex Q2_pos[NBins];
 	TComplex Q2_neg[NBins];
 	double WQ2_pos[NBins];
 	double WQ2_neg[NBins];

 	for (int i = 0; i < NBins; ++i)
 	{
 		Q2_pos[i](0,0); 
 		Q2_neg[i](0,0);
 		WQ2_pos[i] = 0.0;
 		WQ2_neg[i] = 0.0;

 	}

 	for( reco::TrackCollection::const_iterator cand = tracks->begin(); cand != tracks->end(); cand++){

 		double eta = cand->eta();
 		double charge = (double)cand->charge();
 		double pt = cand->pt();
 		double phi = cand->phi();
 		double weight = 1.0;

 		if( doEffCorrection_ ){
 			weight = 1.0/effTable->GetBinContent( effTable->FindBin(eta, pt) );
 		}

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

//kinematic cuts
 		if(pt <= ptCutMin_ ||  ptCutMax_ <= pt ) continue;

 		if(fabs(eta)<1.0){
 			if(doAchEffCorrection_){
 				eta2_N_tot += weight;
 				if( charge > 0){ eta2_N_pos+= weight;}
 				if( charge < 0){ eta2_N_neg+= weight;}
 			}
 			if(!doAchEffCorrection_){
 				eta2_N_tot += 1.0;
 				if( charge > 0){ eta2_N_pos+= 1.0;}
 				if( charge < 0){ eta2_N_neg+= 1.0;}

 			}
 		}

 		
 		if(eta <= etaCutMin_ || etaCutMax_ <= eta) continue;
 		if(reverseBeam_) { eta *= -1.0;}


 		TComplex e(1,2*phi,1);
 		e *= weight; 


 		if(doAchEffCorrection_){
 			N_tot += weight;
 			if( charge > 0){ N_pos+= weight;}
 			if( charge < 0){ N_neg+= weight;}
 		}
 		if(!doAchEffCorrection_){
 			N_tot += 1.0;
 			if( charge > 0){ N_pos+= 1.0;}
 			if( charge < 0){ N_neg+= 1.0;}

 		}

 		for (int i = 0; i < NBins; ++i)
 		{
 			double lb = Binsize*i+etaCutMin_;
 			double ub = Binsize*(i+1)+etaCutMin_;
 			if(lb <= eta && eta < ub){
 				if(charge > 0){
 					Q2_pos[i] += e; 
 					WQ2_pos[i] += weight;

 				}
 				if (charge < 0){
 					Q2_neg[i] += e;
 					WQ2_neg[i] += weight;

 				}

 				
 			}
 		}
 		
 	}

//Cut on NTrackOffline (Should be disabled if useCentrality = True)	
 	if(!useCentrality_){

 		if( nTracks < Nmin_ || nTracks >= Nmax_ ) return;

 	}

//asymmetry calculation
 	double N_diff = N_pos - N_neg;
 	double ach = N_diff/N_tot;
 	asym_Dist->Fill(ach);
 	NTrkHist->Fill(nTracks);

//asymmetry calculation for a differente eta range
 	double eta2_N_diff = eta2_N_pos - eta2_N_neg;
 	double eta2_ach = eta2_N_diff/eta2_N_tot;
 	scatterHist_twoetarange->Fill(eta2_ach,ach);	

 	for(Int_t i=0;i<NAchBins;i++){

 		if(achBins_[i] <= ach && ach < achBins_[i+1]){
 			
 			ach_hist[i]->Fill(ach);
 			TComplex z(0,0);
 			double Npairs=0.0;

 			for (int j = 0; j < NBins; j++)
 			{
 				for(int k = 0; k < NBins; k++){

 					if(abs(j-k) <= (etaGap_/Binsize)) continue;


 					z = Q2_pos[j] * TComplex::Conjugate(Q2_pos[k]);
 					Npairs = WQ2_pos[j] * WQ2_pos[k];
 					z /= Npairs;



 					c2_pos[i][0]->Fill(z.Re(), Npairs);
 					c2_pos[i][1]->Fill(z.Im(), Npairs);

 					z = Q2_neg[j] * TComplex::Conjugate(Q2_neg[k]);
 					Npairs = WQ2_neg[j] * WQ2_neg[k];
 					z /= Npairs;
 					c2_neg[i][0]->Fill(z.Re(), Npairs);
 					c2_neg[i][1]->Fill(z.Im(), Npairs);

 				}
 			} 			
 		}
 	}
 }



// ------------ method called once each job just before starting event loop  ------------
 void V2AnalyzerCumulant::beginJob()    
 {
 	edm::Service<TFileService> fs;
 	TH1D::SetDefaultSumw2();

//ach binning
 	NAchBins = achBins_.size()-1;

 	asym_Dist = fs->make<TH1D>("ChargeAsym","Distribution of Charge Asymmetry",1000,-0.4,0.4);
 	NTrkHist = fs->make<TH1D>("NTrkHist","NTrack",5000,0,5000);
 	cbinHist = fs->make<TH1D>("cbinHist",";cbin",200,0,200);
 	scatterHist_twoetarange = fs->make<TH2D>("scatterHist_twoetarange","A_{ch} of two different eta range;A_{ch} |#eta| < 1;A_{ch} |#eta| < 2.4",1000,-0.3,0.3,1000,-0.3,0.3);
 	


 	edm::FileInPath fip1(efftablePath_.c_str());  
 	TFile f1(fip1.fullPath().c_str(),"READ");
 	effTable = (TH2D*)f1.Get(efftableName_.c_str());

//list of c2 histograms
 	for (Int_t i = 0; i < NAchBins; i++){

 		c2_pos[i][0] = fs->make<TH1D>(Form("c2pos_%d_cos",i),"c2 Distribution",2000,-1,1);
 		c2_pos[i][1] = fs->make<TH1D>(Form("c2pos_%d_sin",i),"c2 Distribution",2000,-1,1);
 		c2_neg[i][0] = fs->make<TH1D>(Form("c2neg_%d_cos",i),"c2 Distribution",2000,-1,1);
 		c2_neg[i][1] = fs->make<TH1D>(Form("c2neg_%d_sin",i),"c2 Distribution",2000,-1,1);
 		ach_hist[i] = fs->make<TH1D>(Form("ach_%d",i+1),Form("ach_%d",i+1),1000,-0.4,0.4);
 		
 	}

 }

// ------------ method called once each job just after ending the event loop  ------------
 void
 V2AnalyzerCumulant::endJob() 
 {    
 }

// ------------ method called when starting to processes a run  ------------
 void 
 V2AnalyzerCumulant::beginRun(edm::Run const&, edm::EventSetup const&)
 {
 }

// ------------ method called when ending the processing of a run  ------------
 void 
 V2AnalyzerCumulant::endRun(edm::Run const&, edm::EventSetup const&)
 {
 }

// ------------ method called when starting to processes a luminosity block  ------------
 void 
 V2AnalyzerCumulant::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
 {
 }

// ------------ method called when ending the processing of a luminosity block  ------------
 void 
 V2AnalyzerCumulant::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
 {
 }

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
 void
 V2AnalyzerCumulant::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
//The following says we do not know what parameters are allowed so do no validation
// Please change this to state exactly what you do use, even if it is no parameters
 	edm::ParameterSetDescription desc;
 	desc.setUnknown();
 	descriptions.addDefault(desc);
 }

//define this as a plug-in
 DEFINE_FWK_MODULE(V2AnalyzerCumulant);
