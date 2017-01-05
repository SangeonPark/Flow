from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

import FWCore.ParameterSet.Config as cms
#load the cfi file and rewrite cross section parameter each time:
process = cms.Process('Demo')
process.load("Flow.V2Analyzer.v2analyzerCumulant_cfi")

config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.allowUndistributedCMSSW = True

outputName = 'multicrab_CMW_MainResult_Cumulant_pPb_new_0106'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'pPb_Main_cfg.py'
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
   
   sampleName = ["/PAHighPt/davidlw-PA2013_FlowCorr_PromptReco_TrkHM_Gplus_Rereco_ReTracking_v18-28b2b9cce04ec3f20baeb96fbd2295a8/USER",
		 "/PAHighPt/davidlw-PA2013_FlowCorr_PromptReco_TrkHM_Gplus_ReTracking_v18-28b2b9cce04ec3f20baeb96fbd2295a8/USER",
		 "/PAHighPt/davidlw-PA2013_FlowCorr_PromptReco_TrkHM_Gplus_Reverse_ReTracking_v18-28b2b9cce04ec3f20baeb96fbd2295a8/USER"]
   beam = [False,False,True]

   for num in range(0,3):
	
       print 'double check that with %r sample the reverse beam option is %r ' % (num, beam[num])
       process.demo.reverseBeam = beam[num]       
       RequestName = outputName + '_' + str(num)
       DataSetName = sampleName[num]
       config.General.requestName = RequestName
       config.Data.inputDataset = DataSetName
       submit(config)
