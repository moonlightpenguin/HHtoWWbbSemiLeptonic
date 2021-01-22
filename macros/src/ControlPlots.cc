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

// this is my very sloppy script to make control plots
void AnalysisTool::ControlPlots(TString selection, TString cuts, vector<TString> processes) {

  TString filename = "/nfs/dust/cms/user/frahmmat/HHtoWWbbSemiLeptonic/" + year + "/" + selection + "/" + cuts + "/uhh2.AnalysisModuleRunner.";



  TLegend *leg = new TLegend(0.25,0.67,0.95,0.91,"");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetLineColor(1);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);



  vector<TString> cutType = {/*"N_lep", */ "N_mu", "pt_mu", "eta_mu", "reliso_mu", "N_jets3", "pt_jets", "eta_jets", "N_bjets", "N_jets4"};
  
  vector<TString> controlPlots = {"Cleaner_General/N_mu", "Cleaner_General/pt_mu", "Cleaner_General/eta_mu_rebin", "Cleaner_General/reliso_mu", "1MuonCategory_General/N_jets", "1MuonCategory_General/pt_jets", "1MuonCategory_General/eta_jets_rebin", "3Jets_General/N_deepjet_med", "1Bjet_General/N_jets"};
  for(unsigned int k=0; k<controlPlots.size(); k++) {
    TCanvas* c2 = new TCanvas("c2", "c2", 600, 600);
    Double_t max=0; // variable to determine maximum value of plot;
    vector<TH1F*> h;
    for(unsigned int i=0; i<processes.size(); i++) {
      TString proc = processes[i];
      cout << "Plot: " << controlPlots[k] << endl;
      cout << "Process: " << proc << endl;
      TString tag ="MC.";
      if(proc.Contains("DATA")) tag = "DATA.";

      TString infilename = filename + tag + proc + "_" + yeartag + ".root";
      cout << "infilename: " << infilename << endl;
      TFile* infile = new TFile(infilename);
      h.push_back((TH1F*) infile->Get(controlPlots[k]));
      //TH1F* h = (TH1F*) infile->Get(controlPlots[k]);
      // normalize
      cout << "norm: " << h[i]->Integral() << endl;
      h[i]->Scale(1/h[i]->Integral());
      if (h[i]->GetBinContent(h[i]->GetMaximumBin()) > max) max = h[i]->GetBinContent(h[i]->GetMaximumBin());
      cout << max << endl;
      cout << "Line: " << __LINE__ << endl;
      h[i]->SetLineColor(proc_colors[proc]);
    }
    for(unsigned int i=0; i<processes.size(); i++) {
      h[i]->SetMaximum(max*1.1); // not opimal, I always plot max*1.1 from the 1st process
      h[i]->Draw("HIST SAME");
    }
    leg->Draw();
    c2->SaveAs("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/macros/Plots/controlPlots_" + year + "_" + selection + "_" + cuts + "_" + cutType[k] + ".eps");
    //c2->SaveAs("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/macros/Plots/controlPlots_" + year + "_" + selection + "_" + cuts + "_" + cutType[k] + ".pdf");

    delete c2;
  }
}
