import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",ignoreTotal = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.options   = cms.untracked.PSet( wantSummary =
cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load("Configuration.StandardSequences.Digi_cff")
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("SimGeneral.MixingModule.mixNoPU_cfi")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.GlobalTag.globaltag = '75X_dataRun2_PromptHI_v3'

process.PAprimaryVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2"),
    filter = cms.bool(True),   # otherwise it won't filter the events
)

#Reject beam scraping events standard pp configuration
process.NoScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
'/store/hidata/HIRun2015/HIMinimumBias5/AOD/02May2016-v1/70000/303B46F5-C127-E611-BF7C-90B11C441C8C.root'
)
)

process.load("Flow.V2Analyzer.PbPbCumulant_cfi")

#define the cuts
#process.demo.Nmin = 185
#process.demo.Nmax = 260

#process.demo.eff = 1
#process.demo.useCentrality = False
#process.demo.doEffCorrection = True

process.TFileService = cms.Service("TFileService",fileName = cms.string("PbPb_502TeV_Cumulant_v3_checking.root"))
process.p = cms.Path(  process.hfCoincFilter *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
		               process.demo 
			)