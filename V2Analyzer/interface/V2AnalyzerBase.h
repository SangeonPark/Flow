#ifndef V2AnalyzerBase_H
#define V2AnalyzerBase_H

// system include files
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <map>
#include <sstream>
#include <cstdlib>


#include <TMath.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <TCanvas.h>
#include <TVector3.h>
#include <TRandom.h>
#include <TNtuple.h>
#include <TGraph.h>
#include <TComplex.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"

#include "DataFormats/Candidate/interface/Candidate.h"

#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidateFwd.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/TrackReco/interface/DeDxData.h"

#include <Math/Functions.h>
#include <Math/SVector.h>
#include <Math/SMatrix.h>

//////////////////////////////////////////////
// CMSSW user include files
#include "DataFormats/Common/interface/DetSetAlgorithm.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXFDetId.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHitCollection.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertex.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertexContainer.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h"

#include "DataFormats/SiPixelDetId/interface/PixelEndcapName.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"

#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "DataFormats/RecoCandidate/interface/TrackAssociation.h"
#include "DataFormats/TrackReco/interface/DeDxData.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

// Heavyion
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"

// Particle Flow
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlock.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/ParticleFlowReco/interface/PFClusterFwd.h"

// Vertex significance
#include "RecoBTag/SecondaryVertex/interface/SecondaryVertex.h"

// Root include files
#include "TTree.h"
//
// Track Matching and fake rate calculations     
//#include "RiceHIG/V0Analysis/interface/V0Validator.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"



//
// class declaration
//

class V2Analyzer : public edm::EDAnalyzer {
public:
      explicit V2Analyzer(const edm::ParameterSet&);
      ~V2Analyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

      TNtuple* track_Data;
      TH1D* asym_Dist;
      TH1D* NTrkHist;
      TH2D* effTable;
      
      double offlineDCA_;
      double etaCutMin_;
      double etaCutMax_;
      double etaHFLow_;
      double etaHFUpp_;
      int order_;
      int NTrkMin_;
      int NTrkMax_;
      bool doEffCorrection_;
      bool doAchEffCorrection_;
      bool reverseBeam_;      
      double Bins[6] = {-999,-0.04,-0.01,0.02,0.045,999 };

      TH1D* c2_pos_case1[5][5][2];
      TH1D* c2_neg_case1[5][5][2];
      TH1D* c2_tot_case1[5][5][2];
      TH1D* c2_pos_case2[5][5][2];
      TH1D* c2_neg_case2[5][5][2];
      TH1D* c2_tot_case2[5][5][2];
      TH1D* ach_hist[5];
      
      edm::InputTag trackSrc_;
      std::string vertexSrc_;
      edm::InputTag towerSrc_;

};

class V2AnalyzerSP : public edm::EDAnalyzer {
public:
      explicit V2AnalyzerSP(const edm::ParameterSet&);
      ~V2AnalyzerSP();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

      TNtuple* track_Data;
      TH1D* asym_Dist;
      TH1D* NTrkHist;
      TH1D* etaHist;
      TH2D* effTable;
      TH1D* cbinHist;

      
      double offlineDCA_;
      double offlineptErr_;
      double etaCutMin_;
      double etaCutMax_;
      double ptCutMin_;
      double ptCutMax_;
      double etaHFLow_;
      double etaHFUpp_;
      double etaGap_;
      double vzLow_;
      double vzHigh_;
      int Nmin_;
      int Nmax_;
      int order_;

      std::vector<double> centBins_;
      std::vector<double> achBins_;
      std::string efftablePath_;
      std::string efftableName_;
      int NAchBins;

      bool doEffCorrection_;
      bool useCentrality_;
      bool reverseBeam_;      

 //     double Bins[6] = {-999,-0.04,-0.015,0.015,0.04,999 };

      TH1D* c2_pos_case1[100][4][2];
      TH1D* c2_neg_case1[100][4][2];
      TH1D* c2_tot_case1[100][4][2];
      TH1D* c2_pos_case2[100][4][2];
      TH1D* c2_neg_case2[100][4][2];
      TH1D* c2_tot_case2[100][4][2];

