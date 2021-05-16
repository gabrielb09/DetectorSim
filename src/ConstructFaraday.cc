#include "LabDetectorConstruction.hh"

void LabDetectorConstruction::ConstructFaraday(){

	G4Box* faradaySolid = new G4Box("faradaySolid", length = 0.5*114.3*mm, width = 0.5*114.3*mm, height = 0.5*57.15*mm);
	G4Box* faradayCavity = new G4Box("faradayCavity", length = 0.5*114.3*mm - 1.02*mm, width = 0.5*114.3*mm - 1.02*mm, height = 0.5*57.15*mm);
	faradayCageS = new G4SubtractionSolid("faradayCage", faradaySolid, faradayCavity, 0, G4ThreeVector(0,0,-1.02*mm));

	faradayCageL = new G4LogicalVolume(faradayCageS, Aluminium, "Faraday_Cage_Logical");
}
