#ifndef DetectorRunAction_h
#define DetectorRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4String.hh"
#include "DetectorMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;
class DetectorMessenger;

class DetectorRunAction : public G4UserRunAction
{
  public:
    DetectorRunAction();
   ~DetectorRunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
    void SetOutDir(G4String newDir){ outdir = newDir; };
    void SetOutFile(G4String newFile){ outfile = newFile; };

  private:
    G4String outdir;
    G4String outfile;
    DetectorMessenger* detectorMessenger;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
