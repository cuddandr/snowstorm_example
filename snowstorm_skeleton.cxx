//Need the StandardRecord to read the CAF -- see setup_cafs.sh
#include "/cvmfs/dune.opensciencegrid.org/products/dune/duneanaobj/v03_06_01b/include/duneanaobj/StandardRecord/StandardRecord.h"

#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

//Expects the path to a structured CAF
int snowstorm_skeleton(std::string file_name)
{
    //Using a TChain here just to show that you can add
    //friends to a TChain (and to make this slightly easier
    //to extend to multiple files). This functions the same
    //as using a single TTree object.
    TChain* caf_chain  = new TChain("cafTree");
    TChain* snow_chain = new TChain("snowstorm");

    std::cout << "Adding " << file_name << " to TChain." << std::endl;
    caf_chain->Add(file_name.c_str());
    snow_chain->Add(file_name.c_str());

    //The magic that syncs the cafTree and Snowstorm tree such that
    //they act as a single TTree/TChain. As seen below, you can now
    //use only one TChain for the analysis.
    caf_chain->AddFriend(snow_chain);

    //Define variables for the Snowstorm parameters
    unsigned long long spill_id;
    double e_field, v_drift, e_lifet, lg_diff, tr_diff;
    double birks_a, birks_k, w_ion;

    //Need to know the parameter nominal values and uncertainties
    //See the 2x2_sim GitHub wiki for these numbers
    double birks_a_nom = 0.800;
    double birks_a_sig = birks_a_nom * 0.025;
    double birks_k_nom = 0.0486;
    double birks_k_sig = birks_a_nom * 0.17;
    double wion_nom = 23.6e-6;
    double wion_sig = wion_nom * 0.02;

    //Set TTree/TChain addresses for the StandardRecord and
    //Snowstorm parameters. Note that we set the branch on
    //the cafTree for everything since we added the Snowstorm
    //TTree/TChain as a friend.
    auto sr = new caf::StandardRecord;
    caf_chain->SetBranchAddress("rec", &sr);
    caf_chain->SetBranchAddress("spill_id", &spill_id);
    caf_chain->SetBranchAddress("e_field", &e_field);
    caf_chain->SetBranchAddress("v_drift", &v_drift);
    caf_chain->SetBranchAddress("e_lifet", &e_lifet);
    caf_chain->SetBranchAddress("lg_diff", &lg_diff);
    caf_chain->SetBranchAddress("tr_diff", &tr_diff);
    caf_chain->SetBranchAddress("birks_a", &birks_a);
    caf_chain->SetBranchAddress("birks_k", &birks_k);
    caf_chain->SetBranchAddress("w_ion", &w_ion);

    const unsigned long nspills = caf_chain->GetEntries();
    const unsigned int incr     = nspills / 10;

    //Loop over each spill in the cafTree
    std::cout << "Looping over " << nspills << " entries/spills..." << std::endl;
    for(unsigned long i = 0; i < nspills; ++i)
    {
        //Because the Snowstorm TTree/TChain was added as a friend to the cafTree,
        //using GetEntry() here retrieves the data from both
        caf_chain->GetEntry(i);

        if(i % incr == 0)
            std::cout << "Spill #: " << i << std::endl;

        //Loop over reco interactions or whatever else for analysis
        const auto num_ixn = sr->common.ixn.ndlp;
        for(unsigned long ixn = 0; ixn < num_ixn; ++ixn)
        {
        }

        //If you want to check the Snowstorm parameter values
        /*
        std::cout << "Spill ID: " << spill_id << std::endl;
        std::cout << "e_field : " << e_field << std::endl;
        std::cout << "v_drift : " << v_drift << std::endl;
        std::cout << "e_lifet : " << e_lifet << std::endl;
        std::cout << "lg_diff : " << lg_diff << std::endl;
        std::cout << "tr_diff : " << tr_diff << std::endl;
        std::cout << "birks_a : " << birks_a << std::endl;
        std::cout << "birks_k : " << birks_k << std::endl;
        std::cout << "w_ion : " << w_ion << std::endl;
        */
    }

    //Perform Snowstorm gradient extraction after looping/processing
    //each spill/entry

    return 0;
}
