class SiLi: public KDetector
{

  public:

    SiLi();
   ~SiLi();
    void ConstructSiLi();

    void SetVoltage(Float_t v){ voltage = v };
    void SetNeff(Float_t n){ neff = n };
    void SetNX(int n){ nx = n };
    void SetNY(int n){ ny = n };
    void SetNZ(int n){ nz = n };

  private:

    Float_t voltage; // voltage applied to detector bottom
    Float_t neff; // effective charge density [10^12 cm^-3]

    // geometry parameters
    Float_t grooveWidth, grooveDepth, electrodeWidth, electrodeDepth,
           gaurdRingWidth, edgeWidth;

    // simulation grid parameters
    int nx, ny, nz; // number of nodes
    int silicon = 0;
    int air = 20;
    int aluminium = ;100

}
