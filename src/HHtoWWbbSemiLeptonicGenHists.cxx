#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicGenHists.h"
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

HHtoWWbbSemiLeptonicGenHists::HHtoWWbbSemiLeptonicGenHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  // book all histograms here

  // Higgs
  book<TH1F>("pt_H_W", "p_{T}^{Higgs 1} [GeV]", 50, 0, 500);
  book<TH1F>("pt_H_b", "p_{T}^{Higgs 2} [GeV]", 50, 0, 500);
  book<TH1F>("pt_H", "p_{T}^{Higgs} [GeV]", 50, 0, 500);
  book<TH1F>("eta_H", "#eta^{Higgs} [GeV]", 50, -2.5, 2.5);
  book<TH1F>("deltaR HH", "#Delta R between two H's", 50, 0, 5);
  book<TH1F>("deltaPhi HH", "#Delta #Phi between two H's", 50, -3.2, 3.2);
  book<TH1F>("deltaEta HH", "#Delta #eta between two H's", 50, -5, 5);



  book<TH1F>("M_HH", "M^{HH} [GeV]", 50, 200, 800);
  book<TH1F>("M_H_W", "M^{Higgs} [GeV] decaying to W", 50, 124.95, 125.05);
  book<TH1F>("M_H_W_reco", "M^{Higgs} [GeV] decaying to W (reco)", 50, 124.95, 125.05);
  book<TH1F>("M_H_b", "M^{Higgs} [GeV] decaying to b", 50, 124.95, 125.05);
  book<TH1F>("M_H_b_reco", "M^{Higgs} [GeV] decaying to b (reco)", 50, 124.95, 125.05);


  pt_H_W_vs_pt_H_b = book<TH2F>("pt_H_W vs pt_H_b", "p_{T}^{H_W} [GeV] vs p_{T}^{H_b} [GeV]", 50, 0, 500, 50, 0, 500);
  M_H_W_vs_M_H_b = book<TH2F>("M_H_W vs M_H_b", "M^{H_W} [GeV] vs M^{H_b} [GeV]", 50, 124.8, 125.2, 50, 124.8, 125.2);
  deltaR_HH_vs_pt_H_W = book<TH2F>("deltaR_HH vs pt_H_W", "#Delta R^{HH} vs p_{T}^{H_W} [GeV]", 50, 0, 5, 50, 0, 500);

  // W's
  book<TH1F>("pt_W1", "p_{T}^{W1} [GeV]", 50, 0, 500);
  book<TH1F>("pt_W2", "p_{T}^{W2} [GeV]", 50, 0, 500);
  book<TH1F>("pt_W", "p_{T}^{W} [GeV]", 50, 0, 500);
  book<TH1F>("eta_W", "#eta^{W} [GeV]", 50, -2.5, 2.5);
  book<TH1F>("deltaR WW", "#Delta R between two W's", 50, 0, 5);
  book<TH1F>("deltaPhi WW", "#Delta #Phi between two W's", 50, -3.2, 3.2);
  book<TH1F>("deltaEta WW", "#Delta #eta between two W's", 50, -5, 5);



  book<TH1F>("M_W1", "M^{W1} [GeV]", 80, 0, 100);
  book<TH1F>("M_W2", "M^{W2} [GeV]", 80, 0, 100);

  pt_W1_vs_pt_W2 = book<TH2F>("pt_W1 vs pt_W2", "p_{T}^{W1} [GeV] vs p_{T}^{W2} [GeV]", 50, 0, 500, 50, 0, 500);
  M_W1_vs_M_W2 = book<TH2F>("M_W1 vs M_W2", "M^{W1} [GeV] vs M^{W2} [GeV]", 80, 0, 100, 80, 0, 100);
  deltaR_WW_vs_pt_W1 = book<TH2F>("deltaR_WW vs pt_W1", "#Delta R^{WW} vs p_{T}^{W1} [GeV]", 50, 0, 5, 50, 0, 500);


  // W daughters
  book<TH1F>("W daughters", "W daughters", 25, 0.5, 25.5);

  book<TH1F>("M_W_had reco", "M^{W}_{had} [GeV] reco", 80, 0, 100);
  book<TH1F>("M_W_lep reco", "M^{W}_{lep} [GeV] reco", 80, 0, 100);

  book<TH1F>("pt_q1", "p_{T}^{q1} [GeV]", 50, 0, 200);
  book<TH1F>("pt_q2", "p_{T}^{q2} [GeV]", 50, 0, 200);
  book<TH1F>("pt_l", "p_{T}^{lepton} [GeV]", 50, 0, 200);
  book<TH1F>("pt_n", "p_{T}^{neutrino} [GeV]", 50, 0, 200);

  pt_q1_vs_pt_q2 = book<TH2F>("pt_q1 vs pt_q2", "p_{T}^{q1} [GeV] vs p_{T}^{q2} [GeV]", 50, 0, 500, 50, 0, 500);
  eta_q1_vs_eta_q2 = book<TH2F>("eta_q1 vs eta_q2", "#eta^{q1} [GeV] vs #eta^{q2} [GeV]", 50, -5, 5, 50, -5, 5);


  book<TH1F>("eta_q1", "#eta^{q1} [GeV]", 50, -5, 5);
  book<TH1F>("eta_q2", "#eta^{q2} [GeV]", 50, -5, 5);
  book<TH1F>("eta_l", "#eta^{lepton} [GeV]", 50, -5, 5);
  book<TH1F>("eta_n", "#eta^{neutrino} [GeV]", 50, -5, 5);

  book<TH1F>("deltaR qq", "#Delta R between two q's", 50, 0, 5);
  book<TH1F>("deltaPhi qq", "#Delta #Phi between two q's", 50, -3.2, 3.2);
  book<TH1F>("deltaEta qq", "#Delta #eta between two q's", 50, -5, 5);

  book<TH1F>("deltaR lnu", "#Delta R between lepton and neutrino", 50, 0, 5);
  book<TH1F>("deltaPhi lnu", "#Delta #Phi between lepton and neutrino", 50, -3.2, 3.2);
  book<TH1F>("deltaEta lnu", "#Delta #eta between lepton and neutrino", 50, -5, 5);


  // b's
  book<TH1F>("pt_b1", "p_{T}^{b1} [GeV]", 50, 0, 500);
  book<TH1F>("pt_b2", "p_{T}^{b2} [GeV]", 50, 0, 500);
  book<TH1F>("pt_b", "p_{T}^{b} [GeV]", 50, 0, 500);
  book<TH1F>("eta_b", "#eta^{b} [GeV]", 50, -2.5, 2.5);
  book<TH1F>("deltaR bb", "#Delta R between two b's", 50, 0, 5);
  book<TH1F>("deltaPhi bb", "#Delta #Phi between two b's", 50, -3.2, 3.2);
  book<TH1F>("deltaEta bb", "#Delta #eta between two b's", 50, -5, 5);

  book<TH1F>("M_b1", "M^{b1} [GeV]", 50, 4.6, 5.2);
  book<TH1F>("M_b2", "M^{b2} [GeV]", 50, 4.6, 5.2);


  
  pt_b1_vs_pt_b2 = book<TH2F>("pt_b1 vs pt_b2", "p_{T}^{b1} [GeV] vs p_{T}^{b2} [GeV]", 50, 0, 500, 50, 0, 500);
  M_b1_vs_M_b2 = book<TH2F>("M_b1 vs M_b2", "M^{b1} [GeV] vs M^{b2} [GeV]", 50, 4.6, 5.2, 50, 4.6, 5.2);
  deltaR_bb_vs_pt_b1 = book<TH2F>("deltaR_bb vs pt_b1", "#Delta R^{bb} vs p_{T}^{b1} [GeV]", 50, 0, 5, 50, 0, 500);


  // test histograms
  book<TH1F>("Higgs Count", "Higgs Count", 5, -0.5, 4.5);
  book<TH1F>("1H_genpId", "pdgId from 1H events", 25, 0.5, 25.5);


  book<TH1F>("hd no b or W", "Higgs daughter is no b or W", 1, 0, 2);

}

