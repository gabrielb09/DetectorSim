#include "LabDetectorConstruction.hh"

void LabDetectorConstruction::ConstructColdPlate(){

	G4Box* plateBase = new G4Box("plateBase", width = 0.5*12.70*cm, length = 0.5*30.48*cm, height = 0.5*6.35*mm);

	G4Box* cuPlate = new G4Box("copperCore", width = 0.5*12.70*cm - 0.1*mm, length = 0.5*30.48*cm - 0.1*mm, height = 0.5*6.35*mm - 0.1*mm);
	cuPlateS = new G4SubtractionSolid("copperCore", cuPlate, ScrewsS, 0, G4ThreeVector(0,0,0));
	cuPlateL = new G4LogicalVolume(cuPlateS, Copper, "Copper_Plate_Logical");

	G4VSolid* niPlate = new G4SubtractionSolid("nicklePlating", plateBase, cuPlate, 0, G4ThreeVector(0, 0, 0));
	niPlateS = new G4SubtractionSolid("nicklePlating", niPlate, ScrewsS, 0, G4ThreeVector(0, 0, 0));
	niPlateL = new G4LogicalVolume(niPlateS, Nickle, "Nickle_Coating_Logical");

	coldPlate = new G4AssemblyVolume();

	rotation = G4RotationMatrix();
	translation.setX(0); translation.setY(0); translation.setZ(0);
	transform = G4Transform3D(rotation, translation);

	coldPlate -> AddPlacedVolume(cuPlateL, transform);
	coldPlate -> AddPlacedVolume(niPlateL, transform);
}
