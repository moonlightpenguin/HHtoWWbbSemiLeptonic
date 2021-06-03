from python.CombineRunner import *

# this is supposed to combine all 5 channels in the future
path_datacards = '/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data/datacards'
CombineRunner = CombineRunner(path_datacards, 2016)

#systematics = ['lumi', 'rate_ttbar', 'rate_dy', 'rate_ttv', 'rate_diboson', 'rate_singletop', 'rate_wjets', 'rate_qcd', 'pu', 'pdf', 'muid', 'muiso', 'mutrigger', 'eleid', 'elereco', 'eletrigger', 'btag_bc', 'btag_udsg', 'scale_TTbar', 'scale_DYJets', 'scale_TTV', 'scale_Diboson', 'scale_SingleTop']

#systematics = ['lumi', 'rate_ttbar', 'rate_dy', 'rate_ttv', 'rate_diboson', 'rate_singletop', 'rate_wjets']
systematics = ['lumi']

backgrounds = ['TTbar', 'DYJets', 'SingleTop', 'TTV', 'Diboson', 'WJets', 'QCD']

categories = ['A']
channels = ['srmu']

#masspoints = [200, 300, 400, 500, 600, 700, 800, 900, 1000, 1200, 1400, 1700, 2000]
nodes = ['SM']


CombineRunner.CreateDatacards(nodes, categories, channels, backgrounds, systematics, 'NN_combine_histograms_2016.root')
CombineRunner.CombineChannels(nodes, categories, channels)
CombineRunner.ExecuteCombineCombination(nodes, categories, channels)
