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
  book<TH1F>("M_H_b_reco", "M_{bb}^{matched} [GeV]", 50, 0, 300);
  book<TH1F>("M_H_b_reco1", "M_{bb}^{matched} [GeV]", 40, 0, 200);
  book<TH1F>("M_H_W_reco", "M_{WW}^{mached} [GeV]", 50, 0, 300);
  book<TH1F>("M_H_W_semireco", "M_{WW}^{matched} [GeV] (semireco)", 50, 0, 300);
  book<TH1F>("MT_H_W_reco", "M_{T,WW}^{matched} [GeV]", 50, 0, 300);
  book<TH1F>("MT_H_W_gen", "M_{T,WW}^{gen} [GeV]", 50, 0, 300);
  book<TH1F>("MT_H_W_test", "M_{T,WW}^{matched} [GeV] (test)", 50, 0, 300);



  // b's
  book<TH1F>("B1_jet_BTag", "B1_jet btagged?", 2, -0.5, 1.5);
  book<TH1F>("B2_jet_BTag", "B2_jet btagged?", 2, -0.5, 1.5);
  book<TH1F>("N_matchedJets_B1", "N_{matchedJets}^{B1}", 5, -0.5, 4.5);
  book<TH1F>("N_matchedJets_B2", "N_{matchedJets}^{B2}", 5, -0.5, 4.5);

  book<TH1F>("B1_GenEta", "#eta^{b1}_{gen}", 50, -5, 5);
  book<TH1F>("B2_GenEta", "#eta^{b2}_{gen}", 50, -5, 5);
  book<TH1F>("B1_GenPt", "p^{b1}_{T, gen}", 50, 0, 300);
  book<TH1F>("B2_GenPt", "p^{b2}_{T, gen}", 50, 0, 300);

  //  book<TH1F>("", "", , ,);


  book<TH1F>("pt_b1", "p_{T}^{b1} [GeV]", 50, 0, 500);
  book<TH1F>("pt_b2", "p_{T}^{b2} [GeV]", 50, 0, 500);
  book<TH1F>("pt_b", "p_{T}^{b} [GeV]", 50, 0, 500);
  book<TH1F>("eta_b", "#eta^{b} [GeV]", 50, -2.5, 2.5);
  book<TH1F>("deltaR bb", "#Delta R between two b's", 50, 0, 5);
  book<TH1F>("deltaPhi bb", "#Delta #Phi between two b's", 50, 0, 3.2);
  book<TH1F>("deltaEta bb", "#Delta #eta between two b's", 50, -5, 5);

  book<TH1F>("M_b1", "M_{b1}^{gen} [GeV]", 50, 0, 10);
  book<TH1F>("M_b2", "M_{b2}^{gen} [GeV]", 50, 0, 10);

  pt_b1_vs_pt_b2 = book<TH2F>("pt_b1 vs pt_b2", "p_{T}^{b1} [GeV] vs p_{T}^{b2} [GeV]", 50, 0, 500, 50, 0, 500);
  M_b1_vs_M_b2 = book<TH2F>("M_b1 vs M_b2", "M^{b1} [GeV] vs M^{b2} [GeV]", 50, 4.6, 5.2, 50, 4.6, 5.2);
  deltaR_bb_vs_pt_b1 = book<TH2F>("deltaR_bb vs pt_b1", "#Delta R^{bb} vs p_{T}^{b1} [GeV]", 50, 0, 5, 50, 0, 500);


  // W's
  
  book<TH1F>("M_WLep_semireco", "M_{WLep} [GeV] (semireco)", 80, 0, 150);
  book<TH1F>("M_WLep", "M_{WLep}^{matched} [GeV]", 80, 0, 150);
  book<TH1F>("M_WHad", "M_{WHad}^{matched} [GeV]", 80, 0, 150);
  book<TH1F>("MT_WLep", "M_{T,WLep}^{matched} [GeV]", 80, 0, 150);
  book<TH1F>("MT_WHad", "M_{T,WHad}^{matched} [GeV]", 80, 0, 150);
  book<TH1F>("M_WHad_offshell", "M_{WHad}^{matched} [GeV] (offshell)", 80, 0, 120);
  book<TH1F>("M_WHad_onshell", "M_{WHad}^{matched} [GeV] (onshell)", 80, 0, 120);
  book<TH1F>("MT_WHad_offshell", "M_{T,WHad}^{matched} [GeV]", 80, 0, 150);
  book<TH1F>("MT_WHad_onshell", "M_{T,WHad}^{matched} [GeV]", 80, 0, 150);
  book<TH1F>("MT_WLep_offshell", "M_{T,WLep}^{matched} [GeV]", 80, 0, 150);
  book<TH1F>("MT_WLep_onshell", "M_{T,WLep}^{matched} [GeV]", 80, 0, 150);

  book<TH1F>("M_WLep_gen", "M^{gen}_{WLep} [GeV]", 80, 0, 120);
  book<TH1F>("M_WHad_gen", "M^{gen}_{WHad} [GeV]", 80, 0, 120);
  book<TH1F>("MT_WLep_gen", "M^{gen}_{T,WLep} [GeV]", 80, 0, 150);
  book<TH1F>("MT_WHad_gen", "M^{gen}_{T,WHad} [GeV]", 80, 0, 150);

  book<TH1F>("pt_WLep", "p_{T,WLep}^{matched} [GeV]", 50, 0, 500);
  book<TH1F>("pt_WHad", "p_{T,WHad}^{matched} [GeV]", 50, 0, 500);

  book<TH1F>("eta_WLep", "#eta_{WLep}^{matched} [GeV]", 50, -2.5, 2.5);
  book<TH1F>("eta_WHad", "#eta_{WHad}^{matched} [GeV]", 50, -2.5, 2.5);

  pt_WLep_vs_pt_WHad = book<TH2F>("pt_WLep vs pt_WHad", "p_{T}^{WLep} [GeV] vs p_{T}^{WHad} [GeV] (matched)", 50, 0, 500, 50, 0, 500);
  M_WLep_vs_M_WHad = book<TH2F>("M_WLep vs M_WHad", "M^{WLep} [GeV] vs M^{WHad} [GeV] (matched)", 50, 0, 120, 50, 0, 120);
  // W daughters

  book<TH1F>("N_matchedJets_Q1", "N_{matchedJets}^{Q1}", 5, -0.5, 4.5);
  book<TH1F>("N_matchedJets_Q2", "N_{matchedJets}^{Q2}", 5, -0.5, 4.5);

  book<TH1F>("pt_q1", "p_{T,q1}^{matched} [GeV]", 50, 0, 200);
  book<TH1F>("pt_q2", "p_{T,q2}^{matched} [GeV]", 50, 0, 200);
  book<TH1F>("pt_l", "p_{T,lepton}^{matched} [GeV]", 50, 0, 200);
  book<TH1F>("pt_n", "p_{T,neutrino}^{matched} [GeV]", 50, 0, 200);

  book<TH1F>("eta_q1", "#eta_{q1}^{matched} [GeV]", 50, -5, 5);
  book<TH1F>("eta_q2", "#eta_{q2}^{matched} [GeV]", 50, -5, 5);
  book<TH1F>("eta_l", "#eta_{lepton}^{matched} [GeV]", 50, -5, 5);
  book<TH1F>("eta_n", "#eta_{neutrino}^{matched} [GeV]", 50, -5, 5);

  book<TH1F>("deltaR qq", "#Delta R between two q's (matched)", 50, 0, 5);
  book<TH1F>("deltaPhi qq", "#Delta #Phi between two q's (matched)", 50, 0, 3.2);
  book<TH1F>("deltaEta qq", "#Delta #eta between two q's (matched)", 50, -5, 5);


}


