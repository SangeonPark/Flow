import FWCore.ParameterSet.Config as cms

demo = cms.EDAnalyzer('V2Analyzer',
                      vertexSrc = cms.string('offlinePrimaryVertices'),
                      trackSrc = cms.InputTag('generalTracks'),
                      towerSrc = cms.InputTag('towerMaker'),
                    # nHitCut = cms.int32(3),	
                      dxySigCut = cms.double(3.0),
                      dzSigCut = cms.double(3.0),
                      etaCutMin = cms.double(-2.4),
                      etaCutMax = cms.double(2.4),
                      NTrkMin = cms.int32(185),
                      NTrkMax = cms.int32(220)	
)
