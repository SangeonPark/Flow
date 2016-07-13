### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()
outputName = 'CMW_v2_pPb_EPOS_HighMultiplicity_0713'
config.General.requestName = outputName
config.General.workArea = outputName
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'asymmetryscatterplot_cfg.py'

config.Data.inputDBS = 'global'
config.Data.allowNonValidInputDataset = True


#EPOS DATA
config.Data.inputDataset = '/EPOSpPb_5TeV_HM150/gsfs-EPOS_HM150_pPb_5TeV_RECODEBUG_20160530-b74f046c211430dc50f1c4dabeee6133/USER'

config.Data.splitting = 'FileBased'
config.Data.ignoreLocality = False
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB()) 
config.Data.publication = False
config.Site.storageSite = 'T3_US_Rice'
