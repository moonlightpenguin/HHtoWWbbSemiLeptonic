#pragma once

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/NtupleObjects.h>
//#include <UHH2/ZprimeSemiLeptonic/include/ZprimeCandidate.h>
#include <UHH2/core/include/LorentzVector.h>


//#include <UHH2/common/include/TTbarGen.h>
//#include <UHH2/ZprimeSemiLeptonic/include/constants.hpp>

#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesisDiscriminators.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesis.h"

#include "TH1.h"
#include "TFile.h"

struct JetCategories {
  int NJets;
  int NBJets;
  LorentzVector b1;
  LorentzVector b2;
  LorentzVector q1;
  LorentzVector q2;
};

JetCategories CategorizeJets(uhh2::Event& event);

class Variables_NN : uhh2::AnalysisModule{

public:
  explicit Variables_NN(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;


private:
  //vector<string> NNInputs_id; 
  //map<string, uhh2::Event::Handle<float>> NNInputs_map;

  uhh2::Event::Handle<bool> h_is_mHH_reconstructed;
  uhh2::Event::Handle<float> h_mH_bb, h_mH_WW;
  uhh2::Event::Handle< float > h_eventweight;


  //High-level oberservables
  uhh2::Event::Handle<float> h_mbb, h_mWW, h_mlnu, h_mqq;
  uhh2::Event::Handle<float> h_DeltaRqq, h_DeltaRlnu, h_DeltaRbb;
  uhh2::Event::Handle<float> h_minDeltaRlj, h_minDeltaRbj, h_minDeltaRjj;
  uhh2::Event::Handle<float> h_HT;
  uhh2::Event::Handle<float> h_N_BTag, h_N_Ak4;
      uhh2::Event::Handle<float> h_mtop_lep_hyp1, h_mtop_lep_hyp2, h_mtop_had_hyp1, h_mtop_had_hyp2;



  //low-level observables
  uhh2::Event::Handle< float > h_Lep_pt, h_Lep_eta, h_Lep_phi, h_Lep_E;
  uhh2::Event::Handle< float > h_MET_pt, h_MET_phi;


  uhh2::Event::Handle< float > h_Ak4_j1_pt, h_Ak4_j1_eta, h_Ak4_j1_phi, h_Ak4_j1_E, h_Ak4_j1_m, h_Ak4_j1_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j2_pt, h_Ak4_j2_eta, h_Ak4_j2_phi, h_Ak4_j2_E, h_Ak4_j2_m, h_Ak4_j2_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j3_pt, h_Ak4_j3_eta, h_Ak4_j3_phi, h_Ak4_j3_E, h_Ak4_j3_m, h_Ak4_j3_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j4_pt, h_Ak4_j4_eta, h_Ak4_j4_phi, h_Ak4_j4_E, h_Ak4_j4_m, h_Ak4_j4_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j5_pt, h_Ak4_j5_eta, h_Ak4_j5_phi, h_Ak4_j5_E, h_Ak4_j5_m, h_Ak4_j5_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j6_pt, h_Ak4_j6_eta, h_Ak4_j6_phi, h_Ak4_j6_E, h_Ak4_j6_m, h_Ak4_j6_deepjetbscore;
  uhh2::Event::Handle< float > h_MH_bb, h_MH_WW;

};
