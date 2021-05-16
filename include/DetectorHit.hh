#ifndef DetectorHit_h
#define DetectorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4String.hh"
#include "G4VProcess.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorHit : public G4VHit
{
  public:

    DetectorHit();
    ~DetectorHit();
    DetectorHit(const DetectorHit&);
    const DetectorHit& operator=(const DetectorHit&);
    G4int operator==(const DetectorHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    void Draw();
    void Print();

    void fPrint();

  public:
    void SetEventID(G4int id){ eventID_ = id; };
    void SetTrackID(G4int id){ trackID_ = id; };
    void SetEdep(G4double edep){ edep_ = edep; };
    void SetEnergy(G4double energy){ kEnergy_ = energy; };
    void SetTime(G4double time){ time_ = time; };
    void SetPos(G4ThreeVector xyz){ pos_ = xyz; };
    void SetVertex(G4ThreeVector vertex_xyz){ vertexPos_ = vertex_xyz; };

  private:

    G4int eventID_, trackID_;

    G4double kEnergy_, edep_, time_;

    G4ThreeVector pos_, vertexPos_;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<DetectorHit> DetectorHitsCollection;

extern G4Allocator<DetectorHit> DetectorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* DetectorHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) DetectorHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void DetectorHit::operator delete(void *aHit)
{
  DetectorHitAllocator.FreeSingle((DetectorHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