      TH1D* ach_hist[100];
      TH1D* pt_pos[100];
      TH1D* pt_neg[100];

      
      edm::InputTag trackSrc_;
      std::string vertexSrc_;
      edm::InputTag towerSrc_;

};

class SelfCorrTestSP : public edm::EDAnalyzer {
public:
      explicit SelfCorrTestSP(const edm::ParameterSet&);
      ~SelfCorrTestSP();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

      TNtuple* track_Data;
      TH1D* asym_Dist;
      TH1D* NTrkHist;
      TH2D* effTable;
      TH1D* cbinHist;

      
      double offlineDCA_;
      double offlineptErr_;
      double etaCutMin_;
      double etaCutMax_;
      double ptCutMin_;
      double ptCutMax_;
      double etaHFLow_;
      double etaHFUpp_;
      double etaGap_;
      double vzLow_;
      double vzHigh_;
      int Nmin_;
      int Nmax_;


      std::vector<double> centBins_;
      std::vector<double> achBins_;
      std::string efftablePath_;
      std::string efftableName_;
      int NAchBins;

      bool doEffCorrection_;
      bool useCentrality_;
      bool reverseBeam_;  
      bool isAchinMinusEta_;    

 //     double Bins[6] = {-999,-0.04,-0.015,0.015,0.04,999 };

      TH1D* c2_pos_case1[100][4][2];
      TH1D* c2_neg_case1[100][4][2];
      TH1D* c2_tot_case1[100][4][2];
      TH1D* c2_pos_case2[100][4][2];
      TH1D* c2_neg_case2[100][4][2];
      TH1D* c2_tot_case2[100][4][2];

      TH1D* ach_hist[100];
      TH1D* ach_hist_otherside[100];
      TH1D* pt_pos_negeta[100];
      TH1D* pt_pos_poseta[100];
      TH1D* pt_neg_negeta[100];
      TH1D* pt_neg_poseta[100];

      
      edm::InputTag trackSrc_;
      std::string vertexSrc_;
      edm::InputTag towerSrc_;

};


class AutoCorrelation : public edm::EDAnalyzer {
public:
      explicit AutoCorrelation(const edm::ParameterSet&);
      ~AutoCorrelation();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

      TNtuple* track_Data;
      TH1D* asym_Dist;
      TH1D* NTrkHist;
      TH2D* effTable;
      TH1D* cbinHist;

      
      double offlineDCA_;
      double offlineptErr_;
      double etaCutMin_;
      double etaCutMax_;
      double ptCutMin_;
      double ptCutMax_;
      double etaHFLow_;
      double etaHFUpp_;
      double etaGap_;
      double vzLow_;
      double vzHigh_;
      int Nmin_;
      int Nmax_;


      std::vector<double> centBins_;
      std::vector<double> achBins_;
      std::string efftablePath_;
      std::string efftableName_;
      int NAchBins;

      bool doEffCorrection_;
      bool useCentrality_;
      bool reverseBeam_;  

 //     double Bins[6] = {-999,-0.04,-0.015,0.015,0.04,999 };

      TH1D* c2_pos_case1[100][4][2];
      TH1D* c2_neg_case1[100][4][2];
      TH1D* c2_tot_case1[100][4][2];
      TH1D* c2_pos_case2[100][4][2];
      TH1D* c2_neg_case2[100][4][2];
      TH1D* c2_tot_case2[100][4][2];

      TH1D* ach_hist[100];
      TH1D* ach_hist_otherside[100];

      TH1D* pt_pos[100];
      TH1D* pt_neg[100];

      
      edm::InputTag trackSrc_;
      std::string vertexSrc_;
      edm::InputTag towerSrc_;

};

class V2AnalyzerCumulant : public edm::EDAnalyzer {
public:
      explicit V2AnalyzerCumulant(const edm::ParameterSet&);
      ~V2AnalyzerCumulant();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

