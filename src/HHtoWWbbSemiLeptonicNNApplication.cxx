#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/core/include/Utils.h"
#include "UHH2/core/include/Event.h"

#include "UHH2/common/include/EventHists.h"
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/MuonHists.h"
#include "UHH2/common/include/MuonIds.h"
#include "UHH2/common/include/ElectronIds.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/common/include/JetHists.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/TopJetIds.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/MCWeight.h"
#include "UHH2/common/include/EventVariables.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/EventVariables.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/AdditionalSelections.h"
#include "UHH2/common/include/LumiSelection.h"
#include "UHH2/common/include/LuminosityHists.h"
#include "UHH2/common/include/TriggerSelection.h"
#include "UHH2/common/include/Utils.h"

#include "UHH2/common/include/NeuralNetworkBase.hpp"

// my own classes
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicSelections.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicHists.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicGenHists.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicMatchedHists.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicMulticlassNNHists.h"


#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicModules.h"
//#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicPDFHists.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenObjects.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenRecoMatching.h"

#include "UHH2/HHtoWWbbSemiLeptonic/include/HHMassReconstruction.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesis.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesisDiscriminators.h"
//#include "UHH2/LQTopLep/include/LQTopLepModules.h" // for trigger SF's

#include <UHH2/HHtoWWbbSemiLeptonic/include/ModuleBASE.h>



using namespace std;
using namespace uhh2;
using namespace uhh2examples;

class NeuralNetworkModule: public NeuralNetworkBase {
public:
  explicit NeuralNetworkModule(uhh2::Context&, const std::string & ModelName, const std::string& ConfigName);
  virtual void CreateInputs(uhh2::Event & event) override;
protected:
  uhh2::Event::Handle<float> h_eventweight;
  uhh2::Event::Handle<float> h_mbb, h_mlnu, h_mqq;
  uhh2::Event::Handle<float> h_DeltaRlnu, h_DeltaRbb, h_DeltaRqq;
  uhh2::Event::Handle<float> h_minDeltaRlj, h_minDeltaRbj, h_minDeltaRjj;
  uhh2::Event::Handle<float> h_HT;
  uhh2::Event::Handle<float> h_N_BTag, h_N_Ak4;
  uhh2::Event::Handle<float> h_mtop_lep_hyp1, h_mtop_lep_hyp2, h_mtop_had_hyp1, h_mtop_had_hyp2;
  uhh2::Event::Handle< float > h_MH_WW;//, h_MH_bb;


  uhh2::Event::Handle< float > h_Lep_pt, h_Lep_eta, h_Lep_phi, h_Lep_E;
  uhh2::Event::Handle< float > h_MET_pt, h_MET_phi;
  uhh2::Event::Handle< float > h_Ak4_j1_pt, h_Ak4_j1_eta, h_Ak4_j1_phi, h_Ak4_j1_E, h_Ak4_j1_m, h_Ak4_j1_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j2_pt, h_Ak4_j2_eta, h_Ak4_j2_phi, h_Ak4_j2_E, h_Ak4_j2_m, h_Ak4_j2_deepjetbscore;
  //uhh2::Event::Handle< float > h_Ak4_j3_pt, h_Ak4_j3_eta, h_Ak4_j3_phi, h_Ak4_j3_E, h_Ak4_j3_m, h_Ak4_j3_deepjetbscore;
  //uhh2::Event::Handle< float > h_Ak4_j4_pt, h_Ak4_j4_eta, h_Ak4_j4_phi, h_Ak4_j4_E, h_Ak4_j4_m, h_Ak4_j4_deepjetbscore;
  //uhh2::Event::Handle< float > h_Ak4_j5_pt, h_Ak4_j5_eta, h_Ak4_j5_phi, h_Ak4_j5_E, h_Ak4_j5_m, h_Ak4_j5_deepjetbscore;
  //uhh2::Event::Handle< float > h_Ak4_j6_pt, h_Ak4_j6_eta, h_Ak4_j6_phi, h_Ak4_j6_E, h_Ak4_j6_m, h_Ak4_j6_deepjetbscore;


};


