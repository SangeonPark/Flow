import FWCore.ParameterSet.Config as cms

import HLTrigger.HLTfilters.hltHighLevel_cfi

process = cms.Process("Demo")

process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",ignoreTotal = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.options   = cms.untracked.PSet( wantSummary =
cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
'root://cms-xrd-global.cern.ch//store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHM_Gplus_ReTracking_v18/28b2b9cce04ec3f20baeb96fbd2295a8/pPb_HM_1001_1_54X.root'
)
)

process.load("Flow.V2Analyzer.v2analyzerSP_cfi")


process.TFileService = cms.Service("TFileService",fileName = cms.string("vn_mainresult_ver3.root"))

hltHM_n1 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHM_n1.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*']

hltHM_n1.andOr = cms.bool(True)
hltHM_n1.throw = cms.bool(False)

hltHM_n2 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHM_n2.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*',
                  'HLT_PAPixelTracks_Multiplicity130_v*'
]

hltHM_n2.andOr = cms.bool(True)
hltHM_n2.throw = cms.bool(False)

hltHM_n3 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHM_n3.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*',
                  'HLT_PAPixelTracks_Multiplicity130_v*',
                  'HLT_PAPixelTracks_Multiplicity160_v*'

]

hltHM_n3.andOr = cms.bool(True)
hltHM_n3.throw = cms.bool(False)

hltHM_n4 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHM_n4.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*',
                  'HLT_PAPixelTracks_Multiplicity130_v*',
                  'HLT_PAPixelTracks_Multiplicity160_v*',
                  'HLT_PAPixelTracks_Multiplicity190_v*'
]

hltHM_n4.andOr = cms.bool(True)
hltHM_n4.throw = cms.bool(False)

hltHM_n5 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHM_n5.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*',
                  'HLT_PAPixelTracks_Multiplicity130_v*',
                  'HLT_PAPixelTracks_Multiplicity160_v*',
                  'HLT_PAPixelTracks_Multiplicity190_v*',
                  'HLT_PAPixelTracks_Multiplicity220_v*'
]

hltHM_n5.andOr = cms.bool(True)
hltHM_n5.throw = cms.bool(False)

process.demo_n1 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftablePath = cms.string('Flow/V2Analyzer/data/TrackCorrections_HIJING_538_OFFICIAL_Mar24.root'),
                      efftableName = cms.string('rTotalEff3D'),
                      Nmin = cms.int32(120),
                      Nmax = cms.int32(150),
                      order = cms.int32(2),  
)

process.demo_n2 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftablePath = cms.string('Flow/V2Analyzer/data/TrackCorrections_HIJING_538_OFFICIAL_Mar24.root'),
                      efftableName = cms.string('rTotalEff3D'),
                      Nmin = cms.int32(150),
                      Nmax = cms.int32(185),
                      order = cms.int32(2),  
)
process.demo_n3 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftablePath = cms.string('Flow/V2Analyzer/data/TrackCorrections_HIJING_538_OFFICIAL_Mar24.root'),
                      efftableName = cms.string('rTotalEff3D'),
                      Nmin = cms.int32(185),
                      Nmax = cms.int32(220),
                      order = cms.int32(2),  
)
process.demo_n4 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftablePath = cms.string('Flow/V2Analyzer/data/TrackCorrections_HIJING_538_OFFICIAL_Mar24.root'),
                      efftableName = cms.string('rTotalEff3D'),
                      Nmin = cms.int32(220),
                      Nmax = cms.int32(260),
                      order = cms.int32(2),  
)
process.demo_n5 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftablePath = cms.string('Flow/V2Analyzer/data/TrackCorrections_HIJING_538_OFFICIAL_Mar24.root'),
                      efftableName = cms.string('rTotalEff3D'),
                      Nmin = cms.int32(260),
                      Nmax = cms.int32(300),
                      order = cms.int32(2),  
)

process.demo_n6 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftablePath = cms.string('Flow/V2Analyzer/data/TrackCorrections_HIJING_538_OFFICIAL_Mar24.root'),
                      efftableName = cms.string('rTotalEff3D'),
                      Nmin = cms.int32(120),
                      Nmax = cms.int32(150),
                      order = cms.int32(3),  
)

process.demo_n7 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftablePath = cms.string('Flow/V2Analyzer/data/TrackCorrections_HIJING_538_OFFICIAL_Mar24.root'),
                      efftableName = cms.string('rTotalEff3D'),
                      Nmin = cms.int32(150),
                      Nmax = cms.int32(185),
                      order = cms.int32(3),  
)
process.demo_n8 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftablePath = cms.string('Flow/V2Analyzer/data/TrackCorrections_HIJING_538_OFFICIAL_Mar24.root'),
                      efftableName = cms.string('rTotalEff3D'),
                      Nmin = cms.int32(185),
                      Nmax = cms.int32(220),
                      order = cms.int32(3),  
)
process.demo_n9 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftablePath = cms.string('Flow/V2Analyzer/data/TrackCorrections_HIJING_538_OFFICIAL_Mar24.root'),
                      efftableName = cms.string('rTotalEff3D'),
                      Nmin = cms.int32(220),
                      Nmax = cms.int32(260),
                      order = cms.int32(3),  
)
process.demo_n10 = process.demo.clone(
                      useCentrality = cms.bool(False),
                      efftablePath = cms.string('Flow/V2Analyzer/data/TrackCorrections_HIJING_538_OFFICIAL_Mar24.root'),
                      efftableName = cms.string('rTotalEff3D'),
                      Nmin = cms.int32(260),
                      Nmax = cms.int32(300),
                      order = cms.int32(3),  
)



process.p_n1 = cms.Path(process.hltHM_n1*process.demo_n1)
process.p_n2 = cms.Path(process.hltHM_n2*process.demo_n2)
process.p_n3 = cms.Path(process.hltHM_n3*process.demo_n3)
process.p_n4 = cms.Path(process.hltHM_n4*process.demo_n4)
process.p_n5 = cms.Path(process.hltHM_n5*process.demo_n5)
process.p_n6 = cms.Path(process.hltHM_n1*process.demo_n6)
process.p_n7 = cms.Path(process.hltHM_n2*process.demo_n7)
process.p_n8 = cms.Path(process.hltHM_n3*process.demo_n8)
process.p_n9 = cms.Path(process.hltHM_n4*process.demo_n9)
process.p_n10 = cms.Path(process.hltHM_n5*process.demo_n10)