      TNtuple* track_Data;
      TH1D* asym_Dist;
      TH1D* vtxZ;
      TH1D* NTrkHist;
      TH1D* etaHist;

      TH2D* effTable;
      TH2D* AcheffTable;
      TH1D* cbinHist;
      TH2D* scatterHist_twoetarange;
      
      double offlineDCA_;
      double offlineptErr_;
      double etaCutMin_;
      double etaCutMax_;
      double ptCutMin_;
      double ptCutMax_;
      double etaHFLow_;
      double etaHFUpp_;
      double etaGap_;
      double vzLow_;
      double vzHigh_;
      int Nmin_;
      int Nmax_;
      int NEtaBins_;
      int order_;

      bool doEffCorrection_;
      bool doAchEffCorrection_;
      bool reverseBeam_;
      bool useCentrality_;

      std::vector<double> centBins_;
      std::vector<double> achBins_;
      std::string efftablePath_;
      std::string efftableName_;
      int NAchBins;

//      double Bins[6] = {-999,-0.04,-0.015,0.015,0.04,999 };

      TH1D* c2_pos[100][2];
      TH1D* c2_neg[100][2];
      TH1D* ach_hist[100];
      TH1D* pt_pos[100];
      TH1D* pt_neg[100];


      edm::InputTag trackSrc_;
      std::string vertexSrc_;
      edm::InputTag towerSrc_;

};

class Closure : public edm::EDAnalyzer {
public:
      explicit Closure(const edm::ParameterSet&);
      ~Closure();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

      TNtuple* track_Data;
      TH1D* gen_asym_Dist;
      TH1D* reco_asym_Dist;

      TH1D* NTrkHist;
      TH2D* effTable;
      TH1D* cbinHist;
      TH2D* scatterHist_genreco;
      
      double offlineDCA_;
      double offlineptErr_;
      double etaCutMin_;
      double etaCutMax_;
      double ptCutMin_;
      double ptCutMax_;
      double etaHFLow_;
      double etaHFUpp_;
      double etaGap_;
      double vzLow_;
      double vzHigh_;
      int Nmin_;
      int Nmax_;
      int NEtaBins_;
      bool doEffCorrection_;
      bool reverseBeam_;
      bool useCentrality_;

      std::vector<double> centBins_;
      std::vector<double> achBins_;
      std::string efftablePath_;
      std::string efftableName_;
      int NAchBins;

//      double Bins[6] = {-999,-0.04,-0.015,0.015,0.04,999 };

      TH1D* gen_c2_pos[100][2];
      TH1D* gen_c2_neg[100][2];
      TH1D* gen_ach_hist[100];

      TH1D* reco_c2_pos[100][2];
      TH1D* reco_c2_neg[100][2];
      TH1D* reco_ach_hist[100];
      
      edm::InputTag trackSrc_;
      std::string vertexSrc_;
      edm::InputTag towerSrc_;

};

class V3AnalyzerSP : public edm::EDAnalyzer {
public:
      explicit V3AnalyzerSP(const edm::ParameterSet&);
      ~V3AnalyzerSP();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

      TNtuple* track_Data;
      TH1D* asym_Dist;
      TH1D* NTrkHist;
      TH1D* etaHist;
      TH2D* effTable;
      TH1D* cbinHist;

      
      double offlineDCA_;
      double offlineptErr_;
      double etaCutMin_;
      double etaCutMax_;
      double ptCutMin_;
      double ptCutMax_;
      double etaHFLow_;
      double etaHFUpp_;
      double etaGap_;
      double vzLow_;
      double vzHigh_;
      int Nmin_;
      int Nmax_;

      std::vector<double> centBins_;
      std::vector<double> achBins_;
      std::string efftablePath_;
      std::string efftableName_;
      int NAchBins;

      bool doEffCorrection_;
      bool useCentrality_;
      bool reverseBeam_;      

 //     double Bins[6] = {-999,-0.04,-0.015,0.015,0.04,999 };

