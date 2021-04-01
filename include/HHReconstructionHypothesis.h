#pragma once
#include "UHH2/core/include/Particle.h"
#include <map>

class HHReconstructionHypothesis {
 public:
  LorentzVector H_bb_v4() const{return m_H_bb_v4;}
  double MT_WW() const{return m_MT_WW;}
  double MT_HH() const{return m_MT_HH;}
  int b1_index() const{return m_b1_index;}
  int b2_index() const{return m_b2_index;}
  int q1_index() const{return m_q1_index;}
  int q2_index() const{return m_q2_index;}

  /*
  LorentzVector Lepton_v4() const{return m_Lepton_v4};
  LorentzVector Neutrino_v4() const{return m_Neutrino_v4};
  LorentzVector Q1_v4() const{return m_Q1_v4};
  LorentzVector Q2_v4() const{return m_Q2_v4};
  LorentzVector WHad_v4() const{return m_WHad_v4;}
  LorentzVector WLep_v4() const{return m_WLep_v4;}
  */

  /// get the discriminator value for this hypothesis; thows a runtime_error if it does not exist.
  float discriminator(const std::string & l) const {
    auto it = m_discriminators.find(l);
    if(it == m_discriminators.end()){
      throw std::runtime_error("HHReconstructionHypothesis::discriminator: discriminator with label '" + l + "' not set");
    }
    return it->second;
  }

  /// test if a discriminator value with a certian label has already been added
  bool has_discriminator(const std::string & label) const {
    return m_discriminators.find(label) != m_discriminators.end();
  }



  void set_H_bb_v4(LorentzVector v4){m_H_bb_v4=v4;}
  void set_MT_WW(double mt){m_MT_WW=mt;}
  void set_MT_HH(double mt){m_MT_HH=mt;}
  void set_b1_index(int index){m_b1_index=index;}
  void set_b2_index(int index){m_b2_index=index;}
  void set_q1_index(int index){m_q1_index=index;}
  void set_q2_index(int index){m_q2_index=index;}

  /*
  void set_Lepton_v4(LorentzVector v4){m_Lepton_v4=v4;}
  void set_Neutrino_v4(LorentzVector v4){m_Neutrino_v4=v4;}
  void set_Q1_v4(LorentzVector v4){m_Q1_v4=v4;}
  void set_Q2_v4(LorentzVector v4){m_Q2_v4=v4;}
  void set_WHad_v4(LorentzVector v4){m_WHad_v4=v4;}
  void set_WLep_v4(LorentzVector v4){m_WLep_v4=v4;}
  */


  void set_discriminator(const std::string & label, float discr){
      m_discriminators[label] = discr;
  }


 private:
  LorentzVector m_H_bb_v4;
  double m_MT_WW;
  double m_MT_HH;
  int m_b1_index;
  int m_b2_index;
  int m_q1_index;
  int m_q2_index;
  /*
  LorentzVector m_Lepton_v4;
  LorentzVector m_Neutrino_v4;
  LorentzVector m_Q1_v4;
  LorentzVector m_Q2_v4;
  LorentzVector m_WHad_v4;
  LorentzVector m_WLep_v4;
  */

  std::map<std::string, float> m_discriminators;
};
