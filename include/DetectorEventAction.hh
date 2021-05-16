#ifndef DetectorEventAction_h
#define DetectorEventAction_h 1

#include "G4UserEventAction.hh"

class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorEventAction : public G4UserEventAction
{
  public:
    DetectorEventAction();
   ~DetectorEventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
