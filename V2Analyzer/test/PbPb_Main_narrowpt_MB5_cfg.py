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

process.load("Flow.V2Analyzer.v2analyzerSP_cfi")


process.TFileService = cms.Service("TFileService",fileName = cms.string("vn_mainresult_ver3.root"))

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



process.p_n1 = cms.Path(process.demo_n1)
process.p_n2 = cms.Path(process.demo_n2)
process.p_n3 = cms.Path(process.demo_n3)
process.p_n4 = cms.Path(process.demo_n4)
process.p_n5 = cms.Path(process.demo_n5)
process.p_n6 = cms.Path(process.demo_n6)
process.p_n7 = cms.Path(process.demo_n7)
process.p_n8 = cms.Path(process.demo_n8)
process.p_n9 = cms.Path(process.demo_n9)
process.p_n10 = cms.Path(process.demo_n10)
process.p_n11 = cms.Path(process.demo_n11)
process.p_n12 = cms.Path(process.demo_n12)
process.p_n13 = cms.Path(process.demo_n13)
process.p_n14 = cms.Path(process.demo_n14)