void HHtoWWbbSemiLeptonicMatchedHists::fill(const Event & event){
  // cout << "MatchedHists: fill" << endl;
  // Don't forget to always use the weight when filling.
  
  double weight = event.weight;
  const auto & HHgenreco = event.get(h_HHgenreco);
  // cout << "Line: " << __LINE__ << endl;




  // b quarks

  HHMatchedJets B1_match = HHgenreco.B1_jets();
  HHMatchedJets B2_match = HHgenreco.B2_jets();

  vector<Jet> b1_jets = B1_match.allJets;
  vector<Jet> b2_jets = B2_match.allJets;

  LorentzVector B1_gen = B1_match.gen;
  LorentzVector B2_gen = B2_match.gen;

  hist("N_matchedJets_B1")->Fill(b1_jets.size(), weight);
  hist("N_matchedJets_B2")->Fill(b2_jets.size(), weight);

  Jet b1 = B1_match.mainJet;
  Jet b2 = B2_match.mainJet;
  LorentzVector B1 = b1.v4();
  LorentzVector B2 = b2.v4();
  
  // cout << B1_match.matched << endl;
  if(!(B1_match.matched)) {
    hist("B1_GenEta")->Fill(B1_gen.eta(), weight);
    hist("B1_GenPt")->Fill(B1_gen.pt(), weight);
  }
  if(!(B2_match.matched)) {
    hist("B2_GenEta")->Fill(B1_gen.eta(), weight);
    hist("B2_GenPt")->Fill(B2_gen.pt(), weight);
  }
  if(B1_match.matched && B2_match.matched) {
    // Higgs
    hist("M_H_b_reco")->Fill((B1+B2).M(), weight);
    hist("M_H_b_reco1")->Fill((B1+B2).M(), weight);

    // bottom quarks
    CSVBTag Btag_medium = CSVBTag(CSVBTag::WP_MEDIUM);
    JetId DeepjetMedium = BTag(BTag::DEEPJET, BTag::WP_MEDIUM);

    if(!Btag_medium(b1,event)) hist("B1_jet_BTag")->Fill(0., weight);
    if(Btag_medium(b1,event)) hist("B1_jet_BTag")->Fill(1., weight);
    if(!Btag_medium(b2,event)) hist("B2_jet_BTag")->Fill(0., weight);
    if(Btag_medium(b2,event)) hist("B2_jet_BTag")->Fill(1., weight);



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



  // W's
  

  HHMatchedJets Q1_match = HHgenreco.Q1_jets();
  HHMatchedJets Q2_match = HHgenreco.Q2_jets();
  HHMatchedLepton L_match = HHgenreco.Lepton();
  HHMatchedLepton N_match = HHgenreco.Neutrino();

  vector<Jet> q1_jets = Q1_match.allJets;
  vector<Jet> q2_jets = Q2_match.allJets;

  hist("N_matchedJets_Q1")->Fill(q1_jets.size(), weight);
  hist("N_matchedJets_Q2")->Fill(q2_jets.size(), weight);

  Jet q1 = Q1_match.mainJet;
  Jet q2 = Q2_match.mainJet;
  LorentzVector Q1 = q1.v4();
  LorentzVector Q2 = q2.v4();

  LorentzVector L = L_match.lepton;
  LorentzVector N = N_match.lepton;


  //gen
  LorentzVector N_gen = N_match.gen;
  LorentzVector L_gen = L_match.gen;
  LorentzVector Q1_gen = Q1_match.gen;
  LorentzVector Q2_gen = Q2_match.gen;

  LorentzVector WLep_gen = N_gen+L_gen;
  LorentzVector WHad_gen = Q1_gen+Q2_gen;

  double MT_WHad_gen = TransverseMass(Q1_gen,Q2_gen,0,0);
  double MT_WLep_gen = TransverseMass(L_gen,N_gen,0,0);
  double MT_H_W_gen = TransverseMass(WHad_gen,WLep_gen,MT_WHad_gen,MT_WLep_gen);


  // (semi-) reco
  LorentzVector WHad = Q1+Q2;
  LorentzVector WLep_semireco = L + N_gen;
  LorentzVector WLep = L + N;

  double MT_WHad = TransverseMass(Q1,Q2,0,0);
  double MT_WLep = TransverseMass(L,N,0,0);
  double MT_H_W = TransverseMass(WHad,WLep,MT_WHad,MT_WLep);
  double MT_H_W_test = TransverseMass(WHad,WLep,min(85.,MT_WHad),min(85.,MT_WLep));


  // WHad
  if(Q1_match.matched && Q2_match.matched) {
    hist("M_H_W_reco")->Fill((WHad+WLep).M(), weight);
    hist("M_H_W_semireco")->Fill((WHad+WLep_semireco).M(), weight);
    hist("MT_H_W_reco")->Fill(MT_H_W, weight);
    hist("MT_H_W_gen")->Fill(MT_H_W_gen, weight);
    hist("MT_H_W_test")->Fill(MT_H_W_test, weight);

    hist("M_WHad")->Fill(WHad.M(), weight);
    hist("MT_WHad")->Fill(MT_WHad, weight);
    hist("MT_WHad_gen")->Fill(MT_WHad_gen, weight);

    if(WHad_gen.M()<50) hist("M_WHad_offshell")->Fill(WHad.M(), weight);
    if(WHad_gen.M()>70 && WHad_gen.M()<90) hist("M_WHad_onshell")->Fill(WHad.M(), weight);

    if(WHad_gen.M()<50) hist("MT_WHad_offshell")->Fill(MT_WHad, weight);
    if(WHad_gen.M()>70 && WHad_gen.M()<90) hist("MT_WHad_onshell")->Fill(MT_WHad, weight);

    hist("M_WHad_gen")->Fill((WHad_gen).M(), weight);
    hist("pt_WHad")->Fill((WHad).pt(), weight);
    hist("eta_WHad")->Fill((WHad).eta(), weight);

    M_WLep_vs_M_WHad->Fill(WLep.M(), WHad.M(), weight);
    pt_WLep_vs_pt_WHad->Fill(WLep.pt(), WHad.pt(), weight);

    hist("pt_q1")->Fill(Q1.pt(),weight);
    hist("pt_q2")->Fill(Q2.pt(),weight);

    hist("eta_q1")->Fill(Q1.eta(),weight);
    hist("eta_q2")->Fill(Q2.eta(),weight);

    double dr_Q = deltaR(Q1,Q2);
    double dphi_Q = deltaPhi(Q1,Q2);
    double deta_Q = Q1.eta() - Q2.eta();
    hist("deltaR qq")->Fill(dr_Q, weight);
    hist("deltaPhi qq")->Fill(dphi_Q, weight);	
    hist("deltaEta qq")->Fill(deta_Q, weight);
  }

    hist("M_WLep")->Fill(WLep.M(), weight);
    hist("MT_WLep")->Fill(MT_WLep, weight);    
    hist("MT_WLep_gen")->Fill(MT_WLep_gen, weight);

    hist("M_WLep_semireco")->Fill(WLep_semireco.M(), weight);
    hist("M_WLep_gen")->Fill(WLep_gen.M(), weight);
    if(WLep_gen.M()<50) hist("MT_WLep_offshell")->Fill(MT_WLep, weight);
    if(WLep_gen.M()>70 && WLep_gen.M()<90) hist("MT_WLep_onshell")->Fill(MT_WLep, weight);
    hist("pt_WLep")->Fill(WLep.pt(), weight);
    hist("eta_WLep")->Fill(WLep.eta(), weight);

    hist("pt_l")->Fill(L.pt(),weight);
    hist("pt_n")->Fill(N.pt(),weight);

    hist("eta_l")->Fill(L.eta(),weight);
    hist("eta_n")->Fill(N.eta(),weight);
}




double HHtoWWbbSemiLeptonicMatchedHists::TransverseMass(LorentzVector A, LorentzVector B, double mA, double mB) {
  double pTA = A.Pt();
  double pTB = B.Pt();
  double pt = (A+B).Pt();

  double Et = sqrt(pow(pTA,2)+pow(mA,2))+sqrt(pow(pTB,2)+pow(mB,2));

  double mt = sqrt(pow(Et,2)-pow(pt,2));
  //cout << "mt: " << mt << endl;
  return mt;
}




HHtoWWbbSemiLeptonicMatchedHists::~HHtoWWbbSemiLeptonicMatchedHists(){}
