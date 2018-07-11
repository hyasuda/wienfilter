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

// CONSTANT OF PHYSICS //
// const double m_mu  = 105.66E+6; // muon mass [eV]
// const double m_e   = 511E+3   ; // electron mass [eV]
// const double c     = 299792458; // light speed [m/s]
// const double pi    = 3.1415   ; // PI
// const double d     = 0.01     ; // Gap length

// int main(){
void plot_map(){


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
    double x_min =  -20.;
    double x_max =   20.;
    double y_min =  -20.;
    double y_max =   20.;
    double z_min = -100.;
    double z_max =  600.;
    TH2D * h2Fx = new TH2D("h2Fx","h2Fx", nbinx, -20., 20., nbinz, -100., 600.);
    TH2D * h2Fy = new TH2D("h2Fy","h2Fy", nbiny, -20., 20., nbinz, -100., 600.);


    stringstream filename;
    // stringstream output;
    filename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180613_ver1_3DBOpera.dat");  // Input file name of OPERA data Bfield
    // filename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180613_ver1_3DEOpera.dat");  // Input file name of OPERA data Efield
    // output.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180613_ver1_3DB.map");  // Output file name to 3DX format
    ifstream ifs(filename.str().c_str(), std::ios::in);
    // ofstream ofs(  output.str().c_str(), std::ios::in);


    // int N = 500000;
    int N = 999999;
    int lineno = 0;
    // double xi[N];
    // double yi[N];
    // double zi[N];
    // double Fxi[N];
    // double Fyi[N];
    // double Fzi[N];

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

    // while(true){
    //     if(lineno < linecut) {
    //         cout << " lineno = " << lineno << " is cut !" << endl;
    //         lineno++;
    //         continue;
    //     }else{
    //         break;
    //     }
    // }
    // cout << "DEBUG B" << endl;

    // while(ifs >> xi[lineno] >> yi[lineno] >> zi[lineno] >> Fxi[lineno] >> Fyi[lineno] >> Fzi[lineno]){
    while(ifs >> xi >> yi >> zi >> Fxi >> Fyi >> Fzi){
        // cout << "DEBUG A" << endl;
        // cout << lineno << "\t" << xi[lineno] << "\t" << yi[lineno] << "\t" << zi[lineno] << "\t" << Fxi[lineno] << "\t" << Fyi[lineno] << "\t" << Fzi[lineno] << endl;
        cout << lineno << "\t" << xi << "\t" << yi << "\t" << zi << "\t" << Fxi << "\t" << Fyi << "\t" << Fzi << endl;
        // if(lineno < linecut) {
        //     cout << " lineno = " << lineno << " is cut !" << endl;
        //     continue;
        // }
        //  x.push_back(  xi[lineno] );
        //  y.push_back(  yi[lineno] );
        //  z.push_back(  zi[lineno] );
        // Fx.push_back( Fxi[lineno] );
        // Fy.push_back( Fyi[lineno] );
        // Fz.push_back( Fzi[lineno] );

         x.push_back(  xi );
         y.push_back(  yi );
         z.push_back(  zi );
        Fx.push_back( Fxi );
        Fy.push_back( Fyi );
        Fz.push_back( Fzi );

        // cout << lineno << "\t" << x[lineno] << "\t" << y[lineno] << "\t" << z[lineno] << "\t" << Fx[lineno] << "\t" << Fy[lineno] << "\t" << Fz[lineno] << endl;

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
    if(flineno == N) cout << "This array is full ! You should enlarge the maximum of array N !! " << endl;

    // delete xi;
    // delete yi;
    // delete zi;
    // delete Fxi;
    // delete Fyi;
    // delete Fzi;

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
        // cout << scientific;
        // cout << xf[i] << "\t" << yf[i] << "\t" << zf[i] << "\t" << Fxf[i] << "\t" << Fyf[i] << "\t" << Fzf[i] << endl;

        if(xf[i]==0 && yf[i]==0){
            gFx->SetPoint(ipointx, zf[i], Fxf[i]);
            // cout << ipointx << "\t" << zf[i] << "\t" << Fxf[i] << endl;
            ipointx++;
        }


        if(xf[i]==0 && yf[i]==0){
            gFy->SetPoint(ipointy, zf[i], Fyf[i]);
            cout << ipointy << "\t" << zf[i] << "\t" << Fyf[i] << endl;
            ipointy++;
        }

        if(xf[i]==0 && yf[i]==0){
            gFz->SetPoint(ipointz, zf[i], Fzf[i]);
            // cout << ipointz << "\t" << zf[i] << "\t" << Fzf[i] << endl;
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
    gFx->GetXaxis()->SetRangeUser(-100,600);
    gFx->GetYaxis()->SetTitle("Bx [Tesla]");
    // gFx->GetYaxis()->SetTitle("Ex [V/m]");

    c2->cd();
    gFy->Draw("AP");
    // gFy->SetLineColor(2);
    gFy->SetMarkerStyle(21);
    gFy->SetMarkerSize(1);
    gFy->GetXaxis()->SetTitle("z [mm]");
    gFy->GetXaxis()->SetRangeUser(-100,600);
    gFy->GetYaxis()->SetTitle("By [Tesla]");
    // gFy->GetYaxis()->SetTitle("Ey [V/m]");

    c3->cd();
    gFz->Draw("AP");
    // gFz->SetLineColor(3);
    gFz->SetMarkerStyle(22);
    gFz->SetMarkerSize(1);
    gFz->GetXaxis()->SetTitle("z [mm]");
    gFz->GetXaxis()->SetRangeUser(-100,600);
    gFz->GetYaxis()->SetTitle("Bz [Tesla]");
    // gFz->GetYaxis()->SetTitle("Ez [V/m]");

    cout << "%%%%% FINISHED %%%%%" << endl;
}
