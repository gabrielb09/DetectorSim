#include "LabDetectorConstruction.hh"

void LabDetectorConstruction::ConstructScrews(){

  G4Tubs* screw = new G4Tubs("screw", 0, radius = 2.65*mm, length = 0.5*32.65*mm, 0, 360*deg);
  G4Tubs* washer = new G4Tubs("washer", inner_radius = 2.67*mm, outer_radius = 18.67*mm, thickness = 0.5*1.19*mm, 0, 360*deg);

  ScrewsS = new G4MultiUnion("Screws");
  WashersS = new G4MultiUnion("Washers");
  rotation = G4RotationMatrix();

  translation.setX(48.0*mm); translation.setY(48.0*mm); translation.setZ(0);
  transform = G4Transform3D(rotation, translation);
  ScrewsS -> AddNode(*screw, transform);
  WashersS -> AddNode(*washer, transform);

  translation.setX(48.0*mm); translation.setY(-48.0*mm); translation.setZ(0);
  transform = G4Transform3D(rotation, translation);
  ScrewsS -> AddNode(*screw, transform);
  WashersS -> AddNode(*washer, transform);

  translation.setX(-48.0*mm); translation.setY(48.0*mm); translation.setZ(0);
  transform = G4Transform3D(rotation, translation);
  ScrewsS -> AddNode(*screw, transform);
  WashersS -> AddNode(*washer, transform);

  translation.setX(-48.0*mm); translation.setY(-48.0*mm); translation.setZ(0);
  transform = G4Transform3D(rotation, translation);
  ScrewsS -> AddNode(*screw, transform);
  WashersS -> AddNode(*washer, transform);

  ScrewsS -> Voxelize();
  WashersS -> Voxelize();

  ScrewsL = new G4LogicalVolume(ScrewsS, StainlessSteel, "Screws_Logical");
  WashersL = new G4LogicalVolume(WashersS, StainlessSteel, "Washers_Logical");
}
