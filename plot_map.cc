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


// int main(){
// void plot_map(string filebase = "/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180614_ver1_3DBOpera.dat"){
// void plot_map(){
void plot_map(string filebase = "Wien_180614_ver1"){
    string dir = "/Users/YASUDA/data/muonLinac/sr/EBmap/";
    string Etag = "_3DEOpera.dat";
    string Btag = "_3DBOpera.dat";

    cout << "%%%%% START %%%%%" << endl;

    gROOT->SetStyle("Plain");
    gROOT->Reset();
    gStyle->SetPadGridX(1);
    gStyle->SetPadGridY(1);
    cout << scientific;

    // TCanvas * c1 = new TCanvas("c1","c1",800,400);
    // TCanvas * c2 = new TCanvas("c2","c2",800,400);
    // TCanvas * c3 = new TCanvas("c3","c3",800,400);
    // TCanvas * c4 = new TCanvas("c4","c4");

    TCanvas * c = new TCanvas("c", "c", 800, 800);

    TGraph * g[2][3];
    for(int j = 0 ; j < 2 ; j++){
        for(int i = 0 ; i < 3 ; i++){
            // g[j][i] = new TGraph(Form("g_[%d][%d]",j,i),Form("g_[%d][%d]",j,i));
            g[j][i] = new TGraph();
        }
    }

    stringstream Efilename;
    stringstream Bfilename;
    Efilename << dir.c_str() << filebase.c_str() << Etag.c_str();
    Bfilename << dir.c_str() << filebase.c_str() << Btag.c_str();
    ifstream Eifs(Efilename.str().c_str(), std::ios::in);
    ifstream Bifs(Bfilename.str().c_str(), std::ios::in);


    double val[6] = {};
    int iline = 0;
    int ipoint = 0;
    while(Eifs >> val[0] >> val[1] >> val[2] >> val[3] >> val[4] >> val[5] ){
        // cout << iline << "\t" << val[0] << "\t" << val[1] << "\t" << val[2] << "\t" << val[3] << "\t" << val[4]<< "\t" << val[5] << "\t" << val[6] << endl;
        iline++;
        if(val[0] != 0. || val[1] != 0.) continue;
        // cout << "On z axis : " << val[0] << "\t" << val[1] << "\t" << val[2] << "\t" << val[3] << "\t" << val[4] << "\t" << val[5] << endl;
        g[0][0]->SetPoint(ipoint, val[2], val[3]);
        g[0][1]->SetPoint(ipoint, val[2], val[4]);
        g[0][2]->SetPoint(ipoint, val[2], val[5]);
        ipoint++;
    }
    iline = 0;
    ipoint = 0;
    while(Bifs >> val[0] >> val[1] >> val[2] >> val[3] >> val[4] >> val[5] ){
        // cout << iline << "\t" << val[0] << "\t" << val[1] << "\t" << val[2] << "\t" << val[3] << "\t" << val[4]<< "\t" << val[5] << "\t" << val[6] << endl;
        iline++;
        if(val[0] != 0. || val[1] != 0.) continue;
        // cout << "On z axis : " << val[0] << "\t" << val[1] << "\t" << val[2] << "\t" << val[3] << "\t" << val[4] << "\t" << val[5] << endl;
        g[1][0]->SetPoint(ipoint, val[2], val[3]);
        g[1][1]->SetPoint(ipoint, val[2], val[4]);
        g[1][2]->SetPoint(ipoint, val[2], val[5]);
        ipoint++;
    }

    c->Divide(2,3);
    for(int j = 0 ; j < 2 ; j++){
        for(int i = 0 ; i < 3 ; i++){
            // if(j == 0) c->cd(2i+1);
            // if(j == 1) c->cd(2i+2);
            c->cd(j + i*2 + 1);
            g[j][i]->Draw("AP");
            g[j][i]->SetMarkerStyle(20);
            g[j][i]->SetMarkerSize(1);
            cout << j << "\t" << i << "\t" << TMath::MaxElement(g[j][i]->GetN(),g[j][i]->GetY()) << "\t" << TMath::MinElement(g[j][i]->GetN(),g[j][i]->GetY()) << endl;
        }
    }

    cout << "%%%%% FINISHED %%%%%" << endl;
}
