// -*- C++ -*-
//
// Package:    AsymmetryScatterPlot
// Class:      AsymmetryScatterPlot
// 
/**\class AsymmetryScatterPlot AsymmetryScatterPlot.cc Flow/V2Analyzer/src/AsymmetryScatterPlot.cc

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
 AsymmetryScatterPlot::AsymmetryScatterPlot(const edm::ParameterSet& iConfig)
 {

 	dxySigCut_ = iConfig.getParameter<double>("dxySigCut");
 	dzSigCut_ = iConfig.getParameter<double>("dzSigCut");
 	etaCutMin_ = iConfig.getParameter<double>("etaCutMin");
 	etaCutMax_ = iConfig.getParameter<double>("etaCutMax");
 	etaHFLow_ = iConfig.getParameter<double>("etaHFLow");
 	etaHFUpp_ = iConfig.getParameter<double>("etaHFUpp");

 	Nmin_ = iConfig.getParameter<int>("Nmin");
 	Nmax_ = iConfig.getParameter<int>("Nmax");
 	NEtaBins_ = iConfig.getParameter<int>("NEtaBins");
 	

 	trackSrc_ = iConfig.getParameter<edm::InputTag>("trackSrc");
 	vertexSrc_ = iConfig.getParameter<std::string>("vertexSrc");
 	towerSrc_ = iConfig.getParameter<edm::InputTag>("towerSrc");
 	genParticleSrc_ = iConfig.getParameter<edm::InputTag>("genParticleSrc");

 	doEffCorrection_ = iConfig.getParameter<bool>("doEffCorrection");
 	reverseBeam_ = iConfig.getParameter<bool>("reverseBeam");
 	useCentrality_ = iConfig.getParameter<bool>("useCentrality");

 	centBins_ = iConfig.getUntrackedParameter<std::vector<double>>("centBins");

//now do what ever initialization is needed

 }


 AsymmetryScatterPlot::~AsymmetryScatterPlot()
 {

// do anything here that needs to be done at desctruction time
// (e.g. close files, deallocate resources etc.)

 }


//
// member functions
//

// ------------ method called for each event  ------------
 void AsymmetryScatterPlot::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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

cout << "point 1" << endl;

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

//variables for charge asymmetry calculation- without efficiency correction
 	double N_pos_noeffcorr = 0.0;
 	double N_neg_noeffcorr = 0.0;
 	double N_tot_noeffcorr = 0.0;

//NTrackOffline values
 	int nTracks = 0;
 	int nTracks_pos = 0;
 	int nTracks_neg = 0;

//define the flow vectors and weight

// 	const int NBins = NEtaBins_;
 //	double Binsize = 4.8/(double)NBins;

/*
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
*/

 	for( reco::TrackCollection::const_iterator cand = tracks->begin(); cand != tracks->end(); cand++){

 		double eta = cand->eta();
 		double charge = (double)cand->charge();
 		double pt = cand->pt();
// 		double phi = cand->phi();
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

//calculating NtrkOff
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
 		if(pt < 0.3 || pt > 3.0 ) continue;
 		if(eta<-2.4 || 2.4 <= eta) continue;

//reversebeam for merging reverse data
 		if(reverseBeam_) { eta *= -1.0;}

//calculating charge asymmetry
 		N_tot += weight;
 		if( charge > 0){ N_pos+= weight;}
 		if( charge < 0){ N_neg+= weight;}

//calculating non-weighted charge asymmetry
 		N_tot_noeffcorr += 1.0;
 		if( charge > 0 ){ N_pos_noeffcorr += 1.0;}
 		if( charge < 0 ){ N_neg_noeffcorr += 1.0;}

//Filling Q vectors in order to calculate c2
 		/*
 		TComplex e(1,2*phi,1);
 		e *= weight; 
 		for (int i = 0; i < NBins; ++i)
 		{
 			double lb = Binsize*i-2.4;
 			double ub = Binsize*(i+1)-2.4;
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
 		*/
 		
 	}

 	cout << "point2" << endl;

//Cut on NTrackOffline (Should be disabled if useCentrality = True)	
 	if(!useCentrality_){

 		if( nTracks < Nmin_ || nTracks >= Nmax_ ) return;

 	}

//asymmetry calculation
 	double N_diff = N_pos - N_neg;
 	double ach = N_diff/N_tot;

 	double N_diff_noeffcorr = N_pos_noeffcorr - N_neg_noeffcorr;
 	double ach_noeffcorr = N_diff_noeffcorr/N_tot_noeffcorr;

 //	asym_Dist->Fill(ach);
 	NTrkHist->Fill(nTracks);

 	edm::Handle<reco::GenParticleCollection> genParticleCollection;
 	iEvent.getByLabel(genParticleSrc_, genParticleCollection);

 	double N_pos_gen=0.0;
 	double N_neg_gen=0.0;
 	double N_tot_gen=0.0;

 	cout << "point3" << endl;

 	for(unsigned it=0; it<genParticleCollection->size(); ++it) {

 		const reco::GenParticle & genCand = (*genParticleCollection)[it];
 		int status = genCand.status();
 		double genpt = genCand.pt();
 		double geneta = genCand.eta();
 		int gencharge = genCand.charge();

 		if( status != 1  || gencharge == 0 ) continue;
 		if( fabs(geneta) > 2.4 ) continue;
 		if( genpt < 0.3 || genpt > 3.0 ) continue;

 		if( gencharge > 0){ N_pos_gen+=1.0; N_tot_gen+=1.0; }
 		if( gencharge < 0){ N_neg_gen+=1.0; N_tot_gen+=1.0; }

 	}

 	double N_diff_gen = N_pos_gen - N_neg_gen;
 	double ach_gen = N_diff_gen/N_tot_gen;

 	scatterHist_effcorr->Fill(ach,ach_gen);
 	scatterHist_noeffcorr->Fill(ach_noeffcorr,ach_gen);



