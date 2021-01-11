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
#include "UHH2/HHtoWWbbSemiLeptonic/include/MassReconstruction.h"
//#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicModules.h"
//#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicPDFHists.h"
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

    std::unique_ptr<Selection> nbtag_medium_sel, muon_trigger_sel1, muon_trigger_sel2;


    unique_ptr<HHtoWWbbMassReconstruction> mHH_reco;
    uhh2::Event::Handle<bool> h_is_mHH_reconstructed;
    uhh2::Event::Handle<float> h_mHH;

    JetId Btag_loose;
    BTag::algo btag_algo;
    BTag::wp wp_btag_loose, wp_btag_medium, wp_btag_tight;

    bool is_mc, do_permutations;
    string s_permutation;

    uhh2::Event::Handle<float> h_eventweight_lumi, h_eventweight_final;

    TString dataset_version;
    Year year;

  };


  void HHtoWWbbSemiLeptonicFullselectionModule::book_histograms(uhh2::Context& ctx, vector<string> tags){
    for(const auto & tag : tags){
      cout << "booking histograms with tag " << tag << endl;
      string mytag = tag+"_General";
      book_HFolder(mytag, new HHtoWWbbSemiLeptonicHists(ctx,mytag));
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

    // for mass reco
    h_is_mHH_reconstructed = ctx.declare_event_output<bool>("is_mHH_reconstructed");
    h_mHH = ctx.declare_event_output<float>("mHH");



    is_mc = ctx.get("dataset_type") == "MC";
    year = extract_year(ctx);


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
    


    // CommonModules
    common.reset(new CommonModules());
    common->disable_lumisel();
    common->disable_jersmear();
    common->disable_jec();
    common->init(ctx);

    // Selections
    nbtag_medium_sel.reset(new NJetSelection(2, -1, DeepjetMedium));



    // Book histograms
    vector<string> histogram_tags = {"Cleaner", "Trigger", "BTag", "Finalselection_mHH_reconstructed"};
    book_histograms(ctx, histogram_tags);

  }


  bool HHtoWWbbSemiLeptonicFullselectionModule::process(Event & event) {




    bool pass_common = common->process(event);
    if(!pass_common) return false;


    double eventweight_lumi = event.weight;
    event.set(h_eventweight_lumi, eventweight_lumi);
    /*
    SF_eleReco->process(event);
    SF_eleID->process(event);
    SF_muonID->process(event);
    SF_muonIso->process(event);
    */
    fill_histograms(event,"Cleaner");

    TString leptonregion = "muon"; // later also add electron region


    if(!(muon_trigger_sel1->passes(event) || muon_trigger_sel2->passes(event))) return false;
    fill_histograms(event,"Trigger");

    if(!nbtag_medium_sel->passes(event)) return false;
    fill_histograms(event,"BTag");

    bool is_mHH_reconstructed = event.get(h_is_mHH_reconstructed);
    if(is_mHH_reconstructed) fill_histograms(event, "Finalselection_mHH_reconstructed");

    event.set(h_eventweight_final, event.weight);
    return true;
  }

  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the HHtoWWbbSemiLeptonicFullselectionModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(HHtoWWbbSemiLeptonicFullselectionModule)

}
