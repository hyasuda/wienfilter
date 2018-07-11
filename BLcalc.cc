// This macro is to calculate the B-L relation in wien filter //
// This is updated on 31, May, 2018. by H. Yasuda //

#include "fstream"
#include "TMath.h"


// CONSTANT OF PHYSICS //
const double m_mu  = 105.65837E+6; // muon mass [eV]
// const double m_e   = 511E+3   ; // electron mass [eV]
const double c     = 299792458; // light speed [m/s]
const double pi    = 3.14159265359   ; // PI

// const double d     = 0.01     ; // Gap lengt
const double d     = 0.1     ; // Gap length [m]


// BEAM AND SPIN ROTATION SETUP //
// In our case : after H- RFQ
const double alpha = 180; // spin flip [deg]
// const double alpha = 90; // spin rotation [deg]
const double beta  = 0.08; // velocity of muon : RFQ out rough
// const double beta  = 0.0796; // velocity of muon : After RFQ out realistic
// const double beta  = 0.01; // velocity of muon : USM
// ref. Proc. of PAC07, B.Steiner, et.al, (2007)
// const double alpha = 90; // spin rotation [deg]
// const double beta  = 0.54822; // velocity of muon



void BLcalc(double Le = 0.5){

    cout << "*******START******* " << endl;


    const double gamma = 1/(sqrt(1-beta*beta)); // Lorentz factor

    double Bx  = 0; // horizontal magnetic field [T]
    // double Le  = 0; // effective length
    // double Le  = 0.381; // effective length : assume [m]
    double Ey  = 0; // vertical electric field [V/m]

    double BxInt = 0;
    double EyInt = 0;

    cout << "##### SETUP PARAMETER #####"             << endl
         << " -Spin Rotation Angle [deg] : " << alpha << endl
         << " -velocity of muon (beta)   : " << beta  << endl
         << " -Lorentz factor (gamma)    : " << gamma << endl;



    // calculated from equivalence of Lorentz force and centrifugal force //
    Bx = ( alpha * pi / 180) * gamma * m_mu * beta / c / Le;
    // Bx = ( alpha * pi / 180) * gamma * m_e * beta / c / Le;

    // Wien condition : Ey = vz*Bx//
    Ey = beta * c * Bx;

    cout << "##### OUTPUT RESULT #####"  << endl;
    cout << " - B-filed output [T]   : " << Bx << endl;
    cout << " - E-filed output [V/m] : " << Ey << endl;


    cout << "*******FINISHED******* " << endl;

    ///// PLOT /////

    gROOT->SetStyle("Plain");
    gROOT->Reset();

    const int n = 1000; // entries
    double x[n], y1[n], y2[n];
    const double Le_max = 10;// Maximum of effective length Le [m]

    // For beta = 0.001
    // const double By_max = 0.001; // Maximum range of By [T]
    // const double Ex_max = 5000; // Maximum range of By [V/m]

    // For beta = 0.008
    const double By_max = 0.5; // Maximum range of By [T]
    const double Ex_max = 5.E+6; // Maximum range of By [V/]

    // TCanvas * c1 = new TCanvas("c1","Ex-By - L relation");
    TCanvas * c1 = new TCanvas("c1","c1",1000,500);
    // c1->SetTitle("Ex-By - Le relation");
    TPad * pad = new TPad("pad","",0,0,1,1);
    // pad->SetLogy();
    pad->Draw();
    pad->cd();

    TH1F * hf1 = c1 -> DrawFrame(0, 0, Le_max, By_max);
    hf1->SetXTitle("Effective Length [m]");
    hf1->SetYTitle("B-field [T]");
    pad->GetFrame()->SetBorderSize(12);

    // ===== Create contents of graph ===== //

    for(int i = 0 ; i < n ; i++){
        x[i] = (i+1) * Le_max / n;

        y1[i] = ( alpha * pi / 180) * gamma * m_mu * beta / c / x[i] ;
        y2[i] = beta * c * y1[i] ;

        if(x[i] == 0.5) {
            cout << "##### CALCULATION OF BE - FIELD #####" << endl
                 << "Effective length [m] = " << x[i] << " and " << " Gap [m] = " << d << ".  then, " << endl
                 << " B-field [T] = " << y1[i] << " , E-field [V/m] " << y2[i] << " , HV [V] = " << y2[i] * d << endl
                 << " B Integral [T*m] = " << y1[i]*x[i] << " , E Integral [kV/mm*m] "  << y2[i]*x[i] << endl;
        }
    }
    TGraph * g1 = new TGraph(n,x,y1);
    TGraph * g2 = new TGraph(n,x,y2);

    // g1->SetMarkerStyle(21);
    g1->SetLineWidth(5);
    g1->SetLineStyle(10);
    // g1->SetTitle("Ex-By - Le relation");
    g1->Draw("L");

    c1->cd();
    TPad * overlay = new TPad("overlay","",0,0,1,1);
    overlay->SetFillStyle(4000);
    overlay->SetFrameFillStyle(4000);
    overlay->Draw();
    overlay->cd();

    double xmin = pad->GetUxmin();
    double ymin = 0;
    double xmax = pad->GetUxmax();
    double ymax = Ex_max; // Max limit of electric field
    TH1F * hframe = overlay->DrawFrame(xmin, ymin, xmax, ymax);
    hframe->GetXaxis()->SetLabelOffset(99);
    hframe->GetYaxis()->SetLabelOffset(99);
    g2->SetLineColor(kRed);
    g2->SetLineWidth(5);
    g2->Draw("L");

    // Draw an axis on the right side
    TGaxis * axis = new TGaxis(xmax, ymin, xmax, ymax, ymin, ymax, 510,"+L");
    axis->SetTitle("E-field [V/m]");
    axis->SetTitleColor(kRed);
    axis->SetLineColor(kRed);
    axis->SetLabelColor(kRed);
    axis->Draw();


}
