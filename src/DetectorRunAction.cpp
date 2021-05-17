#include "DetectorRunAction.hh"

#include "g4root.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorRunAction::DetectorRunAction()
: G4UserRunAction()
{
  detectorMessenger = new DetectorMessenger(this);

  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager -> SetVerboseLevel(1);

  analysisManager -> CreateNtuple("DetectorSimData", "Detector Simulation Data");

  analysisManager -> CreateNtupleIColumn("eventID");
  analysisManager -> CreateNtupleIColumn("trackID");

  analysisManager -> CreateNtupleDColumn("energy");
  analysisManager -> CreateNtupleDColumn("eDep");

  analysisManager -> CreateNtupleDColumn("t");
  analysisManager -> CreateNtupleDColumn("x");
  analysisManager -> CreateNtupleDColumn("y");
  analysisManager -> CreateNtupleDColumn("z");

  analysisManager -> CreateNtupleDColumn("vertex_x");
  analysisManager -> CreateNtupleDColumn("vertex_y");
  analysisManager -> CreateNtupleDColumn("vertex_z");

  analysisManager->FinishNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorRunAction::~DetectorRunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorRunAction::BeginOfRunAction(const G4Run* aRun)
{
  char fname[100];

  G4cout << "### Run " << aRun -> GetRunID() << " start." << G4endl;

  sprintf(fname, "%s/%s.root", outdir.c_str(), outfile.c_str());
  G4cout << "Output file: " << fname << G4endl;

  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager -> OpenFile(fname);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorRunAction::EndOfRunAction(const G4Run*)
{

  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager -> Write();
  analysisManager -> CloseFile();

  G4cout << "Run end  " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
