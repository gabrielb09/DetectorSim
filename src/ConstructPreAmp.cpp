#include "DetectorConstruction.hh"

inline void DetectorConstruction::ConstructPreAmp(){
	// main PCB
	G4Box* mainPCB = new G4Box("mainPCB", length = 0.5*91.6*mm, width = 0.5*75.7*mm, thickness = 0.5*1.6*mm);

	G4Box* cut = new G4Box("cut", length = (74.85*mm + 1*mm)*0.5, width = 3.35*mm, thickness = 0.5*1.65*mm);
	G4UnionSolid* PCBcut = new G4UnionSolid("PCBcut", cut, cut, 0, G4ThreeVector(0,  -75.7*mm, 0));

	holderS = new G4SubtractionSolid("holder", mainPCB, PCBcut, 0, G4ThreeVector(-8.625*mm, 37.85*mm, 0));
	// vertical extensions
	preAmpS = new G4Box("preAmp", length = 0.5*28.5*mm, thickness = 0.5*0.8*mm, width = 0.5*14.3*mm);

	// pins
	pinS = new G4Tubs("pin", 0, radius = 0.254*mm, length = 0.5*3.6*mm, 0, 360*deg);
	pinCapS = new G4Tubs("pin", 0, radius = 0.254*mm, length = 0.1*mm, 0, 360*deg);

	// links
	linkArcS = new G4Torus("linkArc", 0, thickness = 0.5715*mm, radius = 1.7907*mm, 0, 90*deg);
	linkPinS = new G4Tubs("linkPin", 0, thickness = 0.5715*mm, length = 0.5*1.49*mm, 0, 360*deg);

	holderL = new G4LogicalVolume(holderS, HolderMat, "holderL");
	preAmpL = new G4LogicalVolume(preAmpS, PreAmpMat, "preAmpL");
	pinL = new G4LogicalVolume(pinS, Copper, "pinL");
	pinCapL = new G4LogicalVolume(pinCapS, Copper, "pinCapL");
	linkArcL = new G4LogicalVolume(linkArcS, Copper, "linkArcL");
	linkPinL = new G4LogicalVolume(linkPinS, Copper, "linkPinL");


	G4double vertLocations[8] = {31.63*mm, 24.58*mm, 15.41*mm, 6.24*mm, -2.93*mm, -12.10*mm, -21.27*mm, -28.15*mm};
	G4double pinLocations[8] = {34.55*mm, 23.628*mm, 13.722*mm, 4.578*mm, -4.566*mm, -13.71*mm, -23.616*mm, -34.538*mm};
	G4double jointLocations[7] = {12.53*mm, 16.34*mm, 20.15*mm, 23.96*mm, 27.77*mm, 32.85*mm, 36.66*mm};

	rotation = G4RotationMatrix();
	preAmp = new G4AssemblyVolume();

	translation.setX(0); translation.setY(0); translation.setZ(0);
	transform = G4Transform3D(rotation, translation);
	preAmp -> AddPlacedVolume(holderL, transform);


	for (int i = 0; i < 8; i++){
		translation.setX(40.645*mm); translation.setY(pinLocations[i]); translation.setZ(-2.6*mm);
		transform = G4Transform3D(rotation, translation);
		preAmp -> AddPlacedVolume(pinL, transform);

		translation.setX(40.645*mm); translation.setY(pinLocations[i]); translation.setZ(0.85*mm);
		transform = G4Transform3D(rotation, translation);
		preAmp -> AddPlacedVolume(pinCapL, transform);

		translation.setX(24.89*mm); translation.setY(vertLocations[i]); translation.setZ(7.95*mm);
		transform = G4Transform3D(rotation, translation);
		preAmp -> AddPlacedVolume(preAmpL, transform);


		for (int j = 0; j < 7; j++){

			rotation.rotateY(-90*deg); rotation.rotateZ(180*deg);
			translation.setX(jointLocations[j]); translation.setY(vertLocations[i] - 0.4*mm); translation.setZ(0.8*mm);
			transform = G4Transform3D(rotation, translation);
			//cuLeads -> AddNode(*linkArc, transform);
			preAmp -> AddPlacedVolume(linkArcL, transform);

			rotation = G4RotationMatrix();
			translation.setX(jointLocations[j]); translation.setY(vertLocations[i] - 0.4*mm - 1.7907*mm); translation.setZ(-1.545*mm);
			//cuLeads -> AddNode(*linkPin, transform);
			preAmp -> AddPlacedVolume(linkPinL, transform);

			rotation = G4RotationMatrix();
			translation.setX(jointLocations[j]); translation.setY(vertLocations[i] - 0.4*mm - 1.7907*mm); translation.setZ(0);
			//cuLeads -> AddNode(*linkFill, transform);

		}
	}
}
