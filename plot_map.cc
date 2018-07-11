// This macro is to plot the map excluded from OPERA //
// This is made on 13, June, 2018.  by H. Yasuda //

#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;

// SETTING PARAMETER //
const int linecut = 8;  // cutting lineno


// int main(){
void plot_map(string filebase = "/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180614_ver1_3DBOpera.dat"){
// void plot_map(){


    cout << "%%%%% START %%%%%" << endl;

    gROOT->SetStyle("Plain");
    gROOT->Reset();

    TCanvas * c1 = new TCanvas("c1","c1",800,400);
    TCanvas * c2 = new TCanvas("c2","c2",800,400);
    TCanvas * c3 = new TCanvas("c3","c3",800,400);
    // TCanvas * c4 = new TCanvas("c4","c4");

    TGraph * gFx = new TGraph();
    TGraph * gFy = new TGraph();
    TGraph * gFz = new TGraph();

    int nbinx = 20;
    int nbiny = 20;
    int nbinz = 70;
    double x_min =  -30.;
    double x_max =   30.;
    double y_min =  -30.;
    double y_max =   30.;
    double z_min = -300.;
    double z_max =  800.;
    // TH2D * h2Fx = new TH2D("h2Fx","h2Fx", nbinx, -20., 20., nbinz, -100., 600.);
    // TH2D * h2Fy = new TH2D("h2Fy","h2Fy", nbiny, -20., 20., nbinz, -100., 600.);


    stringstream filename;
    // stringstream output;
    // filename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180614_ver1_3DBOpera.dat");  // Input file name of OPERA data Bfield
    // filename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180614_ver1_3DBOpera.dat");  // Input file name of OPERA data Bfield
    filename << filebase.c_str();
    // filename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180613_ver1_3DEOpera.dat");  // Input file name of OPERA data Efield
    // output.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180613_ver1_3DB.map");  // Output file name to 3DX format
    ifstream ifs(filename.str().c_str(), std::ios::in);
    // ofstream ofs(  output.str().c_str(), std::ios::in);


    // int N = 500000;
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
    vector<double> Fx;
    vector<double> Fy;
    vector<double> Fz;

    vector<double>  xf;
    vector<double>  yf;
    vector<double>  zf;
    vector<double> Fxf;
    vector<double> Fyf;
    vector<double> Fzf;

    while(ifs >> xi >> yi >> zi >> Fxi >> Fyi >> Fzi){

        cout << lineno << "\t" << xi << "\t" << yi << "\t" << zi << "\t" << Fxi << "\t" << Fyi << "\t" << Fzi << endl;

         x.push_back(  xi );
         y.push_back(  yi );
         z.push_back(  zi );
        Fx.push_back( Fxi );
        Fy.push_back( Fyi );
        Fz.push_back( Fzi );

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
    cout << "flineno = " << flineno << endl;

    // CHANGE THE FUNCTION AS YOU WANT //
    int ipointx = 0;
    int ipointy = 0;
    int ipointz = 0;
    for(int i = 0 ; i < flineno ; i++){
         xf.push_back( x[i] );
         yf.push_back( y[i] );
         zf.push_back( z[i] );
        Fxf.push_back( Fx[i] );
        Fyf.push_back( Fy[i] );
        Fzf.push_back( Fz[i] );

        if(xf[i]==0 && yf[i]==0){
            gFx->SetPoint(ipointx, zf[i], Fxf[i]);
            ipointx++;
        }


        if(xf[i]==0 && yf[i]==0){
            gFy->SetPoint(ipointy, zf[i], Fyf[i]);
            cout << ipointy << "\t" << zf[i] << "\t" << Fyf[i] << endl;
            ipointy++;
        }

        if(xf[i]==0 && yf[i]==0){
            gFz->SetPoint(ipointz, zf[i], Fzf[i]);
            ipointz++;
        }

    }

    // PUSH DATA TO TGRAPH AND TH2D //

    // gFx->SetRangeUser(-100.,-1.,600.,1.);
    c1->cd();
    gFx->Draw("AP");
    gFx->SetMarkerStyle(20);
    gFx->SetMarkerSize(1);
    gFx->GetXaxis()->SetTitle("z [mm]");
    // gFx->GetXaxis()->SetRangeUser(-300,800);
    // gFx->GetXaxis()->SetRangeUser(-500,500);
    gFx->GetXaxis()->SetRangeUser(-1000,1000);
    gFx->GetYaxis()->SetTitle("Bx [Tesla]");
    // gFx->GetYaxis()->SetTitle("Ex [V/m]");

    c2->cd();
    gFy->Draw("AP");
    // gFy->SetLineColor(2);
    gFy->SetMarkerStyle(21);
    gFy->SetMarkerSize(1);
    gFy->GetXaxis()->SetTitle("z [mm]");
    // gFy->GetXaxis()->SetRangeUser(-300,800);
    // gFy->GetXaxis()->SetRangeUser(-500,500);
    gFy->GetXaxis()->SetRangeUser(-1000,1000);
    gFy->GetYaxis()->SetTitle("By [Tesla]");
    // gFy->GetYaxis()->SetTitle("Ey [V/m]");

    c3->cd();
    gFz->Draw("AP");
    // gFz->SetLineColor(3);
    gFz->SetMarkerStyle(22);
    gFz->SetMarkerSize(1);
    gFz->GetXaxis()->SetTitle("z [mm]");
    // gFz->GetXaxis()->SetRangeUser(-300,800);
    // gFz->GetXaxis()->SetRangeUser(-500,500);
    gFz->GetXaxis()->SetRangeUser(-1000,1000);
    gFz->GetYaxis()->SetTitle("Bz [Tesla]");
    // gFz->GetYaxis()->SetTitle("Ez [V/m]");

    cout << "%%%%% FINISHED %%%%%" << endl;
}