      TH1D* c2_pos_case1[100][4][2];
      TH1D* c2_neg_case1[100][4][2];
      TH1D* c2_tot_case1[100][4][2];
      TH1D* c2_pos_case2[100][4][2];
      TH1D* c2_neg_case2[100][4][2];
      TH1D* c2_tot_case2[100][4][2];

      TH1D* ach_hist[100];
      TH1D* pt_pos[100];
      TH1D* pt_neg[100];

      
      edm::InputTag trackSrc_;
      std::string vertexSrc_;
      edm::InputTag towerSrc_;

};

class V3AnalyzerCumulant : public edm::EDAnalyzer {
public:
      explicit V3AnalyzerCumulant(const edm::ParameterSet&);
      ~V3AnalyzerCumulant();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

      TNtuple* track_Data;
      TH1D* asym_Dist;
      TH1D* NTrkHist;
      TH2D* effTable;
      TH1D* cbinHist;
      TH2D* scatterHist_twoetarange;
      
      double offlineDCA_;
      double offlineptErr_;
      double etaCutMin_;
      double etaCutMax_;
      double ptCutMin_;
      double ptCutMax_;
      double etaHFLow_;
      double etaHFUpp_;
      double etaGap_;
      double vzLow_;
      double vzHigh_;
      int NEtaBins_;
      int Nmin_;
      int Nmax_;
      int NAchBins;

      bool doEffCorrection_;
      bool reverseBeam_;      
      bool useCentrality_;
      bool doAchEffCorrection_;


      std::vector<double> centBins_;      
      std::vector<double> achBins_;
      //double Bins[6] = {-999,-0.04,-0.015,0.015,0.04,999 };
      std::string efftablePath_;
      std::string efftableName_;
      
      TH1D* c2_pos[100][2];
      TH1D* c2_neg[100][2];
      TH1D* ach_hist[100];
      
      edm::InputTag trackSrc_;
      std::string vertexSrc_;
      edm::InputTag towerSrc_;

};

class AsymmetryScatterPlot : public edm::EDAnalyzer {
public:
      explicit AsymmetryScatterPlot(const edm::ParameterSet&);
      ~AsymmetryScatterPlot();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

      TH1D* asym_Dist;
      TH1D* vtzHist;
      TH1D* NTrkHist;
      TH2D* effTable;
      TH2D* reweightTable;

      TH1D* cbinHist;
      TH1D* GenNTrkHist;
      TH2D* scatterHist_effcorr;
      TH2D* scatterHist_noeffcorr;
      TH2D* Npos_scatterHist_effcorr;
      TH2D* Npos_scatterHist_noeffcorr;
      TH2D* Nneg_scatterHist_effcorr;
      TH2D* Nneg_scatterHist_noeffcorr;
      TH2D* ptEtaScatterHist; 
      TH2D* genptEtaScatterHist;

      double offlineDCA_;
      double offlineptErr_;
      double etaCutMin_;
      double etaCutMax_;
      double ptCutMin_;
      double ptCutMax_;
      double etaHFLow_;
      double etaHFUpp_;
      double etaGap_;
      int NEtaBins_;
      int Nmin_;
      int Nmax_;
      int NAchBins;

      bool doEffCorrection_;
      bool reverseBeam_;      
      bool useCentrality_;
      bool doAchEffCorrection_;
      bool doReweightPtEta_;
      bool doReweightNtrk_;

      std::vector<double> centBins_;
      std::vector<double> achBins_;
      

      //double Bins[6] = {-999,-0.04,-0.015,0.015,0.04,999 };
      std::string efftablePath_;
      std::string efftableName_;
      std::string reweighttablePath_;
      std::string reweighttableName_;

      TH1D *c2_pos[100][2];
      TH1D *c2_neg[100][2];
      TH1D *gen_c2_neg[100][2];
      TH1D *gen_c2_pos[100][2];

      TH1D *ach_hist[100];
      TH1D *gen_ach_hist[100];
      
      edm::InputTag trackSrc_;
      std::string vertexSrc_;
      edm::InputTag towerSrc_;
      edm::InputTag genParticleSrc_;

};

#endif
