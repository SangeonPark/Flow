import FWCore.ParameterSet.Config as cms

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
'root://cmsxrootd.fnal.gov//store/user/davidlw/HIMinimumBias5/RecoSkim2015_pprereco_v5/160727_021048/0000/PbPb_MB_2.root'
)
)

process.load("Flow.V2Analyzer.v2analyzerCumulant_cfi")


process.TFileService = cms.Service("TFileService",fileName = cms.string("vn_systematics_ver1.root"))

process.demo_n1 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftablePath = cms.string('Flow/V2Analyzer/data/Hydjet_PbPb_eff_v1.root'),
                      efftableName = cms.string('eff_5'),
                      Nmin = cms.int32(60),
                      Nmax = cms.int32(80),
                      order = cms.int32(2),  
)


process.demo_n2 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftablePath = cms.string('Flow/V2Analyzer/data/Hydjet_ppReco_v5_tight.root'),
                      efftableName = cms.string('rTotalEff3D_5'),
                      offlineDCA = cms.untracked.double(2.0),
                      offlineptErr = cms.untracked.double(0.05),
                      Nmin = cms.int32(60),
                      Nmax = cms.int32(80),
                      order = cms.int32(2),   
)

process.demo_n3 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftablePath = cms.string('Flow/V2Analyzer/data/Hydjet_ppReco_v5_loose.root'),
                      efftableName = cms.string('rTotalEff3D_5'),
                      offlineDCA = cms.untracked.double(5.0),
                      offlineptErr = cms.untracked.double(0.1),
                      Nmin = cms.int32(60),
                      Nmax = cms.int32(80),
                      order = cms.int32(2),    
)
process.demo_n4 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftablePath = cms.string('Flow/V2Analyzer/data/Hydjet_ppReco_v6_wide.root'),
                      efftableName = cms.string('rTotalEff3D_5'),
                      vzLow = cms.untracked.double(3.0),
                      vzHigh = cms.untracked.double(15.0),
                      Nmin = cms.int32(60),
                      Nmax = cms.int32(80),
                      order = cms.int32(2),    
)
process.demo_n5 = process.demo.clone(
                      useCentrality = cms.bool(True),
                      efftablePath = cms.string('Flow/V2Analyzer/data/Hydjet_ppReco_v6_narrow.root'),
                      efftableName = cms.string('rTotalEff3D_5'),
                      vzLow = cms.untracked.double(0.0),
                      vzHigh = cms.untracked.double(3.0),
                      Nmin = cms.int32(60),
                      Nmax = cms.int32(80),
                      order = cms.int32(2),    
)

process.p_n1 = cms.Path(process.demo_n1)
process.p_n2 = cms.Path(process.demo_n2)
process.p_n3 = cms.Path(process.demo_n3)
process.p_n4 = cms.Path(process.demo_n4)
process.p_n5 = cms.Path(process.demo_n5)