NeuralNetworkModule::NeuralNetworkModule(Context& ctx, const std::string & ModelName, const std::string& ConfigName): NeuralNetworkBase(ctx, ModelName, ConfigName) {

  h_eventweight = ctx.declare_event_output<float> ("eventweight");
  // high-level observables

  h_mbb = ctx.get_handle<float> ("mbb");
  h_mlnu = ctx.get_handle<float> ("mlnu");
  h_mqq = ctx.get_handle<float> ("mqq");
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


///  Higgs masses (chi2)
  //h_MH_bb = ctx.get_handle<float> ("MH_bb");
  h_MH_WW = ctx.get_handle<float> ("MH_WW");


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
  /*
  h_Ak4_j3_pt = ctx.get_handle<float> ("Ak4_j3_pt");
  h_Ak4_j3_eta = ctx.get_handle<float>("Ak4_j3_eta");
  h_Ak4_j3_phi = ctx.get_handle<float>("Ak4_j3_phi");
  h_Ak4_j3_E = ctx.get_handle<float>  ("Ak4_j3_E");
  h_Ak4_j3_m = ctx.get_handle<float>  ("Ak4_j3_m");
  h_Ak4_j3_deepjetbscore = ctx.get_handle<float>  ("Ak4_j3_deepjetbscore");

  h_Ak4_j4_pt = ctx.get_handle<float> ("Ak4_j4_pt");
  h_Ak4_j4_eta = ctx.get_handle<float>("Ak4_j4_eta");
  h_Ak4_j4_phi = ctx.get_handle<float>("Ak4_j4_phi");
  h_Ak4_j4_E = ctx.get_handle<float>  ("Ak4_j4_E");
  h_Ak4_j4_m = ctx.get_handle<float>  ("Ak4_j4_m");
  h_Ak4_j4_deepjetbscore = ctx.get_handle<float>  ("Ak4_j4_deepjetbscore");

  h_Ak4_j5_pt = ctx.get_handle<float> ("Ak4_j5_pt");
  h_Ak4_j5_eta = ctx.get_handle<float>("Ak4_j5_eta");
  h_Ak4_j5_phi = ctx.get_handle<float>("Ak4_j5_phi");
  h_Ak4_j5_E = ctx.get_handle<float>  ("Ak4_j5_E");
  h_Ak4_j5_m = ctx.get_handle<float>  ("Ak4_j5_m");
  h_Ak4_j5_deepjetbscore = ctx.get_handle<float>  ("Ak4_j5_deepjetbscore");

  h_Ak4_j6_pt = ctx.get_handle<float> ("Ak4_j6_pt");
  h_Ak4_j6_eta = ctx.get_handle<float>("Ak4_j6_eta");
  h_Ak4_j6_phi = ctx.get_handle<float>("Ak4_j6_phi");
  h_Ak4_j6_E = ctx.get_handle<float>  ("Ak4_j6_E");
  h_Ak4_j6_m = ctx.get_handle<float>  ("Ak4_j6_m");
  h_Ak4_j6_deepjetbscore = ctx.get_handle<float>  ("Ak4_j6_deepjetbscore");
  */

///  Higgs masses
  //h_MH_bb = ctx.get_handle<float> ("MH_bb");
  h_MH_WW = ctx.get_handle<float> ("MH_WW");

}


