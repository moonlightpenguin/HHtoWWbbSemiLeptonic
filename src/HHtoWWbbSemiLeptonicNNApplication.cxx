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

  uhh2::Event::Handle<float> h_mbb, h_mWW, h_mlnu, h_mqq;
  uhh2::Event::Handle<float> h_DeltaRlnu, h_DeltaRbb, h_DeltaRqq;
  uhh2::Event::Handle<float> h_minDeltaRlj, h_minDeltaRbj, h_minDeltaRjj;
  uhh2::Event::Handle<float> h_HT;
  uhh2::Event::Handle<float> h_N_BTag, h_N_Ak4;
  uhh2::Event::Handle<float> h_mtop_lep_hyp1, h_mtop_lep_hyp2, h_mtop_had_hyp1, h_mtop_had_hyp2;
  uhh2::Event::Handle<float> h_MH_bb, h_MH_WW;

  uhh2::Event::Handle<float> h_Lep_pt, h_Lep_eta, h_Lep_phi, h_Lep_E;
  uhh2::Event::Handle<float> h_MET_pt, h_MET_phi;

  uhh2::Event::Handle<float> h_Ak4_j1_pt, h_Ak4_j1_eta, h_Ak4_j1_phi, h_Ak4_j1_E, h_Ak4_j1_m, h_Ak4_j1_deepjetbscore;
  uhh2::Event::Handle<float> h_Ak4_j2_pt, h_Ak4_j2_eta, h_Ak4_j2_phi, h_Ak4_j2_E, h_Ak4_j2_m, h_Ak4_j2_deepjetbscore;


  //vector<uhh2::Event::Handle<float>> NNInputs = {h_mbb, h_mWW, h_mlnu, h_mqq, h_DeltaRlnu, h_DeltaRbb, h_DeltaRqq, h_minDeltaRbj, h_minDeltaRjj, h_HT, h_N_BTag, h_N_Ak4, h_mtop_lep_hyp1, h_mtop_lep_hyp2, h_mtop_had_hyp1, h_mtop_had_hyp2, h_MH_bb, h_MH_WW, h_Lep_pt, h_Lep_eta, h_Lep_phi, h_Lep_E, h_MET_pt, h_MET_phi, h_Ak4_j1_pt, h_Ak4_j1_eta, h_Ak4_j1_phi, h_Ak4_j1_E, h_Ak4_j1_m, h_Ak4_j1_deepjetbscore, h_Ak4_j2_pt, h_Ak4_j2_eta, h_Ak4_j2_phi, h_Ak4_j2_E, h_Ak4_j2_m, h_Ak4_j2_deepjetbscore};
  
  vector<string> NNInputs_id = {"mbb", "mWW", "mlnu", "mqq", "DeltaRlnu", "DeltaRbb", "DeltaRqq", "minDeltaRlj", "minDeltaRbj", "minDeltaRjj", "HT", "N_BTag", "N_Ak4", "mtop_lep_hyp1", "mtop_lep_hyp2", "mtop_had_hyp1", "mtop_had_hyp2", "MH_bb", "MH_WW", "Lep_pt", "Lep_eta", "Lep_phi", "Lep_E", "MET_pt", "MET_phi", "Ak4_j1_pt", "Ak4_j1_eta", "Ak4_j1_phi", "Ak4_j1_E", "Ak4_j1_m", "Ak4_j1_deepjetbscore", "Ak4_j2_pt", "Ak4_j2_eta", "Ak4_j2_phi", "Ak4_j2_E", "Ak4_j2_m", "Ak4_j2_deepjetbscore"};

  map<string, uhh2::Event::Handle<float>> NNInputs_map = {
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
    {"Ak4_j2_deepjetbscore", h_Ak4_j2_deepjetbscore}
  };

};


