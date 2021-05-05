#include <UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicModules.h>
//#include <UHH2/common/include/TTbarReconstruction.h>
//#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/core/include/LorentzVector.h>
#include <UHH2/core/include/Utils.h>
#include <UHH2/common/include/Utils.h>
#include "UHH2/common/include/JetIds.h"
//#include <UHH2/ZprimeSemiLeptonic/include/ZprimeCandidate.h>

//#include <UHH2/ZprimeSemiLeptonic/include/constants.hpp>

#include "UHH2/HHtoWWbbSemiLeptonic/include/Functions.h"
#include "Riostream.h"
#include "TFile.h"
#include "TH1F.h"

using namespace std;
using namespace uhh2;

HHCategorizeJets::HHCategorizeJets(uhh2::Context& ctx){
  h_jetCategories = ctx.declare_event_output<HHJetCategories>("jetCategories");
}


// only safe for 4 Jet category
bool HHCategorizeJets::process(uhh2::Event& event){
  HHJetCategories output;

  std::vector<Jet>* jets = event.jets;
  JetId DeepjetMedium = BTag(BTag::DEEPJET, BTag::WP_MEDIUM);
  vector<Jet> lightjets;

  // assign bjets
  int Ndeepjet_med=0;
  for (unsigned int i =0; i<jets->size(); i++) {
    if(DeepjetMedium(jets->at(i),event)) {
      Ndeepjet_med++;
      if(Ndeepjet_med == 1) output.b1 =jets->at(i);
      if(Ndeepjet_med == 2) output.b2 =jets->at(i);
      // define all other bjets as lightjets
      if(Ndeepjet_med > 2) lightjets.push_back(jets->at(i));
    }
    else lightjets.push_back(jets->at(i));
  }
  
  // if only 1 btagged jet -> take lightjet with highest btag-score as b2
  unsigned int b2_index = 999;
  if(Ndeepjet_med == 1) {
    double btag_max = 0;
    Jet b2;
    for (unsigned int j=0; j<lightjets.size(); j++) {
      if(lightjets[j].btag_DeepJet() > btag_max) b2_index = j;
    }
    
  }
  // assign lightsjets and (possibly) b2
  int Nlightjet=0;
  for (unsigned int j=0; j<lightjets.size(); j++) {
    if(j==b2_index) output.b2 = lightjets[j];
    else{
      Nlightjet++;
      if(Nlightjet==1) output.q1 = lightjets[j];
      if(Nlightjet==2) output.q2 = lightjets[j];
    }
  }
  event.set(h_jetCategories, output);
  return true;
}


