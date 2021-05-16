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
// $Id: LabRunAction.cc,v 1.9 2006/06/29 17:48:16 gunter Exp $
// GEANT4 tag $Name: geant4-09-00 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "LabRunAction.hh"
#include "LabDetectorAnalysis.hh"

#include "G4Run.hh"
#include "g4root.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "global.h"
#include <fstream>

using namespace std;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LabRunAction::LabRunAction()
: G4UserRunAction()
{
  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager -> SetVerboseLevel(1);
  analysisManager -> SetNtupleMerging(true);

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

LabRunAction::~LabRunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LabRunAction::BeginOfRunAction(const G4Run* aRun)
{
  extern global_struct global;
  char fname[100];

  ((G4Run *)(aRun)) -> SetRunID(global.runnum);
  G4cout << "### Run " << aRun -> GetRunID() << " start." << G4endl;

  sprintf(fname, "%s/%s.root", global.outdir, global.outfile );
  G4cout << "Output file: " << fname << G4endl;

  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager -> OpenFile(fname);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LabRunAction::EndOfRunAction(const G4Run*)
{
	extern global_struct global;

  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager -> Write();
  analysisManager -> CloseFile();

  G4cout << "Run end  " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
