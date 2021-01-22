#include <cmath>
#include <iostream>
#include "../include/Tools.h"
#include <TString.h>

using namespace std;

int main(){
  cout << "Hello from main()." << endl;

  AnalysisTool Analysis16(2016);
  AnalysisTool Analysis17(2017);
  AnalysisTool Analysis18(2018);


  // analysis of the Pre-Selection

  TString selection = "Preselection";
  TString cuts = "mu24jet10";
  vector<TString> allProcesses = {"HHtoWWbbSemiLeptonic_SM",/* "DATA_Muon",*/ "TTbar", "DYJets", "QCDMu", "Diboson", "SingleTop", "TTV", "WJets"};
  vector<TString> someProcesses = {"HHtoWWbbSemiLeptonic_SM", "TTbar", "DYJets", "QCDMu"};

  //Analysis16.Efficiencies(selection, cuts, someProcesses);
  //Analysis16.ControlPlots(selection, cuts, someProcesses);


  TString plotname = "1MuonCategory_General/pt_jet3";
  Analysis16.SignalToBackground(cuts, plotname);


  cout << "Finished main(). cya." << endl;
}
