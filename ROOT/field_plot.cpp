int field_plot(const int i){
  gStyle -> SetOptStat(0);

  TFile *inFile = (new TFile("SiLi3D.root"));
  char title[100];

  sprintf(title, "%s%i", "E_Field_", i);
  TH2F *field = (TH2F*)inFile -> Get(title);
  sprintf(title, "%s%i", "Mats_", i);
  TH2F *material = (TH2F*)inFile -> Get(title);

  TCanvas *c1 = new TCanvas("c1", "c1", 2000, 1000);
  c1 -> Divide(2,1);

  c1 -> cd(1);
  material -> Draw("COLZ");
  c1 -> cd(2);
  field -> Draw("COLZ");

  return 0;
}
