#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "TFile.h"
#include "TTree.h"

#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequenceArea.hh"

#include "include/ProgressBar.h"

#include "include/pythiaEvent.hh"
#include "include/extraInfo.hh"

#include "PU14/CmdLine.hh"

using namespace std;
using namespace fastjet;

int main (int argc, char ** argv)
{
  // Uncomment to silence fastjet banner
  ClusterSequence::set_fastjet_banner_stream(NULL);
 
  CmdLine cmdline(argc,argv);
  // inputs read from command line
  unsigned int nEvent = cmdline.value<unsigned int>("-nev",1);  // first argument: command line option; second argument: default value
 
  // Number of events, generated and listed ones.
  //unsigned int nEvent    = 10000;

  //event generator settings

    
    //---------------------------------------------------------------------------
    //   produce event
    //---------------------------------------------------------------------------

    fout << "# event " << ie << "\n";
   
    //create pythia event
    std::vector<fastjet::PseudoJet> particlesSig = pyt.createPythiaEvent();
    fout << "weight " << pyt.getWeight() <<  " pthat " << pyt.getPtHat() << "\n"; //<< " weight " << pow(15./pyt.getPtHat(),4.5)

    std::vector<fastjet::PseudoJet> partons = pyt.getPartonList();
    for(fastjet::PseudoJet p : partons) {
      const int & pdgid = p.user_info<extraInfo>().pdg_id();
      const int & vtx   = p.user_info<extraInfo>().vertex_number();
      fout << p.px() << " " << p.py() << " " << p.pz() << " " << p.m() << " " << pdgid << " " << vtx << "\n";
    }
   
    for(fastjet::PseudoJet p : particlesSig) {
      const int & pdgid = p.user_info<extraInfo>().pdg_id();
      const int & vtx   = p.user_info<extraInfo>().vertex_number();
      fout << p.px() << " " << p.py() << " " << p.pz() << " " << p.m() << " " << pdgid << " " << vtx << "\n";
    }
    fout << "end\n";
    
    //std::cout << "weight: " << std::scientific << pyt.getWeight() << std::endl;
    //std::cout << "pthat: " << std::fixed <<  pyt.getPtHat() << std::endl;
  }

  pyt.getStat();
 

  fout.close();

  std::cout << "\n Finished generating PYTHIA events" << std::endl;
    
}
