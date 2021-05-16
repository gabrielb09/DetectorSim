#include "LabDetectorConstruction.hh"

void LabDetectorConstruction::ConstructCoolingMount(){

	// mount base
	G4Box* mountBase = new G4Box("mountBase", width = 0.5*88.90*mm, length = 0.5*30.48*cm, thickness = 0.5*12.70*mm);
	// pipe groove
	G4Tubs* pipeGroove = new G4Tubs("pipeGroove", 0, radius = 5.35*mm, length = 0.5*(30.48*cm + 1*mm), 0, 360*deg);

	// collection of grooves
	G4MultiUnion* Grooves = new G4MultiUnion("Grooves");
	rotation = G4RotationMatrix();
	rotation.rotateX(90.*deg);
	for (int i = 0; i < 4; i++){
		translation.setX((2*i-3)*10.80*mm); translation.setY(0); translation.setZ(0);
		transform = G4Transform3D(rotation, translation);
		Grooves -> AddNode(*pipeGroove, transform);
	}
	Grooves -> Voxelize();

	G4VSolid* coolantMount = new G4SubtractionSolid("CoolantMount", mountBase, Grooves, 0, G4ThreeVector(0, 0, -0.5*12.70*mm));
	coolantMountS = new G4SubtractionSolid("CoolantMount", coolantMount, ScrewsS, 0, G4ThreeVector(0, 0, 0));
	coolantMountL = new G4LogicalVolume(coolantMountS, Aluminium, "Cooling_Mount_Logical");

	G4Tubs* singlePipe = new G4Tubs("pipe", inner_radius = 5.35*mm - 2.0*mm, outer_radius = 5.35*mm, length = 0.75*(30.48*cm), 0, 360*deg);
	G4Torus* pipeBend = new G4Torus("pipeBend", inner_radius = 5.35*mm - 2.0*mm, outer_radius = 5.35*mm, radius = 10.80*mm, 0, 180*deg);
	coolingPipeS = new G4MultiUnion("Pipe");

	translation.setX(-10.80*mm); translation.setY(-7.62*cm); translation.setZ(0);
	transform = G4Transform3D(rotation, translation);
	coolingPipeS -> AddNode(*singlePipe, transform);

	translation.setX(10.80*mm); translation.setY(-7.62*cm); translation.setZ(0);
	transform = G4Transform3D(rotation, translation);
	coolingPipeS -> AddNode(*singlePipe, transform);

	rotation = G4RotationMatrix();

	translation.setX(0); translation.setY(15.24*cm); translation.setZ(0);
	transform = G4Transform3D(rotation, translation);
	coolingPipeS -> AddNode(*pipeBend, transform);

	coolingPipeS -> Voxelize();

	coolingPipeL = new G4LogicalVolume(coolingPipeS, StainlessSteel, "Pipe_Logical");

	G4Tubs* singleNitrogen = new G4Tubs("pipe", 0, radius = 5.35*mm - 2.0*mm, length = 0.75*(30.48*cm), 0, 360*deg);
	G4Torus* nitrogenBend = new G4Torus("pipeBend", 0, outer_radius = 5.35*mm - 2.0*mm, radius = 10.80*mm, 0, 180*deg);
	coolantLiquidS = new G4MultiUnion("Nitrogen");

	rotation.rotateX(90.*deg);
	translation.setX(-10.80*mm); translation.setY(-7.62*cm); translation.setZ(0);
	transform = G4Transform3D(rotation, translation);
	coolantLiquidS -> AddNode(*singleNitrogen, transform);

	translation.setX(10.80*mm); translation.setY(-7.62*cm); translation.setZ(0);
	transform = G4Transform3D(rotation, translation);
	coolantLiquidS -> AddNode(*singleNitrogen, transform);

	rotation = G4RotationMatrix();

	translation.setX(0); translation.setY(15.24*cm); translation.setZ(0);
	transform = G4Transform3D(rotation, translation);
	coolantLiquidS -> AddNode(*nitrogenBend, transform);

	coolantLiquidS -> Voxelize();
	coolantLiquidL = new G4LogicalVolume(coolantLiquidS, LiquidNitrogen, "Nitrogen_Logical");

	coolingMount = new G4AssemblyVolume();

	translation.setX(0); translation.setY(0); translation.setZ(0);
	transform = G4Transform3D(rotation, translation);
	coolingMount -> AddPlacedVolume(coolantMountL, transform);

	translation.setX(0); translation.setY(0); translation.setZ(-6.35*mm);
	transform = G4Transform3D(rotation, translation);
	coolingMount -> AddPlacedVolume(coolingPipeL, transform);

	translation.setX(0); translation.setY(0); translation.setZ(-6.35*mm);
	transform = G4Transform3D(rotation, translation);
	coolingMount -> AddPlacedVolume(coolantLiquidL, transform);
}
