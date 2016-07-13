import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")


process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",ignoreTotal = cms.untracked.int32(1) )


process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(

        'root://cms-xrd-global.cern.ch//store/user/davidlw/ReggeGribovPartonMCfix_EposLHC_5TeV_pPb/RecoSkim_ReTracking_v4_5M/5cde49c8740ff28f897f533d05a99dbc/pPb_MB_100_2_s6H.root'

    )
)

#loads analyzer
process.load("Flow.V2Analyzer.asymmetryscatterplot_cfi")
process.TFileService = cms.Service("TFileService",fileName = cms.string("scatterplotandclosure.root"))


process.p = cms.Path(process.demo)
