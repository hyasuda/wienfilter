// This macro is to plot the map excluded from OPERA //
// This is made on 20, June, 2018.  by H. Yasuda //

#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;

// SETTING PARAMETER //
// const int linecut = 8;  // cutting lineno

// Normalization factor setting //
// const double NB =  0.00092507;
// const double NE = 35.492;
// const double NB =  0.000810399;
// const double NE = 34.5152;
// const double NB =  2.86282;
// const double NE = 78594.2;
// NAME :  Wien_180621_ver1_3DBOpera  //
// const double NB =  11.6525;
// const double NE = 117366;
// NAME :  Wien_180621_ver4_3DBOpera  //
// const double NB =  12.8021;
// const double NE =  117424;
// NAME :  Wien_180621_ver5_3DBOpera  //
// const double NB =  12.8057;
// const double NE =  200521;
// NAME :  Wien_180621_ver5_3DBOpera : 0550_musr.mac //
const double NE = 181911;
const double NB = 12.50;


const double B0y = -0.177722; // [Tesla]
// const double E0x = -4.2638E+6; // [V/m]
const double E0x = -4.2638; // [kV/mm]

// int main(){
// void plot_map(string filebase = "/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180614_ver1_3DBOpera.dat"){
void plot_map(){


    cout << "%%%%% START %%%%%" << endl;

    gROOT->SetStyle("Plain");
    gROOT->Reset();

    TCanvas * c1 = new TCanvas("c1","c1",800,400);
    TCanvas * c2 = new TCanvas("c2","c2",800,400);
    TCanvas * c3 = new TCanvas("c3","c3",800,400);
    TCanvas * c4 = new TCanvas("c4","c4",800,400);
    TCanvas * c5 = new TCanvas("c5","c5",800,400);
    TCanvas * c6 = new TCanvas("c6","c6",800,400);

    // BEFORE NORAMALIZATION //
    TGraph * gBx = new TGraph();
    TGraph * gBy = new TGraph();
    TGraph * gBz = new TGraph();
    TGraph * gEx = new TGraph();
    TGraph * gEy = new TGraph();
    TGraph * gEz = new TGraph();

    // AFTER NORAMALIZATION //
    TGraph * gBxn = new TGraph();
    TGraph * gByn = new TGraph();
    TGraph * gBzn = new TGraph();
    TGraph * gExn = new TGraph();
    TGraph * gEyn = new TGraph();
    TGraph * gEzn = new TGraph();

    // UNIFORM FIELD //
    TGraph * gByu = new TGraph();
    TGraph * gExu = new TGraph();

    stringstream Efilename;
    stringstream Bfilename;
    // stringstream output;
    // Efilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180620_ver1_3DEOpera.dat");  // Input file name of OPERA data Bfield
    // Bfilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180620_ver1_3DBOpera.dat");  // Input file name of OPERA data Efield
    // Efilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180620_ver1_3DEOpera_2.dat");  // Input file name of OPERA data Bfield
    // Bfilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180620_ver1_3DBOpera_2.dat");  // Input file name of OPERA data Efield
    // Wien_180621_ver1_3DEOpera
    // Efilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180621_ver1_3DEOpera.dat");  // Input file name of OPERA data Bfield
    // Bfilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180621_ver1_3DBOpera.dat");  // Input file name of OPERA data Efield
    // Wien_180621_ver4_3DEOpera
    // Efilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180621_ver4_3DEOpera.dat");  // Input file name of OPERA data Bfield
    // Bfilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180621_ver4_3DBOpera.dat");  // Input file name of OPERA data Efield
    // Wien_180621_ver5_3DEOpera
    Efilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180621_ver5_3DEOpera.dat");  // Input file name of OPERA data Bfield
    Bfilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180621_ver5_3DBOpera.dat");  // Input file name of OPERA data Efield
    // filename << filebase.c_str();
    // output.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180613_ver1_3DB.map");  // Output file name to 3DX format
    ifstream Eifs(Efilename.str().c_str(), std::ios::in);
    ifstream Bifs(Bfilename.str().c_str(), std::ios::in);
    // ofstream ofs(  output.str().c_str(), std::ios::in);


    int N = 999999;
    int lineno = 0;

    double xi;
    double yi;
    double zi;
    double Fxi;
    double Fyi;
    double Fzi;

    vector<double>  x;
    vector<double>  y;
    vector<double>  z;
    vector<double> Bx;
    vector<double> By;
    vector<double> Bz;
    vector<double> Ex;
    vector<double> Ey;
    vector<double> Ez;

    // vector<double>  xf;
    // vector<double>  yf;
    // vector<double>  zf;
    // vector<double> Bxf;
    // vector<double> Byf;
    // vector<double> Bzf;
    // vector<double> Exf;
    // vector<double> Eyf;
    // vector<double> Ezf;

    while(Bifs >> xi >> yi >> zi >> Fxi >> Fyi >> Fzi){

        // cout << lineno << "\t" << xi << "\t" << yi << "\t" << zi << "\t" << Fxi << "\t" << Fyi << "\t" << Fzi << endl;

         x.push_back(  xi );
         y.push_back(  yi );
         z.push_back(  zi );
        Bx.push_back( Fxi );
        By.push_back( Fyi );
        Bz.push_back( Fzi );

        // Initialize the contents unit //
        xi=0;
        yi=0;
        zi=0;
        Fxi=0;
        Fyi=0;
        Fzi=0;

        lineno++;
    }
    int flineno = lineno;
    cout << "Bflineno = " << flineno << endl;
    Bifs.close();

    lineno = 0;
    while(Eifs >> xi >> yi >> zi >> Fxi >> Fyi >> Fzi){

        // cout << lineno << "\t" << xi << "\t" << yi << "\t" << zi << "\t" << Fxi << "\t" << Fyi << "\t" << Fzi << endl;

        // x.push_back(  xi );
        // y.push_back(  yi );
        // z.push_back(  zi );
        Ex.push_back( Fxi * 1.e-6 ); // unit V/m -> kV/mm
        Ey.push_back( Fyi * 1.e-6 );
        Ez.push_back( Fzi * 1.e-6 );

        // Initialize the contents unit //
        xi=0;
        yi=0;
        zi=0;
        Fxi=0;
        Fyi=0;
        Fzi=0;
        lineno++;
    }
    flineno = lineno;
    cout << "Eflineno = " << flineno << endl;
    Eifs.close();

    // CHANGE THE FUNCTION AS YOU WANT //
    int ipointx = 0;
    int ipointy = 0;
    int ipointz = 0;
    int ipointu = 0;
    for(int i = 0 ; i < flineno ; i++){
         // xf.push_back( x[i] );
         // yf.push_back( y[i] );
         // zf.push_back( z[i] );
        // Bxf.push_back( Bx[i] * NB );
        // Byf.push_back( By[i] * NB );
        // Bzf.push_back( Bz[i] * NB );
        // Exf.push_back( Ex[i] * NE );
        // Eyf.push_back( Ey[i] * NE );
        // Ezf.push_back( Ez[i] * NE );

        if(x[i]==0 && y[i]==0){
            if(z[i] < 250 && z[i] > -250){
                cout << "SELECT : " << x[i] << "\t" << y[i] << "\t" << z[i] << endl;
                gExu->SetPoint(ipointu, z[i], E0x);
                gByu->SetPoint(ipointu, z[i], B0y);
                ipointu++;
            }else{
                cout << "NOSELECT : " << x[i] << "\t" << y[i] << "\t" << z[i] << endl;
                gExu->SetPoint(ipointu, z[i], 0.);
                gByu->SetPoint(ipointu, z[i], 0.);
                ipointu++;
            }
        }

        if(x[i]==0 && y[i]==0){
            gEx ->SetPoint(ipointx, z[i], Ex[i]);
            gBx ->SetPoint(ipointx, z[i], Bx[i]);
            gExn->SetPoint(ipointx, z[i], Ex[i] * NE);
            gBxn->SetPoint(ipointx, z[i], Bx[i] * NB);
            ipointx++;
        }


        if(x[i]==0 && y[i]==0){
            gEy ->SetPoint(ipointy, z[i], Ey[i]);
            gBy ->SetPoint(ipointy, z[i], By[i]);
            gEyn->SetPoint(ipointy, z[i], Ey[i] * NE);
            gByn->SetPoint(ipointy, z[i], By[i] * NB);
            // cout << ipointy << "\t" << zf[i] << "\t" << Fyf[i] << endl;
            ipointy++;
        }

        if(x[i]==0 && y[i]==0){
            gEz ->SetPoint(ipointz, z[i], Ez[i]);
            gBz ->SetPoint(ipointz, z[i], Bz[i]);
            gEzn->SetPoint(ipointz, z[i], Ez[i] * NE);
            gBzn->SetPoint(ipointz, z[i], Bz[i] * NB);
            ipointz++;
        }

    }

    // PUSH DATA TO TGRAPH AND TH2D //

    // gFx->SetRangeUser(-100.,-1.,600.,1.);
    c1->cd();
    gBx->Draw("AP");
    gBx->SetMarkerStyle(21);
    gBx->SetMarkerSize(1);
    gBx->GetXaxis()->SetTitle("z [mm]");
    gBx->GetXaxis()->SetRangeUser(-1000,1000);
    gBx->GetYaxis()->SetTitle("Bx [Tesla]");
    gBxn->Draw("SAMEP");
    gBxn->SetMarkerStyle(20);
    gBxn->SetMarkerSize(1);
    gBxn->SetMarkerColor(2);


    c2->cd();
    // gBy->Draw("AP");
    // gBy->SetMarkerStyle(21);
    // gBy->SetMarkerSize(1);
    // gBy->GetXaxis()->SetTitle("z [mm]");
    // gBy->GetXaxis()->SetRangeUser(-1000,1000);
    // gBy->GetYaxis()->SetTitle("By [Tesla]");
    // gBy->GetYaxis()->SetRangeUser(B0y-0.02,+0.02);
    // gByn->Draw("SAMEP");
    gByn->Draw("AP");
    gByn->SetMarkerStyle(20);
    gByn->SetMarkerSize(1);
    // gByn->SetMarkerColor(2);
    gByn->SetMarkerColor(1);
    gByn->GetXaxis()->SetTitle("z [mm]");
    gByn->GetXaxis()->SetRangeUser(-1000,1000);
    gByn->GetYaxis()->SetTitle("By [Tesla]");
    gByn->GetYaxis()->SetRangeUser(B0y-0.02,+0.02);
    // gByu->Draw("SAMEP");
    // gByu->SetMarkerStyle(22);
    // gByu->SetMarkerSize(1);
    // gByu->SetMarkerColor(3);
    gByu->Draw("SAMEL");
    gByu->SetLineStyle(10);
    gByu->SetLineWidth(4);
    gByu->SetLineColor(3);

    c3->cd();
    gBz->Draw("AP");
    gBz->SetMarkerStyle(21);
    gBz->SetMarkerSize(1);
    gBz->GetXaxis()->SetTitle("z [mm]");
    gBz->GetXaxis()->SetRangeUser(-1000,1000);
    gBz->GetYaxis()->SetTitle("Bz [Tesla]");
    gBzn->Draw("SAMEP");
    gBzn->SetMarkerStyle(20);
    gBzn->SetMarkerSize(1);
    gBzn->SetMarkerColor(2);

    c4->cd();
    gExn->Draw("AP");
    gExn->SetMarkerStyle(21);
    gExn->SetMarkerSize(1);
    // gExn->SetMarkerColor(2);
    gExn->SetMarkerColor(1);
    gExn->GetXaxis()->SetTitle("z [mm]");
    gExn->GetXaxis()->SetRangeUser(-1000,1000);
    // gExn->GetYaxis()->SetRangeUser(E0x-4e+5,4e+5); // unit V/m
    gExn->GetYaxis()->SetRangeUser(E0x-0.4,0.4); // unit V/m -> kV/mm
    // gExn->GetYaxis()->SetTitle("Ex [V/m]");
    gExn->GetYaxis()->SetTitle("Ex [kV/mm]");

    // gEx->Draw("SAMEP");
    // gEx->SetMarkerStyle(20);
    // gEx->SetMarkerSize(1);
    // gExu->Draw("SAMEP");
    // gExu->SetMarkerStyle(22);
    // gExu->SetMarkerSize(1);
    // gExu->SetMarkerColor(3);
    gExu->Draw("SAMEL");
    gExu->SetLineStyle(10);
    gExu->SetLineWidth(4);
    gExu->SetLineColor(3);

    c5->cd();
    gEyn->Draw("AP");
    gEyn->SetMarkerStyle(21);
    gEyn->SetMarkerSize(1);
    gEyn->SetMarkerColor(2);
    gEyn->GetXaxis()->SetTitle("z [mm]");
    gEyn->GetXaxis()->SetRangeUser(-1000,1000);
    // gEyn->GetYaxis()->SetTitle("Ey [V/m]");
    gEyn->GetYaxis()->SetTitle("Ey [kV/mm]");
    gEy->Draw("SAMEP");
    gEy->SetMarkerStyle(20);
    gEy->SetMarkerSize(1);


    c6->cd();
    gEzn->Draw("AP");
    gEzn->SetMarkerStyle(21);
    gEzn->SetMarkerSize(1);
    gEzn->SetMarkerColor(2);
    gEzn->GetXaxis()->SetTitle("z [mm]");
    gEzn->GetXaxis()->SetRangeUser(-1000,1000);
    // gEzn->GetYaxis()->SetTitle("Ez [V/m]");
    gEzn->GetYaxis()->SetTitle("Ez [kV/mm]");
    gEz->Draw("SAMEP");
    gEz->SetMarkerStyle(20);
    gEz->SetMarkerSize(1);

    cout << "%%%%% FINISHED %%%%%" << endl;
}
