#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicPreselectionHists.h"
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

HHtoWWbbSemiLeptonicPreselectionHists::HHtoWWbbSemiLeptonicPreselectionHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  // book all histograms here
  // jets
  N_jets = book<TH1F>("N_jets", "N_{jets}", 16, -0.5, 15.5);  
  N_PU = book<TH1F>("N_PU", "N_{PU}", 100, 0, 100);  
  pt_jets = book<TH1F>("pt_jets", "p_{T}^{jets}", 100, 10, 250);
  pt_jet1 = book<TH1F>("pt_jet1", "p_{T}^{jet 1}", 100, 10, 250);
  pt_jet2 = book<TH1F>("pt_jet2", "p_{T}^{jet 2}", 100, 10, 250);
  pt_jet3 = book<TH1F>("pt_jet3", "p_{T}^{jet 3}", 100, 10, 250);
  pt_jet4 = book<TH1F>("pt_jet4", "p_{T}^{jet 4}", 100, 10, 250);
  eta_jets = book<TH1F>("eta_jets", "#eta^{jets}", 40, -2.5, 2.5);
  eta_jets_rebin = book<TH1F>("eta_jets_rebin", "#eta^{jets}", 60, -5.0, 5.0);
  eta_jet1 = book<TH1F>("eta_jet1", "#eta^{jet 1}", 40, -2.5, 2.5);
  eta_jet2 = book<TH1F>("eta_jet2", "#eta^{jet 2}", 40, -2.5, 2.5);
  eta_jet3 = book<TH1F>("eta_jet3", "#eta^{jet 3}", 40, -2.5, 2.5);
  eta_jet4 = book<TH1F>("eta_jet4", "#eta^{jet 4}", 40, -2.5, 2.5);


  //N_jets_vs_pt_jets = book<TH2F>("N_jets_vs_pt_jet", "N_{jets} vs p_{T}^{jets}", 21, -0.5, 20.5, 100, 10, 500);
  N_jet_vs_pt_jet = book<TH2F>("N_jet_vs_pt_jet", "N_{jet} vs p_{T}^{jet}", 11, -0.5, 10.5, 100, 10, 500);
  N_jet_vs_eta_jet = book<TH2F>("N_jet_vs_eta_jet", "N_{jet} vs #eta^{jet}", 11, -0.5, 10.5, 40, -2.5, 2.5);


  EMcharged_jet1 = book<TH1F>("EMcharged_jet1", "EMcharged_jet1", 100,0.0,1.0);
  EMneutral_jet1 = book<TH1F>("EMneutral_jet1", "EMneutral_jet1", 100,0.0,1.0);
  HADcharged_jet1 = book<TH1F>("HADcharged_jet1", "HADcharged_jet1", 100,0.0,1.0);
  HADneutral_jet1 = book<TH1F>("HADneutral_jet1", "HADneutral_jet1", 100,0.0,1.0);

  /*
  EMcharged_vs_eta_jet1 = book<TH2D>("EMcharged_vs_eta_jet1","EMcharged vs #eta; #eta; EMcharged",100,-6,6,100,0.0,1.0);   
  EMneutral_vs_eta_jet1 = book<TH2D>("EMneutral_vs_eta_jet1","EMneutral vs #eta; #eta; EMneutral",100,-6,6,100,0.0,1.0);   
  HADcharged_vs_eta_jet1 = book<TH2D>("HADcharged_vs_eta_jet1","HADcharged vs #eta; #eta; HADcharged",100,-6,6,100,0.0,1.0);   
  HADneutral_vs_eta_jet1 = book<TH2D>("HADneutral_vs_eta_jet1","HADneutral vs #eta; #eta; HADneutral",100,-6,6,100,0.0,1.0);   
  EMcharged_vs_PU_jet1 = book<TH2D>("EMcharged_vs_PU_jet1","EMcharged vs PU; PU; EMcharged",100,0,100,100,0.0,1.0);   
  EMneutral_vs_PU_jet1 = book<TH2D>("EMneutral_vs_PU_jet1","EMneutral vs PU; PU; EMneutral",100,0,100,100,0.0,1.0);   
  HADcharged_vs_PU_jet1 = book<TH2D>("HADcharged_vs_PU_jet1","HADcharged vs PU; PU; HADcharged",100,0,100,100,0.0,1.0);   
  HADneutral_vs_PU_jet1 = book<TH2D>("HADneutral_vs_PU_jet1","HADneutral vs PU; PU; HADneutral",100,0,100,100,0.0,1.0);   
  */

  // bjets
  N_bJets_loose= book<TH1F>("N_bJets_loose", "N_{jets}^{CSV loose}", 11, -0.5, 10.5);
  N_bJets_med = book<TH1F>("N_bJets_med", "N_{jets}^{CSV medium}", 11, -0.5, 10.5);
  N_bJets_tight = book<TH1F>("N_bJets_tight", "N_{jets}^{CSV tight}", 11, -0.5, 10.5);
  N_deepjet_loose = book<TH1F>("N_deepjet_loose", "N_{jets}^{DeepJet loose}", 11, -0.5, 10.5);
  N_deepjet_med = book<TH1F>("N_deepjet_med", "N_{jets}^{DeepJet medium}", 11, -0.5, 10.5);
  N_deepjet_tight = book<TH1F>("N_deepjet_tight", "N_{jets}^{DeepJet tight}", 11, -0.5, 10.5);
  
  DeltaR_bjets = book<TH1F>("DeltaR_bjets", "#Delta R between the highest-pt bjets", 50, 0, 5);

  // leptons
  N_mu = book<TH1F>("N_mu", "N^{#mu}", 11, -0.5, 10.5);
  pt_mu = book<TH1F>("pt_mu", "p_{T}^{#mu} [GeV/c]", 40, 0, 200);
  eta_mu = book<TH1F>("eta_mu", "#eta^{#mu}", 40, -2.5, 2.5);
  eta_mu_rebin = book<TH1F>("eta_mu_rebin", "#eta^{#mu}", 60, -5.0, 5.0);
  reliso_mu = book<TH1F>("reliso_mu", "#mu rel. Iso", 40, 0, 0.5);

  N_ele = book<TH1F>("N_ele", "N^{e}", 11, -0.5, 10.5);
  pt_ele = book<TH1F>("pt_ele", "p_{T}^{e} [GeV]", 40, 0, 200);
  eta_ele = book<TH1F>("eta_ele", "#eta^{e}", 50, -2.5, 2.5);
  eta_ele_rebin = book<TH1F>("eta_ele_rebin", "#eta^{e}", 40, -5.0, 5.0);
  reliso_ele = book<TH1F>("reliso_ele", "e rel. Iso", 40, 0, 0.5);

  N_lep = book<TH1F>("N_lep", "N^{lep}", 11, -0.5, 10.5);


  // primary vertices
  N_pv = book<TH1F>("N_pv", "N^{PV}", 50, 0, 50);

  // MET, ST
  MET = book<TH1F>("MET", "missing E_{T} [GeV]", 50, 0, 1500);
  MET_rebin = book<TH1F>("MET_rebin", "missing E_{T} [GeV]", 50, 0, 800);
  ST = book<TH1F>("ST", "S_{T} [GeV]", 50, 0, 5000);
  ST_rebin = book<TH1F>("ST_rebin", "S_{T} [GeV]", 200, 0, 3000);
  STjets = book<TH1F>("STjets", "S_{T}^{jets} [GeV]", 50, 0, 5000);
  STjets_rebin = book<TH1F>("STjets_rebin", "S_{T}^{jets} [GeV]", 200, 0, 3000);
  STlep = book<TH1F>("STlep", "S_{T}^{lep} [GeV]", 50, 0, 7000);
  STlep_rebin = book<TH1F>("STlep_rebin", "S_{T}^{lep} [GeV]", 50, 0, 1500);
 
  N_jets_vs_STjets = book<TH2F>("N_jets_vs_STjets", "N_{jets} vs S_{T}^{jets}", 21, -0.5, 20.5, 100, 0, 5000);


  // Mass reconstruction
  MT_HH = book<TH1F>("MT_HH", "M_{T}^{HH} [GeV]", 50, 0, 500);
  MT_HH_rebin = book<TH1F>("MT_HH_rebin", "M_{T}^{HH} [GeV]", 50, 0, 1000);
  MT_HH_test = book<TH1F>("MT_HH_test", "M_{T}^{HH} [GeV] (test)", 50, 0, 500);
  MT_HH_Vergleich = book<TH1F>("MT_HH_Vergleich", "M_{T}^{HH} [GeV] (mT root definition)", 50, 0, 500);


  sum_event_weights = book<TH1F>("sum_event_weights", "BinContent = sum(eventweights)", 1, 0.5, 1.5);

}


