//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: LabDetectorMessenger.cc,v 1.11 2006/06/29 17:48:02 gunter Exp $
// GEANT4 tag $Name: geant4-09-00 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "LabDetectorMessenger.hh"

#include "LabDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "globals.hh"
#include "global.h"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LabDetectorMessenger::LabDetectorMessenger(LabDetectorConstruction* myDet)
:myDetector(myDet)
{
// output directry
  OutDirCmd = new G4UIcmdWithAString("/OutputDirectory", this);
  OutDirCmd->SetGuidance("Directory for output files");
  OutDirCmd->SetParameterName("OutputDirectory", true );
  OutDirCmd->SetDefaultValue("./tmp");

// output file
  OutFileCmd = new G4UIcmdWithAString("/OutputFile", this );
  OutFileCmd->SetGuidance("Name of output file");
  OutFileCmd->SetParameterName("OutputFile",true);
  OutFileCmd->SetDefaultValue("test");

// Detector overlap check
  CheckOverlapCmd = new G4UIcmdWithAnInteger("/CheckOverlap", this );
  CheckOverlapCmd->SetGuidance("Verbose level of Labs");
  CheckOverlapCmd->SetParameterName("flag",true);
  CheckOverlapCmd->SetDefaultValue(0);

// update geometry
	UpdateCmd = new G4UIcmdWithoutParameter("/update",this);
  UpdateCmd->SetGuidance("Update geometry.");
  UpdateCmd->AvailableForStates(G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LabDetectorMessenger::~LabDetectorMessenger()
{
	delete OutDirCmd;
  delete OutFileCmd;
	delete CheckOverlapCmd;
	delete UpdateCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LabDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
 extern global_struct global;
	if(command == OutDirCmd) strcpy(global.outdir, newValue );
	if(command == OutFileCmd) strcpy(global.outfile, newValue );
	if(command == CheckOverlapCmd) global.CheckOverlap = (CheckOverlapCmd->GetNewIntValue(newValue));
	if(command == UpdateCmd) myDetector->UpdateGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
