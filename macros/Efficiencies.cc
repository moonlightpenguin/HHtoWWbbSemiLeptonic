// this is my very sloppy script to make efficiency plots and control plots
void Efficiencies(){

  vector<TString> years = {"2016"};
  vector<TString> yeartags = {"2016v3"};
  vector<TString> processes = {"HHtoWWbbSemiLeptonic_SM"/*, "DATA_Muon"*/, "TTbar", "DYJets", "QCDMu"/*, "Diboson", "SingleTop", "TTV", "WJets"*/};
  TString year = "2016";
  TString yeartag = "2016v3";
  TString selection = "Preselection";
  TString cuts = "mu24jet10";
  TString label1 = "xy";
  vector<Color_t> proc_colors = {416/*, 1*/, 810, 798, 613/*, 801, 860, 867, 413*/};
  vector<TString> label = {"Cleaner", "N_{lep}=1", "N_{mu}=1", "Jets #geq 3", "Bjet #geq 1", "Jets #geq 4"};
  vector<TString> histnames_in = {/*"NoCuts_General/sum_event_weights", */"Cleaner_General/sum_event_weights", "1Lepton_General/sum_event_weights", "1MuonCategory_General/sum_event_weights", "3Jets_General/sum_event_weights", "1Bjet_General/sum_event_weights",  "4Jets_General/sum_event_weights"};
  //vector<TString> controlPlots : {Cleaner_General/};

  TString filename = "/nfs/dust/cms/user/frahmmat/HHtoWWbbSemiLeptonic/" + year + "/" + selection + "/" + cuts + "/uhh2.AnalysisModuleRunner.";

  TCanvas* c1 = new TCanvas("c1", "c1", 600, 600);
  TH1F* h_base = new TH1F("efficiencies", "Selection steps", 6, 0.5, 6.5);
  for(int j=0; j<label.size();j++){
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
  for(int i=0; i<processes.size(); i++) {
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
    for(int j =0; j<histnames_in.size(); j++) {
      TH1F* h_in_j = (TH1F*) infile->Get(histnames_in[j]);
      cout << "Number of events after " << j << " cuts: " << h_in_j->Integral() << endl;
      cout << "number of events after " << j << " cuts: " << h_in_j->GetBinContent(1) << endl;
      h_out->SetBinContent(j+1, h_in_j->Integral()/norm);
      //delete h_in_j;
    }
    h_out->SetLineColor(proc_colors[i]);
    h_out->Draw("SAME");
    leg->AddEntry(h_out, processes[i],"L");
  }
  leg->Draw();
  c1->SaveAs("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/macros/efficiencies_" + year + "_" + selection + "_" + cuts + ".eps");
  c1->SaveAs("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/macros/Plots/efficiencies_" + year + "_" + selection + "_" + cuts + ".pdf");
  delete c1;


  // let's also do control plots!
  vector<TString> cutType = {/*"N_lep", */ "N_mu", "pt_mu", "eta_mu", "reliso_mu", "N_jets3", "pt_jets", "eta_jets", "N_bjets", "N_jets4"};
  vector<TString> controlPlots = {"Cleaner_General/N_mu", "Cleaner_General/pt_mu", "Cleaner_General/eta_mu_rebin", "Cleaner_General/reliso_mu", "1MuonCategory_General/N_jets", "1MuonCategory_General/pt_jets", "1MuonCategory_General/eta_jets", "3Jets_General/N_deepjet_med", "1Bjet_General/N_jets"};
  for(int k=0; k<controlPlots.size(); k++) {
    TCanvas* c2 = new TCanvas("c2", "c2", 600, 600);
    Double_t max=0; // variable to determine maximum value of plot;
    vector<TH1F*> h;
    for(int i=0; i<processes.size(); i++) {
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
      h[i]->SetLineColor(proc_colors[i]);
    }
    for(int i=0; i<processes.size(); i++) {
	h[i]->SetMaximum(max*1.1); // not opimal, I always plot max*1.1 from the 1st process
	h[i]->Draw("HIST SAME");
      }
    leg->Draw();
    c2->SaveAs("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/macros/controlPlots_" + year + "_" + selection + "_" + cuts + "_" + cutType[k] + ".eps");
        c2->SaveAs("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/macros/Plots/controlPlots_" + year + "_" + selection + "_" + cuts + "_" + cutType[k] + ".pdf");

    delete c2;
  }


} // end of script
