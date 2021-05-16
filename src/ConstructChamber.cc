#include "LabDetectorConstruction.hh"

void LabDetectorConstruction::ConstructChamber(){
	// chamber walls
	chamberS = new G4Tubs("baseCylinder", inner_radius = 47.5*cm - 2.54*cm, outer_radius = 47.5*cm, height = 0.5*90.0*cm, 0, 360*deg);
	chamberL = new G4LogicalVolume(chamberS, Iron, "Chamber_Walls_Logical");

	// single cap
	G4Tubs* cap = new G4Tubs("cap", 0, radius = 47.5*cm, thickness = 0.5*2.54*cm, 0, 360*deg);
	// bottom and top caps
	lidS = new G4UnionSolid("caps", cap, cap, 0, G4ThreeVector(0,0,92.54*cm));
	lidL = new G4LogicalVolume(lidS, Aluminium, "Chamber_Caps_Logical");

	// volume assembly
	chamber = new G4AssemblyVolume();

	rotation = G4RotationMatrix();
	translation.setX(0); translation.setY(0); translation.setZ(0);

  transform = G4Transform3D(rotation, translation);
  chamber -> AddPlacedVolume(chamberL, transform);

	translation.setX(0); translation.setY(0); translation.setZ(-46.27*cm);
  transform = G4Transform3D(rotation, translation);
  chamber -> AddPlacedVolume(lidL, transform);
}
