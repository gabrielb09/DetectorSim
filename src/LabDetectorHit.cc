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
// $Id: LabDetectorSDHit.cc,v 1.10 2006/06/29 17:48:24 gunter Exp $
// GEANT4 tag $Name: geant4-09-00 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "LabDetectorHit.hh"
#include "LabDetectorAnalysis.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "global.h"
#include "G4SystemOfUnits.hh"

G4Allocator<LabDetectorHit> LabDetectorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LabDetectorHit::LabDetectorHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LabDetectorHit::~LabDetectorHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LabDetectorHit::LabDetectorHit(const LabDetectorHit& right):
	G4VHit()
{
	trackID_   = right.trackID_;
	time_ 		 = right.time_;
	kEnergy_   = right.kEnergy_;
	vertexPos_ = right.vertexPos_;
  edep_      = right.edep_;
  pos_       = right.pos_;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const LabDetectorHit& LabDetectorHit::operator=(const LabDetectorHit& right)
{
	trackID_   = right.trackID_;
	time_ 		 = right.time_;
	kEnergy_   = right.kEnergy_;
	vertexPos_ = right.vertexPos_;
  edep_      = right.edep_;
  pos_       = right.pos_;
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int LabDetectorHit::operator==(const LabDetectorHit& right) const
{
  return (this==&right) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LabDetectorHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(pos_);
    circle.SetScreenSize(2.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LabDetectorHit::Print()
{
  G4cout << "  trackID_: " << trackID_ << "  time_: " << G4BestUnit(time_,"time_")
         << "  energy: " << kEnergy_ / MeV
				 << "  energy deposit: " << G4BestUnit(edep_,"Energy")
				 << "  position: " << G4BestUnit(pos_,"Length") << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LabDetectorHit::fPrint()
{
	extern global_struct global;

	auto analysisManager = G4AnalysisManager::Instance();

	analysisManager -> FillNtupleIColumn(0, int(global.eventID));
	analysisManager -> FillNtupleIColumn(1, int(trackID_));

	analysisManager -> FillNtupleDColumn(2, double(kEnergy_/keV));
	analysisManager -> FillNtupleDColumn(3, double(edep_/keV));

	analysisManager -> FillNtupleDColumn(4, double(time_/s));
	analysisManager -> FillNtupleDColumn(5, double(pos_.getX()/mm));
	analysisManager -> FillNtupleDColumn(6, double(pos_.getY()/mm));
	analysisManager -> FillNtupleDColumn(7, double(pos_.getZ()/mm));

	analysisManager -> FillNtupleDColumn(8, double(vertexPos_.getX()/mm));
	analysisManager -> FillNtupleDColumn(9, double(vertexPos_.getY()/mm));
	analysisManager -> FillNtupleDColumn(10, double(vertexPos_.getZ()/mm));

  analysisManager -> AddNtupleRow();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