//calculating c2 values from filled Q vectors
 	/*
 	for(Int_t i=0;i<5;i++){

 		if(Bins[i] < ach && ach <= Bins[i+1]){
 			ach_hist[i]->Fill(ach);

 			TComplex z(0,0);
 			double Npairs=0.0;

 			for (int j = 0; j < NBins; j++)
 			{
 				for(int k = 0; k < NBins; k++){

 					if(abs(j-k) <= (2.0/Binsize)) continue;


 					z = Q2_pos[j] * TComplex::Conjugate(Q2_pos[k]);
 					Npairs = WQ2_pos[j] * WQ2_pos[k];
 					z /= Npairs;



 					c2_pos[i][0] -> Fill(z.Re(), Npairs);
 					c2_pos[i][1] -> Fill(z.Im(), Npairs);

 					z = Q2_neg[j] * TComplex::Conjugate(Q2_neg[k]);
 					Npairs = WQ2_neg[j] * WQ2_neg[k];
 					z /= Npairs;
 					c2_neg[i][0] -> Fill(z.Re(), Npairs);
 					c2_neg[i][1] -> Fill(z.Im(), Npairs);

 				}
 			} 			
 		}
 	}
 	*/
 	

 }



// ------------ method called once each job just before starting event loop  ------------
 void AsymmetryScatterPlot::beginJob()    
 {
 	edm::Service<TFileService> fs;
 	TH1D::SetDefaultSumw2();
 	TH2D::SetDefaultSumw2();

// 	asym_Dist = fs->make<TH1D>("ChargeAsym","Distribution of Charge Asymmetry",51,-1,1);
 	NTrkHist = fs->make<TH1D>("NTrkHist","NTrack",5000,0,5000);
 	cbinHist = fs->make<TH1D>("cbinHist",";cbin",200,0,200);
 	scatterHist_effcorr = fs->make<TH2D>("scatterHist_effcorr","Scatter Plot efficiency corrected;Observed A_{ch};A_{ch}",100,-0.3,0.3,100,-0.3,0.3);
 	scatterHist_noeffcorr = fs->make<TH2D>("scatterHist_noeffcorr","Scatter Plot without eff correction;Observed A_{ch};A_{ch}",100,-0.3,0.3,100,-0.3,0.3);

 	edm::FileInPath fip1("Flow/V2Analyzer/data/TrackCorrections_HIJING_538_OFFICIAL_Mar24.root");  
 	TFile f1(fip1.fullPath().c_str(),"READ");
 	effTable = (TH2D*)f1.Get("rTotalEff3D");




//list of c2 histograms
 	/*
 	for (Int_t i = 0; i < 5; i++){

 		c2_pos[i][0] = fs->make<TH1D>(Form("c2pos_%d_cos",i),"c2 Distribution",1000,-1,1);
 		c2_pos[i][1] = fs->make<TH1D>(Form("c2pos_%d_sin",i),"c2 Distribution",1000,-1,1);
 		c2_neg[i][0] = fs->make<TH1D>(Form("c2neg_%d_cos",i),"c2 Distribution",1000,-1,1);
 		c2_neg[i][1] = fs->make<TH1D>(Form("c2neg_%d_sin",i),"c2 Distribution",1000,-1,1);

 	}

 	ach_hist[0] = fs->make<TH1D>("ach_1","ach_1",1000,-0.4,0.4);
 	ach_hist[1] = fs->make<TH1D>("ach_2","ach_2",1000,-0.4,0.4);
 	ach_hist[2] = fs->make<TH1D>("ach_3","ach_3",1000,-0.4,0.4);
 	ach_hist[3] = fs->make<TH1D>("ach_4","ach_4",1000,-0.4,0.4);
 	ach_hist[4] = fs->make<TH1D>("ach_5","ach_5",1000,-0.4,0.4);
 	*/

 }

// ------------ method called once each job just after ending the event loop  ------------
 void
 AsymmetryScatterPlot::endJob() 
 {    
 }

// ------------ method called when starting to processes a run  ------------
 void 
 AsymmetryScatterPlot::beginRun(edm::Run const&, edm::EventSetup const&)
 {
 }

// ------------ method called when ending the processing of a run  ------------
 void 
 AsymmetryScatterPlot::endRun(edm::Run const&, edm::EventSetup const&)
 {
 }

// ------------ method called when starting to processes a luminosity block  ------------
 void 
 AsymmetryScatterPlot::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
 {
 }

// ------------ method called when ending the processing of a luminosity block  ------------
 void 
 AsymmetryScatterPlot::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
 {
 }

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
 void
 AsymmetryScatterPlot::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
//The following says we do not know what parameters are allowed so do no validation
// Please change this to state exactly what you do use, even if it is no parameters
 	edm::ParameterSetDescription desc;
 	desc.setUnknown();
 	descriptions.addDefault(desc);
 }

//define this as a plug-in
 DEFINE_FWK_MODULE(AsymmetryScatterPlot);