void NeuralNetworkModule::CreateInputs(Event & event) {
  NNInputs.clear();
  NNoutputs.clear();
 
  int N_variables = 32; // change manually
  string varname[N_variables];
  string scal[N_variables];
  string mean[N_variables];
  string std[N_variables];
  double mean_val[N_variables];
  double std_val[N_variables];
  ifstream normfile ("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data/NNModel/NormInfo.txt", ios::in);
  if (normfile.is_open()) { 
    for(int i = 0; i < N_variables; ++i)
      {   
	normfile >> varname[i] >> scal[i] >> mean[i] >> std[i];
	mean_val[i] = std::stod(mean[i]);
	std_val[i] = std::stod(std[i]);
      }
    normfile.close();
  }
  NNInputs.push_back( tensorflow::Tensor(tensorflow::DT_FLOAT, {1, N_variables}));

  NNInputs.at(0).tensor<float, 2>()(0,0)  = (event.get(h_Ak4_j1_E)   - mean_val[0]) / (std_val[0]);
  NNInputs.at(0).tensor<float, 2>()(0,1)  = (event.get(h_Ak4_j1_deepjetbscore)   - mean_val[1]) / (std_val[1]);
  NNInputs.at(0).tensor<float, 2>()(0,2)  = (event.get(h_Ak4_j1_eta) - mean_val[2]) / (std_val[2]);
  NNInputs.at(0).tensor<float, 2>()(0,3)  = (event.get(h_Ak4_j1_m)   - mean_val[3]) / (std_val[3]);
  NNInputs.at(0).tensor<float, 2>()(0,4)  = (event.get(h_Ak4_j1_phi) - mean_val[4]) / (std_val[4]);
  NNInputs.at(0).tensor<float, 2>()(0,5)  = (event.get(h_Ak4_j1_pt)  - mean_val[5]) / (std_val[5]);

  NNInputs.at(0).tensor<float, 2>()(0,6)  = (event.get(h_Ak4_j2_E)   - mean_val[6]) / (std_val[6]);
  NNInputs.at(0).tensor<float, 2>()(0,7)  = (event.get(h_Ak4_j2_deepjetbscore)   - mean_val[7]) / (std_val[7]);
  NNInputs.at(0).tensor<float, 2>()(0,8)  = (event.get(h_Ak4_j2_eta) - mean_val[8]) / (std_val[8]);
  NNInputs.at(0).tensor<float, 2>()(0,9)  = (event.get(h_Ak4_j2_m)   - mean_val[9]) / (std_val[9]);
  NNInputs.at(0).tensor<float, 2>()(0,10)  = (event.get(h_Ak4_j2_phi) - mean_val[10]) / (std_val[10]);
  NNInputs.at(0).tensor<float, 2>()(0,11)  = (event.get(h_Ak4_j2_pt)  - mean_val[11]) / (std_val[11]);

  NNInputs.at(0).tensor<float, 2>()(0,12)  = (event.get(h_DeltaRbb)   - mean_val[12]) / (std_val[12]);
  NNInputs.at(0).tensor<float, 2>()(0,13)  = (event.get(h_DeltaRlnu)   - mean_val[13]) / (std_val[13]);
  NNInputs.at(0).tensor<float, 2>()(0,14)  = (event.get(h_DeltaRqq) - mean_val[14]) / (std_val[14]);
  NNInputs.at(0).tensor<float, 2>()(0,15)  = (event.get(h_HT)   - mean_val[15]) / (std_val[15]);
  NNInputs.at(0).tensor<float, 2>()(0,16)  = (event.get(h_Lep_E) - mean_val[16]) / (std_val[16]);
  NNInputs.at(0).tensor<float, 2>()(0,17)  = (event.get(h_Lep_eta)  - mean_val[17]) / (std_val[17]);

  NNInputs.at(0).tensor<float, 2>()(0,18)  = (event.get(h_Lep_phi)   - mean_val[18]) / (std_val[18]);
  NNInputs.at(0).tensor<float, 2>()(0,19)  = (event.get(h_Lep_pt)   - mean_val[19]) / (std_val[19]);
  NNInputs.at(0).tensor<float, 2>()(0,20)  = (event.get(h_MET_phi) - mean_val[20]) / (std_val[20]);
  NNInputs.at(0).tensor<float, 2>()(0,21)  = (event.get(h_MET_pt)   - mean_val[21]) / (std_val[21]);
  NNInputs.at(0).tensor<float, 2>()(0,22)  = (event.get(h_MH_WW) - mean_val[22]) / (std_val[22]);
  NNInputs.at(0).tensor<float, 2>()(0,23)  = (event.get(h_N_Ak4)  - mean_val[23]) / (std_val[23]);
  NNInputs.at(0).tensor<float, 2>()(0,24)  = (event.get(h_N_BTag)   - mean_val[24]) / (std_val[24]);
  NNInputs.at(0).tensor<float, 2>()(0,25)  = (event.get(h_mbb) - mean_val[25]) / (std_val[25]);
  NNInputs.at(0).tensor<float, 2>()(0,26)  = (event.get(h_mlnu)   - mean_val[26]) / (std_val[26]);
  NNInputs.at(0).tensor<float, 2>()(0,27)  = (event.get(h_mqq)   - mean_val[27]) / (std_val[27]);
  NNInputs.at(0).tensor<float, 2>()(0,28)  = (event.get(h_mtop_had_hyp1) - mean_val[28]) / (std_val[28]);
  NNInputs.at(0).tensor<float, 2>()(0,29)  = (event.get(h_mtop_had_hyp2)  - mean_val[29]) / (std_val[29]);
  NNInputs.at(0).tensor<float, 2>()(0,30)  = (event.get(h_mtop_lep_hyp1)   - mean_val[30]) / (std_val[30]);
  NNInputs.at(0).tensor<float, 2>()(0,31)  = (event.get(h_mtop_lep_hyp2)   - mean_val[31]) / (std_val[31]);

  if (NNInputs.size()!=LayerInputs.size()) throw logic_error("NeuralNetworkModule.cxx: Create a number of inputs diffetent wrt. LayerInputs.size()="+to_string(LayerInputs.size()));
}


// Change from here on
  
class HHtoWWbbSemiLeptonicNNApplication: public ModuleBASE {
public:

