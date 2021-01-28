#pragma once

#include "UHH2/core/include/Hists.h"
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
};

}