void HHtoWWbbSemiLeptonicGenHists::fill(const Event & event){
  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  
  // Don't forget to always use the weight when filling.
  double weight = event.weight;
  
  vector<GenParticle> * genparticles = event.genparticles;
  int HiggsCount = 0; // Higgs counter

  GenParticle higgs_W;
  GenParticle higgs_b;
  LorentzVector Higgs_W;
  LorentzVector Higgs_b;

  for(unsigned int i=0; i<genparticles->size(); i++) {
    const GenParticle & genp = genparticles->at(i);

    if (abs(genp.pdgId()) == 25) {
      auto hd1 = genp.daughter(genparticles,1);
      auto hd2 = genp.daughter(genparticles,2);
      // check for more daughter particles?
      if (!hd1 || !hd2) throw runtime_error("Higgs has no 2 daughters");

      //higgs.push_back(genp);
      HiggsCount++;
      
      int hd1_Id = abs(hd1->pdgId()); // should be either 5 (b) or 24 (W)
      int hd2_Id = abs(hd1->pdgId()); // should be either 5 (b) or 24 (W)
      if(hd1_Id != hd2_Id) throw runtime_error("two Higgs daughter particles are not the same (?)");
      
      //LorentzVector Higgs = genp.v4();
      LorentzVector HD1 = hd1->v4();
      LorentzVector HD2 = hd2->v4();

      double dr_daughters = deltaR(HD1, HD2);
      double dphi_daughters = deltaPhi(HD1, HD2);
      double deta_daughters = hd2->eta() - hd1->eta();

      hist("pt_H")->Fill(genp.pt(),weight);      
      hist("eta_H")->Fill(genp.eta(),weight);

      //double dr = deltaR(hd1, hd2);
      if(hd1_Id == 5) { // hd1, hd2 are bottom quarks
	// Higgs
	higgs_b = genp;
	Higgs_b = genp.v4();
	hist("pt_H_b")->Fill(genp.pt(),weight);
	hist("M_H_b")->Fill(Higgs_b.M(), weight);
	hist("M_H_b_reco")->Fill((HD1+HD2).M(), weight);


	// bottom quarks
	hist("pt_b")->Fill(hd1->pt(),weight);
	hist("pt_b")->Fill(hd2->pt(),weight);
	hist("pt_b1")->Fill(hd1->pt(),weight);
	hist("pt_b2")->Fill(hd2->pt(),weight);

	hist("eta_b")->Fill(hd1->eta(),weight);
	hist("eta_b")->Fill(hd2->eta(),weight);

	hist("M_b1")->Fill(HD1.M(), weight);
	hist("M_b2")->Fill(HD2.M(), weight);

	M_b1_vs_M_b2->Fill(HD1.M(), HD2.M(), weight);
	pt_b1_vs_pt_b2->Fill(hd1->pt(), hd2->pt(), weight);
	deltaR_bb_vs_pt_b1->Fill(dr_daughters, hd1->pt(), weight);
	//hist("M_b1 vs M_b2")->Fill(HD1.M(), HD2.M(), weight);
	//hist("pt_b1 vs pt_b2")->Fill(hd1->pt(), hd2->pt(), weight);

	hist("deltaR bb")->Fill(dr_daughters, weight);
	hist("deltaPhi bb")->Fill(dphi_daughters, weight);	
	hist("deltaEta bb")->Fill(deta_daughters, weight);


      }
      else if(abs(hd1->pdgId()) == 24) { // hd1, hd2 are W bosons
	// Higgs
	higgs_W = genp;
	Higgs_W = genp.v4();
	hist("pt_H_W")->Fill(genp.pt(),weight);
	hist("M_H_W")->Fill(Higgs_W.M(), weight);
	hist("M_H_W_reco")->Fill((HD1+HD2).M(), weight);

	// W daughters
	auto quark1 = hd1->daughter(genparticles, 1);
	auto quark2 = hd1->daughter(genparticles, 2);
	auto lepton = hd2->daughter(genparticles, 1);
	auto neutrino = hd2->daughter(genparticles, 2);

	if(!isQuark(abs(quark1->pdgId()))) {
	  std::swap(quark1, lepton);
	  std::swap(quark2, neutrino);
	}
	if(!isNeutrino(abs(neutrino->pdgId()))) {
	  std::swap(lepton, neutrino);
	}
	/*
	if(!isQuark(abs(quark1->pdgId()))) {
	  for(unsigned int j=0; j<genparticles->size(); ++j) {
	    const GenParticle & gp = genparticles->at(j);
	    auto m1 = gp.mother(genparticles, 1);
	    auto m2 = gp.mother(genparticles, 2);
	    bool has_W_mother = ((m1 && m1->pdgId() == 24) || (m2 && m2->pdgId() == 24));
	    if(has_W_mother && (isQuark(gp.pdgId()))) {
	      quark1 = &gp;
	      break;
	    }
	  }
	}
	*/

	int q1_Id = abs(quark1->pdgId());
	int q2_Id = abs(quark2->pdgId());
	int l_Id = abs(lepton->pdgId());
	int n_Id = abs(neutrino->pdgId());

	//cout << "quark1 ID: " << q1_Id << endl;
	//cout << "neutrino ID: " << n_Id << endl;
	
	hist("W daughters")->Fill(q1_Id, weight);
	hist("W daughters")->Fill(q2_Id, weight);
	hist("W daughters")->Fill(l_Id, weight);
	hist("W daughters")->Fill(n_Id, weight);

	LorentzVector Quark1 = quark1->v4();
	LorentzVector Quark2 = quark2->v4();
	LorentzVector Lepton = lepton->v4();
	LorentzVector Neutrino = neutrino->v4();

	double dr_qq = deltaR(Quark1, Quark2);
	double dphi_qq = deltaPhi(Quark1, Quark2);
	double deta_qq = quark2->eta() - quark1->eta();
	double dr_lnu = deltaR(Lepton, Neutrino);
	double dphi_lnu = deltaPhi(Lepton, Neutrino);
	double deta_lnu = lepton->eta() - neutrino->eta();

	
	if (!isQuark(q1_Id) || !isQuark(q2_Id) || !isLepton(l_Id) || !isNeutrino(n_Id)) goto skip; // lazy workaround for when I don't find the right daughter particles, should be done properly
	if (!isQuark(q1_Id)) throw runtime_error("quark1 should be a Quark!");
	if (!isQuark(q2_Id)) throw runtime_error("quark2 should be a Quark!");
	if (!isLepton(l_Id)) throw runtime_error("lepton should be a Lepton!");
	if (!isNeutrino(n_Id)) throw runtime_error("neutrino should be a Neutrino!");
        


	hist("M_W_had reco")->Fill((Quark1+Quark2).M(), weight);
	hist("M_W_lep reco")->Fill((Lepton+Neutrino).M(), weight);
	hist("pt_q1")->Fill(quark1->pt(), weight);
	hist("pt_q2")->Fill(quark2->pt(), weight);
	hist("pt_l")->Fill(lepton->pt(), weight);
	hist("pt_n")->Fill(neutrino->pt(), weight);

	hist("eta_q1")->Fill(quark1->eta(), weight);
	hist("eta_q2")->Fill(quark2->eta(), weight);
	hist("eta_l")->Fill(lepton->eta(), weight);
	hist("eta_n")->Fill(neutrino->eta(), weight);

	hist("deltaR qq")->Fill(dr_qq, weight);
	hist("deltaPhi qq")->Fill(dphi_qq, weight);	
	hist("deltaEta qq")->Fill(deta_qq, weight);
	hist("deltaR lnu")->Fill(dr_lnu, weight);
	hist("deltaPhi lnu")->Fill(dphi_lnu, weight);	
	hist("deltaEta lnu")->Fill(deta_lnu, weight);

	pt_q1_vs_pt_q2->Fill(quark1->pt(), quark2->pt(), weight);
	eta_q1_vs_eta_q2->Fill(quark1->eta(), quark2->eta(), weight);


      skip:
	
	// W Bosons
	hist("pt_W")->Fill(hd1->pt(),weight);
	hist("pt_W")->Fill(hd2->pt(),weight);
	hist("pt_W1")->Fill(hd1->pt(),weight);
	hist("pt_W2")->Fill(hd2->pt(),weight);

	hist("eta_W")->Fill(hd1->eta(),weight);
	hist("eta_W")->Fill(hd2->eta(),weight);

	hist("M_W1")->Fill(HD1.M(), weight);
	hist("M_W2")->Fill(HD2.M(), weight);

	M_W1_vs_M_W2->Fill(HD1.M(), HD2.M(), weight);
	pt_W1_vs_pt_W2->Fill(hd1->pt(), hd2->pt(), weight);
	deltaR_WW_vs_pt_W1->Fill(dr_daughters, hd1->pt(), weight);



	hist("deltaR WW")->Fill(dr_daughters, weight);
	hist("deltaPhi WW")->Fill(dphi_daughters, weight);	
	hist("deltaEta WW")->Fill(deta_daughters, weight);
      }
      else hist("hd no W or b")->Fill(1, weight);
      



    }


  } // loop over all genparticles

  hist("Higgs Count")->Fill(HiggsCount, weight);
  if (HiggsCount != 2) {
    /*
    cout << "pdg's 1H event: " << endl;
    for(unsigned int i=0; i<genparticles->size(); i++) {
      const GenParticle & genp = genparticles->at(i);
      cout << genp.pdgId() << endl;
      hist("1H_genpId")->Fill(genp.pdgId());
    }
    */
    throw runtime_error("there should always be 2 Higgs Bosons");
  } 


  double m_HH = (Higgs_W + Higgs_b).M();
  double dr_HH = deltaR(Higgs_W, Higgs_b);
  double dphi_HH = deltaPhi(Higgs_W, Higgs_b);
  double deta_HH = higgs_b.eta() - higgs_W.eta();
  hist("M_HH")->Fill(m_HH, weight);
  hist("deltaR HH")->Fill(dr_HH, weight);
  hist("deltaPhi HH")->Fill(dphi_HH, weight);
  hist("deltaEta HH")->Fill(deta_HH, weight);


  pt_H_W_vs_pt_H_b->Fill(Higgs_W.pt(), Higgs_b.pt(), weight);
  M_H_W_vs_M_H_b->Fill(Higgs_W.M(), Higgs_W.M(), weight);
  deltaR_HH_vs_pt_H_W->Fill(dr_HH, higgs_W.pt(), weight);



}

/*
bool HHtoWWbbSemiLeptonicGenHists::isQuark2(genparticle particle, vector<genparticle> vec){
  int id = abs(particle->pdgId());
  return(id==1 || id==2 || id==3 || id==4 || id==5 || id==6) ;
}
*/

bool HHtoWWbbSemiLeptonicGenHists::isQuark(int id){
  return(id==1 || id==2 || id==3 || id==4 || id==5 || id==6) ;
}
bool HHtoWWbbSemiLeptonicGenHists::isLepton(int id){
  return(id==11 || id==12 || id==13 || id==14 || id==15 || id==16) ;
}
bool HHtoWWbbSemiLeptonicGenHists::isChargedLepton(int id){
  return(id==11 || id==13 || id==15) ;
}
bool HHtoWWbbSemiLeptonicGenHists::isNeutrino(int id){
  return(id==12 || id==14 || id==16) ;
}


HHtoWWbbSemiLeptonicGenHists::~HHtoWWbbSemiLeptonicGenHists(){}
