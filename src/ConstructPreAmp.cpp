#include "DetectorConstruction.hh"

inline void DetectorConstruction::ConstructPreAmp(){
	// main PCB
	G4Box* mainPCB = new G4Box("mainPCB", length = 0.5*91.6*mm, width = 0.5*75.7*mm, thickness = 0.5*1.6*mm);

	G4Box* cut = new G4Box("cut", length = (74.85*mm + 1*mm)*0.5, width = 3.35*mm, thickness = 0.5*1.65*mm);
	G4UnionSolid* PCBcut = new G4UnionSolid("PCBcut", cut, cut, 0, G4ThreeVector(0,  -75.7*mm, 0));

	G4SubtractionSolid* holder = new G4SubtractionSolid("holder", mainPCB, PCBcut, 0, G4ThreeVector(-8.625*mm, 37.85*mm, 0));
	// vertical extensions
	G4Box* preAmpBoard = new G4Box("preAmp", length = 0.5*28.5*mm, thickness = 0.5*0.8*mm, width = 0.5*14.3*mm);

	// add preAmps together
	G4MultiUnion* preAmps = new G4MultiUnion("preAmps");

	rotation = G4RotationMatrix();
	G4double vertLocations[8] = {31.63*mm, 24.58*mm, 15.41*mm, 6.24*mm, -2.93*mm, -12.10*mm, -21.27*mm, -28.15*mm};

	for(int i = 0; i < 8; i++){
		translation.setX(24.89*mm); translation.setY(vertLocations[i]); translation.setZ(7.95*mm);
		transform = G4Transform3D(rotation, translation);
		preAmps -> AddNode(*preAmpBoard, transform);
	}

	preAmps -> Voxelize();

	// pins
	G4Tubs* pin = new G4Tubs("pin", 0, radius = 0.825*mm, length = 0.5*5.2*mm, 0, 360*deg);
	// links
	G4Torus* linkArc = new G4Torus("linkArc", 0, thickness = 0.6*mm, radius = 2.28*mm, 0, 90*deg);
	G4Tubs* linkPin = new G4Tubs("linkPin", 0, thickness = 0.6*mm, length = 0.5*3.09*mm, 0, 360*deg);

	// Copper leads
 	G4MultiUnion* cuLeads = new G4MultiUnion("cuLeads");

	G4double pinLocations[8] = {34.55*mm, 23.628*mm, 13.722*mm, 4.578*mm, -4.566*mm, -13.71*mm, -23.616*mm, -34.538*mm};
	G4double jointLocations[7] = {12.53*mm, 16.34*mm, 20.15*mm, 23.96*mm, 27.77*mm, 32.85*mm, 36.66*mm};
	for (int i = 0; i < 8; i++){
		translation.setX(40.645*mm); translation.setY(pinLocations[i]); translation.setZ(-1.8*mm);
		transform = G4Transform3D(rotation, translation);
		cuLeads -> AddNode(*pin, transform);

		for (int j = 0; j < 7; j++){

			translation.setX(jointLocations[j]); translation.setY(vertLocations[i] - 2.0*mm); translation.setZ(-0.745*mm);
			transform = G4Transform3D(rotation, translation);
			cuLeads -> AddNode(*linkPin, transform);

			rotation.rotateZ(180*deg);
			rotation.rotateY(90*deg);
			translation.setX(jointLocations[j]); translation.setY(vertLocations[i] + 0.28*mm); translation.setZ(0.5*1.6*mm);
			transform = G4Transform3D(rotation, translation);
			cuLeads -> AddNode(*linkArc, transform);

			rotation.rotateY(-90*deg);
			rotation.rotateZ(-180*deg);
			rotation = G4RotationMatrix();

		}
	}

	cuLeads -> Voxelize();



	holderS = new G4SubtractionSolid("holder", holder, cuLeads, 0, G4ThreeVector(0, 0, 0));
	preAmpS = new G4SubtractionSolid("preAmp", preAmps, cuLeads, 0, G4ThreeVector(0, 0, 0));

	holderL = new G4LogicalVolume(holderS, HolderMat, "holderL");
	preAmpL = new G4LogicalVolume(preAmpS, PreAmpMat, "preAmpL");

	copperL = new G4LogicalVolume(cuLeads, Copper, "copperL");

	preAmp = new G4AssemblyVolume();

	translation.setX(0); translation.setY(0); translation.setZ(0);
	transform = G4Transform3D(rotation, translation);
	preAmp -> AddPlacedVolume(holderL, transform);

	translation.setX(0); translation.setY(0); translation.setZ(0);
	transform = G4Transform3D(rotation, translation);
	preAmp -> AddPlacedVolume(preAmpL, transform);

	translation.setX(0); translation.setY(0); translation.setZ(0);
	transform = G4Transform3D(rotation, translation);
	preAmp -> AddPlacedVolume(copperL, transform);
}
