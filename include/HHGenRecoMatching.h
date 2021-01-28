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

class HHGenRecoMatching {
 public:
  HHGenRecoMatching(const vector<Jet> & jets, const HHGenObjects & HHgen, bool throw_on_failure = true);
  /*
  vector<Jet> JetMatching(const GenParticle gp);
  vector<Jet> B1_jets() const;
  vector<Jet> B2_jets() const;
  */

  Jet JetMatching(const vector<Jet> & jets, GenParticle gp) const;
  Jet B1_jet() const;
  Jet B2_jet() const;
  Jet Q1_jet() const;
  Jet Q2_jet() const;

 private:

  GenParticle B1_gen;
  GenParticle B2_gen;
  GenParticle Q1_gen;
  GenParticle Q2_gen;

  Jet b1;
  Jet b2;
  Jet q1;
  Jet q2;

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
