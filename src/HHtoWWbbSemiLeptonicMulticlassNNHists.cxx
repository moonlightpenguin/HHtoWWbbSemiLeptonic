#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicMulticlassNNHists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include <iostream>

using namespace std;
using namespace uhh2;

HHtoWWbbSemiLeptonicMulticlassNNHists::HHtoWWbbSemiLeptonicMulticlassNNHists(uhh2::Context& ctx, const std::string& dirname): Hists(ctx, dirname) {

  h_NNoutput0 = ctx.get_handle<double>("NNoutput0");
  h_NNoutput1 = ctx.get_handle<double>("NNoutput1");
  h_NNoutput2 = ctx.get_handle<double>("NNoutput2");
  h_NNoutput3 = ctx.get_handle<double>("NNoutput3");
  h_NNoutput4 = ctx.get_handle<double>("NNoutput4");

  init();
}

void HHtoWWbbSemiLeptonicMulticlassNNHists::init(){

NN_out0 = book<TH1F>("NN_out0", "NN output 0", 40, 0, 1);
NN_out1 = book<TH1F>("NN_out1", "NN output 1", 40, 0, 1);
NN_out2 = book<TH1F>("NN_out2", "NN output 2", 40, 0, 1);
NN_out3 = book<TH1F>("NN_out3", "NN output 3", 40, 0, 1);
NN_out4 = book<TH1F>("NN_out4", "NN output 4", 40, 0, 1);

NN_out0_rebin = book<TH1F>("NN_out0_rebin", "NN output 0", 10, 0, 1);
NN_out1_rebin = book<TH1F>("NN_out1_rebin", "NN output 1", 10, 0, 1);
NN_out2_rebin = book<TH1F>("NN_out2_rebin", "NN output 2", 10, 0, 1);
NN_out3_rebin = book<TH1F>("NN_out3_rebin", "NN output 3", 10, 0, 1);
NN_out4_rebin = book<TH1F>("NN_out4_rebin", "NN output 4", 10, 0, 1);
}

void HHtoWWbbSemiLeptonicMulticlassNNHists::fill(const Event & event){

double weight = event.weight;
double NNoutput0 = event.get(h_NNoutput0);
double NNoutput1 = event.get(h_NNoutput1);
double NNoutput2 = event.get(h_NNoutput2);
double NNoutput3 = event.get(h_NNoutput3);
double NNoutput4 = event.get(h_NNoutput4);

NN_out0->Fill(NNoutput0, weight);
NN_out1->Fill(NNoutput1, weight);
NN_out2->Fill(NNoutput2, weight);
NN_out3->Fill(NNoutput3, weight);
NN_out4->Fill(NNoutput4, weight);

NN_out0_rebin->Fill(NNoutput0, weight);
NN_out1_rebin->Fill(NNoutput1, weight);
NN_out2_rebin->Fill(NNoutput2, weight);
NN_out3_rebin->Fill(NNoutput3, weight);
NN_out4_rebin->Fill(NNoutput4, weight);
}

HHtoWWbbSemiLeptonicMulticlassNNHists::~HHtoWWbbSemiLeptonicMulticlassNNHists(){}



