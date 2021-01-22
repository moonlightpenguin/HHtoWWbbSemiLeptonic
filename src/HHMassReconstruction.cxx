
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHMassReconstruction.h"
#include "UHH2/common/include/JetIds.h"

using namespace std;
using namespace uhh2;

HHtoWWbbMassReconstruction::HHtoWWbbMassReconstruction(Context & ctx) {

  h_recohyps = ctx.get_handle<vector<HHReconstructionHypothesis>>("HHHypotheses");
  h_is_mHH_reconstructed = ctx.get_handle<bool>("is_mHH_reconstructed");

}

HHtoWWbbMassReconstruction::~HHtoWWbbMassReconstruction() {}


bool HHtoWWbbMassReconstruction::process(uhh2::Event & event) {
  //cout << "Mass Reconstruction: start" << endl;
  
  vector<HHReconstructionHypothesis> recoHyps = {}; // save hyps here
  event.set(h_recohyps, recoHyps);
  event.set(h_is_mHH_reconstructed, false);

  vector<Jet>* jets = event.jets;
  int Njets = jets->size();
  int Ndeepjet_med=0;
  Jet b1;
  Jet b2;
  vector<Jet> bjets;
  JetId DeepjetMedium = BTag(BTag::DEEPJET, BTag::WP_MEDIUM);

  for(int i=0; i<Njets; i++){
    if(DeepjetMedium(jets->at(i),event)){
      Ndeepjet_med++;
      bjets.push_back(event.jets->at(i));
      if(Ndeepjet_med == 1) b1 = jets->at(i);
      if(Ndeepjet_med == 2) b2 = jets->at(i);
    }
  }
  if(Ndeepjet_med<2) return false; // for now only events with min 2 bjets
  //cout << "Number of bjets: " << Ndeepjet_med << endl;

  for(int i=0; i<Ndeepjet_med-1; i++) {
    for(int j=1; j<Ndeepjet_med; j++) {
      if(i < j) {
	HHReconstructionHypothesis hyp;
	LorentzVector H_bb;
	H_bb = bjets[i].v4()+bjets[j].v4();
	hyp.set_H_bb_v4(H_bb);
	//cout << H_bb.M() << endl;
	recoHyps.emplace_back(move(hyp));
      }
    }
  }
  //cout << "recoHyps size: " << recoHyps.size() << endl;
  // end loops here

  event.set(h_recohyps, move(recoHyps));
  event.set(h_is_mHH_reconstructed, true);
  //cout << "Mass Reconstruction: end" << endl;
  return true;
}
