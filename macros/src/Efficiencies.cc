#include "../include/Tools.h"
//#include "../include/constants.h"

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TText.h>
#include <TGaxis.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TROOT.h>
#include <TKey.h>
#include <TLatex.h>
#include <TClass.h>
#include <fstream>




using namespace std;

// this is my very sloppy script to make efficiency plots
void AnalysisTool::Efficiencies(TString selection, TString cuts, vector<TString> processes) {

  // TODO: make those two vectors into one map
  vector<TString> label = {"Cleaner", "N_{lep}=1", "N_{mu}=1", "Jets #geq 3", "Bjet #geq 1", "Jets #geq 4"};
  vector<TString> histnames_in = {/*"NoCuts_General/sum_event_weights", */"Cleaner_General/sum_event_weights", "1Lepton_General/sum_event_weights", "1MuonCategory_General/sum_event_weights", "3Jets_General/sum_event_weights", "1Bjet_General/sum_event_weights",  "4Jets_General/sum_event_weights"};

  TString filename = "/nfs/dust/cms/user/frahmmat/HHtoWWbbSemiLeptonic/" + year + "/" + selection + "/" + cuts + "/uhh2.AnalysisModuleRunner.";

  TCanvas* c1 = new TCanvas("c1", "c1", 600, 600);
  TH1F* h_base = new TH1F("efficiencies", "Selection steps", 6, 0.5, 6.5);
  for(unsigned int j=0; j<label.size();j++){
    h_base->GetXaxis()->SetBinLabel(j+1, label[j].Data());
  }
  cout << "Line: " << __LINE__ << endl;
  h_base->Draw("HIST");
  TLegend *leg = new TLegend(0.25,0.67,0.95,0.91,"");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetLineColor(1);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  //leg->SetHeader("Header");

  // loop over all processes
  for(unsigned int i=0; i<processes.size(); i++) {
    TString proc = processes[i];
    TString tag ="MC.";
    if(proc.Contains("DATA")) tag = "DATA.";

    TString infilename = filename + tag + proc + "_" + yeartag + ".root";
    cout << "infilename: " << infilename << endl;
    TFile* infile = new TFile(infilename);
    


    TH1F* h_out = new TH1F("efficiencies", "Selection steps", 6, 0.5, 6.5);

    TH1F* h_in_1 = (TH1F*) infile->Get(histnames_in[0]);
    double norm = h_in_1->Integral();
    delete h_in_1;
    for(unsigned int j=0; j<histnames_in.size(); j++) {
      TH1F* h_in_j = (TH1F*) infile->Get(histnames_in[j]);
      cout << "Number of events after " << j << " cuts: " << h_in_j->Integral() << endl;
      cout << "number of events after " << j << " cuts: " << h_in_j->GetBinContent(1) << endl;
      h_out->SetBinContent(j+1, h_in_j->Integral()/norm);
      //delete h_in_j;
    }
    cout << proc_colors[proc] << endl;
    h_out->SetLineColor(proc_colors[proc]);
    h_out->Draw("SAME");
    leg->AddEntry(h_out, processes[i],"L");

  }
  leg->Draw();
  c1->SaveAs("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/macros/Plots/efficiencies_" + year + "_" + selection + "_" + cuts + ".eps");
  //c1->SaveAs("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/macros/Plots/efficiencies_" + year + "_" + selection + "_" + cuts + ".pdf");
  delete c1;

} // end of script
