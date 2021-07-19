#include <iostream> // for input and output
#include <memory> // for managing dynamic memory


//#include <UHH2/SingleTth/include/ModuleBASE.h>
#include "UHH2/core/include/AnalysisModule.h" // for implementing an analysis
#include "UHH2/core/include/Event.h" // provides access to objects such as jets, electrons, myons etc.
#include "UHH2/common/include/CommonModules.h" // runs a number of commonly-used analysis modules in the right order
#include "UHH2/common/include/CleaningModules.h" // modules which throw away parts of some collection in the event by
                                                 // applying kinematic or id criteria
//hists
#include "UHH2/common/include/ElectronHists.h" // common electron histograms such as multiplicity, pt, eta, isolation, etc.
#include "UHH2/common/include/MuonHists.h" // common muon histograms such as multiplicity, pt, eta, isolation, etc.
#include "UHH2/common/include/JetHists.h" // common jet histograms such as multiplicity, pt, eta, isolation, etc.
#include "UHH2/common/include/LuminosityHists.h" // creates the "lumi plot", i.e. event yield vs. time in bins of
                                                 // equal integrated luminosity
#include "UHH2/common/include/EventHists.h" // common histograms for some event-wide quantities
//selections
#include "UHH2/common/include/LumiSelection.h" // removes all data events that are not given in the run/lumisection list
                                               // given in the lumi_file
#include "UHH2/common/include/NSelections.h" // defines multiplicity selections on jets, leptons, etc.
//IDs
#include "UHH2/common/include/ElectronIds.h" // implement electron ids
#include "UHH2/common/include/MuonIds.h" // implement muon ids

#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicSelections.h" // select events with specific attributes
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicPreselectionHists.h" // example class for booking and filling histograms
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicGenHists.h" // example class for booking and filling histograms
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicMatchedHists.h" // ???

#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenObjects.h" // ???
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenRecoMatching.h" // ???

#include <UHH2/HHtoWWbbSemiLeptonic/include/ModuleBASE.h> // ???

using namespace std; // standard c++ functions and variables
using namespace uhh2; // bedeutung von "uhh2::context", "uhh2::event", "uhh::analysismodule"?

namespace uhh2examples {

  // class for preselection module
  class HHtoWWbbSemiLeptonicPreselectionModule: public ModuleBASE {
  public:

    explicit HHtoWWbbSemiLeptonicPreselectionModule(Context & ctx);
    virtual bool process(Event & event) override; //was macht das? unterschied zwischen Event und event?
    // override definition: "specifies that a virtual function overrides another virtual function"
    // -> which function replaces which?
    void book_histograms(uhh2::Context&, vector<string>); // line 83
    void fill_histograms(uhh2::Event&, string); // line 106

  // selections
  private:

    std::unique_ptr<CommonModules> common;

    // declare the selections to use. use unique_ptr to ensure automatic call of delete in the destructor
    // to avoid memory leaks.
    std::unique_ptr<Selection> njet4_sel, njet3_sel, dijet_sel, electron_sel, muon_sel, noElectron_sel, noMuon_sel, st_sel, nbtag_medium_sel;



    // gen level stuff
    unique_ptr<uhh2::AnalysisModule> HHgenprod;
    uhh2::Event::Handle<HHGenObjects> h_HHgenobjects;

    unique_ptr<uhh2::AnalysisModule> HHgenrecoprod;
    uhh2::Event::Handle<HHGenRecoMatching> h_HHgenreco;

    ElectronId EleId;
    JetId Jet_ID;
    MuonId MuId;

    JetId Btag_loose;
    BTag::algo btag_algo;
    BTag::wp wp_btag_loose, wp_btag_medium, wp_btag_tight;

    bool is_mc;
    bool is_signal;

  };

