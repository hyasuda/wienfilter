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
const int linecut = 8;  // cutting lineno
// const double B0y = -0.177722; // [Tesla]  After RFQ output Rough
// const double E0x = -4.2638E+6; // [V/m]   After RFQ output Rough
// const double B0y = -0.176828; // [Tesla]     After RFQ output real // beta = 0.0796
const double B0y = 0.176987; // [Tesla]     After RFQ output real // beta = 0.07967
// const double E0x = -4.21972E+6; // [V/m]     After RFQ output real // beta = 0.0796
const double E0x = 4.22723e+06; // [V/m]     After RFQ output real // beta = 0.07967
// const double B0y_sum = -0.0884151; // [Tesla]     After RFQ output real // beta = 0.0796
// const double E0x_sum = -2.10989e+06; // [V/m]     After RFQ output real // beta = 0.0796
const double Le = 0.5; // [m]


int main(){

    cout << "%%%%% START %%%%%" << endl;

    // int nbinx = 20;
    // int nbiny = 20;
    // int nbinz = 70;
    // double x_min =  -30.;
    // double x_max =   30.;
    // double y_min =  -30.;
    // double y_max =   30.;
    // double z_min = -300.;
    // double z_max =  800.;

    stringstream Efilename;
    stringstream Bfilename;
    // stringstream output;
    // Efilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180620_ver1_3DEOpera.dat");  // Input file name of OPERA data Bfield
    // Bfilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180620_ver1_3DBOpera.dat");  // Input file name of OPERA data Efield
    // Efilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180620_ver1_3DEOpera_2.dat");  // Input file name of OPERA data Bfield
    // Bfilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180620_ver1_3DBOpera_2.dat");  // Input file name of OPERA data Efield
    Efilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180621_ver5_3DEOpera.dat");  // Input file name of OPERA data Bfield
    Bfilename.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180621_ver5_3DBOpera.dat");  // Input file name of OPERA data Efield
    // output.str("/Users/YASUDA/data/muonLinac/sr/EBmap/Wien_180613_ver1_3DB.map");  // Output file name to 3DX format
    ifstream Eifs(Efilename.str().c_str(), std::ios::in);
    ifstream Bifs(Bfilename.str().c_str(), std::ios::in);
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

    double NE; // Normalization factor of E-field
    double NB; // Normalization factor of B-field

    vector<double>  x;
    vector<double>  y;
    vector<double>  z;
    vector<double> Ex;
    vector<double> Ey;
    vector<double> Ez;
    vector<double> Bx;
    vector<double> By;
    vector<double> Bz;

    while(Eifs >> xi >> yi >> zi >> Fxi >> Fyi >> Fzi){

        // cout << lineno << "\t" << xi << "\t" << yi << "\t" << zi << "\t" << Fxi << "\t" << Fyi << "\t" << Fzi << endl;

         x.push_back(  xi );
         y.push_back(  yi );
         z.push_back(  zi );
        Ex.push_back( Fxi );
        Ey.push_back( Fyi );
        Ez.push_back( Fzi );

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
    cout << "Eflineno = " << flineno << endl;

    cout << "CHECKPOINT 1" << endl;

    // Initialize the lineno //
    lineno = 0;
    while(Bifs >> xi >> yi >> zi >> Fxi >> Fyi >> Fzi){

        // cout << lineno << "\t" << xi << "\t" << yi << "\t" << zi << "\t" << Fxi << "\t" << Fyi << "\t" << Fzi << endl;

        if(x[lineno] != xi || y[lineno] != yi || z[lineno] != zi) {
            cout << "ERROR :: the lineno is not correct !! Please check the line !!" << endl;
            break;
        }

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

    cout << "CHECKPOINT 2" << endl;

    double Ex_sum = 0;
    double By_sum = 0;
    // cout << "Ex[i]" << "\t" << "By[i]" << "\t" << "z[i+1]" << "\t" << "z[i]" << "\t" << "z[i+1]-z[i]" << "\t" << "Ex_sum" << "\t" << "By_sum" << endl;
    for(int i = 0 ; i < flineno ; i++){
        if(x[i] == 0 && y[i]==0){
            // Ex_sum += Ex[i]*(z[i+1]-z[i])*1.E+3; // V/m * mm * m/mm
            // By_sum += By[i]*(z[i+1]-z[i])*1.E+3; // Tesla * mm * m/mm
            Ex_sum += Ex[i]*10*1.E-3; // V/m * mm * m/mm
            By_sum += By[i]*10*1.E-3; // Tesla * mm * m/mm
            // cout << Ex[i] << "\t" << By[i] << "\t" << z[i+1] << "\t" << z[i] << "\t" << z[i+1]-z[i] << "\t" << Ex_sum << "\t" << By_sum << endl;
        }else{
            // cout << "NOT x == 0 , y == 0" << endl;
        }
    }

    // CALCULATION OF NORMALIZATION FACTOR //
    // NE = (E0x*Le)/Ex_sum; // (V/m * m) / (V/m * m)
    // NB = (B0y*Le)/By_sum; // (Tesla * m) / (V/m * m)
    double E0x_sum = E0x * Le;
    double B0x_sum = B0x * Le;
    NE = (E0x_sum)/Ex_sum; // (V/m * m) / (V/m * m)
    NB = (B0y_sum)/By_sum; // (Tesla * m) / (V/m * m)

    cout << "E0x" << "\t" <<"B0y" << "\t" << "Le" << endl;
    cout <<  E0x  << "\t" << B0y  << "\t" <<  Le  << endl;

    cout << "Ex_sum" << "\t" << "By_sum" << endl;
    cout <<  Ex_sum  << "\t" <<  By_sum  << endl;

    // cout << "NE = (E0x/*Le)/Ex_sum = " << NE << endl;
    // cout << "NB = (B0y*Le)/By_sum = " << NB << endl;
    cout << "NE = E0x_sum/Ex_sum = " << NE << endl;
    cout << "NB = B0y_sum/By_sum = " << NB << endl;

    cout << "%%%%% FINISHED %%%%%" << endl;
}