Variables_NN::Variables_NN(uhh2::Context& ctx){

  // input
  h_is_mHH_reconstructed = ctx.get_handle<bool>("is_mHH_reconstructed");
  h_mH_bb = ctx.get_handle<float>("mH_bb");
  h_mH_WW = ctx.get_handle<float>("mH_WW");
  //h_region = ctx.get_handle<TString>("region");

  // output

  h_eventweight = ctx.declare_event_output<float> ("eventweight");

  // high-level observables

  h_mbb = ctx.declare_event_output<float> ("mbb");
  h_mlnu = ctx.declare_event_output<float> ("mlnu");
  h_DeltaRlnu = ctx.declare_event_output<float> ("DeltaRlnu");
  h_DeltaRbb = ctx.declare_event_output<float> ("DeltaRbb");
  h_minDeltaRlj = ctx.declare_event_output<float> ("minDeltaRlj");
  h_minDeltaRbj = ctx.declare_event_output<float> ("minDeltaRbj");
  h_minDeltaRjj = ctx.declare_event_output<float> ("minDeltaRjj");
  h_HT = ctx.declare_event_output<float> ("HT");
  h_N_BTag = ctx.declare_event_output<float> ("N_BTag");
  h_N_Ak4 = ctx.declare_event_output<float> ("N_Ak4");


///  Higgs masses (chi2)
  h_MH_bb = ctx.declare_event_output<float> ("MH_bb");
  h_MH_WW = ctx.declare_event_output<float> ("MH_WW");


  // low-level observables
  /*
///  MUONS
  h_Mu_pt = ctx.declare_event_output<float> ("Mu_pt");
  h_Mu_eta = ctx.declare_event_output<float> ("Mu_eta");
  h_Mu_phi = ctx.declare_event_output<float> ("Mu_phi");
  h_Mu_E = ctx.declare_event_output<float> ("Mu_E");

///  ELECTRONS
  h_Ele_pt = ctx.declare_event_output<float> ("Ele_pt");
  h_Ele_eta = ctx.declare_event_output<float> ("Ele_eta");
  h_Ele_phi = ctx.declare_event_output<float> ("Ele_phi");
  h_Ele_E = ctx.declare_event_output<float> ("Ele_E");
  */

///  Leptons
  h_Lep_pt = ctx.declare_event_output<float> ("Lep_pt");
  h_Lep_eta = ctx.declare_event_output<float> ("Lep_eta");
  h_Lep_phi = ctx.declare_event_output<float> ("Lep_phi");
  h_Lep_E = ctx.declare_event_output<float> ("Lep_E");


///  MET
  h_MET_pt = ctx.declare_event_output<float> ("MET_pt");
  h_MET_phi = ctx.declare_event_output<float> ("MET_phi");

///  AK4 JETS

  h_Ak4_j1_pt = ctx.declare_event_output<float> ("Ak4_j1_pt");
  h_Ak4_j1_eta = ctx.declare_event_output<float>("Ak4_j1_eta");
  h_Ak4_j1_phi = ctx.declare_event_output<float>("Ak4_j1_phi");
  h_Ak4_j1_E = ctx.declare_event_output<float>  ("Ak4_j1_E");
  h_Ak4_j1_m = ctx.declare_event_output<float>  ("Ak4_j1_m");
  h_Ak4_j1_deepjetbscore = ctx.declare_event_output<float>  ("Ak4_j1_deepjetbscore");

  h_Ak4_j2_pt = ctx.declare_event_output<float> ("Ak4_j2_pt");
  h_Ak4_j2_eta = ctx.declare_event_output<float>("Ak4_j2_eta");
  h_Ak4_j2_phi = ctx.declare_event_output<float>("Ak4_j2_phi");
  h_Ak4_j2_E = ctx.declare_event_output<float>  ("Ak4_j2_E");
  h_Ak4_j2_m = ctx.declare_event_output<float>  ("Ak4_j2_m");
  h_Ak4_j2_deepjetbscore = ctx.declare_event_output<float>  ("Ak4_j2_deepjetbscore");

  h_Ak4_j3_pt = ctx.declare_event_output<float> ("Ak4_j3_pt");
  h_Ak4_j3_eta = ctx.declare_event_output<float>("Ak4_j3_eta");
  h_Ak4_j3_phi = ctx.declare_event_output<float>("Ak4_j3_phi");
  h_Ak4_j3_E = ctx.declare_event_output<float>  ("Ak4_j3_E");
  h_Ak4_j3_m = ctx.declare_event_output<float>  ("Ak4_j3_m");
  h_Ak4_j3_deepjetbscore = ctx.declare_event_output<float>  ("Ak4_j3_deepjetbscore");

  h_Ak4_j4_pt = ctx.declare_event_output<float> ("Ak4_j4_pt");
  h_Ak4_j4_eta = ctx.declare_event_output<float>("Ak4_j4_eta");
  h_Ak4_j4_phi = ctx.declare_event_output<float>("Ak4_j4_phi");
  h_Ak4_j4_E = ctx.declare_event_output<float>  ("Ak4_j4_E");
  h_Ak4_j4_m = ctx.declare_event_output<float>  ("Ak4_j4_m");
  h_Ak4_j4_deepjetbscore = ctx.declare_event_output<float>  ("Ak4_j4_deepjetbscore");

  h_Ak4_j5_pt = ctx.declare_event_output<float> ("Ak4_j5_pt");
  h_Ak4_j5_eta = ctx.declare_event_output<float>("Ak4_j5_eta");
  h_Ak4_j5_phi = ctx.declare_event_output<float>("Ak4_j5_phi");
  h_Ak4_j5_E = ctx.declare_event_output<float>  ("Ak4_j5_E");
  h_Ak4_j5_m = ctx.declare_event_output<float>  ("Ak4_j5_m");
  h_Ak4_j5_deepjetbscore = ctx.declare_event_output<float>  ("Ak4_j5_deepjetbscore");

  h_Ak4_j6_pt = ctx.declare_event_output<float> ("Ak4_j6_pt");
  h_Ak4_j6_eta = ctx.declare_event_output<float>("Ak4_j6_eta");
  h_Ak4_j6_phi = ctx.declare_event_output<float>("Ak4_j6_phi");
  h_Ak4_j6_E = ctx.declare_event_output<float>  ("Ak4_j6_E");
  h_Ak4_j6_m = ctx.declare_event_output<float>  ("Ak4_j6_m");
  h_Ak4_j6_deepjetbscore = ctx.declare_event_output<float>  ("Ak4_j6_deepjetbscore");


///  Higgs masses
  h_MH_bb = ctx.declare_event_output<float> ("MH_bb");
  h_MH_WW = ctx.declare_event_output<float> ("MH_WW");


}

