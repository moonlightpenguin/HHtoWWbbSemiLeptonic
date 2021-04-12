#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesisDiscriminators.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesis.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenRecoMatching.h"

namespace uhh2examples {

  class HHtoWWbbSemiLeptonicMatchedHists: public uhh2::Hists {
  public:
    // use the same constructor arguments as Hists for forwarding:
    HHtoWWbbSemiLeptonicMatchedHists(uhh2::Context & ctx, const std::string & dirname);

    virtual void fill(const uhh2::Event & ev) override;
    virtual ~HHtoWWbbSemiLeptonicMatchedHists();

  protected:

    uhh2::Event::Handle<HHGenRecoMatching> h_HHgenreco;
    
    TH2F* pt_b1_vs_pt_b2, *M_b1_vs_M_b2, *deltaR_bb_vs_pt_b1; //b

    TH2F* pt_WLep_vs_pt_WHad, *M_WLep_vs_M_WHad; //W

    TH2F* pt_H1_vs_pt_H2, *M_H1_vs_M_H2;

    TH1F* b1_correct_chi2, *b2_correct_chi2, *b1_correct_highestPt, *b2_correct_highestPt, *q1_correct_chi2, *q2_correct_chi2, *q1_correct_highestPt, *q2_correct_highestPt, *q1_correct_lowestPt, *q2_correct_lowestPt;
      TH1F* Hbb_correct_chi2, *Hbb_correct_highestPt, *WHad_correct_chi2, *WHad_correct_highestPt, *WHad_correct_lowestPt;
    
    uhh2::Event::Handle<bool> h_is_mHH_reconstructed;
    uhh2::Event::Handle<float> h_mH_bb;
    uhh2::Event::Handle<float> h_mH_WW;

    uhh2::Event::Handle<int> h_b1_index, h_b2_index, h_q1_index, h_q2_index;

  };


}
