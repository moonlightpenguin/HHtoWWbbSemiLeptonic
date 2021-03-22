#include <iostream>
#include <memory>


#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/MCWeight.h"


//hists_
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/MuonHists.h"
#include "UHH2/common/include/JetHists.h"
#include "UHH2/common/include/LuminosityHists.h"
#include "UHH2/common/include/EventHists.h"
//selections
#include "UHH2/common/include/LumiSelection.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/TriggerSelection.h"
#include "UHH2/common/include/AdditionalSelections.h"
//IDs
#include "UHH2/common/include/ElectronIds.h"
#include "UHH2/common/include/MuonIds.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/common/include/TopJetIds.h"
// my own classes
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicSelections.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicHists.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicGenHists.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicMatchedHists.h"


//#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicModules.h"
//#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicPDFHists.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenObjects.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenRecoMatching.h"

#include "UHH2/HHtoWWbbSemiLeptonic/include/HHMassReconstruction.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesis.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesisDiscriminators.h"

#include <UHH2/HHtoWWbbSemiLeptonic/include/ModuleBASE.h>



using namespace std;
using namespace uhh2;

namespace uhh2examples {

  class HHtoWWbbSemiLeptonicFullselectionModule: public ModuleBASE {
  public:

    explicit HHtoWWbbSemiLeptonicFullselectionModule(Context & ctx);
    virtual bool process(Event & event) override;
    void book_histograms(uhh2::Context&, vector<string>);
    void fill_histograms(uhh2::Event&, string);

  private:

    std::unique_ptr<CommonModules> common;

    unique_ptr<Hists> h_btageff;
    std::unique_ptr<AnalysisModule> SF_muonIso, SF_muonID, SF_muonTrigger, SF_btag;
    std::unique_ptr<Selection> nbtag1_medium_sel, nbtag2_medium_sel, muon_trigger_sel1, muon_trigger_sel2;
    

    unique_ptr<HHtoWWbbMassReconstruction> mHH_reco;
    unique_ptr<HHChi2Discriminator> chi2_module;

    // gen level stuff
    unique_ptr<uhh2::AnalysisModule> HHgenprod;
    uhh2::Event::Handle<HHGenObjects> h_HHgenobjects;

    unique_ptr<uhh2::AnalysisModule> HHgenrecoprod;
    uhh2::Event::Handle<HHGenRecoMatching> h_HHgenreco;



    // mass reco stuff
    uhh2::Event::Handle<bool> h_is_mHH_reconstructed;
    uhh2::Event::Handle<float> h_mHH, h_chi2;
    uhh2::Event::Handle<float> h_mH_bb, h_chi2_H_bb;
    uhh2::Event::Handle<float> h_mH_WW, h_chi2_H_WW;
    uhh2::Event::Handle<float> h_mH_mean;


    JetId Btag_loose;
    BTag::algo btag_algo;
    BTag::wp wp_btag_loose, wp_btag_medium, wp_btag_tight;

    bool is_mc, do_permutations;
    bool is_signal;
    string s_permutation;

    uhh2::Event::Handle<float> h_eventweight_lumi, h_eventweight_final;



    // systematic uncertainties
    string Sys_MuonID, Sys_MuonIso;
    string Sys_BTag;
    string Sys_PU;


    TString dataset_version;
    Year year;

  };


