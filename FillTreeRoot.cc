#include <iostream>

void FillTreeRoot(const char* inputfilename = "inputfile.dat"){

  std::ifstream fin;
  fin.open(inputfilename);
  if(!fin.good()){
    std::cerr << "ERROR: Cannot open " << inputfilename << std::endl;
    return;
  }

  struct Event{
    Double_t time;
    Double_t pha;
    Double_t pha_err;
    Double_t model;
    Double_t residual;
    Double_t residual_err;
    Double_t tsaa;
    Double_t temp;
  };

  Event eve;
  TFile * outputTfile = new TFile ("outputTfile.root","RECREATE");
  TTree * tree = new TTree ("EventTree","Event data from ascii file");
  tree->Branch("Event",&eve.time,"time/D:pha/D:pha_err/D:model/D:residual/D:residual_err/D:tsaa/D:temp/D");

  while( ! fin.eof() )
    {
      fin >> eve.time >> eve.pha >> eve.pha_err >> eve.model >> eve.residual >> eve.residual_err >> eve.tsaa >> eve.temp;
      cout << eve.time << " "<< eve.pha << " "<< eve.pha_err << " "<< eve.model << " "<< eve.residual << " "<< eve.residual_err << " "<< eve.tsaa <<  " "<< eve.temp << endl;
      tree->Fill();
  }

  fin.close();
  tree->Print();
  outputTfile->Write();

}
