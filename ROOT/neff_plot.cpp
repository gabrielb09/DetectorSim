int neff_plot(){
  gStyle -> SetOptStat(0);

  TFile *inFile = new TFile("SiLi3D.root");
  int len = inFile -> GetListOfKeys() -> LastIndex() + 1;
  len /= 3;
  TH2F *Potential;
  TH2F *E_Field;
  char title[100];

  TCanvas *c1 = new TCanvas("c1", "c1", 3000, 2000);
  c1 -> Divide(len,2);

  for (int i = 0; i < len; i++){
    c1 -> cd(i + 1);
    sprintf(title, "%s%i", "Potential_", i);
    Potential = (TH2F*)inFile -> Get(title);
    Potential -> SetMinimum(-100.0);
    Potential -> SetMaximum(0.0);
    Potential -> GetXaxis() -> SetRangeUser(-48.5e3, 48.5e3);
    Potential -> GetYaxis() -> SetRangeUser(-1.25e3, 1.25e3);
    Potential -> Draw("COLZ");

    c1 -> cd(i + len + 1);
    sprintf(title, "%s%i", "E_Field_", i);
    E_Field = (TH2F*)inFile -> Get(title);
    E_Field -> GetXaxis() -> SetRangeUser(-48.5e3, 48.5e3);
    E_Field -> GetYaxis() -> SetRangeUser(-1.25e3, 1.25e3);
    E_Field -> SetMaximum(0.13);
    E_Field -> Draw("COLZ");
  }

  return 0;
}