HHtoWWbbSemiLeptonicMulticlassNNInputHists::HHtoWWbbSemiLeptonicMulticlassNNInputHists(uhh2::Context& ctx, const std::string& dirname): Hists(ctx, dirname) {

  /*
  NNInputs_id = {"mbb", "mWW", "mlnu", "mqq", "DeltaRlnu", "DeltaRbb", "DeltaRqq", "minDeltaRlj", "minDeltaRbj", "minDeltaRjj", "HT", "N_BTag", "N_Ak4", "mtop_lep_hyp1", "mtop_lep_hyp2", "mtop_had_hyp1", "mtop_had_hyp2", "MH_bb", "MH_WW", "Lep_pt", "Lep_eta", "Lep_phi", "Lep_E", "MET_pt", "MET_phi", "Ak4_j1_pt", "Ak4_j1_eta", "Ak4_j1_phi", "Ak4_j1_E", "Ak4_j1_m", "Ak4_j1_deepjetbscore", "Ak4_j2_pt", "Ak4_j2_eta", "Ak4_j2_phi", "Ak4_j2_E", "Ak4_j2_m", "Ak4_j2_deepjetbscore", "Ak4_j3_pt", "Ak4_j3_eta", "Ak4_j3_phi", "Ak4_j3_E", "Ak4_j3_m", "Ak4_j3_deepjetbscore", "Ak4_j4_pt", "Ak4_j4_eta", "Ak4_j4_phi", "Ak4_j4_E", "Ak4_j4_m", "Ak4_j4_deepjetbscore", "Ak4_j5_pt", "Ak4_j5_eta", "Ak4_j5_phi", "Ak4_j5_E", "Ak4_j5_m", "Ak4_j5_deepjetbscore", "Ak4_j6_pt", "Ak4_j6_eta", "Ak4_j6_phi", "Ak4_j6_E", "Ak4_j6_m", "Ak4_j6_deepjetbscore"};

  NNInputs_map = {
    {"mbb", h_mbb},
    {"mWW", h_mWW},
    {"mqq", h_mqq},
    {"mlnu", h_mlnu},
    {"DeltaRlnu", h_DeltaRlnu},
    {"DeltaRbb", h_DeltaRbb},
    {"DeltaRqq", h_DeltaRqq},
    {"minDeltaRlj", h_minDeltaRlj},
    {"minDeltaRbj", h_minDeltaRbj},
    {"minDeltaRjj", h_minDeltaRjj},
    {"HT", h_HT},
    {"N_BTag", h_N_BTag},
    {"N_Ak4", h_N_Ak4},
    {"mtop_lep_hyp1", h_mtop_lep_hyp1},
    {"mtop_lep_hyp2", h_mtop_lep_hyp2},
    {"mtop_had_hyp1", h_mtop_had_hyp1},
    {"mtop_had_hyp2", h_mtop_had_hyp2},
    {"MH_bb", h_MH_bb},
    {"MH_WW", h_MH_WW},
    {"Lep_pt", h_Lep_pt},
    {"Lep_eta", h_Lep_eta},
    {"Lep_phi", h_Lep_phi},
    {"Lep_E", h_Lep_E},
    {"MET_pt", h_MET_pt},    
    {"MET_phi", h_MET_phi},
    {"Ak4_j1_pt", h_Ak4_j1_pt},    
    {"Ak4_j1_eta", h_Ak4_j1_eta},
    {"Ak4_j1_phi", h_Ak4_j1_phi},
    {"Ak4_j1_E", h_Ak4_j1_E},
    {"Ak4_j1_m", h_Ak4_j1_E},
    {"Ak4_j1_deepjetbscore", h_Ak4_j1_deepjetbscore},
    {"Ak4_j2_pt", h_Ak4_j2_pt},    
    {"Ak4_j2_eta", h_Ak4_j2_eta},
    {"Ak4_j2_phi", h_Ak4_j2_phi},
    {"Ak4_j2_E", h_Ak4_j2_E},
    {"Ak4_j2_m", h_Ak4_j2_E},
    {"Ak4_j2_deepjetbscore", h_Ak4_j2_deepjetbscore},
    {"Ak4_j3_pt", h_Ak4_j3_pt},
    {"Ak4_j3_eta", h_Ak4_j3_eta},
    {"Ak4_j3_phi", h_Ak4_j3_phi},
    {"Ak4_j3_E", h_Ak4_j3_E},
    {"Ak4_j3_m", h_Ak4_j3_E},
    {"Ak4_j3_deepjetbscore", h_Ak4_j3_deepjetbscore},
    {"Ak4_j4_pt", h_Ak4_j4_pt},
    {"Ak4_j4_eta", h_Ak4_j4_eta},
    {"Ak4_j4_phi", h_Ak4_j4_phi},
    {"Ak4_j4_E", h_Ak4_j4_E},
    {"Ak4_j4_m", h_Ak4_j4_E},
    {"Ak4_j4_deepjetbscore", h_Ak4_j4_deepjetbscore},
    {"Ak4_j5_pt", h_Ak4_j5_pt},
    {"Ak4_j5_eta", h_Ak4_j5_eta},
    {"Ak4_j5_phi", h_Ak4_j5_phi},
    {"Ak4_j5_E", h_Ak4_j5_E},
    {"Ak4_j5_m", h_Ak4_j5_E},
    {"Ak4_j5_deepjetbscore", h_Ak4_j5_deepjetbscore},
    {"Ak4_j6_pt", h_Ak4_j6_pt},
    {"Ak4_j6_eta", h_Ak4_j6_eta},
    {"Ak4_j6_phi", h_Ak4_j6_phi},
    {"Ak4_j6_E", h_Ak4_j6_E},
    {"Ak4_j6_m", h_Ak4_j6_E},
    {"Ak4_j6_deepjetbscore", h_Ak4_j6_deepjetbscore}
  };

  // NN_Variables handles

  
  for(string var : NNInputs_id) {
    map<string, uhh2::Event::Handle<float>>::iterator it = NNInputs_map.find(var);
    if(it == NNInputs_map.end()) throw runtime_error("NNInputs_map in NeuralNetworkModule: "+var+ " is not mapped");
    NNInputs_map.find(var)->second = ctx.get_handle<float>(var);
  }
}
  */


  //high-level
  h_mbb = ctx.get_handle<float> ("mbb");
  h_mlnu = ctx.get_handle<float> ("mlnu");
  h_mqq= ctx.get_handle<float> ("mqq");
  h_DeltaRlnu = ctx.get_handle<float> ("DeltaRlnu");
  h_DeltaRbb = ctx.get_handle<float> ("DeltaRbb");
  h_DeltaRqq = ctx.get_handle<float> ("DeltaRqq");
  h_minDeltaRlj = ctx.get_handle<float> ("minDeltaRlj");
  h_minDeltaRbj = ctx.get_handle<float> ("minDeltaRbj");
  h_minDeltaRjj = ctx.get_handle<float> ("minDeltaRjj");
  h_HT = ctx.get_handle<float> ("HT");
  h_N_BTag = ctx.get_handle<float> ("N_BTag");
  h_N_Ak4 = ctx.get_handle<float> ("N_Ak4");

  h_mtop_lep_hyp1 = ctx.get_handle<float> ("mtop_lep_hyp1");
  h_mtop_lep_hyp2 = ctx.get_handle<float> ("mtop_lep_hyp2");
  h_mtop_had_hyp1 = ctx.get_handle<float> ("mtop_had_hyp1");
  h_mtop_had_hyp2 = ctx.get_handle<float> ("mtop_had_hyp2");

  h_MH_bb = ctx.get_handle<float> ("MH_bb");
  h_MH_WW = ctx.get_handle<float> ("MH_WW");


  //low-level

///  Leptons
  h_Lep_pt = ctx.get_handle<float> ("Lep_pt");
  h_Lep_eta = ctx.get_handle<float> ("Lep_eta");
  h_Lep_phi = ctx.get_handle<float> ("Lep_phi");
  h_Lep_E = ctx.get_handle<float> ("Lep_E");


///  MET
  h_MET_pt = ctx.get_handle<float> ("MET_pt");
  h_MET_phi = ctx.get_handle<float> ("MET_phi");

///  AK4 JETS

  h_Ak4_j1_pt = ctx.get_handle<float> ("Ak4_j1_pt");
  h_Ak4_j1_eta = ctx.get_handle<float>("Ak4_j1_eta");
  h_Ak4_j1_phi = ctx.get_handle<float>("Ak4_j1_phi");
  h_Ak4_j1_E = ctx.get_handle<float>  ("Ak4_j1_E");
  h_Ak4_j1_m = ctx.get_handle<float>  ("Ak4_j1_m");
  h_Ak4_j1_deepjetbscore = ctx.get_handle<float>  ("Ak4_j1_deepjetbscore");

  h_Ak4_j2_pt = ctx.get_handle<float> ("Ak4_j2_pt");
  h_Ak4_j2_eta = ctx.get_handle<float>("Ak4_j2_eta");
  h_Ak4_j2_phi = ctx.get_handle<float>("Ak4_j2_phi");
  h_Ak4_j2_E = ctx.get_handle<float>  ("Ak4_j2_E");
  h_Ak4_j2_m = ctx.get_handle<float>  ("Ak4_j2_m");
  h_Ak4_j2_deepjetbscore = ctx.get_handle<float>  ("Ak4_j2_deepjetbscore");

  init();
}

