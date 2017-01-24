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
'/store/hidata/HIRun2015/HIMinimumBias7/AOD/02May2016-v1/00000/089673D3-6199-E611-B9E9-1418774A30CD.root'
)
)

process.load("Flow.V2Analyzer.v2analyzerCumulant_cfi")


process.TFileService = cms.Service("TFileService",fileName = cms.string("vn_mainresult_cumulant_ver2.root"))

process.demo_n1 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftableName = cms.string('eff_2'),
                      achBins = cms.untracked.vdouble(-1,-0.085,-0.05,-0.025,0.025,0.05,0.085,1),
                      Nmin = cms.int32(185),
                      Nmax = cms.int32(220),
                      order = cms.int32(2),    
)


process.demo_n2 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftableName = cms.string('eff_2'),
                      achBins = cms.untracked.vdouble(-1,-0.09,-0.05,-0.02,0.02,0.05,0.09,1),
                      Nmin = cms.int32(185),
                      Nmax = cms.int32(220),
                      order = cms.int32(2),   
)

process.demo_n3= process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftableName = cms.string('eff_2'),
                      achBins = cms.untracked.vdouble(-1,-0.09,-0.055,-0.02,0.02,0.055,0.09,1),
                      Nmin = cms.int32(185),
                      Nmax = cms.int32(220),
                      order = cms.int32(2),  
)

process.demo_n4 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftableName = cms.string('eff_2'),
                      achBins = cms.untracked.vdouble(-1,-0.09,-0.06,-0.02,0.02,0.06,0.09,1),
                      Nmin = cms.int32(185),
                      Nmax = cms.int32(220),
                      order = cms.int32(2),  
)



process.p_n1 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n1
            )

process.p_n2 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n2
            )

process.p_n3 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n3
            )


process.p_n4 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n4
            )

