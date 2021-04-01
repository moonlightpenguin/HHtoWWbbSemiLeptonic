#pragma once

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesis.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/Functions.h"
#include "UHH2/core/include/Event.h"


class HHtoWWbbMassReconstruction: public uhh2::AnalysisModule {
 public:


  explicit HHtoWWbbMassReconstruction(uhh2::Context & ctx);

  virtual bool process(uhh2::Event & event) override;

  virtual ~HHtoWWbbMassReconstruction();

 private:
  uhh2::Event::Handle<bool> h_is_mHH_reconstructed;
  uhh2::Event::Handle<std::vector<HHReconstructionHypothesis>> h_recohyps;
};