void HHtoWWbbSemiLeptonicMulticlassNNInputHists::init(){

  //high-level
  NN_mbb = book<TH1F>("NN_mbb", "NN_mbb", 40,0,400);
  NN_mlnu = book<TH1F>("NN_mlnu", "NN_mlnu", 40,0,400);
  NN_mqq = book<TH1F>("NN_mqq", "NN_mqq", 40,0,400);
  NN_DeltaRlnu = book<TH1F>("NN_DeltaRlnu", "NN_DeltaRlnu", 40,0,6);
  NN_DeltaRbb = book<TH1F>("NN_DeltaRbb", "NN_DeltaRbb", 40,0,6);
  NN_DeltaRqq = book<TH1F>("NN_DeltaRqq", "NN_DeltaRqq", 40,0,6);
  NN_minDeltaRlj = book<TH1F>("NN_minDeltaRlj", "NN_minDeltaRlj", 40,0,6);
  NN_minDeltaRbj = book<TH1F>("NN_minDeltaRbj", "NN_minDeltaRbj", 40,0,6);
  NN_minDeltaRjj = book<TH1F>("NN_minDeltaRjj", "NN_minDeltaRjj", 40,0,6);
  NN_HT = book<TH1F>("NN_HT", "NN_HT", 40,0,800);
  NN_NBTag = book<TH1F>("NN_NBTag", "NN_NBTag", 6,-0.5,5.5);
  NN_NAk4 = book<TH1F>("NN_NAk4", "NN_NAk4", 11,-0.5,10.5);
  NN_mtop_lep1 = book<TH1F>("NN_mtop_lep1", "NN_mtop_lep1", 40,0,400);
  NN_mtop_lep2 = book<TH1F>("NN_mtop_lep2", "NN_mtop_lep2", 40,0,400);
  NN_mtop_had1 = book<TH1F>("NN_mtop_had1", "NN_mtop_had1", 40,0,400);
  NN_mtop_had2 = book<TH1F>("NN_mtop_had2", "NN_mtop_had2", 40,0,400);

  NN_MH_bb = book<TH1F>("NN_MH_bb", "NN_MH_bb", 40,0,400);
  NN_MH_WW = book<TH1F>("NN_MH_WW", "NN_MH_WW", 40,0,400);

  //low-level
  NN_Lep_pt = book<TH1F>("NN_Lep_pt", "NN_Lep_pt", 40, 0, 400);
  NN_Lep_eta = book<TH1F>("NN_Lep_eta", "NN_Lep_eta", 40, -2.5, 2.5);
  NN_Lep_phi = book<TH1F>("NN_Lep_phi", "NN_Lep_phi", 40, -4, 4);
  NN_Lep_E = book<TH1F>("NN_Lep_E", "NN_Lep_E", 40, 0, 200);

  NN_MET_pt = book<TH1F>("NN_MET_pt", "NN_MET_pt", 40, 0, 400);
  NN_MET_phi = book<TH1F>("NN_MET_phi", "NN_MET_phi", 40, -4, 4);

  NN_Ak4_j1_pt = book<TH1F>("NN_Ak4_j1_pt", "NN_Ak4_j1_pt", 40, 0, 400);
  NN_Ak4_j1_eta = book<TH1F>("NN_Ak4_j1_eta", "NN_Ak4_j1_eta", 40, -2.5, 2.5);
  NN_Ak4_j1_phi = book<TH1F>("NN_Ak4_j1_phi", "NN_Ak4_j1_phi", 40, -4, 4);
  NN_Ak4_j1_E = book<TH1F>("NN_Ak4_j1_E", "NN_Ak4_j1_E", 40, 0, 400);
  NN_Ak4_j1_m = book<TH1F>("NN_Ak4_j1_m", "NN_Ak4_j1_m", 40, 0, 400);
  NN_Ak4_j1_deepjetbscore = book<TH1F>("NN_Ak4_j1_deepjetbscore", "NN_Ak4_j1_deepjetbscore", 40, 0, 1);

  NN_Ak4_j2_pt = book<TH1F>("NN_Ak4_j2_pt", "NN_Ak4_j2_pt", 40, 0, 200);
  NN_Ak4_j2_eta = book<TH1F>("NN_Ak4_j2_eta", "NN_Ak4_j2_eta", 40, -2.5, 2.5);
  NN_Ak4_j2_phi = book<TH1F>("NN_Ak4_j2_phi", "NN_Ak4_j2_phi", 40, -4, 4);
  NN_Ak4_j2_E = book<TH1F>("NN_Ak4_j2_E", "NN_Ak4_j2_E", 40, 0, 400);
  NN_Ak4_j2_m = book<TH1F>("NN_Ak4_j2_m", "NN_Ak4_j2_m", 40, 0, 400);
  NN_Ak4_j2_deepjetbscore = book<TH1F>("NN_Ak4_j2_deepjetbscore", "NN_Ak4_j2_deepjetbscore", 40, 0, 1);


}

