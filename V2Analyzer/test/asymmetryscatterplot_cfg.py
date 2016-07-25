import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")


process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",ignoreTotal = cms.untracked.int32(1) )


process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(


        #EPOS High Multiplicity pPb
        #'root://cms-xrd-global.cern.ch//store/user/gsfs/EPOSpPb_5TeV_HM150/EPOS_HM150_pPb_5TeV_RECODEBUG_20160530/160531_003234/0000/EPOSpPb_RAW2DIGI_L1Reco_RECO_100.root',
        #'root://cms-xrd-global.cern.ch//store/user/gsfs/EPOSpPb_5TeV_HM150/EPOS_HM150_pPb_5TeV_RECODEBUG_20160530/160531_003234/0000/EPOSpPb_RAW2DIGI_L1Reco_RECO_101.root',
        #'root://cms-xrd-global.cern.ch//store/user/gsfs/EPOSpPb_5TeV_HM150/EPOS_HM150_pPb_5TeV_RECODEBUG_20160530/160531_003234/0000/EPOSpPb_RAW2DIGI_L1Reco_RECO_102.root',
        #'root://cms-xrd-global.cern.ch//store/user/gsfs/EPOSpPb_5TeV_HM150/EPOS_HM150_pPb_5TeV_RECODEBUG_20160530/160531_003234/0000/EPOSpPb_RAW2DIGI_L1Reco_RECO_103.root',
        #'root://cms-xrd-global.cern.ch//store/user/gsfs/EPOSpPb_5TeV_HM150/EPOS_HM150_pPb_5TeV_RECODEBUG_20160530/160531_003234/0000/EPOSpPb_RAW2DIGI_L1Reco_RECO_104.root',
        #'root://cms-xrd-global.cern.ch//store/user/gsfs/EPOSpPb_5TeV_HM150/EPOS_HM150_pPb_5TeV_RECODEBUG_20160530/160531_003234/0000/EPOSpPb_RAW2DIGI_L1Reco_RECO_105.root',
        #'root://cms-xrd-global.cern.ch//store/user/gsfs/EPOSpPb_5TeV_HM150/EPOS_HM150_pPb_5TeV_RECODEBUG_20160530/160531_003234/0000/EPOSpPb_RAW2DIGI_L1Reco_RECO_106.root',
        #'root://cms-xrd-global.cern.ch//store/user/gsfs/EPOSpPb_5TeV_HM150/EPOS_HM150_pPb_5TeV_RECODEBUG_20160530/160531_003234/0000/EPOSpPb_RAW2DIGI_L1Reco_RECO_107.root',
        #'root://cms-xrd-global.cern.ch//store/user/gsfs/EPOSpPb_5TeV_HM150/EPOS_HM150_pPb_5TeV_RECODEBUG_20160530/160531_003234/0000/EPOSpPb_RAW2DIGI_L1Reco_RECO_108.root',
        #'root://cms-xrd-global.cern.ch//store/user/gsfs/EPOSpPb_5TeV_HM150/EPOS_HM150_pPb_5TeV_RECODEBUG_20160530/160531_003234/0000/EPOSpPb_RAW2DIGI_L1Reco_RECO_109.root',
        #'root://cms-xrd-global.cern.ch//store/user/gsfs/EPOSpPb_5TeV_HM150/EPOS_HM150_pPb_5TeV_RECODEBUG_20160530/160531_003234/0000/EPOSpPb_RAW2DIGI_L1Reco_RECO_110.root'


        


        #EPOS PbPb
        'root://cms-xrd-global.cern.ch//store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_1.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_10.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_100.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_101.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_102.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_103.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_104.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_105.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_106.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_107.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_108.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_109.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_11.root',
        'root://cms-xrd-global.cern.ch//store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_110.root'

        #HYDJET PbPb
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v3/160216_232421/0000/step2pp_RAW2DIGI_L1Reco_RECO_112.root',
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v3/160216_232421/0000/step2pp_RAW2DIGI_L1Reco_RECO_113.root',
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v3/160216_232421/0000/step2pp_RAW2DIGI_L1Reco_RECO_100.root',
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v3/160216_232421/0000/step2pp_RAW2DIGI_L1Reco_RECO_101.root',
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v3/160216_232421/0000/step2pp_RAW2DIGI_L1Reco_RECO_102.root',
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v3/160216_232421/0000/step2pp_RAW2DIGI_L1Reco_RECO_103.root',
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v3/160216_232421/0000/step2pp_RAW2DIGI_L1Reco_RECO_104.root',
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v3/160216_232421/0000/step2pp_RAW2DIGI_L1Reco_RECO_105.root',
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v3/160216_232421/0000/step2pp_RAW2DIGI_L1Reco_RECO_106.root',
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v3/160216_232421/0000/step2pp_RAW2DIGI_L1Reco_RECO_107.root',
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v3/160216_232421/0000/step2pp_RAW2DIGI_L1Reco_RECO_108.root',
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v3/160216_232421/0000/step2pp_RAW2DIGI_L1Reco_RECO_109.root',
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v3/160216_232421/0000/step2pp_RAW2DIGI_L1Reco_RECO_111.root',
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v3/160216_232421/0000/step2pp_RAW2DIGI_L1Reco_RECO_110.root'



        #EPOS pPb
        #'root://cms-xrd-global.cern.ch//store/user/davidlw/ReggeGribovPartonMCfix_EposLHC_5TeV_pPb/RecoSkim_ReTracking_v4_5M/5cde49c8740ff28f897f533d05a99dbc/pPb_MB_100_2_s6H.root'

    )
)

#loads analyzer
process.load("Flow.V2Analyzer.asymmetryscatterplot_cfi")
process.TFileService = cms.Service("TFileService",fileName = cms.string("EPOS_0725.root"))


process.p = cms.Path(process.demo)