  explicit HHtoWWbbSemiLeptonicNNApplication(Context & ctx);
  virtual bool process(Event & event) override;
  void book_histograms(uhh2::Context&, vector<string>);
  void fill_histograms(uhh2::Event&, string, string region);

private:
  // necessary?
  uhh2::Event::Handle<float> h_eventweight;
  uhh2::Event::Handle<float> h_mbb, h_mlnu, h_mqq;
  uhh2::Event::Handle<float> h_DeltaRlnu, h_DeltaRbb, h_DeltaRqq;
  uhh2::Event::Handle<float> h_minDeltaRlj, h_minDeltaRbj, h_minDeltaRjj;
  uhh2::Event::Handle<float> h_HT;
  uhh2::Event::Handle<float> h_N_BTag, h_N_Ak4;
  uhh2::Event::Handle<float> h_mtop_lep_hyp1, h_mtop_lep_hyp2, h_mtop_had_hyp1, h_mtop_had_hyp2;
  uhh2::Event::Handle< float > h_MH_WW;//, h_MH_bb;

  uhh2::Event::Handle< float > h_Lep_pt, h_Lep_eta, h_Lep_phi, h_Lep_E;
  uhh2::Event::Handle< float > h_MET_pt, h_MET_phi;
  uhh2::Event::Handle< float > h_Ak4_j1_pt, h_Ak4_j1_eta, h_Ak4_j1_phi, h_Ak4_j1_E, h_Ak4_j1_m, h_Ak4_j1_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j2_pt, h_Ak4_j2_eta, h_Ak4_j2_phi, h_Ak4_j2_E, h_Ak4_j2_m, h_Ak4_j2_deepjetbscore;
  //uhh2::Event::Handle< float > h_Ak4_j3_pt, h_Ak4_j3_eta, h_Ak4_j3_phi, h_Ak4_j3_E, h_Ak4_j3_m, h_Ak4_j3_deepjetbscore;
  //uhh2::Event::Handle< float > h_Ak4_j4_pt, h_Ak4_j4_eta, h_Ak4_j4_phi, h_Ak4_j4_E, h_Ak4_j4_m, h_Ak4_j4_deepjetbscore;
  //uhh2::Event::Handle< float > h_Ak4_j5_pt, h_Ak4_j5_eta, h_Ak4_j5_phi, h_Ak4_j5_E, h_Ak4_j5_m, h_Ak4_j5_deepjetbscore;
  //uhh2::Event::Handle< float > h_Ak4_j6_pt, h_Ak4_j6_eta, h_Ak4_j6_phi, h_Ak4_j6_E, h_Ak4_j6_m, h_Ak4_j6_deepjetbscore;

  std::unique_ptr<CommonModules> common;

  unique_ptr<Hists> h_btageff, h_MulticlassNN_output, h_NNInputVariables;
  std::unique_ptr<AnalysisModule> SF_muonIso, SF_muonID, SF_muonTrigger, SF_eleReco, SF_eleID, SF_eleTrigger, SF_btag;
  std::unique_ptr<Selection> nbtag1_medium_sel, nbtag2_medium_sel, njet4_sel, muon_trigger_sel1, muon_trigger_sel2, ele_trigger_sel1, ele_trigger_sel2, ele_trigger_sel3;
    

  unique_ptr<HHtoWWbbMassReconstruction> mHH_reco;
  unique_ptr<HHChi2Discriminator> chi2_module;

  // gen level stuff
  unique_ptr<uhh2::AnalysisModule> HHgenprod;
  uhh2::Event::Handle<HHGenObjects> h_HHgenobjects;

  unique_ptr<uhh2::AnalysisModule> HHgenrecoprod;
  uhh2::Event::Handle<HHGenRecoMatching> h_HHgenreco;


  // NN Stuff
  unique_ptr<Variables_NN> Variables_module;
  Event::Handle<vector<tensorflow::Tensor>> h_NNoutput;
  Event::Handle<double> h_NNoutput0, h_NNoutput1, h_NNoutput2, h_NNoutput3, h_NNoutput4;
  unique_ptr<NeuralNetworkModule> NNModule;

  // mass reco stuff
  uhh2::Event::Handle<bool> h_is_mHH_reconstructed;
  uhh2::Event::Handle<float> h_mHH, h_chi2;
  uhh2::Event::Handle<float> h_mH_bb, h_chi2_H_bb;
  uhh2::Event::Handle<float> h_mH_WW, h_chi2_H_WW;
    
  uhh2::Event::Handle<TString> h_region;


  uhh2::Event::Handle<float> h_muon_triggerweight, h_muon_triggerweight_up, h_muon_triggerweight_down;
  uhh2::Event::Handle<float> h_electron_triggerweight, h_electron_triggerweight_up, h_electron_triggerweight_down;


  JetId Btag_loose;
  BTag::algo btag_algo;
  BTag::wp wp_btag_loose, wp_btag_medium, wp_btag_tight;

  bool is_mc, do_permutations;
  bool is_signal;
  string s_permutation;

  uhh2::Event::Handle<float> h_eventweight_lumi, h_eventweight_final;



