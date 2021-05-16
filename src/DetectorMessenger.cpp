#include "DetectorMessenger.hh"

#include "DetectorRunAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorRunAction* myRunAct)
:myRunAction(myRunAct)
{
// output directry
  OutDirCmd = new G4UIcmdWithAString("/OutputDirectory", this);
  OutDirCmd -> SetGuidance("Directory for output files");
  OutDirCmd -> SetParameterName("OutputDirectory", true );
  OutDirCmd -> SetDefaultValue("./tmp");

// output file
  OutFileCmd = new G4UIcmdWithAString("/OutputFile", this );
  OutFileCmd -> SetGuidance("Name of output file");
  OutFileCmd -> SetParameterName("OutputFile",true);
  OutFileCmd -> SetDefaultValue("test");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
	delete OutDirCmd;
  delete OutFileCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
	if(command == OutDirCmd){myRunAction -> SetOutDir(newValue); };
	if(command == OutFileCmd){myRunAction -> SetOutFile(newValue); };
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
