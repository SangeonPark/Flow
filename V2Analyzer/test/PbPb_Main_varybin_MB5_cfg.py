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


process.TFileService = cms.Service("TFileService",fileName = cms.string("vn_mainresult_varybin_ver1.root"))

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




process.p_n1 = cms.Path(process.demo_n1)
process.p_n2 = cms.Path(process.demo_n2)
process.p_n3 = cms.Path(process.demo_n3)
process.p_n4 = cms.Path(process.demo_n4)