bool Variables_NN::process(uhh2::Event& evt){

  double weight = evt.weight;
  evt.set(h_eventweight, -10);
  evt.set(h_eventweight, weight);

  /*
/////////   MUONS
  evt.set(h_Mu_pt, -10);
  evt.set(h_Mu_eta,-10);
  evt.set(h_Mu_phi, -10);
  evt.set(h_Mu_E, -10);

  vector<Muon>* muons = evt.muons;
  int Nmuons = muons->size();

  for(int i=0; i<Nmuons; i++){
      evt.set(h_Mu_pt, muons->at(i).pt());
      evt.set(h_Mu_eta, muons->at(i).eta());
      evt.set(h_Mu_phi, muons->at(i).phi());
      evt.set(h_Mu_E, muons->at(i).energy());
  }


/////////   ELECTRONS
  evt.set(h_Ele_pt, -10);
  evt.set(h_Ele_eta, -10);
  evt.set(h_Ele_phi, -10);
  evt.set(h_Ele_E, -10);

  vector<Electron>* electrons = evt.electrons;
  int Nelectrons = electrons->size();

  for(int i=0; i<Nelectrons; i++){
      evt.set(h_Ele_pt, electrons->at(i).pt());
      evt.set(h_Ele_eta, electrons->at(i).eta());
      evt.set(h_Ele_phi, electrons->at(i).phi());
      evt.set(h_Ele_E, electrons->at(i).energy());
  }
  */
/////////   LEPTONS
  evt.set(h_Lep_pt, -10);
  evt.set(h_Lep_eta, -10);
  evt.set(h_Lep_phi, -10);
  evt.set(h_Lep_E, -10);

  vector<Electron>* electrons = evt.electrons;
  int Nelectrons = electrons->size();

  vector<Muon>* muons = evt.muons;
  int Nmuons = muons->size();

  LorentzVector lepton;

  if(evt.electrons->size() == 1 && evt.muons->size() == 0) {
    lepton = electrons->at(0).v4();
    for(int i=0; i<Nelectrons; i++){
      evt.set(h_Lep_pt, electrons->at(i).pt());
      evt.set(h_Lep_eta, electrons->at(i).eta());
      evt.set(h_Lep_phi, electrons->at(i).phi());
      evt.set(h_Lep_E, electrons->at(i).energy());
    }
  }
  else if(evt.muons->size() == 1 && evt.electrons->size() == 0) {
    lepton = muons->at(0).v4();
    for(int i=0; i<Nmuons; i++){
      evt.set(h_Lep_pt, muons->at(i).pt());
      evt.set(h_Lep_eta, muons->at(i).eta());
      evt.set(h_Lep_phi, muons->at(i).phi());
      evt.set(h_Lep_E, muons->at(i).energy());
    }
  }
  else throw runtime_error("In HHtoWWbbSemiLeptonicModules: region is neither srmu or srele");

/////////   MET
  evt.set(h_MET_pt, -10);
  evt.set(h_MET_phi, -10);

  evt.set(h_MET_pt, evt.met->pt());
  evt.set(h_MET_phi, evt.met->phi());


///////// AK4 JETS
  evt.set(h_N_Ak4, -10);

  evt.set(h_Ak4_j1_pt, -10);
  evt.set(h_Ak4_j1_eta, -10);
  evt.set(h_Ak4_j1_phi, -10);
  evt.set(h_Ak4_j1_E, -10);
  evt.set(h_Ak4_j1_m, -10);
  evt.set(h_Ak4_j1_deepjetbscore, -10);

  evt.set(h_Ak4_j2_pt, -10);
  evt.set(h_Ak4_j2_eta, -10);
  evt.set(h_Ak4_j2_phi, -10);
  evt.set(h_Ak4_j2_E, -10);
  evt.set(h_Ak4_j2_m, -10);
  evt.set(h_Ak4_j2_deepjetbscore, -10);

  evt.set(h_Ak4_j3_pt, -10);
  evt.set(h_Ak4_j3_eta, -10);
  evt.set(h_Ak4_j3_phi, -10);
  evt.set(h_Ak4_j3_E, -10);
  evt.set(h_Ak4_j3_m, -10);
  evt.set(h_Ak4_j3_deepjetbscore, -10);

  evt.set(h_Ak4_j4_pt, -10);
  evt.set(h_Ak4_j4_eta, -10);
  evt.set(h_Ak4_j4_phi, -10);
  evt.set(h_Ak4_j4_E, -10);
  evt.set(h_Ak4_j4_m, -10);
  evt.set(h_Ak4_j4_deepjetbscore, -10);

  evt.set(h_Ak4_j5_pt, -10);
  evt.set(h_Ak4_j5_eta, -10);
  evt.set(h_Ak4_j5_phi, -10);
  evt.set(h_Ak4_j5_E, -10);
  evt.set(h_Ak4_j5_m, -10);
  evt.set(h_Ak4_j5_deepjetbscore, -10);

  evt.set(h_Ak4_j6_pt, -10);
  evt.set(h_Ak4_j6_eta, -10);
  evt.set(h_Ak4_j6_phi, -10);
  evt.set(h_Ak4_j6_E, -10);
  evt.set(h_Ak4_j6_m, -10);
  evt.set(h_Ak4_j6_deepjetbscore, -10);


  vector<Jet>* Ak4jets = evt.jets;
  int NAk4jets = Ak4jets->size();
  evt.set(h_N_Ak4, NAk4jets);

  for(int i=0; i<NAk4jets; i++){
      if(i==0){
      evt.set(h_Ak4_j1_pt, Ak4jets->at(i).pt());
      evt.set(h_Ak4_j1_eta, Ak4jets->at(i).eta());
      evt.set(h_Ak4_j1_phi, Ak4jets->at(i).phi());
      evt.set(h_Ak4_j1_E, Ak4jets->at(i).energy());
      evt.set(h_Ak4_j1_m, Ak4jets->at(i).v4().M());
      evt.set(h_Ak4_j1_deepjetbscore, Ak4jets->at(i).btag_DeepJet());
      }
      if(i==1){
      evt.set(h_Ak4_j2_pt, Ak4jets->at(i).pt());
      evt.set(h_Ak4_j2_eta, Ak4jets->at(i).eta());
      evt.set(h_Ak4_j2_phi, Ak4jets->at(i).phi());
      evt.set(h_Ak4_j2_E, Ak4jets->at(i).energy());
      evt.set(h_Ak4_j2_m, Ak4jets->at(i).v4().M());
      evt.set(h_Ak4_j2_deepjetbscore, Ak4jets->at(i).btag_DeepJet());
      }
      if(i==2){
      evt.set(h_Ak4_j3_pt, Ak4jets->at(i).pt());
      evt.set(h_Ak4_j3_eta, Ak4jets->at(i).eta());
      evt.set(h_Ak4_j3_phi, Ak4jets->at(i).phi());
      evt.set(h_Ak4_j3_E, Ak4jets->at(i).energy());
      evt.set(h_Ak4_j3_m, Ak4jets->at(i).v4().M());
      evt.set(h_Ak4_j3_deepjetbscore, Ak4jets->at(i).btag_DeepJet());
      }
      if(i==3){
      evt.set(h_Ak4_j4_pt, Ak4jets->at(i).pt());
      evt.set(h_Ak4_j4_eta, Ak4jets->at(i).eta());
      evt.set(h_Ak4_j4_phi, Ak4jets->at(i).phi());
      evt.set(h_Ak4_j4_E, Ak4jets->at(i).energy());
      evt.set(h_Ak4_j4_m, Ak4jets->at(i).v4().M());
      evt.set(h_Ak4_j4_deepjetbscore, Ak4jets->at(i).btag_DeepJet());
      }
      if(i==4){
      evt.set(h_Ak4_j5_pt, Ak4jets->at(i).pt());
      evt.set(h_Ak4_j5_eta, Ak4jets->at(i).eta());
      evt.set(h_Ak4_j5_phi, Ak4jets->at(i).phi());
      evt.set(h_Ak4_j5_E, Ak4jets->at(i).energy());
      evt.set(h_Ak4_j5_m, Ak4jets->at(i).v4().M());
      evt.set(h_Ak4_j5_deepjetbscore, Ak4jets->at(i).btag_DeepJet());
      }
      if(i==5){
      evt.set(h_Ak4_j6_pt, Ak4jets->at(i).pt());
      evt.set(h_Ak4_j6_eta, Ak4jets->at(i).eta());
      evt.set(h_Ak4_j6_phi, Ak4jets->at(i).phi());
      evt.set(h_Ak4_j6_E, Ak4jets->at(i).energy());
      evt.set(h_Ak4_j6_m, Ak4jets->at(i).v4().M());
      evt.set(h_Ak4_j6_deepjetbscore, Ak4jets->at(i).btag_DeepJet());
      }
  }


  // high-level observables

  evt.set(h_mbb, -10);
  evt.set(h_mlnu, -10);
  evt.set(h_DeltaRlnu, -10);
  evt.set(h_DeltaRbb, -10);
  evt.set(h_minDeltaRlj, -10);
  evt.set(h_minDeltaRbj, -10);
  evt.set(h_minDeltaRjj, -10);
  evt.set(h_HT, -10);
  evt.set(h_N_BTag, -10);


  //Jet & j = Ak4jets->at(0);
  // double dR = deltaR(j, lepton);

  //double dR = minDeltaR(Ak4jets, lepton);
  //evt.set(h_minDeltaRlj, minDeltaR(Ak4jets, lepton));
  
  /*
  for(unsigned int i =0; i<Ak4jets->size(); i++) {
    if(DeepjetMedium(jets->at(i),event)) {
      //bjets->push_back(jets->at(i));
      Ndeepjet_med++;
      if(Ndeepjet_med == 1) b1 =jets->at(i);
      if(Ndeepjet_med == 2) b2 =jets->at(i);
    }

  }
  */
  // Higgs mass
  evt.set(h_MH_bb, -10);
  evt.set(h_MH_WW, -10);
  bool is_mHH_reconstructed = evt.get(h_is_mHH_reconstructed);
  if(is_mHH_reconstructed){
    float mass_bb = evt.get(h_mH_bb);
    float mass_WW = evt.get(h_mH_WW);
    evt.set(h_MH_bb, mass_bb);
    evt.set(h_MH_WW, mass_WW);
  }



  return true;
}
