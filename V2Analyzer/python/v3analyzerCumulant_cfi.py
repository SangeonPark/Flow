import FWCore.ParameterSet.Config as cms

import HLTrigger.HLTfilters.hltHighLevel_cfi
hltHM = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHM.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*',
                  'HLT_PAPixelTracks_Multiplicity130_v*',
                  'HLT_PAPixelTracks_Multiplicity160_v*'
                  #'HLT_PAPixelTracks_Multiplicity190_v*'
                  #'HLT_PAPixelTracks_Multiplicity220_v*'
]

hltHM.andOr = cms.bool(True)
hltHM.throw = cms.bool(False)

demo = cms.EDAnalyzer('V3AnalyzerCumulant',
                      vertexSrc = cms.string('offlinePrimaryVertices'),
                      trackSrc = cms.InputTag('generalTracks'),
                      towerSrc = cms.InputTag('towerMaker'),
                      # nHitCut = cms.int32(3),
                      etaHFLow = cms.double(3.0),
                      etaHFUpp = cms.double(5.0),
                      dxySigCut = cms.double(3.0),
                      dzSigCut = cms.double(3.0),
                      etaCutMin = cms.double(-2.4),
                      etaCutMax = cms.double(2.4),
                      Nmin = cms.int32(185),
                      Nmax = cms.int32(260),
                      NEtaBins = cms.int32(48),
                      doEffCorrection = cms.bool(True),
                      reverseBeam = cms.bool(True)
                      
)
