#pragma once

#include "UHH2/core/include/Hists.h"

namespace uhh2examples {

/**  \brief Example class for booking and filling histograms
 * 
 * NOTE: This class uses the 'hist' method to retrieve histograms.
 * This requires a string lookup and is therefore slow if you have
 * many histograms. Therefore, it is recommended to use histogram
 * pointers as member data instead, like in 'common/include/ElectronHists.h'.
 */
class HHtoWWbbSemiLeptonicGenHists: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
    HHtoWWbbSemiLeptonicGenHists(uhh2::Context & ctx, const std::string & dirname);

    virtual void fill(const uhh2::Event & ev) override;
    virtual bool isQuark(int id);
    virtual bool isLepton(int id);
    virtual bool isChargedLepton(int id);
    virtual bool isNeutrino(int id);

    virtual ~HHtoWWbbSemiLeptonicGenHists();

 protected:
    TH2F* pt_W1_vs_pt_W2, *M_W1_vs_M_W2, *deltaR_WW_vs_pt_W1; //W
    TH2F* pt_b1_vs_pt_b2, *M_b1_vs_M_b2, *deltaR_bb_vs_pt_b1; //b
    TH2F* pt_H_W_vs_pt_H_b, *M_H_W_vs_M_H_b, *deltaR_HH_vs_pt_H_W; //Higgs
    TH2F* pt_q1_vs_pt_q2, *eta_q1_vs_eta_q2; //quarks

};

}
