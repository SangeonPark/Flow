// -*- C++ -*-
//
// Package:    V3AnalyzerSP
// Class:      V3AnalyzerSP
// 
/**\class V3AnalyzerSP V3AnalyzerSP.cc Flow/V2Analyzer/src/V3AnalyzerSP.cc

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
 V3AnalyzerSP::V3AnalyzerSP(const edm::ParameterSet& iConfig)
 {

 	offlineptErr_ = iConfig.getUntrackedParameter<double>("offlineptErr");
 	offlineDCA_ = iConfig.getUntrackedParameter<double>("offlineDCA");
 	etaCutMin_ = iConfig.getParameter<double>("etaCutMin");
 	etaCutMax_ = iConfig.getParameter<double>("etaCutMax");
 	ptCutMin_ = iConfig.getParameter<double>("ptCutMin");
 	ptCutMax_ = iConfig.getParameter<double>("ptCutMax");

 	etaHFLow_ = iConfig.getParameter<double>("etaHFLow");
 	etaHFUpp_ = iConfig.getParameter<double>("etaHFUpp");
 	Nmin_ = iConfig.getParameter<int>("Nmin");
 	Nmax_ = iConfig.getParameter<int>("Nmax");
 	vzLow_ = iConfig.getUntrackedParameter<double>("vzLow");
 	vzHigh_ = iConfig.getUntrackedParameter<double>("vzHigh");

 	trackSrc_ = iConfig.getParameter<edm::InputTag>("trackSrc");
 	vertexSrc_ = iConfig.getParameter<std::string>("vertexSrc");
 	towerSrc_ = iConfig.getParameter<edm::InputTag>("towerSrc");

 	doEffCorrection_ = iConfig.getParameter<bool>("doEffCorrection");
 	reverseBeam_ = iConfig.getParameter<bool>("reverseBeam");


 	useCentrality_ = iConfig.getParameter<bool>("useCentrality");
 	centBins_ = iConfig.getUntrackedParameter<std::vector<double>>("centBins");
 	achBins_ = iConfig.getUntrackedParameter<std::vector<double>>("achBins");
 	efftablePath_ = iConfig.getParameter<std::string>("efftablePath");
 	efftableName_ = iConfig.getParameter<std::string>("efftableName");

//now do what ever initialization is needed

 }


 V3AnalyzerSP::~V3AnalyzerSP()
 {

// do anything here that needs to be done at desctruction time
// (e.g. close files, deallocate resources etc.)

 }


//
// member functions
//

// ------------ method called for each event  ------------
 void V3AnalyzerSP::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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
 	if( fabs(bestvz) < vzLow_ || fabs(bestvz) > vzHigh_ ) return;

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

 	double N_pos = 0.0;
 	double N_neg = 0.0;
 	double N_tot = 0.0;

 	double N_pos_fixed = 0.0;
 	double N_neg_fixed = 0.0;
 	double N_tot_fixed = 0.0;

 	double pt_tot_pos = 0.0;
 	double pt_avg_pos = 0.0;
 	double pt_weight_pos = 0.0;

 	double pt_tot_neg = 0.0;
 	double pt_avg_neg = 0.0;
 	double pt_weight_neg = 0.0;


 	double W_Q2C = 0.0;
 	double W_Q2pluseta_pos = 0.0;
 	double W_Q2pluseta_neg = 0.0;
 	double W_Q2minuseta_pos = 0.0;
 	double W_Q2minuseta_neg = 0.0;


 	int nTracks = 0;
 	int nTracks_pos = 0;
 	int nTracks_neg = 0;

//define the flow vectors 
 	TComplex Q2pluseta_pos(0,0);
 	TComplex Q2pluseta_neg(0,0);
 	TComplex Q2minuseta_pos(0,0);
 	TComplex Q2minuseta_neg(0,0);

 	TComplex Q2C(0,0);

 	TComplex Q2A(0,0);
 	TComplex Q2B(0,0);

 	for( reco::TrackCollection::const_iterator cand = tracks->begin(); cand != tracks->end(); cand++){

 		double eta = cand->eta();
 		double charge = (double)cand->charge();
 		double pt = cand->pt();
 		double weight = 1.0;
 		if( doEffCorrection_ ){
 			weight = 1.0/effTable->GetBinContent( effTable->FindBin(eta, pt) );
 		}
//highPurity
 		if(!cand->quality(reco::TrackBase::highPurity)) continue;
 		math::XYZPoint bestvtx(bestvx,bestvy,bestvz);
 		double dzbest = cand->dz(bestvtx);
 		double dxybest = cand->dxy(bestvtx);
 		double dzerror = sqrt(cand->dzError()*cand->dzError()+bestvzError*bestvzError);
 		double dxyerror = sqrt(cand->d0Error()*cand->d0Error()+bestvxError*bestvyError);
 		double dzos = dzbest/dzerror;
 		double dxyos = dxybest/dxyerror;
 		if(fabs(dzos) > 3) continue;
 		if(fabs(dxyos) > 3) continue;
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
 		if(pt <= 0.3 ||  3.0 <= pt ) continue;
 		if(eta <= -2.4 || 2.4 <= eta) continue;
 		N_tot_fixed += weight;
 		if(charge>0){ N_pos_fixed += weight; }
 		if(charge<0){ N_neg_fixed += weight; }
 	}
 	//Cut on NTrackOffline (Should be disabled if useCentrality = True)	
 	if(!useCentrality_){

 		if( nTracks < Nmin_ || nTracks >= Nmax_ ) return;

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
 		if(fabs(dzos) > offlineDCA_) continue;
 		if(fabs(dxyos) > offlineDCA_) continue;

//ptError
 		if(fabs(cand->ptError())/cand->pt() > offlineptErr_ ) continue;


 		if(pt <= ptCutMin_ ||  ptCutMax_ <= pt ) continue;
 		if(eta <= etaCutMin_ || etaCutMax_ <= eta) continue;
 		if(reverseBeam_) { eta *= -1.0;}

 		etaHist->Fill(eta);

 		TComplex e(1,3*phi,1);

 		e *= weight;
 		N_tot += weight; 
 		if( charge > 0){
 			N_pos+=weight;
 			pt_tot_pos += pt*weight;
 			pt_weight_pos += weight; 
 		}
 		if( charge < 0){
 			N_neg+=weight;
 			pt_tot_neg += pt*weight;
 			pt_weight_neg += weight;

 		}


 		if(-1.0 <= eta && eta < 1.0){
 			Q2C += e;
 			W_Q2C += weight;


 		}
 		if(0 < eta && eta < 2.4){
 			if(charge > 0.0){
 				Q2pluseta_pos += e;
 				W_Q2pluseta_pos += weight;

 			}
 			if(charge < 0.0){
 				Q2pluseta_neg += e;
 				W_Q2pluseta_neg += weight;

 			}
 		}
 		if(-2.4 < eta && eta < 0){
 			if(charge > 0.0){
 				Q2minuseta_pos += e;
 				W_Q2minuseta_pos += weight;

 			}
 			if(charge < 0.0){
 				Q2minuseta_neg += e;
 				W_Q2minuseta_neg += weight;

 			}
 		}

 	}

 	double W_Q2A = 0;
 	double W_Q2B = 0;

 	for(unsigned i=0; i<towers->size(); i++){

 		const CaloTower & hit = (*towers)[i];

 		double caloEta = hit.eta();
 		double caloPhi = hit.phi();
 		double w = hit.et(vtx.z());
 		if(reverseBeam_) { caloEta *= -1.0;}


 		TComplex e(1,3*caloPhi,1);

 		e*=w;


 		if( -etaHFUpp_ <= caloEta && caloEta < -etaHFLow_ ){
 			W_Q2A+=w;
 			Q2A += e;
 		}

 		else if( etaHFLow_ <= caloEta && caloEta < etaHFUpp_ ){
 			W_Q2B+=w;
 			Q2B += e;
 		}
 	}

 	double N_diff_fixed = N_pos_fixed - N_neg_fixed;
 	double ach = N_diff_fixed/N_tot_fixed;

 	pt_avg_pos = pt_tot_pos/pt_weight_pos; 
 	pt_avg_neg = pt_tot_neg/pt_weight_neg; 

 	asym_Dist->Fill(ach);
 	NTrkHist->Fill(nTracks);

 	for(Int_t i=0;i<NAchBins;i++){

 		if(achBins_[i] < ach && ach <= achBins_[i+1]){
 			ach_hist[i]->Fill(ach);
 			pt_pos[i]->Fill(pt_avg_pos);
 			pt_neg[i]->Fill(pt_avg_neg);

 			TComplex z;
 			double Npairs;

         //case 1, positive
 			z = Q2pluseta_pos * TComplex::Conjugate(Q2A);
 			Npairs = W_Q2pluseta_pos * W_Q2A;
 			z /= Npairs;
 			c2_pos_case1[i][0][0]->Fill(z.Re(),Npairs);
 			c2_pos_case1[i][0][1]->Fill(z.Im(),Npairs);

 			z = Q2A * TComplex::Conjugate(Q2B);
 			Npairs = W_Q2A * W_Q2B;
 			z /= Npairs;
 			c2_pos_case1[i][1][0]->Fill(z.Re(),Npairs);
 			c2_pos_case1[i][1][1]->Fill(z.Im(),Npairs);

 			z = Q2A * TComplex::Conjugate(Q2C);
 			Npairs = W_Q2A * W_Q2C;
 			z /= Npairs;
 			c2_pos_case1[i][2][0]->Fill(z.Re(),Npairs);
 			c2_pos_case1[i][2][1]->Fill(z.Im(),Npairs);

 			z = Q2B * TComplex::Conjugate(Q2C);
 			Npairs = W_Q2B * W_Q2C;
 			z /= Npairs;
 			c2_pos_case1[i][3][0]->Fill(z.Re(),Npairs);
 			c2_pos_case1[i][3][1]->Fill(z.Im(),Npairs);


     //case1, negative
 			z = Q2pluseta_neg * TComplex::Conjugate(Q2A);
 			Npairs = W_Q2pluseta_neg * W_Q2A;
 			z /= Npairs;
 			c2_neg_case1[i][0][0]->Fill(z.Re(),Npairs);
 			c2_neg_case1[i][0][1]->Fill(z.Im(),Npairs);

 			z = Q2A * TComplex::Conjugate(Q2B);
 			Npairs = W_Q2A * W_Q2B;
 			z /= Npairs;
 			c2_neg_case1[i][1][0]->Fill(z.Re(),Npairs);
 			c2_neg_case1[i][1][1]->Fill(z.Im(),Npairs);

 			z = Q2A * TComplex::Conjugate(Q2C);
 			Npairs = W_Q2A * W_Q2C;
 			z /= Npairs;
 			c2_neg_case1[i][2][0]->Fill(z.Re(),Npairs);
 			c2_neg_case1[i][2][1]->Fill(z.Im(),Npairs);

 			z = Q2B * TComplex::Conjugate(Q2C);
 			Npairs = W_Q2B * W_Q2C;
 			z /= Npairs;
 			c2_neg_case1[i][3][0]->Fill(z.Re(),Npairs);
 			c2_neg_case1[i][3][1]->Fill(z.Im(),Npairs);

     //case2, positive
 			z = Q2minuseta_pos * TComplex::Conjugate(Q2B);
 			Npairs = W_Q2minuseta_pos * W_Q2B;
 			z /= Npairs;
 			c2_pos_case2[i][0][0]->Fill(z.Re(),Npairs);
 			c2_pos_case2[i][0][1]->Fill(z.Im(),Npairs);

 			z = Q2B * TComplex::Conjugate(Q2A);
 			Npairs = W_Q2B * W_Q2A;
 			z /= Npairs;
 			c2_pos_case2[i][1][0]->Fill(z.Re(),Npairs);
 			c2_pos_case2[i][1][1]->Fill(z.Im(),Npairs);

 			z = Q2B * TComplex::Conjugate(Q2C);
 			Npairs = W_Q2B * W_Q2C;
 			z /= Npairs;
 			c2_pos_case2[i][2][0]->Fill(z.Re(),Npairs);
 			c2_pos_case2[i][2][1]->Fill(z.Im(),Npairs);

 			z = Q2C * TComplex::Conjugate(Q2A);
 			Npairs = W_Q2C * W_Q2A;
 			z /= Npairs;
 			c2_pos_case2[i][3][0]->Fill(z.Re(),Npairs);
 			c2_pos_case2[i][3][1]->Fill(z.Im(),Npairs);


     //case2, negative
 			z = Q2minuseta_neg * TComplex::Conjugate(Q2B);
 			Npairs = W_Q2minuseta_neg * W_Q2B;
 			z /= Npairs;
 			c2_neg_case2[i][0][0]->Fill(z.Re(),Npairs);
 			c2_neg_case2[i][0][1]->Fill(z.Im(),Npairs);

 			z = Q2B * TComplex::Conjugate(Q2A);
 			Npairs = W_Q2B * W_Q2A;
 			z /= Npairs;
 			c2_neg_case2[i][1][0]->Fill(z.Re(),Npairs);
 			c2_neg_case2[i][1][1]->Fill(z.Im(),Npairs);

 			z = Q2B * TComplex::Conjugate(Q2C);
 			Npairs = W_Q2B * W_Q2C;
 			z /= Npairs;
 			c2_neg_case2[i][2][0]->Fill(z.Re(),Npairs);
 			c2_neg_case2[i][2][1]->Fill(z.Im(),Npairs);

 			z = Q2C * TComplex::Conjugate(Q2A);
 			Npairs = W_Q2C * W_Q2A;
 			z /= Npairs;
 			c2_neg_case2[i][3][0]->Fill(z.Re(),Npairs);
 			c2_neg_case2[i][3][1]->Fill(z.Im(),Npairs);

 		}
 	}


 }


// ------------ method called once each job just before starting event loop  ------------
 void V3AnalyzerSP::beginJob()    
 {
 	edm::Service<TFileService> fs;
 	TH1D::SetDefaultSumw2();

 	NAchBins = achBins_.size()-1;


 	asym_Dist = fs->make<TH1D>("ChargeAsym","Distribution of Charge Asymmetry",1000,-0.4,0.4);
 	NTrkHist = fs->make<TH1D>("NTrkHist","NTrack",5000,0,5000);
 	cbinHist = fs->make<TH1D>("cbinHist",";cbin",200,0,200);
 	etaHist = fs->make<TH1D>("etaHist",";etaHist", 1000,-2.4,2.4);




 	edm::FileInPath fip1(efftablePath_.c_str());  
 	TFile f1(fip1.fullPath().c_str(),"READ");
 	effTable = (TH2D*)f1.Get(efftableName_.c_str());

//list of c2 histograms
 	for (Int_t i = 0; i < NAchBins; i++){
 		for(Int_t j = 0 ; j < 4; j++){

 			c2_pos_case1[i][j][0] = fs->make<TH1D>(Form("c2pos_%d_%d_cos_case1",i,j),"c2 Distribution",1000,-1,1);
 			c2_pos_case1[i][j][1] = fs->make<TH1D>(Form("c2pos_%d_%d_sin_case1",i,j),"c2 Distribution",1000,-1,1);
 			c2_neg_case1[i][j][0] = fs->make<TH1D>(Form("c2neg_%d_%d_cos_case1",i,j),"c2 Distribution",1000,-1,1);
 			c2_neg_case1[i][j][1] = fs->make<TH1D>(Form("c2neg_%d_%d_sin_case1",i,j),"c2 Distribution",1000,-1,1);
 			c2_pos_case2[i][j][0] = fs->make<TH1D>(Form("c2pos_%d_%d_cos_case2",i,j),"c2 Distribution",1000,-1,1);
 			c2_pos_case2[i][j][1] = fs->make<TH1D>(Form("c2pos_%d_%d_sin_case2",i,j),"c2 Distribution",1000,-1,1);
 			c2_neg_case2[i][j][0] = fs->make<TH1D>(Form("c2neg_%d_%d_cos_case2",i,j),"c2 Distribution",1000,-1,1);
 			c2_neg_case2[i][j][1] = fs->make<TH1D>(Form("c2neg_%d_%d_sin_case2",i,j),"c2 Distribution",1000,-1,1);

 		}
 		ach_hist[i] = fs->make<TH1D>(Form("ach_%d",i+1),Form("ach_%d",i+1),1000,-0.4,0.4);
 		pt_pos[i] = fs->make<TH1D>(Form("pt_pos_%d",i+1),Form("pt_pos_%d",i+1),1000,0.0,4.0);
 		pt_neg[i] = fs->make<TH1D>(Form("pt_neg_%d",i+1),Form("pt_neg_%d",i+1),1000,0.0,4.0);



 	}
 }

// ------------ method called once each job just after ending the event loop  ------------
 void
 V3AnalyzerSP::endJob() 
 {    
 }

// ------------ method called when starting to processes a run  ------------
 void 
 V3AnalyzerSP::beginRun(edm::Run const&, edm::EventSetup const&)
 {
 }

// ------------ method called when ending the processing of a run  ------------
 void 
 V3AnalyzerSP::endRun(edm::Run const&, edm::EventSetup const&)
 {
 }

// ------------ method called when starting to processes a luminosity block  ------------
 void 
 V3AnalyzerSP::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
 {
 }

// ------------ method called when ending the processing of a luminosity block  ------------
 void 
 V3AnalyzerSP::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
 {
 }

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
 void
 V3AnalyzerSP::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
//The following says we do not know what parameters are allowed so do no validation
// Please change this to state exactly what you do use, even if it is no parameters
 	edm::ParameterSetDescription desc;
 	desc.setUnknown();
 	descriptions.addDefault(desc);
 }

//define this as a plug-in
 DEFINE_FWK_MODULE(V3AnalyzerSP);