void HHtoWWbbSemiLeptonicMulticlassNNInputHists::fill(const Event & event){

  double weight = event.weight;

  // NN_Variables
  // cout << "mlnu: " << event.get(h_mlnu) << endl;


  //high-level
  NN_mbb->Fill(event.get(h_mbb), weight);
  NN_mlnu->Fill(event.get(h_mlnu), weight);
  NN_mqq->Fill(event.get(h_mqq), weight);
  NN_DeltaRlnu->Fill(event.get(h_DeltaRlnu), weight);
  NN_DeltaRbb->Fill(event.get(h_DeltaRbb), weight);
  NN_DeltaRqq->Fill(event.get(h_DeltaRqq), weight);
  NN_minDeltaRlj->Fill(event.get(h_minDeltaRlj), weight);
  NN_minDeltaRbj->Fill(event.get(h_minDeltaRbj), weight);
  NN_minDeltaRjj->Fill(event.get(h_minDeltaRjj), weight);
  NN_HT->Fill(event.get(h_HT), weight);
  NN_NBTag->Fill(event.get(h_N_BTag), weight);
  NN_NAk4->Fill(event.get(h_N_Ak4), weight);
  NN_mtop_lep1->Fill(event.get(h_mtop_lep_hyp1), weight);
  NN_mtop_lep2->Fill(event.get(h_mtop_lep_hyp2), weight);
  NN_mtop_had1->Fill(event.get(h_mtop_had_hyp1), weight);
  NN_mtop_had2->Fill(event.get(h_mtop_had_hyp2), weight);

  NN_MH_bb->Fill(event.get(h_MH_bb), weight);
  NN_MH_WW->Fill(event.get(h_MH_WW), weight);
  
  //low-level
  NN_Lep_pt->Fill(event.get(h_Lep_pt), weight);
  NN_Lep_eta->Fill(event.get(h_Lep_eta), weight);
  NN_Lep_phi->Fill(event.get(h_Lep_phi), weight);
  NN_Lep_E->Fill(event.get(h_Lep_E), weight);

  NN_MET_pt->Fill(event.get(h_MET_pt), weight);
  NN_MET_phi->Fill(event.get(h_MET_phi), weight);

  NN_Ak4_j1_pt->Fill(event.get(h_Ak4_j1_pt), weight);
  NN_Ak4_j1_eta->Fill(event.get(h_Ak4_j1_eta), weight);
  NN_Ak4_j1_phi->Fill(event.get(h_Ak4_j1_phi), weight);
  NN_Ak4_j1_E->Fill(event.get(h_Ak4_j1_E), weight);
  NN_Ak4_j1_m->Fill(event.get(h_Ak4_j1_m), weight);
  NN_Ak4_j1_deepjetbscore->Fill(event.get(h_Ak4_j1_deepjetbscore), weight);

  NN_Ak4_j2_pt->Fill(event.get(h_Ak4_j2_pt), weight);
  NN_Ak4_j2_eta->Fill(event.get(h_Ak4_j2_eta), weight);
  NN_Ak4_j2_phi->Fill(event.get(h_Ak4_j2_phi), weight);
  NN_Ak4_j2_E->Fill(event.get(h_Ak4_j2_E), weight);
  NN_Ak4_j2_m->Fill(event.get(h_Ak4_j2_m), weight);
  NN_Ak4_j2_deepjetbscore->Fill(event.get(h_Ak4_j2_deepjetbscore), weight);

}

HHtoWWbbSemiLeptonicMulticlassNNInputHists::~HHtoWWbbSemiLeptonicMulticlassNNInputHists(){}
