#pragma once

#include "UHH2/core/include/Hists.h"

namespace uhh2examples {

  /**  \brief Example class for booking and filling histograms
   * 
   * NOTE: This class uses the 'hist' method to retrieve histograms.
   * This requires a string lookup and is therefore slow if you have
   * many histograms. Therefore, it is recommended to use histogram
   * pointers as member data instead, like in 'common/include/ElectronHists.h'.
   */
  class HHtoWWbbSemiLeptonicPreselectionHists: public uhh2::Hists {
  public:
    // use the same constructor arguments as Hists for forwarding:
    HHtoWWbbSemiLeptonicPreselectionHists(uhh2::Context & ctx, const std::string & dirname);

    virtual void fill(const uhh2::Event & ev) override;
    virtual ~HHtoWWbbSemiLeptonicPreselectionHists();

  protected:
    //TODO with all histograms

    // Jets
    TH1F *N_jets, *N_PU, *pt_jets, *pt_jet1, *pt_jet2, *pt_jet3, *pt_jet4, *eta_jets, *eta_jets_rebin, *eta_jet1, *eta_jet2, *eta_jet3, *eta_jet4;
    TH2F *N_jet_vs_pt_jet, *N_jet_vs_eta_jet;

    TH1F *EMcharged_jet1, *EMneutral_jet1, *HADcharged_jet1, *HADneutral_jet1;

    // TH2D *EMcharged_vs_eta_jet1, *EMneutral_vs_eta_jet1, *HADcharged_vs_eta_jet1, *HADneutral_vs_eta_jet1, *EMcharged_vs_PU_jet1, *EMneutral_vs_PU_jet1, *HADcharged_vs_PU_jet1, *HADneutral_vs_PU_jet1, 


    // bjets
    TH1F *N_bJets_loose, *N_bJets_med, *N_bJets_tight, *N_deepjet_loose, *N_deepjet_med, *N_deepjet_tight, *DeltaR_bjets;

    // leptons
    TH1F *N_mu, *pt_mu, *eta_mu, *eta_mu_rebin, *reliso_mu;
    TH1F *N_ele, *pt_ele, *eta_ele, *eta_ele_rebin, *reliso_ele;
    TH1F *N_lep;

    // MET
    TH1F *MET, *MET_rebin, *MET_rebin2;

    // ST
    TH1F *ST, *ST_rebin, *STjets, *STjets_rebin, *STlep, *STlep_rebin;
    TH2F *N_jets_vs_STjets;

    // M_HH
    TH1F *MT_HH, *MT_HH_rebin, *MT_HH_test, *MT_HH_Vergleich;

    // stuff
    TH1F *sum_event_weights;
    TH1F *N_pv;

  };

}
