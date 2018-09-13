// This macro is to plot the map excluded from OPERA //
// This is made on 13, June, 2018.  by H. Yasuda //

#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <math.h>
#include "TMath.h"
using namespace std;

// SETTING PARAMETER //
const int linecut = 8;  // cutting lineno
const double NE = 181911; // Normalized factor
const double NB = 12.50; // Normalized factor
const double beta = 0.07967; // speed of muon
const double c0 = 299792458; // speed of light

ifstream Bifs;
void setmap();
void plot();
string filename;
TGraph * g[2];
TH2D * h2[2];

// void plot_map(string filebase = "Wien_180614_ver1"){
void plot_map(string input = "HtypeXY.map"){
    cout << "EROOR" << endl;
    filename = input.c_str();

    double v0  = c0 * beta; // speed of muon
    cout << "%%%%% START %%%%%" << endl;
    gROOT->SetStyle("Plain");
    gROOT->Reset();
    gStyle->SetPadGridX(1);
    gStyle->SetPadGridY(1);
    cout << scientific;

    string dir = "/Users/YASUDA/data/muonLinac/sr/EBmap/Opera2d/";
    stringstream Bfile;

    cout << "Reading ... " << dir.c_str() << filename.c_str() << endl;
    Bfile << dir.c_str() << filename.c_str();
    ifstream Bifs(Bfile.str().c_str(), std::ios::in);
    if(!Bifs) cout << "ERROR : This file is not found !!" << endl;

    for(int i = 0 ; i < 2 ; i++){
        g[i] = new TGraph();
        g[i]->SetMarkerStyle(8);
        g[i]->SetMarkerSize(0.5);
    }

    // h2[1] = new TH2D("h2_0","h2_0", 100, -15., 15., 100, -15., 15., 100, 0.173862, 0.173876);
    // h2[0] = new TH2D("h2_1","h2_1", 100, -15., 15., 100, -15., 15., 100, -15.E-06, 15.E-06);
    h2[1] = new TH2D("h2_0","h2_0", 100, -15., 15., 100, -15., 15.);
    h2[0] = new TH2D("h2_1","h2_1", 100, -15., 15., 100, -15., 15.);

    double val[4]={};
    int ipoint = 0;
    while(Bifs >> val[0] >> val[1] >> val[2] >> val[3]){
        cout << val[0] << "\t" << val[1] << "\t" << val[2] << "\t" << val[3] << endl;
        g[0]->SetPoint(ipoint, val[0], val[2]);
        g[1]->SetPoint(ipoint, val[0], val[3]);
        h2[0]->Fill(val[0], val[1], val[2]);
        h2[1]->Fill(val[0], val[1], val[3]);
        ipoint++;
    }

    TCanvas * c = new TCanvas("c1","c1", 1000, 800);
    c->Divide(2,2);

    c->cd(1);
    g[0]->Draw("AP");
    c->cd(2);
    g[1]->Draw("AP");
    c->cd(3);
    h2[0]->Draw("colz");
    c->cd(4);
    h2[1]->Draw("colz");

}
