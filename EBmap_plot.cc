// This macro is to plot the EB field map along x,y,z axis from OPERA //
// This is made on 22, July, 2018. by H. Yasuda //

#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <math.h>
// gSystem.Load("libPhysics.so");
using namespace std;

// SETTING PARAMETER //
const double NB =  12.8057;
const double NE =  200521;

const double B0y = -0.177722; // [Tesla]
const double E0x = -4.2638E+6; // [V/m]

const int ng = 9;

void EBmap_plot(){

    cout << "%%%%% START %%%%%" << endl;

    gROOT->SetStyle("Plain");
    gROOT->Reset();


    /////////// READING MAP FILE //////////

    stringstream Efilename;
    stringstream Bfilename;
    Efilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180621_ver5_3DEOpera.dat");  // Input file name of OPERA data Bfield
    Bfilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180621_ver5_3DBOpera.dat");  // Input file name of OPERA data Efield
    ifstream Eifs(Efilename.str().c_str(), std::ios::in);
    ifstream Bifs(Bfilename.str().c_str(), std::ios::in);

    TCanvas * cB = new TCanvas("cB","B-field map",1400,800);
    TCanvas * cE = new TCanvas("cE","E-field map",1400,800);
    TGraph * gB[ng];
    TGraph * gE[ng];

    for(int i = 0 ; i < ng ; i++ ){
        // gB[i] = new TGraph(Form("gB%d", i),Form("gB%d", i),-100,100);
        // gE[i] = new TGraph(Form("gE%d", i),Form("gE%d", i),-100,100);
        gB[i] = new TGraph();
        gE[i] = new TGraph();
    }


    double xi,yi,zi,Fxi,Fyi,Fzi;
    double lineno = 0;

    while(Bifs >> xi >> yi >> zi >> Fxi >> Fyi >> Fzi){
        gB[0]->SetPoint(lineno, xi, Fxi * NB);
        gB[1]->SetPoint(lineno, xi, Fyi * NB );
        gB[2]->SetPoint(lineno, xi, Fzi * NB );
        gB[3]->SetPoint(lineno, yi, Fxi * NB );
        gB[4]->SetPoint(lineno, yi, Fyi * NB );
        gB[5]->SetPoint(lineno, yi, Fzi * NB );
        gB[6]->SetPoint(lineno, zi, Fxi * NB );
        gB[7]->SetPoint(lineno, zi, Fyi * NB );
        gB[8]->SetPoint(lineno, zi, Fzi * NB );
        lineno++;
    }
    cout << "lineno = " << lineno << endl;
    lineno = 0;

    while(Eifs >> xi >> yi >> zi >> Fxi >> Fyi >> Fzi){
        gE[0]->SetPoint(lineno, xi, Fxi * NE );
        gE[1]->SetPoint(lineno, xi, Fyi * NE );
        gE[2]->SetPoint(lineno, xi, Fzi * NE );
        gE[3]->SetPoint(lineno, yi, Fxi * NE );
        gE[4]->SetPoint(lineno, yi, Fyi * NE );
        gE[5]->SetPoint(lineno, yi, Fzi * NE );
        gE[6]->SetPoint(lineno, zi, Fxi * NE );
        gE[7]->SetPoint(lineno, zi, Fyi * NE );
        gE[8]->SetPoint(lineno, zi, Fzi * NE );
        lineno++;
    }
    cout << "lineno = " << lineno << endl;
    lineno = 0;

    cB->Divide(3,3);
    cE->Divide(3,3);

    for(int i = 1 ; i <= ng ; i++){
        cB->cd(i);
        gB[i]->Draw();
        cE->cd(i);
        gE[i]->Draw();
    }

}