  // function that books historgrams
  void HHtoWWbbSemiLeptonicPreselectionModule::book_histograms(uhh2::Context& ctx, vector<string> tags){
    for(const auto & tag : tags){
      cout << "booking histograms with tag " << tag << endl;
      string mytag = tag+"_General";
      book_HFolder(mytag, new HHtoWWbbSemiLeptonicPreselectionHists(ctx,mytag));
      mytag = tag+"_Signal";
      book_HFolder(mytag, new HHtoWWbbSemiLeptonicGenHists(ctx,mytag));
      mytag = tag+"_Matched";
      //book_HFolder(mytag, new HHtoWWbbSemiLeptonicMatchedHists(ctx,mytag));
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

  // function that fills historgrams
  void HHtoWWbbSemiLeptonicPreselectionModule::fill_histograms(uhh2::Event& event, string tag){
    string mytag = tag+"_General";
    HFolder(mytag)->fill(event);
    if(is_signal) {
      mytag = tag+"_Signal";
      HFolder(mytag)->fill(event);
      mytag = tag+"_Matched";
      //HFolder(mytag)->fill(event);
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





// preselection process
HHtoWWbbSemiLeptonicPreselectionModule::HHtoWWbbSemiLeptonicPreselectionModule(Context & ctx){

    cout << "Hello World from HHtoWWbbSemiLeptonicModule!" << endl;

    // If needed, access the configuration of the module here, e.g.:
    string testvalue = ctx.get("TestKey", "<not set>");
    cout << "TestKey in the configuration was: " << testvalue << endl;

    for(auto & kv : ctx.get_all()){
      cout << " " << kv.first << " = " << kv.second << endl;
    }

    // Gen level stuff
    const string HHgen_label("HHgenobjects");
    HHgenprod.reset(new HHGenObjectsProducer(ctx, HHgen_label, true));
    h_HHgenobjects = ctx.get_handle<HHGenObjects>(HHgen_label);
    const string HHgenreco_label("HHgenreco");
    HHgenrecoprod.reset(new HHGenRecoProducer(ctx, HHgenreco_label, true));
    h_HHgenreco = ctx.get_handle<HHGenRecoMatching>(HHgenreco_label);


    is_mc = ctx.get("dataset_type") == "MC";


    TString dataset_version = ctx.get("dataset_version");
    cout << "dataset version: " << dataset_version << endl;
    is_signal = dataset_version.Contains("HHtoWWbb");
    cout << "is_signal: " << is_signal << endl;



    Year year = extract_year(ctx);

    // Object IDs
    //cout << "Year: " << year << endl;
    JetId jet_pfid = JetPFID(JetPFID::WP_TIGHT_CHS);
    EleId = AndId<Electron>(ElectronID_Fall17_tight, PtEtaCut(28.0, 2.4));
    if (year == Year::is2016v2) MuId = AndId<Muon>(MuonID(Muon::Tight), PtEtaCut(25.0, 2.4), MuonIso(0.15));
    else                        MuId = AndId<Muon>(MuonID(Muon::CutBasedIdTight), PtEtaCut(25.0, 2.4), MuonID(Muon::PFIsoTight));
    Jet_ID = AndId<Jet>(jet_pfid, PtEtaCut(5.0, 2.4));


    // BTagging
    btag_algo = BTag::DEEPJET;
    wp_btag_loose = BTag::WP_LOOSE;
    wp_btag_medium = BTag::WP_MEDIUM;
    wp_btag_tight = BTag::WP_TIGHT;
    // loose, medium, tight
    JetId DeepjetLoose = BTag(btag_algo, wp_btag_loose);
    JetId DeepjetMedium = BTag(btag_algo, wp_btag_medium);
    JetId DeepjetTight = BTag(btag_algo, wp_btag_tight);

    // Common Modules
    common.reset(new CommonModules());
    common->switch_jetlepcleaner(true);
    common->set_electron_id(EleId);
    common->set_muon_id(MuId);
    common->set_jet_id(Jet_ID);
    common->switch_jetPtSorter();
    common->init(ctx);


    // Selections
    // jet/muon/electron numbers (min/max)
    njet4_sel.reset(new NJetSelection(4, -1));
    njet3_sel.reset(new NJetSelection(3, -1));
    //dijet_sel.reset(new DijetSelection()); // see HHtoWWbbSemiLeptonicSelections
    muon_sel.reset(new NMuonSelection(1, 1));
    electron_sel.reset(new NElectronSelection(1, 1)); // set to one electron
    noMuon_sel.reset(new NMuonSelection(0, 0));
    noElectron_sel.reset(new NElectronSelection(0, 0)); //
    nbtag_medium_sel.reset(new NJetSelection(1, -1, DeepjetMedium)); // maybe not in presel, look into signal samples when aviable
    st_sel.reset(new StSelection(100)); // not sure if useful, look into histograms before using





    // Book Histograms
    vector<string> histogram_tags = {"NoCuts", "Cleaner", "1Lepton", "1Lepton_srele", "1Lepton_srmu", "3Jets_srele", "3Jets_srmu", "1Bjet_srele", "1Bjet_srmu", "4Jets_srele", "4Jets_srmu"};
    book_histograms(ctx, histogram_tags);
}


  bool HHtoWWbbSemiLeptonicPreselectionModule::process(Event & event) {
    //cout << "HHtoWWbbSemiLeptonicModule: Starting to process event (runid, eventid) = (" << event.run << ", " << event.event << "); weight = " << event.weight << endl;

    if(is_signal){
      HHgenprod->process(event);
      //HHgenrecoprod->process(event);
    }


    fill_histograms(event,"NoCuts"); // no cuts = shows all events
    bool pass_common = common->process(event);
    //cout << "pass_common: " << pass_common << endl;
    if(!pass_common) return false;
    //cout << "Line: " << __LINE__ << endl;
    fill_histograms(event,"Cleaner");


    // event ID ausgeben
    bool electronCategory = electron_sel->passes(event) && noMuon_sel->passes(event); // N_e == 1, N_mu == 0
    bool muonCategory = muon_sel->passes(event) && noElectron_sel->passes(event); // N_e == 0, N_mu == 1

    // verifies number of jets/muons/electrons for event
    // fills histograms
    if(!electronCategory && !muonCategory) return false;
    fill_histograms(event, "1Lepton");

    if(electronCategory) {
      fill_histograms(event, "1Lepton_srele");
    }
    else if(muonCategory) {
      fill_histograms(event, "1Lepton_srmu");
    }


    if(!njet3_sel->passes(event)) return false;
    if(electronCategory) fill_histograms(event, "3Jets_srele");
    else if(muonCategory) fill_histograms(event, "3Jets_srmu");
    // take these cuts out of the selection, but keep the histograms
    if(nbtag_medium_sel->passes(event)) {
      if(electronCategory) fill_histograms(event, "1Bjet_srele");
      else if(muonCategory) fill_histograms(event, "1Bjet_srmu");

      if(njet4_sel->passes(event) && electronCategory) fill_histograms(event, "4Jets_srele");
      else if(njet4_sel->passes(event) && muonCategory) fill_histograms(event, "4Jets_srmu");
    }

    return true;


  }

  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the HHtoWWbbSemiLeptonicModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(HHtoWWbbSemiLeptonicPreselectionModule)

}
