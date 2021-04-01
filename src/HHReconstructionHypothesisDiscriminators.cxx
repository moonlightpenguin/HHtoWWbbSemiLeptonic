#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesisDiscriminators.h"
#include "UHH2/core/include/Utils.h"
#include <set>

using namespace uhh2;
using namespace std;

// invariant mass of a lorentzVector, but save for timelike / spacelike vectors
float inv_mass(const LorentzVector & p4) {
  if(p4.isTimelike()) {
    return p4.mass();
  }
  else {
    return -sqrt(-p4.mass2());
  }
}


const HHReconstructionHypothesis * get_best_hypothesis(const std::vector<HHReconstructionHypothesis> & hyps, const std::string & label) {
  //cout << "get_best_hypothesis: start" << endl;
  const HHReconstructionHypothesis * best = nullptr;
  float current_best_disc = numeric_limits<float>::infinity();
  for(const auto & hyp : hyps){
    if(!hyp.has_discriminator(label)) continue;

    auto disc = hyp.discriminator(label);
    if(disc < current_best_disc){
      best = &hyp;
      current_best_disc = disc;
    }
  }
  //cout << "best disc: " << current_best_disc << endl;
  if(std::isfinite(current_best_disc)){
    return best;
  }
  else{
    return nullptr;
  }

}


HHChi2Discriminator::HHChi2Discriminator(Context & ctx, const std::string & rechyps_name, const cfg & config_): config(config_) {
  //cout << "HHChi2Discriminator: constructor" << endl;
  h_hyps = ctx.get_handle<vector<HHReconstructionHypothesis>>(rechyps_name); //
  h_is_mHH_reconstructed = ctx.get_handle<bool>("is_mHH_reconstructed");
  h_mHH = ctx.get_handle<float>("mHH");
  h_chi2 = ctx.get_handle<float>("chi2");

  h_mH_bb = ctx.get_handle<float>("mH_bb");
  h_chi2_H_bb = ctx.get_handle<float>("chi2_H_bb");

  h_mH_WW = ctx.get_handle<float>("mH_WW");
  h_chi2_H_WW = ctx.get_handle<float>("chi2_H_WW");

  h_b1_index = ctx.get_handle<int>("b1_index");
  h_b2_index = ctx.get_handle<int>("b2_index");
  h_q1_index = ctx.get_handle<int>("q1_index");
  h_q2_index = ctx.get_handle<int>("q2_index");

}



bool HHChi2Discriminator::process(uhh2::Event & event) {
  //cout << "HHChi2Discriminator: process" << endl;
  bool is_mHH_reconstructed = event.get(h_is_mHH_reconstructed);
  if (!is_mHH_reconstructed) return false;
  auto & hyps = event.get(h_hyps); // get vector of hypotheses from event

  const double mass_H_bb = 111.7; // from gauss fit to matched result
  const double mass_H_bb_sigma = 18.3; // from gauss fit to matched result
  const double mass_H_WW = 124; // MT, gauss fit
  const double mass_H_WW_sigma = 44.7; // MT, gauss fit


  for(auto & hyp: hyps){ // loop over hypothesis vector
    //cout << inv_mass(hyp.H_bb_v4()) << endl;
    //cout << hyp.MT_WW() << endl;

    double mass_H_bb_reco = inv_mass(hyp.H_bb_v4());
    double mass_H_WW_reco = hyp.MT_WW();
    //double mass_H_mean_reco = (mass_H_bb_reco - mass_H_WW_reco)/2;
    
    //double mass_HH_reco = hyp.MT_HH();


    double chi2_H_bb = pow((mass_H_bb_reco - mass_H_bb) / mass_H_bb_sigma, 2);
    double chi2_H_WW = pow((mass_H_WW_reco - mass_H_WW) / mass_H_WW_sigma, 2);
    //double chi2_mH_diff_rel = pow( ((mass_H_bb_reco - mass_H_WW_reco)/mass_H_mean_reco - mass_H_diff_rel) / mass_H_diff_rel_sigma  , 2);


    hyp.set_discriminator(config.discriminator_label + "_H_bb", chi2_H_bb);
    hyp.set_discriminator(config.discriminator_label + "_H_WW", chi2_H_WW);
    //hyp.set_discriminator(config.discriminator_label + "_mHdiff_rel", chi2_mH_diff_rel);
    hyp.set_discriminator(config.discriminator_label, chi2_H_bb + chi2_H_WW);


  }


  // const HHReconstructionHypothesis* hyp = get_best_hypothesis( hyps, "Chi2_H_bb" );
  //const HHReconstructionHypothesis* hyp = get_best_hypothesis( hyps, "Chi2_H_WW" );
  const HHReconstructionHypothesis* hyp = get_best_hypothesis( hyps, "Chi2" );

 
  double chi2_H_bb = hyp->discriminator("Chi2_H_bb");
  double chi2_H_WW = hyp->discriminator("Chi2_H_WW");
  double chi2 = hyp->discriminator("Chi2");
  double mH_bb_reco = 0;
  double mH_WW_reco = 0;
  double mHH_reco = 0;


  mH_bb_reco = hyp->H_bb_v4().M();
  mH_WW_reco = hyp->MT_WW();
  mHH_reco = hyp->MT_HH();
  /*
  cout << "mH_WW: " << mH_WW_reco << endl;
  cout << "mH_bb: " << mH_bb_reco << endl;
  cout << "mHH: " << mHH_reco << endl;
  */
  event.set(h_mH_bb, mH_bb_reco);
  event.set(h_chi2_H_bb, chi2_H_bb);
  event.set(h_mH_WW, mH_WW_reco);
  event.set(h_chi2_H_WW, chi2_H_WW);
  event.set(h_mHH, mHH_reco);
  event.set(h_chi2, chi2);

  event.set(h_b1_index, hyp->b1_index());
  event.set(h_b2_index, hyp->b2_index());

  event.set(h_q1_index, hyp->q1_index());
  event.set(h_q2_index, hyp->q2_index());

  return true;
}