NeuralNetworkModule::NeuralNetworkModule(Context& ctx, const std::string & ModelName, const std::string& ConfigName): NeuralNetworkBase(ctx, ModelName, ConfigName) {
  
  h_eventweight = ctx.declare_event_output<float> ("eventweight");
  
  for(string var : NNInputs_id) {
    map<string, uhh2::Event::Handle<float>>::iterator it = NNInputs_map.find(var);
    if(it == NNInputs_map.end()) throw runtime_error("NNInputs_map in NeuralNetworkModule: "+var+ " is not mapped");
    NNInputs_map.find(var)->second = ctx.get_handle<float>(var);
  }
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
  ifstream normfile ("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data/NNModel/3classes/NormInfo.txt", ios::in);
  if (normfile.is_open()) { 
    for(int i = 0; i < N_variables; ++i) {   
      normfile >> varname[i] >> scal[i] >> mean[i] >> std[i];
      mean_val[i] = std::stod(mean[i]);
      std_val[i] = std::stod(std[i]);
    }
    normfile.close();
  }
  NNInputs.push_back( tensorflow::Tensor(tensorflow::DT_FLOAT, {1, N_variables}));
  //cout << varname[0] << endl;
  //cout << mean_val[0] << endl;

  
  for(int i = 0; i<N_variables; i++) {
    string identifier = varname[i];
   
    map<string, uhh2::Event::Handle<float>>::iterator it = NNInputs_map.find(identifier);
    if(it == NNInputs_map.end()) throw runtime_error("NNInputs_map in CreateInputs: "+identifier+ " is not mapped");
    float val = event.get(NNInputs_map.find(identifier)->second);
    //cout << val << endl;
    NNInputs.at(0).tensor<float, 2>()(0,i)  = (val - mean_val[i]) / (std_val[i]);
  }

  if (NNInputs.size()!=LayerInputs.size()) throw logic_error("NeuralNetworkModule.cxx: Create a number of inputs diffetent wrt. LayerInputs.size()="+to_string(LayerInputs.size()));
}


  
class HHtoWWbbSemiLeptonicNNApplication: public ModuleBASE {
public:

  explicit HHtoWWbbSemiLeptonicNNApplication(Context & ctx);
  virtual bool process(Event & event) override;
  void book_histograms(uhh2::Context&, vector<string>);
  void fill_histograms(uhh2::Event&, string, string region);

private:

  std::unique_ptr<CommonModules> common;

  unique_ptr<Hists> h_btageff, h_MulticlassNN_output, h_NNInputVariables;




  // NN Stuff
  unique_ptr<Variables_NN> Variables_module;
  Event::Handle<vector<tensorflow::Tensor>> h_NNoutput;
  Event::Handle<double> h_NNoutput0, h_NNoutput1, h_NNoutput2, h_NNoutput3, h_NNoutput4;
  unique_ptr<NeuralNetworkModule> NNModule;

  uhh2::Event::Handle<TString> h_region;



  bool is_mc, do_permutations;
  bool is_signal;
  string s_permutation;

  uhh2::Event::Handle<float> h_eventweight_lumi, h_eventweight_final;


  TString dataset_version;
  Year year;

};

