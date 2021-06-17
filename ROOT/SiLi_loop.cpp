{
  // Physical Detector Parameters
  double radius = 48.5e3; // um
  double thickness = 2.5e3; // um
  Float_t voltage = -100.0; // volts
  const int n_itter = 3;
  double neffs[n_itter] = {1.5e-2, 1.2e-2, 1e-2}; // 10^12 cm^-3

  // Simulation Parameters

  // number of grid points
  int nx = 2000;
  int ny = 2000;
  int nz = 100;
  // grid spacing
  double dx = 2*radius/nx; // um
  double dy = 2*radius/ny; // um
  double dz = thickness/nz; // um
  // expand grid to include a layer of air around detector
  double air_width = 1e2; // um = 1mm
  double width = 2*(radius + air_width);
  double height = thickness + 2*air_width;
  nx += (int)(air_width*2/dx);
  ny += (int)(air_width*2/dy);
  nz += (int)(air_width*2/dz);

  // name material numbers
  const int silicon = 0;
  const int air = 20;
  const int aluminium = 1;
  // name electrode mode numbers
  const int bias = 2;
  const int read_out = 16384;
  const int ground = 1;

  // create detector
  KDetector SiLi;
  // set calculation parameters
  double precision = 1e-5;
  int max_iter = (int)1e8;
  SiLi.SetCalculationParameters(precision,  max_iter);
  // Set temperature
  SiLi.Temperature = 236; // kelvin

  cout << "Initializing Geometry/Material/Neff Arrays" << endl;
  // geometry hist
  SiLi.EG = new TH3I("EG", "EG", nx, -1*width/2, width/2, ny, -1*width/2, width/2, nz, -1*height/2, height/2);
  SiLi.EG -> GetXaxis() -> SetTitle("x [#mum]");
  SiLi.EG -> GetYaxis() -> SetTitle("y [#mum]");
  SiLi.EG -> GetZaxis() -> SetTitle("z [#mum]");
  SiLi.EG -> SetStats(0);

  // material hist
  SiLi.DM = new TH3I("DM", "DM", nx, -1*width/2, width/2, ny, -1*width/2, width/2, nz, -1*height/2, height/2);
  SiLi.DM -> GetXaxis() -> SetTitle("x [#mum]");
  SiLi.DM -> GetYaxis() -> SetTitle("y [#mum]");
  SiLi.DM -> GetZaxis() -> SetTitle("z [#mum]");
  SiLi.DM -> SetStats(0);

  // neff hist
  // NOTE: The Neff hist will be set such that a uniform charge concentration
  // is distributed throughout the entire SiLi volume. KDetSim can not handle
  // varible free carrier concentrations so it is best to select an neff s.t., at -100V
  // the entire detector is depleted (this can be established by inspecting the E-Field)
  SiLi.NeffH = new TH3F("NeffH", "NeffH", nx, -1*width/2, width/2, ny, -1*width/2, width/2, nz, -1*height/2, height/2);
  SiLi.NeffH -> GetXaxis() -> SetTitle("x [#mum]");
  SiLi.NeffH -> GetYaxis() -> SetTitle("y [#mum]");
  SiLi.NeffH -> GetZaxis() -> SetTitle("z [#mum]");
  SiLi.NeffH -> SetStats(0);

  TFile *outFile = new TFile("SiLi3D.root", "RECREATE");
  char title[100];
  TH1 *E_Field;
  TH1 *Material;
  TH1 *Potential;

  // build from botom up
  double x, y, z;
  // positions of grooves
  double grooves[7] = {-2.89e4, -1.84e4, -0.9e4, 0.0e4, 0.9e4, 1.84e4, 2.89e4};
  cout << "Filling Detector Arrays" << endl;
  // note: material is silicon by default hence no code to set material to silicon
  for(int k = 0; k <= nz; k++){
    z = SiLi.DM -> GetZaxis() -> GetBinCenter(k); // um
    for(int j = 0; j <= ny; j++){
      y = SiLi.DM -> GetYaxis() -> GetBinCenter(j); // um
      for(int i = 0; i <= nx; i++){
        x = SiLi.DM -> GetXaxis() -> GetBinCenter(i); // um
        // check if inside SiLi
        if ((x*x + y*y <= radius*radius) && (z >= -1.25e3) && (z <= 1.25e3)){
          // bottom electrode
          if (z <= (-1.25e3 + 50)){
            SiLi.DM -> SetBinContent(i, j, k, aluminium);
            SiLi.EG -> SetBinContent(i, j, k, bias);
          }
          // top electrode and grooves
          else if (z >= (1.25e3 - 300)){
            // inside gaurd ring
            if (x*x + y*y <= 2.116e9){
              // inside groove
              if ((x*x + y*y >= 2.025e9) || // gaurd Ring groove
                  ((y <= grooves[0] + 0.5e3) && (y >= grooves[0] - 0.5e3)) || // strip grooves
                  ((y <= grooves[1] + 0.5e3) && (y >= grooves[1] - 0.5e3)) ||
                  ((y <= grooves[2] + 0.5e3) && (y >= grooves[2] - 0.5e3)) ||
                  ((y <= grooves[3] + 0.5e3) && (y >= grooves[3] - 0.5e3)) ||
                  ((y <= grooves[4] + 0.5e3) && (y >= grooves[4] - 0.5e3)) ||
                  ((y <= grooves[5] + 0.5e3) && (y >= grooves[5] - 0.5e3)) ||
                  ((y <= grooves[6] + 0.5e3) && (y >= grooves[6] - 0.5e3))) {
                SiLi.DM -> SetBinContent(i, j, k, air);
              }
              // outside groove
              else{
                // Strip Electrode
                if (z >= (1.25e3 - 50)){
                  SiLi.DM -> SetBinContent(i, j, k, aluminium);
                  SiLi.EG -> SetBinContent(i, j, k, read_out + ground);
                }
                // Silicon
              }
            }
            // outside gaurd ring
            else{
              // GR electrode
              if (z >= (1.25e3 - 50)){
                SiLi.DM -> SetBinContent(i, j, k, aluminium);
                SiLi.EG -> SetBinContent(i, j, k, ground);
              }
              // Silicon
            }
          }
        }
        // outside SiLi
        else{
          SiLi.DM -> SetBinContent(i, j, k, air);
        }
      }
    }
  }

  for(int l = 0; l < n_itter; l++){

    for(int k = 0; k <= nz; k++){
      z = SiLi.DM -> GetZaxis() -> GetBinCenter(k); // um
      for(int j = 0; j <= ny; j++){
        y = SiLi.DM -> GetYaxis() -> GetBinCenter(j); // um
        for(int i = 0; i <= nx; i++){
          x = SiLi.DM -> GetXaxis() -> GetBinCenter(i);; // um
          // make sure i am in the SiLi detector
          if ((x*x + y*y <= radius*radius) && (z >= -1.25e3) && (z <= 1.25e3)){
            // silicon above electrode and bellow grooves
            if ((z >= 50 - 1.25e3) && (z < 1.25e3 - 300)){
              SiLi.NeffH -> SetBinContent(i, j, k, neffs[l]);
            }
            // in range of grooves but below top electrode
            else if ((z >= 1.25e3 - 300) && (z < 1.25e3 - 50)){
              // inside gaurd ring
              if (x*x + y*y <= 2.116e9){
              // strip grooves
              if (!((x*x + y*y >= 2.025e9) || // gaurd Ring groove
                  ((y <= grooves[0] + 0.5e3) && (y >= grooves[0] - 0.5e3)) || // strip grooves
                  ((y <= grooves[1] + 0.5e3) && (y >= grooves[1] - 0.5e3)) ||
                  ((y <= grooves[2] + 0.5e3) && (y >= grooves[2] - 0.5e3)) ||
                  ((y <= grooves[3] + 0.5e3) && (y >= grooves[3] - 0.5e3)) ||
                  ((y <= grooves[4] + 0.5e3) && (y >= grooves[4] - 0.5e3)) ||
                  ((y <= grooves[5] + 0.5e3) && (y >= grooves[5] - 0.5e3)) ||
                  ((y <= grooves[6] + 0.5e3) && (y >= grooves[6] - 0.5e3)))) {
                  SiLi.NeffH -> SetBinContent(i, j, k, neffs[l]);
                }
              }
              // outside gaurd ring
              else if (z < 1.25e3 - 50){
                SiLi.NeffH -> SetBinContent(i, j, k, neffs[l]);
              }
            }
          }
        }
      }
    }

    cout << "Detector Complete" << endl;

    // set simulation to diffusion mode
    SiLi.diff = 1;

    cout << "Configuring Simulation" << endl;

    cout << "Initializing Boundary Conditions" << endl;
    // set up boundary conditions
    SiLi.SetBoundaryConditions();

    cout << "Setting HV" << endl;
    // set up voltage
    Int_t calnow;
    SiLi.SetVoltage(voltage, calnow = 0);

    // callibrate real field
    cout << "Callibrating Real E-Field" << endl;
    SiLi.CalPhyField();
    cout << "E-Field Callibration Complete" << endl;

    // callibrate ramo field
    cout << "Callibrating Ramo Field" << endl;
    SiLi.CalRamoField();
    cout << "Ramo-Field Callibration Complete" << endl;

    SiLi.Real -> E -> GetZaxis() -> SetRange(0, 0);
    SiLi.Real -> E -> GetXaxis() -> SetRange(nx/2, nx/2);
    E_Field = SiLi.Real -> E -> Project3D("zyo");
    E_Field -> SetTitle("Electric Field (V/um)");
    sprintf(title, "%s%i", "E_Field_", l);
    E_Field -> Write(title);

    SiLi.Real -> U -> GetZaxis() -> SetRange(0, 0);
    SiLi.Real -> U -> GetXaxis() -> SetRange(nx/2, nx/2);
    Potential = SiLi.Real -> U -> Project3D("zyo");
    Potential -> SetTitle("Potential (V)");
    sprintf(title, "%s%i", "Potential_", l);
    Potential -> Write(title);

    SiLi.NeffH -> GetZaxis() -> SetRange(0, 0);
    SiLi.NeffH -> GetXaxis() -> SetRange(nx/2, nx/2);
    Material = SiLi.NeffH -> Project3D("zyo");
    Material -> SetTitle("Neff");
    sprintf(title, "%s%i", "Neff_", l);
    Material -> Write(title);
  }
  delete outFile;
}