  // systematic uncertainties
  string Sys_EleID, Sys_EleReco;
  string Sys_MuonID, Sys_MuonIso;
  string Sys_BTag;
  string Sys_PU;


  TString dataset_version;
  Year year;

};


void HHtoWWbbSemiLeptonicNNApplication::book_histograms(uhh2::Context& ctx, vector<string> tags){
  for(const auto & tag : tags){
    cout << "booking histograms with tag " << tag << endl;
    string mytag = tag + "_srele" + "_General";
    book_HFolder(mytag, new HHtoWWbbSemiLeptonicHists(ctx,mytag));
    mytag = tag + "_srmu" + "_General";
    book_HFolder(mytag, new HHtoWWbbSemiLeptonicHists(ctx,mytag));

    mytag = tag + "_srele" + "_Signal"; 
    book_HFolder(mytag, new HHtoWWbbSemiLeptonicGenHists(ctx,mytag));
    mytag = tag + "_srmu" + "_Signal"; 
    book_HFolder(mytag, new HHtoWWbbSemiLeptonicGenHists(ctx,mytag));
    mytag = tag + "_srele" + "_Matched"; 
    book_HFolder(mytag, new HHtoWWbbSemiLeptonicMatchedHists(ctx,mytag));
    mytag = tag + "_srmu" + "_Matched"; 
    book_HFolder(mytag, new HHtoWWbbSemiLeptonicMatchedHists(ctx,mytag));
      
    /*
      mytag = tag+"_Muons";
      book_HFolder(mytag, new MuonHists(ctx,mytag));
      mytag = tag+"_Electrons";
      book_HFolder(mytag, new ElectronHists(ctx,mytag));
      mytag = tag+"_Jets";
      book_HFolder(mytag, new JetHists(ctx,mytag));
      mytag = tag+"_Event";
      book_HFolder(mytag, new EventHists(ctx,mytag));
    */
  }
}

void HHtoWWbbSemiLeptonicNNApplication::fill_histograms(uhh2::Event& event, string tag, string region){
  string mytag = tag + "_" + region + "_General";
  HFolder(mytag)->fill(event);
  if(is_signal){
    mytag = tag + "_" + region + "_Signal"; 
    HFolder(mytag)->fill(event);
    mytag = tag + "_" + region + "_Matched"; 
    HFolder(mytag)->fill(event);
  }
  /*
    mytag = tag+"_Muons";
    HFolder(mytag)->fill(event);
    mytag = tag+"_Electrons";
    HFolder(mytag)->fill(event);
    mytag = tag+"_Jets";
    HFolder(mytag)->fill(event);
    mytag = tag+"_Event";
    HFolder(mytag)->fill(event);
  */
}



