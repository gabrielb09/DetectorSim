#include "DetectorSD.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorSD::DetectorSD(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
	collectionName.insert(HCname = name);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorSD::~DetectorSD(){ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorSD::Initialize(G4HCofThisEvent* HCE)
{
  DetectorCollection = new DetectorHitsCollection(SensitiveDetectorName, collectionName[0]);
  auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  HCE -> AddHitsCollection(hcID, DetectorCollection );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  DetectorHit* newHit = new DetectorHit();

  newHit -> SetEventID(G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID());
  newHit -> SetTrackID(step -> GetTrack() -> GetTrackID());
  newHit -> SetEdep(step -> GetTotalEnergyDeposit());
  newHit -> SetEnergy(step -> GetPreStepPoint() -> GetKineticEnergy());
  newHit -> SetPos(step -> GetPostStepPoint() -> GetPosition());
  newHit -> SetVertex(step -> GetTrack() -> GetVertexPosition());
  newHit -> SetTime(step -> GetTrack() -> GetLocalTime());

  DetectorCollection -> insert(newHit);

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorSD::EndOfEvent(G4HCofThisEvent*)
{

  NbHits = DetectorCollection -> entries();
  for(G4int i = 0; i<NbHits; i++ )
  {
    (*DetectorCollection)[i] -> fPrint();
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
