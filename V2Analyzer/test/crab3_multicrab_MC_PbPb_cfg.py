from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

import FWCore.ParameterSet.Config as cms
#load the cfi file and rewrite cross section parameter each time:
process = cms.Process('Demo')
process.load("Flow.V2Analyzer.asymmetryscatterplot_cfi")

ntrkRange = [200,400,800,1500]

outputName = "multicrab_CMW_MC_PbPb_pt_eta_scatterplot"

config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'asymmetryscatterplot_cfg.py'
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
   sampleName = ["/EPOS_PbPb5TeV/davidlw-Cent30100_DIGI-RECO_v1-d1b7f9a11ac0f50a520ee8a635252e33/USER",
                 "/Hydjet_Quenched_MinBias_5020GeV_750/davidlw-ppRECO_std_v3-b19fc96d6ecc5870a54312d2edbb74e0/USER"]       
   
   for num in range(0,2):
      for paths in range(0,3):
         print 'double check that we are using sample %r ' % (num)		
         print 'double check that NtrkOffline range is fram %r to %r' % (ntrkRange[paths],ntrkRange[paths+1])

         process.demo.Nmin = ntrkRange[paths]
         process.demo.Nmax = ntrkRange[paths+1]
         RequestName = outputName + '_' + str(num) + "_" + str(paths)
         DataSetName = sampleName[num]
         config.General.requestName = RequestName
         config.Data.inputDataset = DataSetName
         submit(config)
