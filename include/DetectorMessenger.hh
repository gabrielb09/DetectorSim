#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "G4UImessenger.hh"

class DetectorRunAction;
class G4UIcmdWithAString;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorMessenger: public G4UImessenger
{
  public:
    DetectorMessenger(DetectorRunAction*);
   ~DetectorMessenger();

    void SetNewValue(G4UIcommand* command, G4String newValue);

  private:
    DetectorRunAction*          myRunAction;
    G4UIcmdWithAString*         OutDirCmd;
    G4UIcmdWithAString*         OutFileCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
