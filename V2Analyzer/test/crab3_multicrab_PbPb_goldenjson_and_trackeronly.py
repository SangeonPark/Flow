from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

import FWCore.ParameterSet.Config as cms
#load the cfi file and rewrite cross section parameter each time:
process = cms.Process('Demo')
process.load("Flow.V2Analyzer.closure_cfi")

#ntrkRange = [200,400,800,1500]
#ntrkLow = [60,70,80,90,100,120,140,160]
#ntrkUpp = [70,80,90,100,120,140,160,180]
#ntrkLow = [90,120,150,185,220,260,300,400]
#ntrkUpp = [120,150,185,220,260,300,400,500]

ntrkLow = [60,80,100,120,140,160]
ntrkUpp = [80,100,120,140,160,180]


#efftableNameList = ["eff_1","eff_2","eff_2","eff_2","eff_3","eff_3","eff_3","eff_4"]
efftableNameList = ["eff_5","eff_4","eff_4","eff_3","eff_1","eff_1"]
efftablePathList = ["Flow/V2Analyzer/data/Hydjet_PbPb_eff_v1.root","Flow/V2Analyzer/data/Hydjet_PbPb_eff_v1.root"]


outputName = "multicrab_CMW_v2_PbPb_systematics_trackselection_tight_0824"

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
      for paths in range(0,1):
         print 'double check that we are using sample %r ' % (sampleName[num])		
         print 'double check that centrality range is fram %r to %r' % (ntrkLow[paths],ntrkUpp[paths])
         print 'double check that we are using %r' % (efftableNameList[paths])
         print 'double check that we are using %r' % (efftablePathList[num])
         print '%r _ %r ' % (num,paths)
         

         process.demo.Nmin = ntrkLow[paths]
         process.demo.Nmax = ntrkUpp[paths]
         process.demo.efftablePath = efftablePathList[num]
         process.demo.efftableName = efftableNameList[paths]
         RequestName = outputName + '_' + str(num) + "_" + str(ntrkLow[paths])
         DataSetName = sampleName[num]
         config.General.requestName = RequestName
         config.Data.inputDataset = DataSetName
         submit(config)
