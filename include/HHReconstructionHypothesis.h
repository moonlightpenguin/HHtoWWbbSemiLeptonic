#pragma once
#include "UHH2/core/include/Particle.h"
#include <map>


class HHReconstructionHypothesis {
 public:
  LorentzVector H_bb_v4() const{return m_H_bb_v4;}


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

  void set_discriminator(const std::string & label, float discr){
      m_discriminators[label] = discr;
  }


 private:
  LorentzVector m_H_bb_v4;


  std::map<std::string, float> m_discriminators;
};
