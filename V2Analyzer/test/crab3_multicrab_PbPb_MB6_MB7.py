from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

import FWCore.ParameterSet.Config as cms
#load the cfi file and rewrite cross section parameter each time:
process = cms.Process('Demo')
process.load("Flow.V2Analyzer.v2analyzerCumulant_cfi")

outputName = "multicrab_CMW_PbPb_varybinning_185_220_ver4_0124_failed"

config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'PbPb_Main_varybin_5TeV_cfg.py'
config.Data.inputDBS = 'global'
config.Data.allowNonValidInputDataset = True
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 5
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = outputName
config.Site.storageSite = 'T3_US_Rice'

if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand
   from CRABClient.ClientExceptions import ClientException
   from httplib import HTTPException

   config.General.workArea = outputName

   def submit(config):
      try:
           crabCommand('submit', config = config)
      except HTTPException as hte:
           print "Failed submitting task: %s" % (hte.headers)
      except ClientException as cle:
          print "Failed submitting task: %s" % (cle)


   sampleName = [ "/HIMinimumBias6/HIRun2015-02May2016-v1/AOD",
                  "/HIMinimumBias7/HIRun2015-02May2016-v1/AOD"]       
   lumiName = [ "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/HI/Cert_262548-263757_PromptReco_HICollisions15_JSON_v2.txt",
                "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/HI/Cert_263685-263757_PromptReco_HICollisions15_TrackerOnly_JSON.txt"]
   for num in range(0,1):
      for mask in range(1,2):
         print 'double check that we are using sample %r ' % (sampleName[num])		
         print 'double check that we are using mask %r' % (lumiName[mask])
         RequestName = outputName + '_' + str(num) + "_" + str(mask)
         DataSetName = sampleName[num]
         lumiMaskName = lumiName[mask]
         config.General.requestName = RequestName
         config.Data.inputDataset = DataSetName
         config.Data.lumiMask = lumiMaskName
         submit(config)
