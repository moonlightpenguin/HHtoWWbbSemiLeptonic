#pragma once

#include <TString.h>
//#include <Color_t>
#include <iostream>
#include <map>

using namespace std;

const map<const TString, const TString> infotexts{
  {"2016", "35.9 fb^{-1} (13 TeV)"},
  {"2017", "41.5 fb^{-1} (13 TeV)"},
  {"2018", "59.7 fb^{-1} (13 TeV)"}
};

const map<const TString, const TString> offline_e_thresholds{
  {"2016", "30"},
  {"2017", "40"},
  {"2018", "35"}
};
/*
const map<const TString, Color_t> proc_colors = {
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
*/
