from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

import FWCore.ParameterSet.Config as cms
#load the cfi file and rewrite cross section parameter each time:
process = cms.Process('Demo')
process.load("Flow.V2Analyzer.SelfCorrTestSP_cfi")

outputName = "multicrab_CMW_SelfCorr_SP_PbPb_MB5_0110"

config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'PbPbCumulant_cfg.py'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
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


   sampleName = [ "/HIMinimumBias5/davidlw-RecoSkim2015_pprereco_v5-70836070e3530d592901940b96c951fe/USER",
                  "/HIMinimumBias5/davidlw-RecoSkim2015_pprereco_TrackerOnly_v5-70836070e3530d592901940b96c951fe/USER"]       
   
   for num in range(0,2):
      print 'double check that we are using sample %r ' % (sampleName[num])
      RequestName = outputName + '_' + str(num) 
      DataSetName = sampleName[num]
      config.General.requestName = RequestName
      config.Data.inputDataset = DataSetName
      submit(config)
