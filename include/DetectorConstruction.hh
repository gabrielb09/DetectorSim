#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "DetectorSD.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Torus.hh"
#include "G4Sphere.hh"
#include "G4Ellipsoid.hh"
#include "G4Trd.hh"
#include "G4GenericTrap.hh"
#include "G4Polyhedra.hh"

#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4AssemblyVolume.hh"
#include "G4MultiUnion.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"

#include "G4SystemOfUnits.hh"

#include <vector>

class G4Box;
class G4Tubs;
class G4Cons;
class G4Sphere;
class G4Ellipsoid;
class G4Trd;
class G4Torus;
class G4GenericTrap;
class G4Polyhedra;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4VSolid;
class G4UnionSolid;
class G4SubtractionSolid;
class G4IntersectionSolid;
class G4Material;
class DetectorMessenger;
class G4AssemblyVolume;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

	DetectorConstruction();
  ~DetectorConstruction();

	void DefineMaterials();
	void UpdateGeometry();
  void ConstructSDandField();

	G4VPhysicalVolume* Construct();

	G4double GetWorldFullLength(){
    return WorldLength;
  };

  private:

	G4VPhysicalVolume* ConstructDetector();

  void ConstructScrews();
  void ConstructAlSquare();
  void ConstructChamber();
  void ConstructColdPlate();
  void ConstructCoolingMount();
  void ConstructFaraday();
  void ConstructMount();
  void ConstructPreAmp();
  void ConstructSiLi();

  // basic materials
  // elements
  G4Material* Air;
  G4Element* H;
  G4Element* B;
  G4Element* C;
  G4Element* N;
  G4Element* O;
  G4Element* F;
  G4Element* Al;
  G4Element* Si;
  G4Element* P;
  G4Element* S;
  G4Element* Ca;
  G4Element* Ti;
  G4Element* Cr;
  G4Element* Mn;
  G4Element* Fe;
  G4Element* Ni;

  G4int natoms;
  G4double density, temperature, pressure, FractionMass;
  G4int nel;

  // molecules
  G4Material* SiO2;
  G4Material* Al2O3;
  G4Material* TiO2;
  G4Material* CaO2;
  G4Material* B2O3;
  G4Material* Fe2O3;
  G4Material* PTFE;

  // constructed materials
  G4Material* Vacuum;
  G4Material* StainlessSteel;
  G4Material* EGlass;
  G4Material* Resin;
  G4Material* FR_4;
  G4Material* R3003;
  G4Material* HolderMat;
  G4Material* PreAmpMat;
  G4Material* Polyimide;
  G4Material* LiquidNitrogen;
  G4Material* Aluminium;
  G4Material* Iron;
  G4Material* Copper;
  G4Material* Nickle;
  G4Material* Silicon;

  G4double length, width, height, thickness, radius, inner_radius, outer_radius;

  // transformations
  G4RotationMatrix rotation;
  G4ThreeVector translation;
  G4Transform3D transform;

  // world geometry
  G4Box*              worldS;
  G4LogicalVolume*    worldL;
  G4VPhysicalVolume*  worldP;

  // screws geometry
  G4MultiUnion*       ScrewsS;
  G4LogicalVolume*    ScrewsL;
  G4VPhysicalVolume*  ScrewsP;

  // washers geometry
  G4MultiUnion*       WashersS;
  G4LogicalVolume*    WashersL;
  G4VPhysicalVolume*  WashersP;

  // Aluminium square geometry
  G4VSolid*           AlSquareS;
  G4LogicalVolume*    AlSquareL;
  G4VPhysicalVolume*  AlSquareP;

  // test chamber geometry
  G4AssemblyVolume* chamber;

  G4VSolid*           chamberS;
  G4LogicalVolume*    chamberL;

  G4VSolid*           lidS;
  G4LogicalVolume*    lidL;

  // Nickle/Copper cooling plate geometry
  G4AssemblyVolume* coldPlate;

  G4VSolid*           niPlateS;
  G4LogicalVolume*    niPlateL;

  G4VSolid*           cuPlateS;
  G4LogicalVolume*    cuPlateL;

  // coolant system geometry
  G4AssemblyVolume*   coolingMount;

  G4VSolid*           coolantMountS;
  G4LogicalVolume*    coolantMountL;

  G4MultiUnion*       coolingPipeS;
  G4LogicalVolume*    coolingPipeL;

  G4MultiUnion*       coolantLiquidS;
  G4LogicalVolume*    coolantLiquidL;

  // faraday cage geometry
  G4VSolid*           faradayCageS;
  G4LogicalVolume*    faradayCageL;
  G4VPhysicalVolume*  faradayCageP;

  // mount geometry
  G4VSolid*           mountS;
  G4LogicalVolume*    mountL;
  G4VPhysicalVolume*  mountP;

  G4VSolid*           mountRingS;
  G4LogicalVolume*    mountRingL;
  G4VPhysicalVolume*  mountRingP;

  G4LogicalVolume*    insulatingRingL;
  G4VPhysicalVolume*  insulatingRingP;

  // detector geometry
  G4VSolid*           detectorS;
  G4LogicalVolume*    detectorL;

  G4VSolid*           piGroovesS;
  G4LogicalVolume*    piGroovesL;

  G4AssemblyVolume*   SiLi;

  // pre-amp geometry
  G4VSolid*           holderS;
  G4LogicalVolume*    holderL;

  G4VSolid*           preAmpS;
  G4LogicalVolume*    preAmpL;

  G4LogicalVolume*    copperL;

  G4AssemblyVolume*   preAmp;

	DetectorMessenger* detectorMessenger;        // pointer to the Messenger


    G4double WorldLength;                           // Full length of the world volume
    G4int overlap;

    // G4int overlap;
    G4int CopyWorld;
    G4int CopyScrews;
    G4int CopyWashers;
    G4int CopyChamber;
    G4int CopyFaraday;
    G4int CopyPreAmp;
    G4int CopyMount;
    G4int CopySiLi;
    G4int CopyAlSquare;
    G4int CopyColdPlate;
    G4int CopyCoolingSyst;

    G4VisAttributes* TransparentVisAtt;
    G4VisAttributes* SiLiVisAtt;
    G4VisAttributes* FR4VisAtt;
    G4VisAttributes* R3003VisAtt;
    G4VisAttributes* CuVisAtt;
    G4VisAttributes* ChamberVisAtt;
    G4VisAttributes* PIVisAtt;
    G4VisAttributes* N2VisAtt;
    G4VisAttributes* NiVisAtt;
    G4VisAttributes* SteelVisAtt;
    G4VisAttributes* FaradayVisAtt;
    G4VisAttributes* AlVisAtt;

    //detectors
    G4SDManager* DetectorManager;
    G4VSensitiveDetector* SDetector;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
