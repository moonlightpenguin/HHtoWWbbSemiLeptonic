
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenRecoMatching.h"

using namespace uhh2;
using namespace std;



HHGenRecoMatching::HHGenRecoMatching(const vector<Jet> & jets, const HHGenObjects & HHgen, bool throw_on_failure) {
  //cout << "HHGenRecoMatching: start" << endl;
    
  B1_gen = HHgen.B1();
  B2_gen = HHgen.B2();
  Q1_gen = HHgen.Q1();
  Q2_gen = HHgen.Q2();

  b1 = JetMatching(jets, B1_gen);
  b2 = JetMatching(jets, B2_gen);

}

// what happens when there is no jet inside dR_max ? -> pt=0
Jet HHGenRecoMatching::JetMatching(const vector<Jet> & jets, GenParticle gp) const{
  //cout << "JetMatching: start" << endl;
  double dR_max = 0.4;
  double dR_min = 999;
  Jet matchedJet;
  for(unsigned int i=0; i<jets.size(); i++) {
    double dR = deltaR(jets[i], gp);
    if((dR < dR_max) && (dR < dR_min)) {
      matchedJet = jets[i];
      dR_min = dR;
    }
  }
  cout << "pt matched Jet: " << matchedJet.pt() << endl;
  return matchedJet;
}


Jet HHGenRecoMatching::B1_jet() const{
  return b1;
}
Jet HHGenRecoMatching::B2_jet() const{
  return b2;
}
Jet HHGenRecoMatching::Q1_jet() const{
  return q1;
}
Jet HHGenRecoMatching::Q2_jet() const{
  return q2;
}




/*
vector<Jet> HHGenRecoMatching::JetMatching(const GenParticle gp) {
  double dR_max = 0.4;
  double dR_min = 999;
  vector<Jet> matchedJets;
  for(unsigned int i=0; i<recoJets.size(); i++) {
    double dR = deltaR(recoJets[i], gp);
      if(dR < dR_max) {
	matchedJets.push_back(recoJets[i]);
      }
  }
  // sort by dR
  return matchedJets;
}


vector<Jet> HHGenRecoMatching::B1_jets() const {
  return JetMatching(B1_gen);
}

*/



HHGenRecoProducer::HHGenRecoProducer(uhh2::Context & ctx, const std::string & name, bool throw_on_failure): throw_on_failure(throw_on_failure) {
  h_HHgenrecomatching = ctx.get_handle<HHGenRecoMatching>(name);
  h_HHgenobjects = ctx.get_handle<HHGenObjects>("HHgenobjects");

}



bool HHGenRecoProducer::process(Event & event) {
  const HHGenObjects & HHgen = event.get(h_HHgenobjects);

  event.set(h_HHgenrecomatching, HHGenRecoMatching(*event.jets, HHgen, throw_on_failure));
  return true;
}
