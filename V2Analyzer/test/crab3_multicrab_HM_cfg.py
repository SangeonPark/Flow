from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

import FWCore.ParameterSet.Config as cms
#load the cfi file and rewrite cross section parameter each time:
process = cms.Process('Demo')
process.load("Flow.V2Analyzer.v2analyzerCumulant_cfi")

ntrkRange = [120,150,185,220,260,300]

hltPathNames = ['HLT_PAPixelTracks_Multiplicity100_v*',
		'HLT_PAPixelTracks_Multiplicity130_v*',
		'HLT_PAPixelTracks_Multiplicity160_v*',
		'HLT_PAPixelTracks_Multiplicity190_v*',
		'HLT_PAPixelTracks_Multiplicity220_v*']

config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.allowUndistributedCMSSW = True

outputName = 'multicrab_CMW_pPb_v2_systematics_vertexZ_Wide'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'v2analyzerCumulant_cfg.py'
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

   for paths in range(2,3):
   	  for num in range(0,3):
		
                print 'double check that with %r sample the reverse beam option is %r ' % (num, beam[num])
		print 'double check that multipclicity range is from %r to %r' % (ntrkRange[paths], ntrkRange[paths+1])
		
		process.demo.Nmin = ntrkRange[paths]
		process.demo.Nmax = ntrkRange[paths+1]
		
		if paths == 0:
			process.hltHM.HLTPaths = [hltPathNames[0]]
		if paths == 1:
			process.hltHM.HLTPaths = [hltPathNames[0],hltPathNames[1]]
		if paths == 2:
			process.hltHM.HLTPaths = [hltPathNames[0],hltPathNames[1],hltPathNames[2]]
		if paths == 3:
			process.hltHM.HLTPaths = [hltPathNames[0],hltPathNames[1],hltPathNames[2],hltPathNames[3]]
		if paths == 4:
			process.hltHM.HLTPaths = [hltPathNames[0],hltPathNames[1],hltPathNames[2],hltPathNames[3],hltPathNames[4]]

		process.demo.reverseBeam = beam[num]       
                RequestName = outputName + '_' + str(paths) + "_" + str(num)
                DataSetName = sampleName[num]
                config.General.requestName = RequestName
                config.Data.inputDataset = DataSetName
		submit(config)
