#include "DetectorEventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorEventAction::DetectorEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorEventAction::~DetectorEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorEventAction::BeginOfEventAction(const G4Event* evt)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorEventAction::EndOfEventAction(const G4Event* evt)
{
    G4int event_id = evt -> GetEventID();
    if (event_id < 10 || event_id%1000 == 0) G4cout << ">>> Event " << evt -> GetEventID() << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
