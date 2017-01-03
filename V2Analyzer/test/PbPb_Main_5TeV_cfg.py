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
                      efftableName = cms.string('eff_1'),
                      Nmin = cms.int32(90),
                      Nmax = cms.int32(120),
                      order = cms.int32(2),  
)


process.demo_n2 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftableName = cms.string('eff_2'),
                      Nmin = cms.int32(120),
                      Nmax = cms.int32(150),
                      order = cms.int32(2),  
)

process.demo_n3 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftableName = cms.string('eff_2'),
                      Nmin = cms.int32(150),
                      Nmax = cms.int32(185),
                      order = cms.int32(2),  
)
process.demo_n4 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftableName = cms.string('eff_2'),
                      Nmin = cms.int32(185),
                      Nmax = cms.int32(220),
                      order = cms.int32(2),  
)
process.demo_n5 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftableName = cms.string('eff_3'),
                      Nmin = cms.int32(220),
                      Nmax = cms.int32(260),
                      order = cms.int32(2),  
)
process.demo_n6 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftableName = cms.string('eff_3'),
                      Nmin = cms.int32(260),
                      Nmax = cms.int32(300),
                      order = cms.int32(2),  
)
process.demo_n7 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftableName = cms.string('eff_3'),
                      Nmin = cms.int32(300),
                      Nmax = cms.int32(400),
                      order = cms.int32(2),  
)

process.demo_n8 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftableName = cms.string('eff_4'),
                      Nmin = cms.int32(400),
                      Nmax = cms.int32(500),
                      order = cms.int32(2),  
)

process.demo_n9 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftableName = cms.string('eff_5'),
                      Nmin = cms.int32(60),
                      Nmax = cms.int32(80),
                      order = cms.int32(2),  
)


process.demo_n10 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftableName = cms.string('eff_4'),
                      Nmin = cms.int32(80),
                      Nmax = cms.int32(100),
                      order = cms.int32(2),  
)

process.demo_n11 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftableName = cms.string('eff_3'),
                      Nmin = cms.int32(100),
                      Nmax = cms.int32(120),
                      order = cms.int32(2),  
)

process.demo_n12 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftableName = cms.string('eff_2'),
                      Nmin = cms.int32(120),
                      Nmax = cms.int32(140),
                      order = cms.int32(2),  
)

process.demo_n13 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftableName = cms.string('eff_1'),
                      Nmin = cms.int32(140),
                      Nmax = cms.int32(160),
                      order = cms.int32(2),  
)

process.demo_n14 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftableName = cms.string('eff_1'),
                      Nmin = cms.int32(160),
                      Nmax = cms.int32(180),
                      order = cms.int32(2),  
)

process.demo_n15 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftableName = cms.string('eff_5'),
                      Nmin = cms.int32(60),
                      Nmax = cms.int32(80),
                      order = cms.int32(3),  
)


process.demo_n16 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftableName = cms.string('eff_4'),
                      Nmin = cms.int32(80),
                      Nmax = cms.int32(100),
                      order = cms.int32(3),  
)

process.demo_n17 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftableName = cms.string('eff_3'),
                      Nmin = cms.int32(100),
                      Nmax = cms.int32(120),
                      order = cms.int32(3),  
)

process.demo_n18 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftableName = cms.string('eff_2'),
                      Nmin = cms.int32(120),
                      Nmax = cms.int32(140),
                      order = cms.int32(3),  
)

process.demo_n19 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftableName = cms.string('eff_1'),
                      Nmin = cms.int32(140),
                      Nmax = cms.int32(160),
                      order = cms.int32(3),  
)

process.demo_n20 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftableName = cms.string('eff_1'),
                      Nmin = cms.int32(160),
                      Nmax = cms.int32(180),
                      order = cms.int32(3),  
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

process.p_n5 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n5
            )

process.p_n6 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n6
            )

process.p_n7 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n7
            )

process.p_n8 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n8
            )

process.p_n9 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n9
            )

process.p_n10 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n10
            )

process.p_n11 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n11
            )

process.p_n12 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n12
            )

process.p_n13 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n13
            )

process.p_n14 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n14
            )

process.p_n15 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n15
            )

process.p_n16 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n16
            )

process.p_n17 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n17
            )

process.p_n18 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n18
            )

process.p_n19 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n19
            )

process.p_n20 = cms.Path(  process.hfCoincFilter3 *
                       process.PAprimaryVertexFilter *
                       process.NoScraping *
                       process.demo_n20
            )