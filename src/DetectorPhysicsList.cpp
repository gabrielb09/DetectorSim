#include "DetectorPhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4SystemOfUnits.hh"

#include "G4HadronPhysicsQGSP_BERT.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
DetectorPhysicsList::DetectorPhysicsList():  G4VModularPhysicsList()
{
    SetDefaultCutValue(1.0*um);

    G4int ver = 1;
    SetVerboseLevel(ver);

    // EM Physics
    RegisterPhysics( new G4EmStandardPhysics_option4(ver) );

    // Synchroton Radiation & GN Physics
    RegisterPhysics( new G4EmExtraPhysics(ver) );

    // Decays
    RegisterPhysics( new G4DecayPhysics(ver) );

    // Hadron Elastic scattering
    RegisterPhysics( new G4HadronElasticPhysics(ver) );

    // Hadron Physics
    RegisterPhysics( new G4HadronPhysicsQGSP_BERT(ver));

    // Stopping Physics
    RegisterPhysics( new G4StoppingPhysics(ver) );

    // Ion Physics
    RegisterPhysics( new G4IonPhysics(ver));

    // Neutron tracking cut
    RegisterPhysics( new G4NeutronTrackingCut(ver));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
DetectorPhysicsList::~DetectorPhysicsList()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorPhysicsList::SetCuts()
{
    // Use default cut values gamma and e processes
    SetCutsWithDefault();
}
