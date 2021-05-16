#include "DetectorHit.hh"
#include "g4root.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"

G4Allocator<DetectorHit> DetectorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorHit::DetectorHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorHit::~DetectorHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorHit::DetectorHit(const DetectorHit& right):
	G4VHit()
{
	eventID_		= right.eventID_;
	trackID_   	= right.trackID_;
	time_				= right.time_;
	kEnergy_		= right.kEnergy_;
	vertexPos_	= right.vertexPos_;
  edep_				= right.edep_;
  pos_				= right.pos_;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const DetectorHit& DetectorHit::operator=(const DetectorHit& right)
{
	eventID_		= right.eventID_;
	trackID_   	= right.trackID_;
	time_				= right.time_;
	kEnergy_		= right.kEnergy_;
	vertexPos_	= right.vertexPos_;
  edep_				= right.edep_;
  pos_				= right.pos_;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int DetectorHit::operator==(const DetectorHit& right) const
{
  return (this==&right) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(pos_);
    circle.SetScreenSize(2.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorHit::fPrint()
{
	auto analysisManager = G4AnalysisManager::Instance();

	analysisManager -> FillNtupleIColumn(0, int(eventID_));
	analysisManager -> FillNtupleIColumn(1, int(trackID_));

	analysisManager -> FillNtupleDColumn(2, double(kEnergy_/keV));
	analysisManager -> FillNtupleDColumn(3, double(edep_/keV));

	analysisManager -> FillNtupleDColumn(4, double(time_/s));
	analysisManager -> FillNtupleDColumn(5, double(pos_.getX()/mm));
	analysisManager -> FillNtupleDColumn(6, double(pos_.getY()/mm));
	analysisManager -> FillNtupleDColumn(7, double(pos_.getZ()/mm));

	analysisManager -> FillNtupleDColumn(8, double(vertexPos_.getX()/mm));
	analysisManager -> FillNtupleDColumn(9, double(vertexPos_.getY()/mm));
	analysisManager -> FillNtupleDColumn(10, double(vertexPos_.getZ()/mm));

  analysisManager -> AddNtupleRow();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorHit::Print(){};
