#ifndef pythiaEvent_h
#define pythiaEvent_h

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#include "Pythia8/Pythia.h"

#include "extraInfo.hh"

//using namespace std;

//---------------------------------------------------------------
// Description
// This class generates a pythia8 event
// Author: M. Verweij
//---------------------------------------------------------------

class pythiaEvent2 {

private :
  Pythia8::Pythia pythia;
  double pthat_;
  unsigned int tune_;
  double rapMin_;
  double rapMax_;
  bool   partonLevel_;
  bool   vinciaShower_;
  int    process_;      //0: dijet; 1: prompt photon

  std::vector<fastjet::PseudoJet> partons;

public :
  pythiaEvent2(double pthat = 120., unsigned int tune = 14, double rapMin = -3., double rapMax = 3., bool partonLevel = false, bool vinciaShower = false, bool flatPtHat = false, int process = 0);
  std::vector<fastjet::PseudoJet> createPythiaEvent();
  
  std::vector<fastjet::PseudoJet> getPartonList() const { return partons; }

  void getStat() {pythia.stat();}
  double getWeight() {return pythia.info.weight();}
  double getPtHat()  {return pythia.info.pTHat();}

};
  
pythiaEvent2::pythiaEvent2(double pthat, unsigned int tune, double rapMin, double rapMax, bool partonLevel, bool vinciaShower, bool flatPtHat, int process) :
  pthat_(pthat), tune_(tune), rapMin_(rapMin), rapMax_(rapMax), partonLevel_(partonLevel), vinciaShower_(vinciaShower), process_(process)
{
    
  // Generator. LHC process and output selection. Initialization.
  // tunes: http://home.thep.lu.se/~torbjorn/pythia82html/Tunes.html
  pythia.readFile("main31.cmnd");
  pythia.readString("Beams:eCM = 5020.");
  if(process_==0)      pythia.readString("HardQCD:all = on");
  else if(process_==1) pythia.readString("PromptPhoton:all = on");
  pythia.readString(Form("PhaseSpace:pTHatMin = %.1f",pthat_));
  pythia.readString("Next:numberShowInfo = 0");
  pythia.readString("Next:numberShowProcess = 0");
  pythia.readString("Next:numberShowEvent = 0");
  pythia.readString("Random:setSeed = on");
  pythia.readString("Random:seed = 0");
  if(partonLevel_) {
    pythia.readString("HadronLevel:all = off");
  }
  if(vinciaShower_)
    pythia.readString("PartonShowers:Model = 2"); //activate the VINCIA parton shower
  else
      pythia.readString(Form("Tune:pp = %d",tune_));

  if(flatPtHat) {
    //flat pthard
    pythia.readString("PhaseSpace:bias2Selection = on");
    pythia.readString("PhaseSpace:bias2SelectionPow = 4.5");
    pythia.readString("PhaseSpace:bias2SelectionRef = 15");
  }
  
  pythia.init();

}

std::vector<fastjet::PseudoJet> pythiaEvent2::createPythiaEvent() {

  pythia.next(); //generate next event
    
  std::vector<fastjet::PseudoJet> particles;
  partons.clear(); //empty list before storing partons of new event

  //int iprint = 0;
  
  for (int i = 0; i < pythia.event.size(); ++i) {
    if (pythia.event[i].isFinal()) { //all final state particles
      fastjet::PseudoJet p(pythia.event[i].px(),pythia.event[i].py(),pythia.event[i].pz(),pythia.event[i].e());
      p.set_user_info(new extraInfo(pythia.event[i].id(), 0)); 
      if(p.rap()>rapMin_ && p.rap()<rapMax_)
        particles.push_back(p);
    } else if (pythia.event[i].status()==-23) { //outgoing partons from the hard scattering
      fastjet::PseudoJet p(pythia.event[i].px(),pythia.event[i].py(),pythia.event[i].pz(),pythia.event[i].e());
      p.set_user_info(new extraInfo(pythia.event[i].id(), -1)); 
      partons.push_back(p);
      
      
      
    
    }
  }

 
  
  return particles;
}


#endif