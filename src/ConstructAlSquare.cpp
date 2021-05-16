#include "DetectorConstruction.hh"

inline void DetectorConstruction::ConstructAlSquare(){
	// base solids
	G4Box* baseSquare = new G4Box("baseSquare", length = 0.5*12.7*cm, width = 0.5*12.7*cm, thickness = 0.5*4.76*mm);

	G4Tubs* circleCut = new G4Tubs("circleCut", 0, radius = 5.84*cm, thickness = 0.5*5.76*mm, 0, 360*deg);

	G4Box* cutOut = new G4Box("cutOut", length = 0.25*12.7*cm, width = 0.5*5.08*cm, thickness = 0.5*5.76*mm);

	// union of cuts
	G4UnionSolid* Cuts = new G4UnionSolid("Cuts", circleCut, cutOut, 0, G4ThreeVector(0.5*12.7*cm, 0, 0));
	// cut from base
	G4VSolid* AlSquare = new G4SubtractionSolid("AlSquare", baseSquare, Cuts, 0, G4ThreeVector(0, 0, 0));
	// screw holes
	AlSquareS = new G4SubtractionSolid("AlSquare", AlSquare, ScrewsS, 0, G4ThreeVector(0,0,0));

	// logical Volume
	AlSquareL = new G4LogicalVolume(AlSquareS, Aluminium, "AlSquareLog");
}
