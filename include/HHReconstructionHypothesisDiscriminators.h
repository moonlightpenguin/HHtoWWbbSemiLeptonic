#pragma once
#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"

#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesis.h"
//#include "UHH2/common/include/TTbarGen.h"
//#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGen.h"

const HHReconstructionHypothesis * get_best_hypothesis(const std::vector<HHReconstructionHypothesis> & hyps, const std::string & label);

class HHChi2Discriminator: public uhh2::AnalysisModule {
public:
    struct cfg {
        std::string discriminator_label;
        cfg(): discriminator_label("Chi2"){}
    };

    HHChi2Discriminator(uhh2::Context & ctx, const std::string & rechyps_name="HHHypotheses", const cfg & config = cfg());
    virtual bool process(uhh2::Event & event) override;

private:
  uhh2::Event::Handle<std::vector<HHReconstructionHypothesis>> h_hyps;
  uhh2::Event::Handle<bool> h_is_mHH_reconstructed;
  uhh2::Event::Handle<float> h_mH_mean, h_mH_bb, h_mH_WW;
  uhh2::Event::Handle<float> h_chi2_H_bb, h_chi2_H_WW;
  uhh2::Event::Handle<float> h_mHH, h_chi2;
  cfg config;
};
