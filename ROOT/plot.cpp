#include <string>
#include <iostream>

int plot(const char filename[20]){

	gROOT -> Reset();

	int event;

	TFile *inFile;
	TTree *tree;
	TH1D  *spectrum;

	// spectrum
  spectrum = new TH1D();
  spectrum -> SetName("spectrum");
  spectrum -> SetTitle("Total Energy Deposit");
  spectrum -> SetBins(500, 20.0, 70.0);
  // assign titles to the histogram axes
	spectrum -> GetXaxis() -> SetTitle("Energy [keV]");
	spectrum -> GetYaxis() -> SetTitle("Counts");

	// output file name + path, returns "../output/filename_plot.root"
	// filename comes from input to program
	const char* dir = "../output/";
	char outputFile[100];
	sprintf(outputFile, "%s%s%s", dir, filename, "_spec.root");

	char inputFile[100];
	sprintf(inputFile, "%s%s%s", dir, filename, ".root");

	// open data file
  inFile = (new TFile(inputFile));
  // extract the tree
  tree = (TTree*) inFile -> Get("DetectorSimData");
  tree -> Print();

	// variables for Dataint eventID, trackID, particleID, nextVolNum, lastEventID;
	int eventID, trackID, currentEvent;
	double edep, total_edep;
  double x, y, z;
	double vert_x, vert_y, vert_z;

	tree -> SetBranchAddress("eventID", &eventID);
	tree -> SetBranchAddress("trackID", &trackID);
  tree -> SetBranchAddress("eDep", &edep);
  tree -> SetBranchAddress("x", &x);
  tree -> SetBranchAddress("y", &y);
  tree -> SetBranchAddress("z", &z);
	tree -> SetBranchAddress("vertex_x", &vert_x);
	tree -> SetBranchAddress("vertex_y", &vert_y);
	tree -> SetBranchAddress("vertex_z", &vert_z);

	int length = tree -> GetEntries(); // get total number of entries

	tree -> GetEntry(0);
	currentEvent = eventID;
	total_edep = 0.0;

	int total_events = 0.0;

	for(int i = 0; i < length; i++){
    tree -> GetEntry(i);

		if (eventID == currentEvent){
			total_edep += edep;
		}

		else{

			if ((-1.15 <= vert_z <= 1.15) || (vert_z == 102.0)){
				spectrum -> Fill(total_edep + gRandom -> Gaus(0., 3.0/2.35));
			}

			total_edep = 0.0;
			currentEvent = eventID;
			total_edep += edep;

			total_events += 1;
		}
  }

	if ((-1.15 <= vert_z <= 1.15) || (vert_z == 102.0)){
		spectrum -> Fill(total_edep + gRandom -> Gaus(0., 3.0/2.35));
	}

	cout << "total number of events: " << total_events << endl;

TFile *outFile = new TFile(outputFile, "RECREATE");
spectrum -> Write("spectrum");
delete outFile;


return 0;
}
