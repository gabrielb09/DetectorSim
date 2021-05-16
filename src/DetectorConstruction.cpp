#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "ConstructSiLi.cpp"
#include "ConstructMount.cpp"
#include "ConstructScrews.cpp"
#include "ConstructPreAmp.cpp"
#include "ConstructChamber.cpp"
#include "ConstructFaraday.cpp"
#include "ConstructAlSquare.cpp"
#include "ConstructColdPlate.cpp"
#include "ConstructCoolingMount.cpp"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4LogicalVolume.hh"
#include "G4AssemblyVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4RunManager.hh"

#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4ProductionCuts.hh"

#include "G4String.hh"
#include "G4UserLimits.hh"
#include "G4Colour.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:worldS(0),worldL(0),worldP(0)
{
  DefineMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
  delete detectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
    // Material definition with NIST Manager

    G4NistManager* nistManager = G4NistManager::Instance();

    Air = nistManager -> FindOrBuildMaterial("G4_AIR");
    // Elements
    H = nistManager -> FindOrBuildElement("H");
    B = nistManager -> FindOrBuildElement("B");
    C = nistManager -> FindOrBuildElement("C");
    N = nistManager -> FindOrBuildElement("N");
    O = nistManager -> FindOrBuildElement("O");
    F = nistManager -> FindOrBuildElement("F");
    Al = nistManager -> FindOrBuildElement("Al");
    Si = nistManager -> FindOrBuildElement("Si");
    P = nistManager -> FindOrBuildElement("P");
    S = nistManager -> FindOrBuildElement("S");
    Ca = nistManager -> FindOrBuildElement("Ca");
    Ti = nistManager -> FindOrBuildElement("Ti");
    Cr = nistManager -> FindOrBuildElement("Cr");
    Mn = nistManager -> FindOrBuildElement("Mn");
    Fe = nistManager -> FindOrBuildElement("Fe");
    Ni = nistManager -> FindOrBuildElement("Ni");


    // molecules

    SiO2 = new G4Material("SiO2", density = 2.65*g/cm3, nel = 2);
      SiO2 -> AddElement(Si, natoms = 1);
      SiO2 -> AddElement(O, natoms = 2);

    Al2O3 = new G4Material("Al2O3", density = 2.88*g/cm3, nel = 2);
      Al2O3 -> AddElement(Al, natoms = 2);
      Al2O3 -> AddElement(O, natoms = 3);

    TiO2 = new G4Material("TiO2", density = 4.23*g/cm3, nel = 2);
      TiO2 -> AddElement(Ti, natoms = 1);
      TiO2 -> AddElement(O, natoms = 2);

    CaO2 = new G4Material("CaO2", density = 2.91*g/cm3, nel = 2);
      CaO2 -> AddElement(Ca, natoms = 1);
      CaO2 -> AddElement(O, natoms = 2);

    B2O3 = new G4Material("B2O3", density = 2.55*g/cm3, nel = 2);
      B2O3 -> AddElement(B, natoms = 2);
      B2O3 -> AddElement(O, natoms = 3);

    Fe2O3 = new G4Material("Fe2O3", density = 5.24*g/cm3, nel = 2);
      Fe2O3 -> AddElement(Fe, natoms = 2);
      Fe2O3 -> AddElement(O, natoms = 3);

    PTFE = new G4Material("PTFE", density = 2.2*g/cm3, nel = 2);
      PTFE -> AddElement(C, natoms = 2);
      PTFE -> AddElement(F, natoms = 4);

    // complex materials

    // NIST materials
    Aluminium = nistManager -> FindOrBuildMaterial("G4_Al");
    Iron = nistManager -> FindOrBuildMaterial("G4_Fe");
    Copper = nistManager -> FindOrBuildMaterial("G4_Cu");
    Nickle = nistManager -> FindOrBuildMaterial("G4_Ni");
    Silicon = nistManager -> FindOrBuildMaterial("G4_Si");

    // Vacuum
    Vacuum = new G4Material("Vacuum", density = 2.376e-15*g/cm3, nel = 1, kStateGas, temperature = 310*kelvin, pressure = 1.0e-8*bar);
      Vacuum -> AddMaterial(Air, 100*perCent);

    //Type 304 stainless steel
    StainlessSteel = new G4Material("StainlessSteel", density = 8.03*g/cm3, nel = 9);
      StainlessSteel -> AddElement(Fe, FractionMass = 68.245*perCent);
      StainlessSteel -> AddElement(Cr, FractionMass = 19*perCent);
      StainlessSteel -> AddElement(Ni, FractionMass = 9.5*perCent);
      StainlessSteel -> AddElement(Mn, FractionMass = 2.0*perCent);
      StainlessSteel -> AddElement(N, FractionMass = 0.1*perCent);
      StainlessSteel -> AddElement(S, FractionMass = 0.03*perCent);
      StainlessSteel -> AddElement(C, FractionMass = 0.08*perCent);
      StainlessSteel -> AddElement(Si, FractionMass = 1.0*perCent);
      StainlessSteel -> AddElement(P, FractionMass = 0.045*perCent);

    // FR-4
    EGlass = new G4Material("E_Glass", density = 2.54*g/cm3, nel = 5);
      EGlass -> AddMaterial(SiO2, FractionMass = 54.0*perCent);
      EGlass -> AddMaterial(CaO2, FractionMass = 23.0*perCent);
      EGlass -> AddMaterial(Al2O3, FractionMass = 14.0*perCent);
      EGlass -> AddMaterial(B2O3, FractionMass = 8.6*perCent);
      EGlass -> AddMaterial(Fe2O3, FractionMass = 0.4*perCent);

    Resin = new G4Material("Resin", density = 1.19*g/cm3, nel = 4);
      Resin -> AddElement(C, natoms = 38);
      Resin -> AddElement(H, natoms = 50);
      Resin -> AddElement(O, natoms = 8);
      Resin -> AddElement(N, natoms = 2);


    FR_4 = new G4Material("FR_4", density = 1.850*g/cm3, nel = 2);
        FR_4 -> AddMaterial(EGlass, FractionMass = 60.0*perCent);
        FR_4 -> AddMaterial(Resin, FractionMass = 40.0*perCent);

    HolderMat = new G4Material("FR_4", density = 2.099*g/cm3, nel = 2);
      HolderMat -> AddMaterial(FR_4, FractionMass = 88.15*perCent);
      HolderMat -> AddMaterial(Copper, FractionMass = 11.85*perCent);

    R3003 = new G4Material("Rogers 3003", density = 2.1*g/cm3, nel = 3);
      R3003 -> AddMaterial(SiO2, FractionMass = 55.76*perCent);
      R3003 -> AddMaterial(TiO2, FractionMass = 9.84*perCent);
      R3003 -> AddMaterial(PTFE, FractionMass = 34.6*perCent);

    PreAmpMat = new G4Material("FR_4", density = 2.424*g/cm3, nel = 2);
      PreAmpMat -> AddMaterial(R3003, FractionMass = 86.64*perCent);
      PreAmpMat -> AddMaterial(Copper, FractionMass = 13.36*perCent);
    // Polyimide
    Polyimide = new G4Material("Polyimide", density = 1.42*g/cm3, nel = 4);
        Polyimide -> AddElement(C, natoms = 35);
        Polyimide -> AddElement(H, natoms = 26);
        Polyimide -> AddElement(O, natoms = 8);
        Polyimide -> AddElement(N, natoms = 4);

    // Liquid Nitrogen
    LiquidNitrogen = new G4Material("LiquidNitrogen", density = 0.808*g/cm3, nel = 1, kStateLiquid, temperature = 77*kelvin);
      LiquidNitrogen -> AddElement(N, FractionMass = 100*perCent);

    // Print materials
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	return ConstructDetector();
}
G4VPhysicalVolume* DetectorConstruction::ConstructDetector()
{
    //------------------------------------------------
    // Copy Number
    //------------------------------------------------

    CopyWorld = -100;
    CopyChamber = 100;
    CopyFaraday = 4;
    CopyPreAmp = 3;
    CopyWashers = 2;
    CopyMount = 1;
    CopySiLi = 0;
    CopyAlSquare = -1;
    CopyColdPlate = -2;
    CopyCoolingSyst = -3;
    CopyScrews = -4;

	//--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------

    //------------------------------------------------
    // World
    //------------------------------------------------

    WorldLength = 2.5*m;
    worldS = new G4Box("worldS",WorldLength*0.5,WorldLength*0.5,WorldLength*0.5);
    worldL= new G4LogicalVolume(worldS, Vacuum, "World", 0, 0, 0);
    //  Must place the World Physical volume unrotated at (0,0,0).
    worldP = new G4PVPlacement(0, G4ThreeVector(), worldL, "World", 0, false, CopyWorld, true);

    //------------------------------------------------
    // Screws
    //------------------------------------------------

    // create screws
    ConstructScrews();
    // place the screws
    ScrewsP = new G4PVPlacement(0, G4ThreeVector(0, 0, -5.785*mm), ScrewsL, "ScrewsP", worldL, false, CopyScrews);
    WashersP = new G4PVPlacement(0, G4ThreeVector(0, 0, 9.945*mm), WashersL, "WashersP", worldL, false, CopyWashers);

    //------------------------------------------------
    // Al Square
    //------------------------------------------------

    // create Al Square
    ConstructAlSquare();
    // place the square beneath the mount
    AlSquareP = new G4PVPlacement(0, G4ThreeVector(0,0, -5.03*mm), AlSquareL, "AlSquareP", worldL, false, CopyAlSquare);


    //------------------------------------------------
    // Chamber
    //------------------------------------------------

    ConstructChamber();

    rotation = G4RotationMatrix();
  	translation.setX(0); translation.setY(0); translation.setZ(0);
    transform = G4Transform3D(rotation, translation);

    chamber -> MakeImprint(worldL, transform);

    //------------------------------------------------
    // Cold Plate
    //------------------------------------------------

    // create Cold Plate
    ConstructColdPlate();
    rotation = G4RotationMatrix();
    translation.setX(0); translation.setY(0); translation.setZ(-12.285*mm);
  	transform = G4Transform3D(rotation, translation);

    coldPlate -> MakeImprint(worldL, transform);

    //------------------------------------------------
    // Coolant Mount
    //------------------------------------------------
    ConstructCoolingMount();

    translation.setX(0); translation.setY(0); translation.setZ(-21.81*mm);
  	transform = G4Transform3D(rotation, translation);
    coolingMount -> MakeImprint(worldL, transform);

    //------------------------------------------------
    // Faraday Cage
    //------------------------------------------------

    ConstructFaraday();
    faradayCageP = new G4PVPlacement(0, G4ThreeVector(0, 0, 45.925*mm), faradayCageL, "Faraday_Cage_Phys", worldL, false, CopyFaraday);

    //------------------------------------------------
    // Test Mount
    //------------------------------------------------

    // create Mount
    ConstructMount();
    // place the mount above the detector
    mountP = new G4PVPlacement(0, G4ThreeVector(0, 0, 3.35*mm), mountL, "MountPhys", worldL, false, CopyMount);
    mountRingP = new G4PVPlacement(0, G4ThreeVector(0, 0, 2.8*mm), mountRingL, "Mount_Ring_Phys", worldL, false, CopyMount);
    insulatingRingP = new G4PVPlacement(0, G4ThreeVector(0, 0, -2.8*mm), insulatingRingL, "Insulating_Ring_Phys", worldL, false, CopyMount);

    //------------------------------------------------
    // Pre-Amp
    //------------------------------------------------

    // create preAmp
    ConstructPreAmp();
    // place preAmp
    rotation = G4RotationMatrix();
    translation.setX(-45.355); translation.setY(0); translation.setZ(12.65*mm);
  	transform = G4Transform3D(rotation, translation);
    preAmp -> MakeImprint(worldL, transform);

    //------------------------------------------------
    // SiLi
    //------------------------------------------------

    // create Detector and Polyimide solids
    ConstructSiLi();

    translation.setX(0); translation.setY(0); translation.setZ(0);
  	transform = G4Transform3D(rotation, translation);
    SiLi -> MakeImprint(worldL, transform);

    //------------------------------------------------
    // Visualization attributes
    //------------------------------------------------

    TransparentVisAtt = new G4VisAttributes(G4Colour(1.00, 1.00, 1.00, 0.0));
    SiLiVisAtt = new G4VisAttributes(G4Colour(1.0, 0.75, 0.0, 1.0));
    FR4VisAtt = new G4VisAttributes(G4Colour(0.20, 0.38, 0.33, 0.8));
    R3003VisAtt = new G4VisAttributes(G4Colour(0.8, 0.8, 0.8, 1.0));
    CuVisAtt = new G4VisAttributes(G4Colour(0.58, 0.27, 0.13, 1.0));
    ChamberVisAtt = new G4VisAttributes(G4Colour(0.50, 0.50, 0.50, 0.25));
    PIVisAtt = new G4VisAttributes(G4Colour(0.65, 0.54, 0.20, 0.75));
    N2VisAtt = new G4VisAttributes(G4Colour(0.29, 0.64, 0.97, 0.5));
    NiVisAtt = new G4VisAttributes(G4Colour(1.00, 1.00, 1.00, 1.0));
    SteelVisAtt = new G4VisAttributes(G4Colour(0.50, 0.50, 0.50, 1.0));
    FaradayVisAtt = new G4VisAttributes(G4Colour(0.75, 0.75, 0.75, 0.5));
    AlVisAtt = new G4VisAttributes(G4Colour(0.75, 0.75, 0.75, 1.0));

    worldL -> SetVisAttributes(TransparentVisAtt);
    ScrewsL -> SetVisAttributes(SteelVisAtt);
    WashersL -> SetVisAttributes(SteelVisAtt);
    AlSquareL -> SetVisAttributes(AlVisAtt);
    chamberL -> SetVisAttributes(ChamberVisAtt);
    lidL -> SetVisAttributes(ChamberVisAtt);
    niPlateL -> SetVisAttributes(NiVisAtt);
    cuPlateL -> SetVisAttributes(CuVisAtt);
    coolantMountL -> SetVisAttributes(AlVisAtt);
    coolingPipeL -> SetVisAttributes(SteelVisAtt);
    coolantLiquidL -> SetVisAttributes(N2VisAtt);
    faradayCageL -> SetVisAttributes(FaradayVisAtt);
    mountL -> SetVisAttributes(AlVisAtt);
    detectorL -> SetVisAttributes(SiLiVisAtt);
    piGroovesL -> SetVisAttributes(PIVisAtt);
    holderL -> SetVisAttributes(FR4VisAtt);
    preAmpL -> SetVisAttributes(R3003VisAtt);
    copperL -> SetVisAttributes(CuVisAtt);

	return worldP;
}

void DetectorConstruction::ConstructSDandField()
{
  DetectorManager = G4SDManager::GetSDMpointer();
  SDetector = DetectorManager -> FindSensitiveDetector("SensitiveSiLi", false);

  SDetector = new DetectorSD("SensitiveSiLi");
  DetectorManager -> AddNewDetector(SDetector);
  SetSensitiveDetector(detectorL, SDetector);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
