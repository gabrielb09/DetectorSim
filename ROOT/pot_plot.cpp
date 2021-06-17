int pot_plot(){
  gStyle -> SetOptStat(0);

  TFile *inFile = (new TFile("SiLi3D.root"));

  TH2F *Efield = (TH2F*)inFile -> Get("E_Field_2D");
  TH2F *Potential = (TH2F*)inFile -> Get("Potential_2D");

  TCanvas *c1 = new TCanvas("c1", "c1", 2000, 1000);
  c1 -> Divide(1,2);

  c1 -> cd(1);
  Potential -> Draw("COLZ");
  c1 -> cd(2);
  Efield -> Draw("COLZ");

  return 0;
}