void HHtoWWbbSemiLeptonicPreselectionHists::fill(const Event & event){
  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  
  // Don't forget to always use the weight when filling.
  double weight = event.weight;
  sum_event_weights->Fill(1., weight);
  
  std::vector<Jet>* jets = event.jets;
  int Njets = jets->size();
  N_jets->Fill(Njets, weight);
  if(!event.isRealData)  N_PU->Fill(event.genInfo->pileup_TrueNumInteractions(), weight);

  if(Njets>=1){
    eta_jet1->Fill(jets->at(0).eta(), weight);
    pt_jet1->Fill(jets->at(0).pt(), weight);
    EMcharged_jet1->Fill(jets->at(0).chargedEmEnergyFraction(), weight);
    EMneutral_jet1->Fill(jets->at(0).neutralEmEnergyFraction(), weight);
    HADcharged_jet1->Fill(jets->at(0).chargedHadronEnergyFraction(), weight);
    HADneutral_jet1->Fill(jets->at(0).neutralHadronEnergyFraction(), weight);
    
    /*
    EMcharged_vs_eta_jet1->Fill(jets->at(0).eta(),jets->at(0).chargedEmEnergyFraction(), weight);
    EMneutral_vs_eta_jet1->Fill(jets->at(0).eta(),jets->at(0).neutralEmEnergyFraction(), weight);
    HADcharged_vs_eta_jet1->Fill(jets->at(0).eta(),jets->at(0).chargedHadronEnergyFraction(), weight);
    HADneutral_vs_eta_jet1->Fill(jets->at(0).eta(),jets->at(0).neutralHadronEnergyFraction(), weight);
    if(!event.isRealData){
      EMcharged_vs_PU_jet1->Fill(event.genInfo->pileup_TrueNumInteractions(),jets->at(0).chargedEmEnergyFraction(), weight);
      EMneutral_vs_PU_jet1->Fill(event.genInfo->pileup_TrueNumInteractions(),jets->at(0).neutralEmEnergyFraction(), weight);
      HADcharged_vs_PU_jet1->Fill(event.genInfo->pileup_TrueNumInteractions(),jets->at(0).chargedHadronEnergyFraction(), weight);
      HADneutral_vs_PU_jet1->Fill(event.genInfo->pileup_TrueNumInteractions(),jets->at(0).neutralHadronEnergyFraction(), weight);
    }
    */
  }
  if(Njets>=2){
    eta_jet2->Fill(jets->at(1).eta(), weight);
    pt_jet2->Fill(jets->at(1).pt(), weight);

  }
  if(Njets>=3){
    eta_jet3->Fill(jets->at(2).eta(), weight);
    pt_jet3->Fill(jets->at(2).pt(), weight);

  }
  if(Njets>=4){
    eta_jet4->Fill(jets->at(3).eta(), weight);
    pt_jet4->Fill(jets->at(3).pt(), weight);

  }
  // pt_jets, eta_jets
  for(int i=0; i<Njets; i++)  {
    pt_jets->Fill(jets->at(i).pt(), weight);
    eta_jets->Fill(jets->at(i).eta(), weight);
    eta_jets_rebin->Fill(jets->at(i).eta(), weight);
    N_jet_vs_pt_jet->Fill(i, jets->at(i).pt(), weight);
    N_jet_vs_eta_jet->Fill(i, jets->at(i).eta(), weight);

  }


  // bjets
  int Nbjets_loose = 0, Nbjets_medium = 0, Nbjets_tight = 0;
  int Ndeepjet_loose = 0, Ndeepjet_med = 0, Ndeepjet_tight = 0;
  CSVBTag Btag_loose = CSVBTag(CSVBTag::WP_LOOSE);
  CSVBTag Btag_medium = CSVBTag(CSVBTag::WP_MEDIUM);
  CSVBTag Btag_tight = CSVBTag(CSVBTag::WP_TIGHT);

  JetId DeepjetLoose = BTag(BTag::DEEPJET, BTag::WP_LOOSE);
  JetId DeepjetMedium = BTag(BTag::DEEPJET, BTag::WP_MEDIUM);
  JetId DeepjetTight = BTag(BTag::DEEPJET, BTag::WP_TIGHT);

  //vector<Jet>* bjets;
  Jet b1;
  Jet b2;

  for (unsigned int i =0; i<jets->size(); i++) {
    if(Btag_loose(jets->at(i),event))  Nbjets_loose++;
    if(Btag_medium(jets->at(i),event)) Nbjets_medium++;
    if(Btag_tight(jets->at(i),event))  Nbjets_tight++;
    if(DeepjetLoose(jets->at(i),event))  Ndeepjet_loose++;
    if(DeepjetMedium(jets->at(i),event)) {
      //bjets->push_back(jets->at(i));
      Ndeepjet_med++;
      if(Ndeepjet_med == 1) b1 =jets->at(i);
      if(Ndeepjet_med == 2) b2 =jets->at(i);
    }
    if(DeepjetTight(jets->at(i),event))  Ndeepjet_tight++;


  }

  N_bJets_loose->Fill(Nbjets_loose,weight);
  N_bJets_med->Fill(Nbjets_medium,weight);
  N_bJets_tight->Fill(Nbjets_tight,weight);
  N_deepjet_loose->Fill(Ndeepjet_loose,weight);
  N_deepjet_med->Fill(Ndeepjet_med,weight);
  N_deepjet_tight->Fill(Ndeepjet_tight,weight);

  // Delta R 
  
  if(Ndeepjet_med >= 2) {
    double dr = deltaR(b1, b2);
    DeltaR_bjets->Fill(dr,weight);
  }
  
  // Muons
  vector<Muon>* muons = event.muons;
  int Nmuons = event.muons->size();
  N_mu->Fill(Nmuons, weight);
  for (const Muon & thismu : *event.muons){
      pt_mu->Fill(thismu.pt(), weight);
      eta_mu->Fill(thismu.eta(), weight);
      eta_mu_rebin->Fill(thismu.eta(), weight);
      reliso_mu->Fill(thismu.relIso(), weight);
  }


  // Electrons
  vector<Electron>* electrons = event.electrons;
  int Nelectrons = event.electrons->size();
  N_ele->Fill(Nelectrons, weight);
  for (const Electron & thismu : *event.electrons){
      pt_ele->Fill(thismu.pt(), weight);
      eta_ele->Fill(thismu.eta(), weight);      
      eta_ele_rebin->Fill(thismu.eta(), weight);
      reliso_ele->Fill(thismu.relIso(), weight);
  }

  N_lep->Fill(Nelectrons+Nmuons, weight);

  // General
  int Npvs = event.pvs->size();
  N_pv->Fill(Npvs, weight);



  double met = event.met->pt();
  double st = 0., st_jets = 0., st_lep = 0.;
  for(const auto & jet : *jets)           st_jets += jet.pt();
  for(const auto & electron : *electrons) st_lep += electron.pt();
  for(const auto & muon : *muons)         st_lep += muon.pt();
  st = st_jets + st_lep + met;


  MET->Fill(met, weight);
  MET_rebin->Fill(met, weight);

  ST->Fill(st, weight);
  ST_rebin->Fill(st, weight);

  STjets->Fill(st_jets, weight);
  STjets_rebin->Fill(st_jets, weight);
  N_jets_vs_STjets->Fill(Njets, st_jets, weight);

  STlep->Fill(st_lep, weight);
  STlep_rebin->Fill(st_lep, weight);


  // Transverse Mass
  // only if there is a lepton
  if(Nmuons >= 1 or Nelectrons>= 1) {
    vector<Jet>* JetVector = event.jets;
    // find the two highest-pt bjets, combine them to H1
    // find the two highest-pt non-bjets, combine them to W1

    LorentzVector H1;
    LorentzVector W1;

    for (unsigned int i=0; i< JetVector->size(); i++){
      int j=0;
      int k=0;
      if(DeepjetMedium(JetVector->at(i),event)){
	if(j==2) break;
	H1 = H1 + JetVector->at(i).v4();
	j++;
      }
      else{
	if(k==2) break;
	W1 = W1 + JetVector->at(i).v4();
	k++;
      }
    }


    // combine mu and met to W2
    LorentzVector lepton;
    if (Nmuons >=1) lepton = event.muons->at(0).v4();
    else lepton = event.electrons->at(0).v4(); // if there are no muons, there must be electrons
    LorentzVector MET = event.met->v4();
    LorentzVector W2 = lepton + MET;

    // combine W1 and W2 to H2
    LorentzVector H2 = W1 + W2;
    LorentzVector HH = H1 + H2;
    // combine H1 and H2 to mT
    TVector3 H1_pT = toVector(H1);
    H1_pT.SetZ(0);
    TVector3 H2_pT = toVector(H2);
    H2_pT.SetZ(0);
    double H1_E = H1.Et(); // ET function from root
    double H2_E = H2.Et();
    double m_H = 125; // 125.09
    double H1_ET = sqrt(pow(m_H,2) + H1_pT*H1_pT); // definition of ET from wikipedia
    double H2_ET = sqrt(pow(m_H,2) + H2_pT*H2_pT);


    double mT = sqrt(pow(H1_E + H2_E, 2) - (H1_pT + H2_pT)*(H1_pT + H2_pT));
    double mT1 = sqrt(pow(H1_ET + H2_ET, 2) - (H1_pT + H2_pT)*(H1_pT + H2_pT));


    MT_HH->Fill(mT, weight);
    MT_HH_rebin->Fill(mT, weight);

    MT_HH_test->Fill(mT1, weight);


    MT_HH_Vergleich->Fill(HH.Mt(), weight);// vergleichen mit mt
  }

}

HHtoWWbbSemiLeptonicPreselectionHists::~HHtoWWbbSemiLeptonicPreselectionHists(){}
