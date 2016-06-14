import FWCore.ParameterSet.Config as cms

demo = cms.EDAnalyzer('V2AnalyzerSP',
                      vertexSrc = cms.string('offlinePrimaryVertices'),
                      trackSrc = cms.InputTag('generalTracks'),
                      towerSrc = cms.InputTag('towerMaker'),
                      
                    # nHitCut = cms.int32(3),	
                      dxySigCut = cms.double(3.0),
                      dzSigCut = cms.double(3.0),
                      etaCutMin = cms.double(-2.4),
                      etaCutMax = cms.double(2.4),
                      etaHFLow = cms.double(3.0),
                      etaHFUpp = cms.double(5.0),
                      NTrkMin = cms.int32(220),
                      NTrkMax = cms.int32(1000000),
                      doEffCorrection = cms.bool(True),
                      reverseBeam = cms.bool(False)
                      
)
