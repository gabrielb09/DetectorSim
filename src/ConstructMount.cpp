#include "DetectorConstruction.hh"

inline void DetectorConstruction::ConstructMount(){
	// base aluminium box
	G4Box* mountBase = new G4Box("mountBase", length = 0.5*120.0*mm, width = 0.5*120.0*mm, thickness = 0.5*12.0*mm);

	// corner cut-outs
	// list of vertecies
	std::vector<G4TwoVector> vertecies(8);
	// x and y position of vertecies
	G4double x[4] = {0, 0, -1*(12.0*mm + 1*mm), 0};
	G4double y[4] = {0, -1*(12.0*mm + 1*mm), 0, 0};
	for (int i = 0; i < 4; i++){
    		vertecies[i]   = G4TwoVector(x[i], y[i]);
    		vertecies[i+4] = G4TwoVector(x[i], y[i]);
    	}
   	// create single corner in top left
	G4GenericTrap* Corner = new G4GenericTrap("corner", thickness = 0.5*12.0*mm + 1.0*mm, vertecies);

	// create a union of all 4 corners
	G4MultiUnion* Corners = new G4MultiUnion("Corners");
	G4double X[4] = {61*mm, -61*mm, -61*mm, 61*mm};
	G4double Y[4] = {61*mm, 61*mm, -61*mm, -61*mm};

	for (int i = 0; i < 4; i++){
		rotation = G4RotationMatrix();
		rotation.rotateZ(i*90*deg);
		translation.setX(X[i]); translation.setY(Y[i]); translation.setZ(0);
		transform = G4Transform3D(rotation, translation);
		Corners -> AddNode(*Corner, transform);
	}
	Corners -> Voxelize();

	// subtract corners from base
	G4SubtractionSolid* mountCut = new G4SubtractionSolid("cornerCut", mountBase, Corners, 0, G4ThreeVector(0, 0, 0));

	// hole
	G4Tubs* Hole = new G4Tubs("hole", 0, radius = 47.5*mm, thickness = 0.5*12.0*mm, 0, 360*deg);
	// top cavity
	G4Cons* TopCavity = new G4Cons("topCavity", 0, inner_radius = 47.5*mm - 0.5*mm, 0, outer_radius = 50.5*mm + 0.5*mm, thickness = (3.0*mm + 1*mm)*0.5, 0, 360*deg);
	// bottom cavity
	G4Tubs* BotCavity = new G4Tubs("botCavity", 0, radius = 57.0*mm, thickness = (7.0*mm + 1*mm)*0.5, 0, 360*deg);
	// union of cavities
	G4MultiUnion* Cavity = new G4MultiUnion("Cavity");
	// add cavities together
	rotation = G4RotationMatrix();

	translation.setX(0); translation.setY(0); translation.setZ(0);
	transform = G4Transform3D(rotation, translation);
	Cavity -> AddNode(*Hole, transform);

	translation.setX(0); translation.setY(0); translation.setZ(4.5*mm);
	transform = G4Transform3D(rotation, translation);
	Cavity -> AddNode(*TopCavity, transform);

	translation.setX(0); translation.setY(0); translation.setZ(-3*mm);
	transform = G4Transform3D(rotation, translation);
	Cavity -> AddNode(*BotCavity, transform);

	Cavity -> Voxelize();

	// subtract cavities from base
	G4SubtractionSolid* mountHoled = new G4SubtractionSolid("holeCut", mountCut, Cavity, 0, G4ThreeVector(0, 0, 0));

	// notches
	G4Box* topNotch = new G4Box("topNotch", length = 0.5*60.0*mm, width = 0.5*70.0*mm, thickness = (4.5*mm + 1*mm)*0.5);
	G4Box* botNotch = new G4Box("botNotch", length = 0.5*8.0*mm, width = 0.5*12.0*mm, thickness = (5.0*mm + 1*mm)*0.5);
	// union of notches
	G4MultiUnion* Notches = new G4MultiUnion("notches");

	translation.setX(-60*mm); translation.setY(0); translation.setZ(4.25*mm);
	transform = G4Transform3D(rotation, translation);
	Notches -> AddNode(*topNotch, transform);

	translation.setX(60*mm); translation.setY(0); translation.setZ(-3.5*mm);
	transform = G4Transform3D(rotation, translation);
	Notches -> AddNode(*botNotch, transform);

	Notches -> Voxelize();

	// subtract notches from base
	G4VSolid* mount = new G4SubtractionSolid("Mount", mountHoled, Notches, 0, G4ThreeVector(0, 0, 0));
	mountS = new G4SubtractionSolid("Mount", mount, ScrewsS, 0, G4ThreeVector(0, 0, -2.0*mm));
	mountL = new G4LogicalVolume(mountS, Aluminium, "MountLog");

	// mounting ring
	G4VSolid* Ring = new G4Tubs("Mount_Ring", inner_radius = 46.5*mm, outer_radius = 56.75*mm, thickness = 0.5*3.1*mm, 0, 360*deg);
	mountRingS = new G4SubtractionSolid("Mount_Ring", Ring, ScrewsS, 0, G4ThreeVector(0, 0, 0));
	mountRingL = new G4LogicalVolume(mountRingS, Aluminium, "Mount_Ring_Log");
	insulatingRingL = new G4LogicalVolume(mountRingS, FR_4, "Insulating_Ring_Log");
}
