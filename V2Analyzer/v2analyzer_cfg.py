import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")
import HLTrigger.HLTfilters.hltHighLevel_cfi

process.hltHM = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()

process.hltHM.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*',

                          'HLT_PAPixelTracks_Multiplicity130_v*',

                          'HLT_PAPixelTracks_Multiplicity160_v*'

                          #'HLT_PAPixelTracks_Multiplicity190_v*'

                          #'HLT_PAPixelTracks_Multiplicity220_v*'

]



process.hltHM.andOr = cms.bool(True)
process.hltHM.throw = cms.bool(False)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
	 'root://xrootd-cms.infn.it//store/user/davidlw/PAMinBiasUPC/		PA2013_FlowCorr_PromptReco_MB_Gplus_Rereco_ReTracking_v18/25c9a89be536a41c8ccb3c75e9fd9358/	pPb_HM_1000_1_Bgt.root'
        #'file:myfile.root'
    )
)

#loads analyzer
process.load("Flow.V2Analyzer.v2analyzer_cfi")
process.TFileService = cms.Service("TFileService",fileName = cms.string("v2Data.root"))


process.p = cms.Path(process.hltHM*process.demo)
