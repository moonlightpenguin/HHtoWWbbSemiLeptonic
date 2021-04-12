
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenRecoMatching.h"

using namespace uhh2;
using namespace std;



HHGenRecoMatching::HHGenRecoMatching(const vector<Jet> & jets, const LorentzVector & lepton, const LorentzVector & met, const HHGenObjects & HHgen, bool throw_on_failure) {
  //cout << "HHGenRecoMatching: start" << endl;
    
  B1_gen = HHgen.B1();
  B2_gen = HHgen.B2();
  Q1_gen = HHgen.Q1();
  Q2_gen = HHgen.Q2();
  L_gen = HHgen.ChargedLepton().v4();
  N_gen = HHgen.Neutrino().v4();

  b1_match = JetMatching(jets, B1_gen);
  b2_match = JetMatching(jets, B2_gen);
  q1_match = JetMatching(jets, Q1_gen);
  q2_match = JetMatching(jets, Q2_gen);



  l_match = LeptonMatching(lepton, L_gen);
  n_match = LeptonMatching(met, N_gen);

}


HHMatchedJets HHGenRecoMatching::JetMatching(const vector<Jet> & jets, const GenParticle gp) const{
  HHMatchedJets output;
  double dR_max = 0.4;
  double dR_min = 999;
  Jet matchedJet;
  vector<Jet> matchedJets;
  output.matched = false;
  int jet_index=-1;
  for(unsigned int i=0; i<jets.size(); i++) {
    double dR = deltaR(jets[i], gp);
    if(dR < dR_max) {
      matchedJets.push_back(jets[i]);
      if(dR < dR_min) {
	matchedJet = jets[i];
	dR_min = dR;
	jet_index = i+1; // oder nur i ?
      }
      output.matched = true;
    }
  }
  output.mainJet = matchedJet;
  output.allJets = matchedJets;
  output.dR_JetGen = dR_min;
  output.gen = gp.v4();
  output.jet_index = jet_index;

  return output;
}

HHMatchedLepton HHGenRecoMatching::LeptonMatching(const LorentzVector & lepton, LorentzVector gp) const{
  HHMatchedLepton output;
  double dR_max = 0.4;
  output.matched = false;
  double dR = deltaR(lepton,gp);
  if(dR < dR_max) output.matched = true;
  output.lepton = lepton;
  output.gen = gp;
  output.dR_LepGen = dR;
  return output;
}


HHMatchedJets HHGenRecoMatching::B1_jets() const{
  return b1_match;
}
HHMatchedJets HHGenRecoMatching::B2_jets() const{
  return b2_match;
}
HHMatchedJets HHGenRecoMatching::Q1_jets() const{
  return q1_match;
}
HHMatchedJets HHGenRecoMatching::Q2_jets() const{
  return q2_match;
}
HHMatchedLepton HHGenRecoMatching::Lepton() const{
  return l_match;
}
HHMatchedLepton HHGenRecoMatching::Neutrino() const{
  return n_match;
}








HHGenRecoProducer::HHGenRecoProducer(uhh2::Context & ctx, const std::string & name, bool throw_on_failure): throw_on_failure(throw_on_failure) {
  h_HHgenrecomatching = ctx.get_handle<HHGenRecoMatching>(name);
  h_HHgenobjects = ctx.get_handle<HHGenObjects>("HHgenobjects");

}



bool HHGenRecoProducer::process(Event & event) {
  const HHGenObjects & HHgen = event.get(h_HHgenobjects);
  const LorentzVector & met = event.met->v4();

  if(event.muons->size() == 1) {
    const LorentzVector & mu = event.muons->at(0).v4();
    event.set(h_HHgenrecomatching, HHGenRecoMatching(*event.jets, mu, met, HHgen, throw_on_failure));
  }
  else if (event.electrons->size() == 1) {
    const LorentzVector & ele = event.electrons->at(0).v4();
    event.set(h_HHgenrecomatching, HHGenRecoMatching(*event.jets, ele, met, HHgen, throw_on_failure));
  }
  else throw runtime_error("In HHGenRecoMatching: neither srmu nor srele");
  return true;
}
