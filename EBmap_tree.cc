// This macro is to plot the EB field map along x,y,z axis from OPERA //
// This is made on 22, July, 2018. by H. Yasuda //

#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <math.h>
#include "TTree.h"
#include "TFile.h"
using namespace std;


void EBmap_tree(){

    // TFile * file = new TFile("map/map_test.root","recreate");
    TFile * file = new TFile("map/Wien_180621_ver5_3DOpera.root","recreate");
    TTree * tree = new TTree("tree", "tree");

    double x, y, z, Ex, Ey, Ez, Bx, By, Bz;
    tree->Branch("x", &x);
    tree->Branch("y", &y);
    tree->Branch("z", &z);
    tree->Branch("Ex", &Ex);
    tree->Branch("Ey", &Ey);
    tree->Branch("Ez", &Ez);
    tree->Branch("Bx", &Bx);
    tree->Branch("By", &By);
    tree->Branch("Bz", &Bz);

    /////////// READING MAP FILE //////////

    stringstream Efilename;
    stringstream Bfilename;
    Efilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180621_ver5_3DEOpera.dat");  // Input file name of OPERA data Bfield
    Bfilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180621_ver5_3DBOpera.dat");  // Input file name of OPERA data Efield
    ifstream Eifs(Efilename.str().c_str(), std::ios::in);
    ifstream Bifs(Bfilename.str().c_str(), std::ios::in);

    int lineno = 0;
    while(Eifs >> x >> y >> z >> Ex >> Ey >> Ez && Bifs >> x >> y >> z >> Bx >> By >> Bz){
        if(lineno < 20) cout << x << "\t" << x << "\t" << y << "\t" << z << "\t" << Ex << "\t" << Ey << "\t"  << Ez << "\t"  << Bx << "\t" << By << "\t" << Bz << endl;
        tree->Fill();
        lineno++;
    }

    tree->Write();
    file->Close();

}
