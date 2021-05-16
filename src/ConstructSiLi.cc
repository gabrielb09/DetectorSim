#include "LabDetectorConstruction.hh"
#include "G4TwoVector.hh"

// function to get the x positions of a circle: used to calcualte the length of the grooves
G4double getCirlceX(G4double r, G4double y){
	G4double x = sqrt(pow(r,2.) - pow(y,2.)); // x = sqrt(r^2 - y^2)
	return x;
}

void LabDetectorConstruction::ConstructSiLi(){

	G4double groovePositions[7] = {0.0*cm, -2.89*cm, -1.84*cm, -0.9*cm, 0.9*cm, 1.84*cm, 2.89*cm}; // Positions of grooves from center of detector

	// Initial Wafer
  G4Tubs* SiLiWaffer = new G4Tubs("SiLiWaffer",0.0, radius = 5.05*cm, thickness = 0.5*2.5*mm, 0, 360*deg);

	// Top Hat
  G4Tubs* HatEdge = new G4Tubs("HatEdge", inner_radius = 4.85*cm, outer_radius = 5.05*cm + 1*mm,
																					thickness = 0.5*1.5*mm + 0.05*mm,
																					0, 360*deg);

  G4SubtractionSolid* Brim = new G4SubtractionSolid("Brim", SiLiWaffer, HatEdge, 0, G4ThreeVector(0,0, .55*mm)); //subtract the top hat from the wafer

  // Guard Ring
  G4Tubs* GaurdRing = new G4Tubs("GaurdRing", inner_radius = 4.55*cm - 0.5*1.0*mm, outer_radius = 4.55*cm + 0.5*1.0*mm,
																							thickness = 0.5*0.3*mm, 0, 360*deg);

  // Grooves

	G4MultiUnion* Grooves = new G4MultiUnion("Grooves");

	translation.setX(0); translation.setY(0); translation.setZ(1.1*mm);
	transform = G4Transform3D(rotation, translation);
  Grooves -> AddNode(*GaurdRing, transform);

	G4VSolid* groove;

	for(int i = 0; i < 7; i++){
		// create a groove
			std::vector<G4TwoVector> vertecies(8);
			// find vertecies
			G4double x[4] = {
											 getCirlceX(4.55*cm, groovePositions[i] + 0.5*1.0*mm),
										-1*getCirlceX(4.55*cm, groovePositions[i] + 0.5*1.0*mm),
	    					 		-1*getCirlceX(4.55*cm, groovePositions[i] - 0.5*1.0*mm),
										   getCirlceX(4.55*cm, groovePositions[i] - 0.5*1.0*mm)
										 };
	    G4double y[4] = {0.5*1.0*mm, 0.5*1.0*mm, -0.5*1.0*mm, -0.5*1.0*mm};

			for (int j = 0; j < 4; j++){
				vertecies[j]   = G4TwoVector(x[j], y[j]);
	    	vertecies[j+4] = G4TwoVector(x[j], y[j]);
	    }

			groove = new G4GenericTrap("groove", thickness = 0.5*0.3*mm, vertecies);

			translation.setX(0); translation.setY(groovePositions[i]); translation.setZ(1.1*mm);
			transform = G4Transform3D(rotation, translation);
      Grooves -> AddNode(*groove, transform);
	}

  Grooves -> Voxelize();

  // subtract grooves from waffer
	detectorS = new G4SubtractionSolid("detector", Brim, Grooves, 0, G4ThreeVector(0, 0, 0));
	piGroovesS = new G4SubtractionSolid("polyimide", Grooves, Brim, 0, G4ThreeVector(0, 0, 2.35*mm));

  detectorL = new G4LogicalVolume(detectorS, Silicon, "SiLi Detector Logical");
	piGroovesL = new G4LogicalVolume(piGroovesS, Polyimide, "Polyimide Logical");

	SiLi = new G4AssemblyVolume();
	rotation = G4RotationMatrix();
	translation.setX(0); translation.setY(0); translation.setZ(0);
	transform = G4Transform3D(rotation, translation);

	SiLi -> AddPlacedVolume(detectorL, transform);
	SiLi -> AddPlacedVolume(piGroovesL, transform);
}
