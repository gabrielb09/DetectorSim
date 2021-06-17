{
  // reset ROOT and load KDetSim
  gROOT -> Reset();
  gSystem -> Load("~/KDetSimDist/lib/KDetSim.sl");

  int numElectrodes;
  double length, width, height, radius, x, y, z, weight;
  int material;

  int silicon = 0;
  int air = 20;
  int aluminium = 100;

  K3D *SiLi = new K3D(numElectrodes = 9, length = 2*50.5e3, width = 2*50.5e3, height = 2.5e3);
  SiLi -> SetUpVolume(25, 50);

  // basic detector + gaurd ring
  Float_t pos[3] = {0,0,0};

  pos[0] = 50.5e3/2; pos[1] = 50.5e3/2;
  SiLi -> ElCylinder(pos, radius = 48.5e3, length = 2.5e3, 0, weight = 0, material = silicon);
  pos[0] = 50.5e3/2; pos[1] = 50.5e3/2; pos[2] = 2.2e3;
  SiLi -> ElCylinder(pos, radius = 46e3, length = 0.3e3, 0, weight = 0, material = air);
  SiLi -> ElCylinder(pos, radius = 45e3, length = 0.3e3, 0, weight = 0, material = silicon);

  // strip grooves
  Float_t grooves_x[7] = {15.774e3, 9.111e3, 6.002e3, 5.002e3, 6.002e3, 9.111e3, 15.774e3};
  Float_t grooves_y[7] = {21.6e3, 32.1e3, 41.5e3, 50.5e3, 59.5e3, 68.9e3, 79.4e3};
  Float_t grooves_width[7] = {70.286e3, 83.227e3, 89.202e3, 91.e3, 89.202e3, 83.227e3, 70.286e3};
  Float_t Pos[3] = {0, 0, 2.2e3};
  Float_t Size[3] = {0, 1e3, 0.3e3};

  for(int i = 0; i < 7; i++){
    Pos[0] = grooves_x[i];
    Pos[1] = grooves_y[i] - 0.5e3;

    Size[0] = grooves_width[i];

    SiLi -> ElRectangle(Pos, Size, 0, air);
  }

  SiLi -> SetUpElectrodes();
  SiLi -> SetBoundaryConditions();
}
