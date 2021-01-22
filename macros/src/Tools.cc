#include <TString.h>
#include <TFile.h>
#include <iostream>

#include "../include/Tools.h"

using namespace std;

AnalysisTool::AnalysisTool(int year_) {
  base_path = "/nfs/dust/cms/user/frahmmat/HHtoWWbbSemiLeptonic/";
  uhh2_path = "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/";
  pre_tag = "Preselection";
  full_tag = "Fullselection";


  year = "";
  year += year_;
  yeartag = "";
  if(year == "2016") yeartag = "2016v3";
  else if (year == "2017") yeartag = "2017v2";
  else if (year == "2018") yeartag = "2018";
  else throw runtime_error("Invalid year_ specified");


  // processes
  signal_tag = "HHtoWWbbSemiLeptonic_SM";
  backgrounds_tag = {"TTbar", "DYJets", "QCDMu", "Diboson", "SingleTop", "TTV", "WJets"};

  //colors
  proc_colors = {
    {"HHtoWWbbSemiLeptonic_SM", 416},
    {"DATA_Muon", 1},
    {"TTbar", 810},
    {"DYJets", 798},
    {"QCDMu", 613},
    {"Diboson", 801},
    {"SingleTop", 860},
    {"TTV", 867},
    {"WJets", 413}
  };

}
