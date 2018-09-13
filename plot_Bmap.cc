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

    gROOT->SetStyle("Plain");
    gROOT->Reset();
    gStyle->SetPadGridX(1);
    gStyle->SetPadGridY(1);
    cout << scientific;

    TCanvas * c = new TCanvas("c", "c", 600, 800);
    TCanvas * cL = new TCanvas("cL", "cL", 600, 600);

    TGraph * g[2][3];
    for(int j = 0 ; j < 2 ; j++){
        for(int i = 0 ; i < 3 ; i++){
            // g[j][i] = new TGraph(Form("g_[%d][%d]",j,i),Form("g_[%d][%d]",j,i));
            g[j][i] = new TGraph();
        }
    }

    TGraph * gL[3];
    for(int i = 0 ; i < 3 ; i++){
        gL[i] = new TGraph();
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
    int ipoint = 0;

    while(Bifs >> val[0] >> val[1] >> val[2] >> val[3] >> val[4] >> val[5] ){
        // cout << iline << "\t" << val[0] << "\t" << val[1] << "\t" << val[2] << "\t" << val[3] << "\t" << val[4]<< "\t" << val[5] << "\t" << val[6] << endl;
        iline++;
        if(val[0] != 0. || val[1] != 0.) continue;
        // cout << "On z axis : " << val[0] << "\t" << val[1] << "\t" << val[2] << "\t" << val[3] << "\t" << val[4] << "\t" << val[5] << endl;
        g[1][0]->SetPoint(ipoint, val[2], val[3] ); // z-Bx
        g[1][1]->SetPoint(ipoint, val[2], val[4] ); // z-By
        g[1][2]->SetPoint(ipoint, val[2], val[5] ); // z-Bz
        gL[1]->SetPoint(ipoint, val[2], val[4] * v0); // Lorentz force of By

        g[0][0]->SetPoint(ipoint, val[2], -4.3E+06); // z-Ex
        g[0][1]->SetPoint(ipoint, val[2], 0); // z-Ey
        g[0][2]->SetPoint(ipoint, val[2], 0); // z-Ez
        if(val[2] < -250. || val[2] > 250) gL[0]->SetPoint(ipoint, val[2], 0); // Lorentz force of Ex
        if(val[2] >= -250. && val[2] <= 250.) gL[0]->SetPoint(ipoint, val[2], -4.3E+06 ); // Lorentz force of Ex
        // if(val[2] > 250.) gL[0]->SetPoint(ipoint, val[2], 0); // Lorentz force of Ex

        ipoint++;
    }
    cout << "TOTAL LINE : " << ipoint << endl;

    c->Divide(1,3);
    for(int i = 0 ; i < 3 ; i++){
        int j = 1;
        c->cd(i + 1);
        g[j][i]->Draw("AP");
        g[j][i]->SetMarkerStyle(20);
        g[j][i]->SetMarkerSize(0.5);
        // cout << j << "\t" << i << "\t" << TMath::MaxElement(g[j][i]->GetN(),g[j][i]->GetY()) << "\t" << TMath::MinElement(g[j][i]->GetN(),g[j][i]->GetY()) << endl;
    }

    cout << gL[0]->GetN() << endl;
    double gLx[2] = {};
    double gLy[2] = {};
    for(int i = 0 ; i < gL[0]->GetN() ; i++){
        gL[0]->GetPoint(i, gLx[0], gLy[0]);
        gL[1]->GetPoint(i, gLx[1], gLy[1]);
        gL[2]->SetPoint(i, gLx[0], gLy[0] - gLy[1]);
    }

    // cL->cd();
    // gL[0]->Draw("AL");
    // gL[0]->SetLineStyle(9);
    // gL[0]->SetLineWidth(3);
    // gL[0]->SetLineColor(2);
    // gL[0]->GetXaxis()->SetRangeUser(-1e+3,1e+3);
    // gL[0]->GetYaxis()->SetRangeUser(-4e+6,5e+5);
    // gL[1]->Draw("L");
    // gL[1]->SetLineStyle(1);
    // gL[1]->SetLineWidth(3);
    // gL[1]->SetLineColor(4);
    // gL[2]->Draw("L");
    // gL[2]->SetLineStyle(2);
    // gL[2]->SetLineWidth(3);
    // gL[2]->SetLineColor(3);

    cL->cd();
    gL[0]->Draw("AP");
    gL[0]->SetMarkerStyle(20);
    gL[0]->SetMarkerColor(2);
    gL[0]->SetMarkerSize(0.5);
    gL[1]->Draw("P");
    gL[1]->SetMarkerStyle(21);
    gL[1]->SetMarkerColor(4);
    gL[1]->SetMarkerSize(0.5);
    gL[2]->Draw("P");
    gL[2]->SetMarkerStyle(22);
    gL[2]->SetMarkerColor(3);
    gL[2]->SetMarkerSize(0.5);


    cout << "%%%%% FINISHED %%%%%" << endl;
}
