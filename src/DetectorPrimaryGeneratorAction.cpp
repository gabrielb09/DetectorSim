#include "DetectorPrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorPrimaryGeneratorAction::DetectorPrimaryGeneratorAction()
:G4VUserPrimaryGeneratorAction()
{
    GeneralParticleSource = new G4GeneralParticleSource();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorPrimaryGeneratorAction::~DetectorPrimaryGeneratorAction()
{
	delete GeneralParticleSource;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  GeneralParticleSource -> GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
