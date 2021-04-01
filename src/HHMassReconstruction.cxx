
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHMassReconstruction.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/Functions.h"
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
  vector<Jet> bjets;
  vector<Jet> lightjets; // == non-btagged jets

  vector<int> bjet_index; // for reco efficiency
  vector<int> lightjet_index; // for reco efficiency

  JetId DeepjetMedium = BTag(BTag::DEEPJET, BTag::WP_MEDIUM);
  
  LorentzVector lepton;
  if(event.muons->size() == 1) lepton = event.muons->at(0).v4();
  else if(event.electrons->size() == 1) lepton = event.electrons->at(0).v4();
  else throw runtime_error("HHMassReconstruction: no lepton or more than one leptons");  
  LorentzVector neutrino = event.met->v4();
  LorentzVector WLep = lepton + neutrino;
  double MT_WLep = TransverseMass(lepton,neutrino,0,0);

  for(int i=0; i<Njets; i++){
    if(DeepjetMedium(jets->at(i),event)){
      Ndeepjet_med++;
      bjets.push_back(event.jets->at(i));
      bjet_index.push_back(i+1); // starting at 1
    }
    else {
      lightjets.push_back(event.jets->at(i));
      lightjet_index.push_back(i+1); // starting at 1

    }
  }
  if(Ndeepjet_med<2) return false; // for now only events with min 2 bjets
  //cout << "Number of bjets: " << Ndeepjet_med << endl;
  if(lightjets.size()<2) return false; // for H->WW we also need min 2 jets -> implement different categories?


  // WHad hypothesis
  for(unsigned int i=0; i<lightjets.size()-1; i++) {
    for(unsigned int j=1; j<lightjets.size(); j++) {
      if(i < j) {
	LorentzVector WHad = lightjets[i].v4()+lightjets[j].v4();
	double MT_WHad = TransverseMass(lightjets[i].v4(),lightjets[j].v4(),0,0);
	double MT_H_WW = TransverseMass(WHad,WLep, MT_WHad, MT_WLep);

	// bb hypothesis
	for(int k=0; k<Ndeepjet_med-1; k++) {
	  for(int l=1; l<Ndeepjet_med; l++) {
	    if(k < l) {
	      LorentzVector H_bb = bjets[k].v4()+bjets[l].v4();
	      double MT_H_bb = TransverseMass(bjets[k].v4(),bjets[l].v4(),4.8,4.8); // true b mass on gen level == 4.8 GeV
	      double MT_HH = TransverseMass(WHad+WLep,bjets[k].v4()+bjets[l].v4(),MT_H_WW,MT_H_bb);
	      HHReconstructionHypothesis hyp;
	      hyp.set_H_bb_v4(H_bb);
	      hyp.set_MT_WW(MT_H_WW);
	      hyp.set_MT_HH(MT_HH);
	      hyp.set_b1_index(bjet_index[k]); // pt_b1>pt_b2
	      hyp.set_b2_index(bjet_index[l]);
	      hyp.set_q1_index(lightjet_index[i]); // pt_q1>pt_q2
	      hyp.set_q2_index(lightjet_index[j]);
	      /*
	      hyp.set_Lepton_v4(lepton);
	      hyp.set_Neutrino_v4(neutrino);
	      hyp.set_Q1_v4(lightjets[i].v4());
	      hyp.set_Q2_v4(lightjets[j].v4());
	      hyp.set_WLep_v4(WLep);
	      hyp.set_WHad_v4(WHad);
	      */
	      recoHyps.emplace_back(move(hyp)); // only once
	    }
	  }
	}
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