HHtoWWbbSemiLeptonicNNApplication::HHtoWWbbSemiLeptonicNNApplication(Context & ctx){
  
  for(auto & kv : ctx.get_all()){
    cout << " " << kv.first << " = " << kv.second << endl;
  }


  h_eventweight_lumi = ctx.declare_event_output<float>("eventweight_lumi");
  h_eventweight_final = ctx.declare_event_output<float>("eventweight_final");

  // Gen level stuff
  const string HHgen_label("HHgenobjects");
  HHgenprod.reset(new HHGenObjectsProducer(ctx, HHgen_label, true));
  h_HHgenobjects = ctx.get_handle<HHGenObjects>(HHgen_label);
  const string HHgenreco_label("HHgenreco");
  HHgenrecoprod.reset(new HHGenRecoProducer(ctx, HHgenreco_label, true));
  h_HHgenreco = ctx.get_handle<HHGenRecoMatching>(HHgenreco_label);

  // for mass reco
  h_is_mHH_reconstructed = ctx.declare_event_output<bool>("is_mHH_reconstructed");
  h_mHH = ctx.declare_event_output<float>("mHH");
  h_chi2 = ctx.declare_event_output<float>("chi2");

  h_mH_bb = ctx.declare_event_output<float>("mH_bb");
  h_chi2_H_bb = ctx.declare_event_output<float>("chi2_H_bb");
  h_mH_WW = ctx.declare_event_output<float>("mH_WW");
  h_chi2_H_WW = ctx.declare_event_output<float>("chi2_H_WW");

  h_region = ctx.declare_event_output<TString>("region");
  /*
    h_muon_triggerweight = ctx.declare_event_output<float>("weight_sfmu_trigger");
    h_muon_triggerweight_up = ctx.declare_event_output<float>("weight_sfmu_trigger_up");
    h_muon_triggerweight_down = ctx.declare_event_output<float>("weight_sfmu_trigger_down");

    h_electron_triggerweight = ctx.declare_event_output<float>("weight_sfelec_trigger");
    h_electron_triggerweight_up = ctx.declare_event_output<float>("weight_sfelec_trigger_up");
    h_electron_triggerweight_down = ctx.declare_event_output<float>("weight_sfelec_trigger_down");
  */

  is_mc = ctx.get("dataset_type") == "MC";
  year = extract_year(ctx);
  dataset_version = ctx.get("dataset_version");
  is_signal = dataset_version.Contains("HHtoWWbb");

  // BTagging
  btag_algo = BTag::DEEPJET;
  wp_btag_loose = BTag::WP_LOOSE;
  wp_btag_medium = BTag::WP_MEDIUM;
  wp_btag_tight = BTag::WP_TIGHT;

  JetId DeepjetLoose = BTag(btag_algo, wp_btag_loose);
  JetId DeepjetMedium = BTag(btag_algo, wp_btag_medium);
  JetId DeepjetTight = BTag(btag_algo, wp_btag_tight);

  // Triggers
  if(year == Year::is2016v2 || year == Year::is2016v3){
    muon_trigger_sel1.reset(new TriggerSelection("HLT_IsoMu24_v*"));
    muon_trigger_sel2.reset(new TriggerSelection("HLT_IsoTkMu24_v*"));
    ele_trigger_sel1.reset(new TriggerSelection("HLT_Ele27_WPTight_Gsf_v*"));
    ele_trigger_sel2.reset(new TriggerSelection("HLT_Ele115_CaloIdVT_GsfTrkIdT_v*"));
    ele_trigger_sel3.reset(new TriggerSelection("HLT_Photon175_v*"));

  }
  else if(year == Year::is2017v1 || year == Year::is2017v2){
    muon_trigger_sel1.reset(new TriggerSelection("HLT_IsoMu27_v*"));
    muon_trigger_sel2.reset(new TriggerSelection("HLT_IsoMu27_v*"));
    ele_trigger_sel1.reset(new TriggerSelection("HLT_Ele35_WPTight_Gsf_v*"));
    ele_trigger_sel2.reset(new TriggerSelection("HLT_Ele115_CaloIdVT_GsfTrkIdT_v*")); // this trigger does not work for some 2017 Electron+Photon B events
    ele_trigger_sel3.reset(new TriggerSelection("HLT_Photon200_v*"));
  }
  else if(year == Year::is2018){
    muon_trigger_sel1.reset(new TriggerSelection("HLT_IsoMu24_v*"));
    muon_trigger_sel2.reset(new TriggerSelection("HLT_IsoMu24_v*"));
    ele_trigger_sel1.reset(new TriggerSelection("HLT_Ele32_WPTight_Gsf_v*"));
    ele_trigger_sel2.reset(new TriggerSelection("HLT_Ele115_CaloIdVT_GsfTrkIdT_v*"));
    ele_trigger_sel3.reset(new TriggerSelection("HLT_Ele32_WPTight_Gsf_v*"));
  }


  // initialize HH Mass Reconstruction
    
  mHH_reco.reset(new HHtoWWbbMassReconstruction(ctx));
  chi2_module.reset(new HHChi2Discriminator(ctx, "HHHypotheses"));

  // systematic uncertainties
  Sys_EleID = ctx.get("Systematic_EleID");
  Sys_EleReco = ctx.get("Systematic_EleReco");
  Sys_MuonID = ctx.get("Systematic_MuonID");
  Sys_MuonIso = ctx.get("Systematic_MuonIso");
  Sys_BTag = ctx.get("Systematic_BTag");
  Sys_PU = ctx.get("Systematic_PU");


  // scale factors

  SF_muonID.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/MuonID_EfficienciesAndSF_average_RunBtoH.root", "NUM_TightID_DEN_genTracks_eta_pt", 0., "id", false, Sys_MuonID));
  SF_muonIso.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/MuonIso_EfficienciesAndSF_average_RunBtoH.root", "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt", 0., "iso", false, Sys_MuonIso));
  //SF_muonTrigger.reset(new MuonTriggerWeights(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/MuonTrigger_EfficienciesAndSF_average_RunBtoH.root", "IsoMu24_OR_IsoTkMu24_PtEtaBins"), 0.);
  //SF_muonTrigger.reset(new MuonTriggerWeights(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/LQTopLep/data", year));

  SF_eleReco.reset(new MCElecScaleFactor(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root", 1, "reco", Sys_EleReco));
  SF_eleID.reset(new MCElecScaleFactor(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/2016LegacyReReco_ElectronTight_Fall17V2.root", 1, "id", Sys_EleID));
  //SF_eleTrigger.reset(new ElectronTriggerWeights(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/LQTopLep/data", year));





  // SF_btag.reset(new MCBTagScaleFactor(ctx, btag_algo, wp_btag_medium, "jets", Sys_BTag)); // comment out when re-doing SF_btag


  // CommonModules
  common.reset(new CommonModules());
  common->disable_lumisel();
  common->disable_jersmear();
  common->disable_jec();
  common->init(ctx, Sys_PU);

  // Selections
  nbtag1_medium_sel.reset(new NJetSelection(1, -1, DeepjetMedium));
  nbtag2_medium_sel.reset(new NJetSelection(2, -1, DeepjetMedium));
  njet4_sel.reset(new NJetSelection(4, -1));

  // NN Stuff
  Variables_module.reset(new Variables_NN(ctx));
  h_NNoutput = ctx.get_handle<vector<tensorflow::Tensor>>("NNoutput");
  h_NNoutput0 = ctx.declare_event_output<double>("NNoutput0");
  h_NNoutput1 = ctx.declare_event_output<double>("NNoutput1");
  h_NNoutput2 = ctx.declare_event_output<double>("NNoutput2");
  h_NNoutput3 = ctx.declare_event_output<double>("NNoutput3");
  h_NNoutput4 = ctx.declare_event_output<double>("NNoutput4");

  string data_dir = "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data//";
  NNModule.reset(new NeuralNetworkModule(ctx, data_dir+"NNModel/test_model.pb", data_dir+"NNModel/test_model.config.pbtxt"));
  

  // Book histograms
  vector<string> histogram_tags = {"Cleaner", "Trigger", "TriggerSF", "BTag", "mHH_reconstructed", "4JetCategory", "DNN_output0", "DNN_output1", "DNN_output2", "DNN_output3", "DNN_output4"};
  book_histograms(ctx, histogram_tags);

  h_btageff.reset(new BTagMCEfficiencyHists(ctx, "BTagEff", DeepjetMedium));
  h_MulticlassNN_output.reset(new HHtoWWbbSemiLeptonicMulticlassNNHists(ctx, "MulticlassNN"));
  h_NNInputVariables.reset(new HHtoWWbbSemiLeptonicMulticlassNNInputHists(ctx, "NNInputVariables"));
  //h_xx = ctx.get_handle<float>("xx");

  
  // necessary?
  h_mbb = ctx.get_handle<float> ("mbb");
  h_mlnu = ctx.get_handle<float> ("mlnu");
  h_mqq = ctx.get_handle<float> ("mqq");
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


///  Higgs masses (chi2)
  //h_MH_bb = ctx.get_handle<float> ("MH_bb");
  h_MH_WW = ctx.get_handle<float> ("MH_WW");


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
}


bool HHtoWWbbSemiLeptonicNNApplication::process(Event & event) {
  // cout << "Fullselection: process" << endl;
  // cout << "FullselectionModule Line: " << __LINE__ << endl;

  // cout << "dataset_version: "<< dataset_version << endl;
  if (is_signal){
    HHgenprod->process(event);
    HHgenrecoprod->process(event);
  }
  event.set(h_is_mHH_reconstructed, false);
  event.set(h_mHH, -1);
  event.set(h_chi2, -1);

  event.set(h_mH_bb, -1);
  event.set(h_chi2_H_bb, -1);
  event.set(h_mH_WW, -1);
  event.set(h_chi2_H_WW, -1);

  string region = "";

  if(event.muons->size() == 1 && event.electrons->size() == 0) region = "srmu";
  else if(event.electrons->size() == 1 && event.muons->size() == 0) region = "srele";
  else throw runtime_error("In HHtoWWbbSemiLeptonicFullSelectionModule: region is neither srmu or srele");
    

  //cout << "test: "<< event.get(h_mHH) << endl;

  mHH_reco->process(event);    
  //cout << "mHH reconstructed? " << event.get(h_is_mHH_reconstructed) << endl;
  chi2_module->process(event);

  Variables_module->process(event);
  bool pass_common = common->process(event);
  if(!pass_common) return false;


  double eventweight_lumi = event.weight;
  event.set(h_eventweight_lumi, eventweight_lumi);
    

  SF_eleReco->process(event);
  SF_eleID->process(event);
    
  SF_muonID->process(event);
  SF_muonIso->process(event);
    
  fill_histograms(event,"Cleaner", region);

  TString leptonregion = "muon";
  if(region == "srele") leptonregion = "ele";

  if(leptonregion == "muon"){
    // Muon regions
    if(!(muon_trigger_sel1->passes(event) || muon_trigger_sel2->passes(event))) return false;

    //cout << "dataset_version: " << dataset_version << endl;
    // Reject electron and photon data
    if(!is_mc && !dataset_version.Contains("Muon")) return false;
  }
  else{
    // Electron regions
    if(!is_mc && (year == Year::is2017v1 || year == Year::is2017v2) && event.run < 299368) { // Trigger 2 does not work here
      if(dataset_version.Contains("Electron")){
	if(!(ele_trigger_sel1->passes(event))) return false;
      }
      else if(dataset_version.Contains("Photon")){
	// Automatically discards photon data in 2018
	if(!(!ele_trigger_sel1->passes(event) && ele_trigger_sel3->passes(event))) return false;
      }
    }
    else if(!is_mc){
      if(dataset_version.Contains("Electron")){
	if(!(ele_trigger_sel1->passes(event) || ele_trigger_sel2->passes(event))) return false;
      }
      else if(dataset_version.Contains("Photon")){
	// Automatically discards photon data in 2018
	if(!(!(ele_trigger_sel1->passes(event) || ele_trigger_sel2->passes(event)) && ele_trigger_sel3->passes(event))) return false;
      }
      // Reject muon data
      else return false;
    }
    else{
      // Just a simple OR for MC
      if(!(ele_trigger_sel1->passes(event) || ele_trigger_sel2->passes(event) || ele_trigger_sel3->passes(event))) return false;
    }
  }
  fill_histograms(event, "Trigger", region);

  /*
    if(leptonregion == "muon"){
    SF_muonTrigger->process(event);
    event.set(h_electron_triggerweight, 1.);
    event.set(h_electron_triggerweight_up, 1.);
    event.set(h_electron_triggerweight_down, 1.);
    }
    else{
    SF_eleTrigger->process(event);
    event.set(h_muon_triggerweight, 1.);
    event.set(h_muon_triggerweight_up, 1.);
    event.set(h_muon_triggerweight_down, 1.);
    }
    fill_histograms(event,"TriggerSF", region);
  */


  //SF_btag->process(event); //comment out when re-doing SF_btag
  h_btageff->fill(event);

  if(!nbtag1_medium_sel->passes(event)) return false; // comment out when re-doing SF_btag
  fill_histograms(event,"BTag", region);
  //if(!nbtag2_medium_sel->passes(event)) return false;


  bool is_mHH_reconstructed = event.get(h_is_mHH_reconstructed);
  // cout << "is_mHH_reconstructed: " << is_mHH_reconstructed << endl;
  if(is_mHH_reconstructed) fill_histograms(event, "mHH_reconstructed", region);

  // DNN: for now only in srmu; should be done seperately for ech and much at some point
    
  if(leptonregion != "muon") return false; // quick hack to only consider muons in DNN
  if(!njet4_sel->passes(event)) return false; // quick hack to only consider 4 Jet category


  fill_histograms(event, "4JetCategory", region);
  NNModule->process(event);
  h_NNInputVariables->fill(event);

  vector<tensorflow::Tensor> NNoutputs = NNModule->GetOutputs();
  event.set(h_NNoutput, NNoutputs);

  double out0 =  (double)(NNoutputs[0].tensor<float, 2>()(0,0));
  double out1 =  (double)(NNoutputs[0].tensor<float, 2>()(0,1));
  double out2 =  (double)(NNoutputs[0].tensor<float, 2>()(0,2));
  double out3 =  (double)(NNoutputs[0].tensor<float, 2>()(0,3));
  double out4 =  (double)(NNoutputs[0].tensor<float, 2>()(0,4));
  //double out5 =  (double)(NNoutputs[0].tensor<float, 2>()(0,5));

  vector<double> out_event = {out0,out1,out2,out3,out4};

  cout << "out0= " << out0 << endl;
  cout << "out1= " << out1 << endl;
  cout << "out2= " << out2 << endl;
  cout << "out3= " << out3 << endl;
  cout << "out4= " << out4 << endl;
  //cout << "out5= " << out5 << endl;

  event.set(h_NNoutput0, out0);
  event.set(h_NNoutput1, out1);
  event.set(h_NNoutput2, out2);
  event.set(h_NNoutput3, out3);
  event.set(h_NNoutput4, out4);

  h_MulticlassNN_output->fill(event);
  // Categorization using NN output
  double max_score = 0.0;
  string max_score_tag = "";
  for (unsigned  int i = 0; i < out_event.size(); i++ ) {
    if ( out_event[i] > max_score) {
    max_score = out_event[i];
    max_score_tag = std::to_string(i);
    }
  }
  string DNN_hist_tag  = "DNN_output"+max_score_tag;
  fill_histograms(event, DNN_hist_tag, region);
  

  event.set(h_eventweight_final, event.weight);
  event.set(h_region, region);
  return true;
}

// as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
// make sure the HHtoWWbbSemiLeptonicNNApplication is found by class name. This is ensured by this macro:
UHH2_REGISTER_ANALYSIS_MODULE(HHtoWWbbSemiLeptonicNNApplication)
