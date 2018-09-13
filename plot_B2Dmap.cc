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

void plot_map(string filebase = "Wien_180614_ver1"){
    string dir = "/Users/YASUDA/data/muonLinac/sr/EBmap/";
    // string Etag = "_3DEOpera.dat";
    // string Btag = "_3DBOpera.dat";
    double v0  = c0 * beta; // speed of muon

    cout << "%%%%% START %%%%%" << endl;
    cout << "### Performing plot_Bmap.cc now ###" << endl;

    // gROOT->SetStyle("Bold");
    // gROOT->Reset();
    gStyle->SetPadGridX(1);
    gStyle->SetPadGridY(1);
    cout << scientific;

    TCanvas * c2d = new TCanvas("c2d","c2d", 1200, 800);

    TH2D * h2[11];

    for(int i = 0 ; i < 11 ; i++){
        h2[i] = new TH2D(Form("h2_%d", i), Form("h2_%d", i), 60, -15., 15., 60, -15., 15);
    }

    // stringstream Efilename;
    // Efilename << dir.c_str() << filebase.c_str() << Etag.c_str();
    // ifstream Eifs(Efilename.str().c_str(), std::ios::in);

    stringstream Bfilename;
    // Bfilename << dir.c_str() << filebase.c_str() << Btag.c_str();
    Bfilename << dir.c_str() << filebase.c_str() ;
    ifstream Bifs(Bfilename.str().c_str(), std::ios::in);
    cout << "Reading ... " << Bfilename.str().c_str() << endl;
    if(!Bifs) cout << "ERROR : Failed to read the file " << Bfilename.str().c_str() << endl;
    if(Bifs) cout << "Complete to reading file !" << endl;

    double val[6] = {};
    int iline = 0;

    int ipoint[11] = {};
    while( Bifs >> val[0] >> val[1] >> val[2] >> val[3] >> val[4] >> val[5] ){
        for(int i = 0 ; i < 11 ; i++){
            if(val[2] == -500. + 100*i) {
                h2[i]->Fill(val[0], val[1], val[4]); // Fill By in -500. - +500.
                ipoint[i]++;
            }
        }
    }

    cout << "Entry : " << ipoint[0] << endl;

    double entry = 0;
    double mean[11] = {};
    for(int i = 0 ; i < 11 ; i++){
        for(int j = 0 ; j < ipoint[0] ; j++){
            // cout << h2[i]->GetBinContent(j) << endl;
            if(h2[i]->GetBinContent(j) == 0.) continue;
            mean[i] += h2[i]->GetBinContent(j);
            entry++;
        }
    }

    cout << "MEAN" << endl;
    entry = entry/11;
    cout << (int)entry << endl;
    for(int i = 0 ; i < 11 ; i++){
        mean[i] = mean[i] / entry;
        cout << mean[i] << endl;
    }

    double rms[11] = {};
    double dev = 0;
    for(int i = 0 ; i < 11 ; i++){
        for(int j = 0 ; j < ipoint[0] ; j++){
            dev =  h2[i]->GetBinContent(j) - mean[i];
            rms[i] += dev*dev;
        }
    }

    cout << "RMS" << endl;
    for(int i = 0 ; i < 11 ; i++){
        rms[i] = sqrt(rms[i]/entry);
        cout << rms[i] << endl;
    }



    c2d->Divide(4,3);
    for(int i = 0 ; i < 11 ; i++){
        c2d->cd(1 + i);
        // h2[i]->Draw("surf3z");
        h2[i]->Draw("surf1z");
        // h2[i]->Draw("colz");
        // cout << h2[i]->GetMean() << "\t" << h2[i]->GetRMS() << endl;
    }

    cout << "%%%%% FINISHED %%%%%" << endl;
}
