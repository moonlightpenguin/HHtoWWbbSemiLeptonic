#pragma once

#include "UHH2/core/include/GenParticle.h"
#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenObjects.h"
#include "UHH2/common/include/Utils.h"
#include <vector>
#include <math.h>


using namespace uhh2;
using namespace std;

struct HHMatchedJets {
  // just return LorentzVectors instead of jets? -> difference between classes?
  bool matched;
  Jet mainJet;
  vector<Jet> allJets; // should be pt sorted
  double dR_JetGen;
  LorentzVector gen;
  // LorentzVector gen;
  int jet_index;
};

struct HHMatchedLepton {
  bool matched;
  LorentzVector lepton;
  LorentzVector gen;
  double dR_LepGen;
};

class HHGenRecoMatching {
 public:
  HHGenRecoMatching(const vector<Jet> & jets, const LorentzVector & lepton, const LorentzVector & met, const HHGenObjects & HHgen, bool throw_on_failure = true);

  HHMatchedJets JetMatching(const vector<Jet> & jets, GenParticle gp) const;
  HHMatchedLepton LeptonMatching(const LorentzVector & lepton, LorentzVector gp) const;


  HHMatchedJets B1_jets() const;
  HHMatchedJets B2_jets() const;
  HHMatchedJets Q1_jets() const;
  HHMatchedJets Q2_jets() const;
  HHMatchedLepton Lepton() const;
  HHMatchedLepton Neutrino() const;


 private:
  GenParticle B1_gen;
  GenParticle B2_gen;
  GenParticle Q1_gen;
  GenParticle Q2_gen;
  LorentzVector L_gen;
  LorentzVector N_gen;

  HHMatchedJets b1_match;
  HHMatchedJets b2_match;
  HHMatchedJets q1_match;
  HHMatchedJets q2_match;
  HHMatchedLepton l_match;
  HHMatchedLepton n_match;
};



class HHGenRecoProducer: public uhh2::AnalysisModule {
 public:
  explicit HHGenRecoProducer(uhh2::Context & ctx, const std::string & name = "HHgenreco", bool throw_on_failure=true);
  virtual bool process(uhh2::Event & event) override;



 private: 
  uhh2::Event::Handle<HHGenRecoMatching> h_HHgenrecomatching;

  uhh2::Event::Handle<HHGenObjects> h_HHgenobjects;

  bool throw_on_failure;
};
