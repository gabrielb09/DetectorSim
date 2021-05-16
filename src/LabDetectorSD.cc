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
// $Id: LabDetectorSD.cc,v 1.9 2006/06/29 17:48:27 gunter Exp $
// GEANT4 tag $Name: geant4-09-00 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "LabDetectorSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"
#include "global.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LabDetectorSD::LabDetectorSD(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
	collectionName.insert(HCname = name);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LabDetectorSD::~LabDetectorSD(){ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LabDetectorSD::Initialize(G4HCofThisEvent* HCE)
{
  DetectorCollection = new LabDetectorHitsCollection(SensitiveDetectorName, collectionName[0]);
  auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  HCE -> AddHitsCollection(hcID, DetectorCollection );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool LabDetectorSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  extern global_struct global;

  LabDetectorHit* newHit = new LabDetectorHit();

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

void LabDetectorSD::EndOfEvent(G4HCofThisEvent*)
{
	extern global_struct global;

  NbHits = DetectorCollection -> entries();
  for(G4int i = 0; i<NbHits; i++ )
  {
    (*DetectorCollection)[i] -> fPrint();
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
