#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"

class HHtoWWbbSemiLeptonicMulticlassNNHists: public uhh2::Hists {
public:
  explicit HHtoWWbbSemiLeptonicMulticlassNNHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

 protected:
  void init();

  TH1F *NN_out0, *NN_out1, *NN_out2, *NN_out3, *NN_out4;
  TH1F *NN_out0_rebin, *NN_out1_rebin, *NN_out2_rebin, *NN_out3_rebin, *NN_out4_rebin;
  uhh2::Event::Handle<double> h_NNoutput0;
  uhh2::Event::Handle<double> h_NNoutput1;
  uhh2::Event::Handle<double> h_NNoutput2;
  uhh2::Event::Handle<double> h_NNoutput3;
  uhh2::Event::Handle<double> h_NNoutput4;

  virtual ~HHtoWWbbSemiLeptonicMulticlassNNHists();
};
          
class HHtoWWbbSemiLeptonicMulticlassNNInputHists: public uhh2::Hists {
public:
  explicit HHtoWWbbSemiLeptonicMulticlassNNInputHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

 protected:
  void init();

  //vector<string> NNInputs_id; 
  //map<string, uhh2::Event::Handle<float>> NNInputs_map;

  // NN_Variables
  //high-level
  uhh2::Event::Handle<float> h_mbb, h_mlnu, h_mqq, h_DeltaRlnu, h_DeltaRbb, h_DeltaRqq, h_minDeltaRlj, h_minDeltaRbj, h_minDeltaRjj, h_HT, h_N_BTag, h_N_Ak4, h_mtop_lep_hyp1, h_mtop_lep_hyp2, h_mtop_had_hyp1, h_mtop_had_hyp2, h_MH_bb, h_MH_WW;

  TH1F *NN_mbb, *N_mWW, *NN_mlnu, *NN_mqq, *NN_DeltaRlnu, *NN_DeltaRbb, *NN_DeltaRqq, *NN_minDeltaRlj, *NN_minDeltaRbj, *NN_minDeltaRjj, *NN_HT, *NN_NBTag, *NN_NAk4, *NN_mtop_lep1, *NN_mtop_lep2, *NN_mtop_had1, *NN_mtop_had2, *NN_MH_bb, *NN_MH_WW;

  //low-level
  uhh2::Event::Handle< float > h_Lep_pt, h_Lep_eta, h_Lep_phi, h_Lep_E;
  uhh2::Event::Handle< float > h_MET_pt, h_MET_phi;
  uhh2::Event::Handle< float > h_Ak4_j1_pt, h_Ak4_j1_eta, h_Ak4_j1_phi, h_Ak4_j1_E, h_Ak4_j1_m, h_Ak4_j1_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j2_pt, h_Ak4_j2_eta, h_Ak4_j2_phi, h_Ak4_j2_E, h_Ak4_j2_m, h_Ak4_j2_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j3_pt, h_Ak4_j3_eta, h_Ak4_j3_phi, h_Ak4_j3_E, h_Ak4_j3_m, h_Ak4_j3_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j4_pt, h_Ak4_j4_eta, h_Ak4_j4_phi, h_Ak4_j4_E, h_Ak4_j4_m, h_Ak4_j4_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j5_pt, h_Ak4_j5_eta, h_Ak4_j5_phi, h_Ak4_j5_E, h_Ak4_j5_m, h_Ak4_j5_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j6_pt, h_Ak4_j6_eta, h_Ak4_j6_phi, h_Ak4_j6_E, h_Ak4_j6_m, h_Ak4_j6_deepjetbscore;

  TH1F *NN_Lep_pt, *NN_Lep_eta, *NN_Lep_phi, *NN_Lep_E;
  TH1F *NN_MET_pt, *NN_MET_phi;
  TH1F *NN_Ak4_j1_pt, *NN_Ak4_j1_eta, *NN_Ak4_j1_phi, *NN_Ak4_j1_E, *NN_Ak4_j1_m, *NN_Ak4_j1_deepjetbscore;;
  TH1F *NN_Ak4_j2_pt, *NN_Ak4_j2_eta, *NN_Ak4_j2_phi, *NN_Ak4_j2_E, *NN_Ak4_j2_m, *NN_Ak4_j2_deepjetbscore;;
  TH1F *NN_Ak4_j3_pt, *NN_Ak4_j3_eta, *NN_Ak4_j3_phi, *NN_Ak4_j3_E, *NN_Ak4_j3_m, *NN_Ak4_j3_deepjetbscore;;
  TH1F *NN_Ak4_j4_pt, *NN_Ak4_j4_eta, *NN_Ak4_j4_phi, *NN_Ak4_j4_E, *NN_Ak4_j4_m, *NN_Ak4_j4_deepjetbscore;;
  TH1F *NN_Ak4_j5_pt, *NN_Ak4_j5_eta, *NN_Ak4_j5_phi, *NN_Ak4_j5_E, *NN_Ak4_j5_m, *NN_Ak4_j5_deepjetbscore;;
  TH1F *NN_Ak4_j6_pt, *NN_Ak4_j6_eta, *NN_Ak4_j6_phi, *NN_Ak4_j6_E, *NN_Ak4_j6_m, *NN_Ak4_j6_deepjetbscore;;


  virtual ~HHtoWWbbSemiLeptonicMulticlassNNInputHists();
};
