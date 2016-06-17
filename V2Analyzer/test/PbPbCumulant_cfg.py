import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'root://cms-xrd-global.cern.ch//store/user/davidlw/HIMinBiasUPC/PR2011_MBPPRereco_TRKANASKIM_v6/ccf03100d177f42de0f9cdc7627799d3/pPb_HM_1000_1_lq0.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/HIMinBiasUPC/PR2011_MBPPRereco_TRKANASKIM_v6/ccf03100d177f42de0f9cdc7627799d3/pPb_HM_1001_1_Jfy.root',
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/HIMinBiasUPC/PR2011_MBPPRereco_TRKANASKIM_v6/ccf03100d177f42de0f9cdc7627799d3/pPb_HM_1002_1_nsm.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/HIMinBiasUPC/PR2011_MBPPRereco_TRKANASKIM_v6/ccf03100d177f42de0f9cdc7627799d3/pPb_HM_1003_1_DON.root',
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/HIMinBiasUPC/PR2011_MBPPRereco_TRKANASKIM_v6/ccf03100d177f42de0f9cdc7627799d3/pPb_HM_1004_1_jR1.root',
        #'root://xrootd-cms.infn.it//store/user/davidlw/HIMinBiasUPC/PR2011_MBPPRereco_TRKANASKIM_v6/ccf03100d177f42de0f9cdc7627799d3/pPb_HM_1005_1_CRF.root',
        #'root://xrootd-cms.infn.it//store/user/davidlw/HIMinBiasUPC/PR2011_MBPPRereco_TRKANASKIM_v6/ccf03100d177f42de0f9cdc7627799d3/pPb_HM_1006_1_I87.root',
        #'root://xrootd-cms.infn.it//store/user/davidlw/HIMinBiasUPC/PR2011_MBPPRereco_TRKANASKIM_v6/ccf03100d177f42de0f9cdc7627799d3/pPb_HM_1007_1_PuH.root',
        #'root://xrootd-cms.infn.it//store/user/davidlw/HIMinBiasUPC/PR2011_MBPPRereco_TRKANASKIM_v6/ccf03100d177f42de0f9cdc7627799d3/pPb_HM_1008_1_S9u.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/HIMinBiasUPC/PR2011_MBPPRereco_TRKANASKIM_v6/ccf03100d177f42de0f9cdc7627799d3/pPb_HM_1009_1_mgy.root'
        
        #'file:myfile.root'
	#'root://xrootd-cms.infn.it//store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHM_Gplus_Rereco_ReTracking_v18/28b2b9cce04ec3f20baeb96fbd2295a8/pPb_HM_1001_1_Ab9.root',
	#'root://xrootd-cms.infn.it//store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHM_Gplus_Rereco_ReTracking_v18/28b2b9cce04ec3f20baeb96fbd2295a8/pPb_HM_1002_1_mXl.root'




    )
)

#loads analyzer
process.load("Flow.V2Analyzer.v3analyzerCumulant_cfi")
process.TFileService = cms.Service("TFileService",fileName = cms.string("v3_Cumulant_185_260_PbPb.root"))


process.p = cms.Path(process.demo)
