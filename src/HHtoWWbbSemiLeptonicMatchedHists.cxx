#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicMatchedHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/common/include/JetIds.h"
#include <math.h>

#include "TH1F.h"
#include "TH2F.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

HHtoWWbbSemiLeptonicMatchedHists::HHtoWWbbSemiLeptonicMatchedHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  // get GenRecoMatching
  h_HHgenreco = ctx.get_handle<HHGenRecoMatching>("HHgenreco");

  // book all histograms here

  // Higgs
  book<TH1F>("M_H_b_reco", "M^{Higgs} [GeV] decaying to b (reco)", 50, 0, 300);

  // b's
  book<TH1F>("pt_b1", "p_{T}^{b1} [GeV]", 50, 0, 500);
  book<TH1F>("pt_b2", "p_{T}^{b2} [GeV]", 50, 0, 500);
  book<TH1F>("pt_b", "p_{T}^{b} [GeV]", 50, 0, 500);
  book<TH1F>("eta_b", "#eta^{b} [GeV]", 50, -2.5, 2.5);
  book<TH1F>("deltaR bb", "#Delta R between two b's", 50, 0, 5);
  book<TH1F>("deltaPhi bb", "#Delta #Phi between two b's", 50, 0, 3.2);
  book<TH1F>("deltaEta bb", "#Delta #eta between two b's", 50, -5, 5);

  book<TH1F>("M_b1", "M^{b1} [GeV]", 50, 0, 10);
  book<TH1F>("M_b2", "M^{b2} [GeV]", 50, 0, 10);

  pt_b1_vs_pt_b2 = book<TH2F>("pt_b1 vs pt_b2", "p_{T}^{b1} [GeV] vs p_{T}^{b2} [GeV]", 50, 0, 500, 50, 0, 500);
  M_b1_vs_M_b2 = book<TH2F>("M_b1 vs M_b2", "M^{b1} [GeV] vs M^{b2} [GeV]", 50, 4.6, 5.2, 50, 4.6, 5.2);
  deltaR_bb_vs_pt_b1 = book<TH2F>("deltaR_bb vs pt_b1", "#Delta R^{bb} vs p_{T}^{b1} [GeV]", 50, 0, 5, 50, 0, 500);





}


void HHtoWWbbSemiLeptonicMatchedHists::fill(const Event & event){
  cout << "MatchedHists: fill" << endl;
  // Don't forget to always use the weight when filling.
  
  double weight = event.weight;
  const auto & HHgenreco = event.get(h_HHgenreco);
  cout << "Line: " << __LINE__ << endl;
   
  Jet b1 = HHgenreco.B1_jet();
  Jet b2 = HHgenreco.B2_jet();


  LorentzVector B1 = b1.v4();
  LorentzVector B2 = b2.v4();

  // LorentzVector B1 = HHgenreco.B1_jet().v4();
  // LorentzVector B2 = HHgenreco.B2_jet().v4();


  // Higgs
  hist("M_H_b_reco")->Fill((B1+B2).M(), weight);


  // bottom quarks
  hist("pt_b")->Fill(B1.pt(),weight);
  hist("pt_b")->Fill(B2.pt(),weight);
  hist("pt_b1")->Fill(B1.pt(),weight);
  hist("pt_b2")->Fill(B2.pt(),weight);

  hist("eta_b")->Fill(B1.eta(),weight);
  hist("eta_b")->Fill(B2.eta(),weight);

  hist("M_b1")->Fill(B1.M(), weight);
  hist("M_b2")->Fill(B2.M(), weight);

  M_b1_vs_M_b2->Fill(B1.M(), B2.M(), weight);
  pt_b1_vs_pt_b2->Fill(B1.pt(), B2.pt(), weight);

  double dr_B = deltaR(B1,B2);
  double dphi_B = deltaPhi(B1,B2);
  double deta_B = B1.eta() - B2.eta();

  deltaR_bb_vs_pt_b1->Fill(dr_B, B1.pt(), weight);
  hist("deltaR bb")->Fill(dr_B, weight);
  hist("deltaPhi bb")->Fill(dphi_B, weight);	
  hist("deltaEta bb")->Fill(deta_B, weight);

  

}


HHtoWWbbSemiLeptonicMatchedHists::~HHtoWWbbSemiLeptonicMatchedHists(){}