void HHtoWWbbSemiLeptonicNNApplication::book_histograms(uhh2::Context& ctx, vector<string> tags){
  for(const auto & tag : tags){
    cout << "booking histograms with tag " << tag << endl;
    string mytag = tag + "_srele" + "_General";
    //book_HFolder(mytag, new HHtoWWbbSemiLeptonicHists(ctx,mytag));
    mytag = tag + "_srmu" + "_General";
    book_HFolder(mytag, new HHtoWWbbSemiLeptonicHists(ctx,mytag));
    mytag = tag + "_srmu" + "_NNInput";
    book_HFolder(mytag, new HHtoWWbbSemiLeptonicMulticlassNNInputHists(ctx,mytag));
    mytag = tag + "_srmu" + "_NNOutput";
    book_HFolder(mytag, new HHtoWWbbSemiLeptonicMulticlassNNHists(ctx,mytag));


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
  mytag = tag + "_" + region + "_NNInput";
  HFolder(mytag)->fill(event);
  mytag = tag + "_" + region + "_NNOutput";
  HFolder(mytag)->fill(event);


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

  h_eventweight_lumi = ctx.get_handle<float>("eventweight_lumi");
  h_eventweight_final = ctx.get_handle<float>("eventweight_final");

  h_region = ctx.get_handle<TString>("region");

  is_mc = ctx.get("dataset_type") == "MC";
  year = extract_year(ctx);
  dataset_version = ctx.get("dataset_version");
  is_signal = dataset_version.Contains("HHtoWWbb");


  // initialize HH Mass Reconstruction
    
  //mHH_reco.reset(new HHtoWWbbMassReconstruction(ctx));
  //chi2_module.reset(new HHChi2Discriminator(ctx, "HHHypotheses"));


  // CommonModules
  common.reset(new CommonModules());
  common->disable_lumisel();
  common->disable_jersmear();
  common->disable_jec();
  common->init(ctx);


  // NN Stuff
  Variables_module.reset(new Variables_NN(ctx));
  h_NNoutput = ctx.get_handle<vector<tensorflow::Tensor>>("NNoutput");
  h_NNoutput0 = ctx.declare_event_output<double>("NNoutput0");
  h_NNoutput1 = ctx.declare_event_output<double>("NNoutput1");
  h_NNoutput2 = ctx.declare_event_output<double>("NNoutput2");
  h_NNoutput3 = ctx.declare_event_output<double>("NNoutput3");
  h_NNoutput4 = ctx.declare_event_output<double>("NNoutput4");

  string data_dir = "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data//";
  NNModule.reset(new NeuralNetworkModule(ctx, data_dir+"NNModel/3classes/test_model.pb", data_dir+"NNModel/3classes/test_model.config.pbtxt"));
  

  // Book histograms
  vector<string> histogram_tags = {"Finalselection", "DNN_output0", "DNN_output1", "DNN_output2", "DNN_output3", "DNN_output4"};
  book_histograms(ctx, histogram_tags);

  //h_xx = ctx.get_handle<float>("xx");

  


}


bool HHtoWWbbSemiLeptonicNNApplication::process(Event & event) {
  //cout << "NNApplication: process" << endl;

  bool pass_common = common->process(event);
  if(!pass_common) return false;


  //double eventweight_lumi = event.weight;
    

  string region = (string)event.get(h_region);

  Variables_module->process(event);
  NNModule->process(event);


  vector<tensorflow::Tensor> NNoutputs = NNModule->GetOutputs();
  event.set(h_NNoutput, NNoutputs);

  double out0 =  (double)(NNoutputs[0].tensor<float, 2>()(0,0));
  double out1 =  (double)(NNoutputs[0].tensor<float, 2>()(0,1));
  double out2 =  (double)(NNoutputs[0].tensor<float, 2>()(0,2));
  double out3 =  (double)(NNoutputs[0].tensor<float, 2>()(0,3));
  double out4 =  (double)(NNoutputs[0].tensor<float, 2>()(0,4));
  //double out5 =  (double)(NNoutputs[0].tensor<float, 2>()(0,5));

  vector<double> out_event = {out0,out1,out2,out3,out4};
  /*
  cout << "out0= " << out0 << endl;
  cout << "out1= " << out1 << endl;
  cout << "out2= " << out2 << endl;
  cout << "out3= " << out3 << endl;
  cout << "out4= " << out4 << endl;
  */
  event.set(h_NNoutput0, out0);
  event.set(h_NNoutput1, out1);
  event.set(h_NNoutput2, out2);
  event.set(h_NNoutput3, out3);
  event.set(h_NNoutput4, out4);
  fill_histograms(event, "Finalselection", region);

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
