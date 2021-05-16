#ifndef DetectorPhysicsList_h
#define DetectorPhysicsList_h 1

#include "G4VModularPhysicsList.hh"

class DetectorPhysicsList: public G4VModularPhysicsList
{
public:
  DetectorPhysicsList();
  virtual ~DetectorPhysicsList();

public:
  // SetCuts()
  virtual void SetCuts();


};


#endif
