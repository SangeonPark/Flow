### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()
outputName = 'CMW_PbPb_Cumulant_v3_185_260_0716_ver2_correct'
config.General.requestName = outputName
config.General.workArea = outputName
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'PbPb_502TeV_cfg.py'

config.Data.inputDBS = 'global'
config.Data.allowNonValidInputDataset = True

#MB
#config.Data.inputDataset = '/PAMinBiasUPC/davidlw-PA2013_FlowCorr_PromptReco_MB_Gplus_ReTracking_v18-25c9a89be536a41c8ccb3c75e9fd9358/USER'

#High Multiplicity
#config.Data.inputDataset = '/PAHighPt/davidlw-PA2013_FlowCorr_PromptReco_TrkHM_Gplus_Rereco_ReTracking_v18-28b2b9cce04ec3f20baeb96fbd2295a8/USER'
#config.Data.inputDataset = '/PAHighPt/davidlw-PA2013_FlowCorr_PromptReco_TrkHM_Gplus_ReTracking_v18-28b2b9cce04ec3f20baeb96fbd2295a8/USER'
#config.Data.inputDataset = '/PAHighPt/davidlw-PA2013_FlowCorr_PromptReco_TrkHM_Gplus_Reverse_ReTracking_v18-28b2b9cce04ec3f20baeb96fbd2295a8/USER'

#EPOS:
#config.Data.inputDataset = '/PAMinBiasUPC/davidlw-PA2013_FlowCorr_PromptReco_MB_Gplus_Rereco_ReTracking_v18-25c9a89be536a41c8ccb3c75e9fd9358/USER'
#HIJING:
#config.Data.inputDataset = '/Hijing_PPb502_MinimumBias/davidlw-RecoSkim_ReTracking_v4_10M-5cde49c8740ff28f897f533d05a99dbc/USER'

#PbPb Data
config.Data.inputDataset = '/HIMinimumBias5/HIRun2015-02May2016-v1/AOD'

config.Data.splitting = 'FileBased'
config.Data.ignoreLocality = False
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB()) 
config.Data.publication = False
config.Site.storageSite = 'T3_US_Rice'
