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

 	dxySigCut_ = iConfig.getParameter<double>("dxySigCut");
 	dzSigCut_ = iConfig.getParameter<double>("dzSigCut");
 	etaCutMin_ = iConfig.getParameter<double>("etaCutMin");
 	etaCutMax_ = iConfig.getParameter<double>("etaCutMax");
 	etaHFLow_ = iConfig.getParameter<double>("etaHFLow");
 	etaHFUpp_ = iConfig.getParameter<double>("etaHFUpp");

 	NTrkMin_ = iConfig.getParameter<int>("NTrkMin");
 	NTrkMax_ = iConfig.getParameter<int>("NTrkMax");

 	trackSrc_ = iConfig.getParameter<edm::InputTag>("trackSrc");
 	vertexSrc_ = iConfig.getParameter<std::string>("vertexSrc");
 	towerSrc_ = iConfig.getParameter<edm::InputTag>("towerSrc");

 	doEffCorrection_ = iConfig.getParameter<bool>("doEffCorrection");
 	reverseBeam_ = iConfig.getParameter<bool>("reverseBeam");

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
 	if(bestvz < -15.0 || bestvz>15.0) return;

 	edm::Handle<reco::TrackCollection> tracks;
 	iEvent.getByLabel(trackSrc_, tracks);

 	double N_pos = 0.0;
 	double N_neg = 0.0;
 	double N_tot = 0.0;


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

 		if(pt < 0.3 || pt > 3.0 ) continue;
 		if(2.4 < fabs(eta)) continue;
 		if(reverseBeam_) { eta *= -1.0;}


 		TComplex e(1,3*phi,1);

 		e *= weight; 


 		if(-1.0 <= eta && eta < 1.0){
 			Q2C += e;
 			N_tot+=weight;
 			W_Q2C += weight;
 			if(charge > 0.0){
 				N_pos+=weight;
 			}
 			if(charge < 0.0){
 				N_neg+=weight;
 			}

 		}
 		if(1.0 <= eta && eta < 2.4){
 			N_tot += weight;
 			if(charge > 0.0){
 				N_pos+=weight;
 				Q2pluseta_pos += e;
 				W_Q2pluseta_pos += weight;

 			}
 			if(charge < 0.0){
 				N_neg+=weight;
 				Q2pluseta_neg += e;
 				W_Q2pluseta_neg += weight;

 			}
 		}
 		if(-2.4 <= eta && eta < -1.0){
 			N_tot += weight;
 			if(charge > 0.0){
 				N_pos+=weight;
 				Q2minuseta_pos += e;
 				W_Q2minuseta_pos += weight;

 			}
 			if(charge < 0.0){
 				N_neg+=weight;
 				Q2minuseta_neg += e;
 				W_Q2minuseta_neg += weight;

 			}
 		}

 	}

 	Handle<CaloTowerCollection> towers;
 	iEvent.getByLabel(towerSrc_, towers);

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


 	if( nTracks < NTrkMin_ || nTracks >= NTrkMax_ ) return;


 	double N_diff = N_pos - N_neg;
 	double ach = N_diff/N_tot;
 	asym_Dist->Fill(ach);
 	NTrkHist->Fill(nTracks);

 	for(Int_t i=0;i<5;i++){

 		if(Bins[i] < ach && ach <= Bins[i+1]){
 			ach_hist[i]->Fill(ach);

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

 	asym_Dist = fs->make<TH1D>("ChargeAsym","Distribution of Charge Asymmetry",21,-0.4,0.4);
 	NTrkHist = fs->make<TH1D>("NTrkHist","NTrack",1000,0,500);

 	edm::FileInPath fip1("Flow/V2Analyzer/data/TrackCorrections_HIJING_538_OFFICIAL_Mar24.root");  
 	TFile f1(fip1.fullPath().c_str(),"READ");
 	effTable = (TH2D*)f1.Get("rTotalEff3D");

//list of c2 histograms
 	for (Int_t i = 0; i < 5; i++){
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
 	}

 	ach_hist[0] = fs->make<TH1D>("ach_1","ach_1",1000,-0.4,0.4);
 	ach_hist[1] = fs->make<TH1D>("ach_2","ach_2",1000,-0.4,0.4);
 	ach_hist[2] = fs->make<TH1D>("ach_3","ach_3",1000,-0.4,0.4);
 	ach_hist[3] = fs->make<TH1D>("ach_4","ach_4",1000,-0.4,0.4);
 	ach_hist[4] = fs->make<TH1D>("ach_5","ach_5",1000,-0.4,0.4);
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
