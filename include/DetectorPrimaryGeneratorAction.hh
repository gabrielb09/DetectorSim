#ifndef DetectorPrimaryGeneratorAction_h
#define DetectorPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class DetectorConstruction;
class G4GeneralParticleSource;
class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    DetectorPrimaryGeneratorAction();
   ~DetectorPrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event*);

  private:
		G4GeneralParticleSource* GeneralParticleSource;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