  void HHtoWWbbSemiLeptonicFullselectionModule::book_histograms(uhh2::Context& ctx, vector<string> tags){
    for(const auto & tag : tags){
      cout << "booking histograms with tag " << tag << endl;
      string mytag = tag+"_General";
      book_HFolder(mytag, new HHtoWWbbSemiLeptonicHists(ctx,mytag));
      mytag = tag+"_Signal"; 
      book_HFolder(mytag, new HHtoWWbbSemiLeptonicGenHists(ctx,mytag));
      mytag = tag+"_GenRecoMatched"; 
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

  void HHtoWWbbSemiLeptonicFullselectionModule::fill_histograms(uhh2::Event& event, string tag){
    string mytag = tag+"_General";
    HFolder(mytag)->fill(event);
      if(is_signal){
	mytag = tag+"_Signal"; 
	HFolder(mytag)->fill(event);
	mytag = tag+"_GenRecoMatched"; 
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



  HHtoWWbbSemiLeptonicFullselectionModule::HHtoWWbbSemiLeptonicFullselectionModule(Context & ctx){
    
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
    h_mH_mean = ctx.declare_event_output<float>("mH_mean");


    is_mc = ctx.get("dataset_type") == "MC";
    year = extract_year(ctx);
    TString dataset_version = ctx.get("dataset_version");
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
      /*
      ele_trigger_sel1.reset(new TriggerSelection("HLT_Ele27_WPTight_Gsf_v*"));
      ele_trigger_sel2.reset(new TriggerSelection("HLT_Ele115_CaloIdVT_GsfTrkIdT_v*"));
      ele_trigger_sel3.reset(new TriggerSelection("HLT_Photon175_v*"));
      */

    }
    else if(year == Year::is2017v1 || year == Year::is2017v2){
      muon_trigger_sel1.reset(new TriggerSelection("HLT_IsoMu27_v*"));
      muon_trigger_sel2.reset(new TriggerSelection("HLT_IsoMu27_v*"));
      /*
      ele_trigger_sel1.reset(new TriggerSelection("HLT_Ele35_WPTight_Gsf_v*"));
      ele_trigger_sel2.reset(new TriggerSelection("HLT_Ele115_CaloIdVT_GsfTrkIdT_v*")); // this trigger does not work for some 2017 Electron+Photon B events
      ele_trigger_sel3.reset(new TriggerSelection("HLT_Photon200_v*"));
      */
    }
    else if(year == Year::is2018){
      muon_trigger_sel1.reset(new TriggerSelection("HLT_IsoMu24_v*"));
      muon_trigger_sel2.reset(new TriggerSelection("HLT_IsoMu24_v*"));
      /*
      ele_trigger_sel1.reset(new TriggerSelection("HLT_Ele32_WPTight_Gsf_v*"));
      ele_trigger_sel2.reset(new TriggerSelection("HLT_Ele115_CaloIdVT_GsfTrkIdT_v*"));
      ele_trigger_sel3.reset(new TriggerSelection("HLT_Ele32_WPTight_Gsf_v*"));
      */
    }


    // initialize HH Mass Reconstruction
    
    mHH_reco.reset(new HHtoWWbbMassReconstruction(ctx));
    chi2_module.reset(new HHChi2Discriminator(ctx, "HHHypotheses"));

    // systematic uncertainties

    Sys_MuonID = ctx.get("Systematic_MuonID");
    Sys_MuonIso = ctx.get("Systematic_MuonIso");
    Sys_BTag = ctx.get("Systematic_BTag");
    Sys_PU = ctx.get("Systematic_PU");


    // scale factors

    SF_muonID.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/MuonID_EfficienciesAndSF_average_RunBtoH.root", "NUM_TightID_DEN_genTracks_eta_pt", 0., "id", false, Sys_MuonID));
    SF_muonIso.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/MuonIso_EfficienciesAndSF_average_RunBtoH.root", "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt", 0., "iso", false, Sys_MuonIso));
    // SF_muonTrigger.reset(new MuonTriggerWeights(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/MuonTrigger_EfficienciesAndSF_average_RunBtoH.root", "IsoMu24_OR_IsoTkMu24_PtEtaBins"), 0.);

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



    // Book histograms
    vector<string> histogram_tags = {"Cleaner", "Trigger", "BTag", "Finalselection_mHH_reconstructed"};
    book_histograms(ctx, histogram_tags);

    h_btageff.reset(new BTagMCEfficiencyHists(ctx, "BTagEff", DeepjetMedium));
  }


  bool HHtoWWbbSemiLeptonicFullselectionModule::process(Event & event) {
    // cout << "Fullselection: process" << endl;
    //cout << "Line: " << __LINE__ << endl;

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
    event.set(h_mH_mean, -1);


    //cout << "test: "<< event.get(h_mHH) << endl;
    // cout << "Line: " << __LINE__ << endl;

    mHH_reco->process(event);
    chi2_module->process(event);

    bool pass_common = common->process(event);
    if(!pass_common) return false;


    double eventweight_lumi = event.weight;
    event.set(h_eventweight_lumi, eventweight_lumi);
    
    /*
    SF_eleReco->process(event);
    SF_eleID->process(event);
    */
    SF_muonID->process(event);
    SF_muonIso->process(event);
    
    fill_histograms(event,"Cleaner");

    TString leptonregion = "muon"; // later also add electron region


    if(!(muon_trigger_sel1->passes(event) || muon_trigger_sel2->passes(event))) return false;
    // SF_muonTrigger->process(event);
    fill_histograms(event,"Trigger");



    //SF_btag->process(event); //comment out when re-doing SF_btag
    h_btageff->fill(event);

    if(!nbtag1_medium_sel->passes(event)) return false; // comment out when re-doing SF_btag
    fill_histograms(event,"BTag");
    if(!nbtag2_medium_sel->passes(event)) return false;

    // cout << "is mass reconstructed? " << event.get(h_is_mHH_reconstructed) << endl;
    // cout << "mH_bb: " << event.get(h_mH_bb) << endl;
    // cout << "Chi2_H_bb: " << event.get(h_chi2_H_bb) << endl;

    bool is_mHH_reconstructed = event.get(h_is_mHH_reconstructed);
    // cout << "is_mHH_reconstructed: " << is_mHH_reconstructed << endl;
    if(is_mHH_reconstructed) fill_histograms(event, "Finalselection_mHH_reconstructed");

    event.set(h_eventweight_final, event.weight);
    return true;
  }

  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the HHtoWWbbSemiLeptonicFullselectionModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(HHtoWWbbSemiLeptonicFullselectionModule)

}
