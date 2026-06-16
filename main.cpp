#include <iostream>
#include "Vektor.h" 
#include "CMyMatrix.h"
#include "C_DGLSolver.h"
#include "CKomplex.h"
#include <cmath>
#include <string>
using namespace std;



double f(CMyVektor v)
{
    double x = v.GetWert(0);
    double y = v.GetWert(1);

    return sin(x*y) + sin(x) + cos(y);

}

double g(CMyVektor v)
{
    double x1 = v.GetWert(0);
    double x2 = v.GetWert(1);
    double x3 = v.GetWert(2);
 
    return -(2*pow(x1,2) - 2*x1*x2 + pow(x2,2) + pow(x3,2) - 2*x1 - 4*x3);
}

void p1()
{
    CMyVektor startstelle(2);
    startstelle.SetWert(0.2,0);
    startstelle.SetWert(-2.1,1);

    CMyVektor fMax(2);
    fMax.Maximierung(f,startstelle,1.0);

    std::cout << "---------------------------------------------------------------------------------------------";

    CMyVektor startstelleG(3);
    startstelleG.SetWert(0,0);
    startstelleG.SetWert(0,1);
    startstelleG.SetWert(0,2);

    CMyVektor gMax(3);
    gMax.Maximierung(g,startstelleG,0.1);

}

CMyVektor aufgabe2funktion(CMyVektor x)
{
    CMyVektor f(3);
    f.SetWert(x.GetWert(0) * x.GetWert(1) * std::exp(x.GetWert(2)), 0);
    f.SetWert(x.GetWert(1) * x.GetWert(2) * x.GetWert(3), 1);
    f.SetWert(x.GetWert(3), 2);

    return f;
}

void p2aufgabe2()
{
    //aufgabe 2

    //startwert
    CMyVektor x(4);
    x.SetWert(1,0);
    x.SetWert(2,1);
    x.SetWert(0,2);
    x.SetWert(3,3);


    
    //jacobi
    CMyMatrix jacob(0,0);
    CMyMatrix ergebnis = jacob.jacobi(x,aufgabe2funktion);

    ergebnis.PrintMatrix();

}


CMyVektor aufgabe3funktion(CMyVektor v)
{
    CMyVektor f(2);
    double x = v.GetWert(0);
    double y = v.GetWert(1); 

    f.SetWert(std::pow(x, 3) * std::pow(y, 3) - 2.0 * y, 0);
    
    f.SetWert(x - 2.0, 1);

    return f;
}

void p2aufgabe3()
{
    //startstelle
    CMyVektor startstelle(2);
    startstelle.SetWert(1,0);
    startstelle.SetWert(1,1);

    CMyMatrix matrix(0,0);

    CMyVektor nullstelle = matrix.NewtonVerfahren(startstelle,aufgabe3funktion);

}

CMyVektor p4Teil1(CMyVektor y, double x)
{
    CMyVektor dy(2);

    double y1 = y.GetWert(0);
    double y2 = y.GetWert(1);

    //erste funktion
    dy.SetWert(2*y2 - x*y1,0);
    dy.SetWert(y1*y2 - 2*pow(x,3),1);

    return dy;
}

double p4Teil2(CMyVektor y, double x)
{
    double y0 = y.GetWert(0);
    double y1 = y.GetWert(1);
    double y2 = y.GetWert(2);

    double y3 = 2.0 * x * y1 * y2 + 2.0 * (y0 * y0) * y1;

    return y3;

}

// int main() 
// {
// //     std::cout << "Aufgabe1" << std::endl;

// //     CMyVektor ystart(2);
// //     ystart.SetWert(0,0);
// //     ystart.SetWert(1,1);

// //     C_DGLSolver Solver(p4Teil1);

// //     std::cout << "Euler:" << std::endl;
// //     Solver.Euler(0,2,ystart,100,1);
// //     std::cout << std::endl;

// //     std::cout << "Heuner:" << std::endl;
// //     Solver.Heuner(0,2,ystart,100,1);
// //     std::cout << std::endl;



// //     std::cout << "Aufgabe2" << std::endl;

// //     CMyVektor yStartOrdnung(3); 
// //     yStartOrdnung.SetWert(1.0, 0); 
// //     yStartOrdnung.SetWert(-1.0, 1); 
// //     yStartOrdnung.SetWert(2.0, 2);  

// //     C_DGLSolver SolverOrdnung(p4Teil2);

// //     std::cout << "Euler mit 10:" << std::endl;
// //     SolverOrdnung.Euler(1,2,yStartOrdnung,10,0);
// //     std::cout << std::endl;

// //     std::cout << "Heuner mit 10:" << std::endl;
// //     SolverOrdnung.Heuner(1,2,yStartOrdnung,10,0);
// //     std::cout << std::endl;

// //     std::cout << "Euler mit 100:" << std::endl;
// //     SolverOrdnung.Euler(1,2,yStartOrdnung,100,0);
// //     std::cout << std::endl;

// //     std::cout << "Heuner mit 100:" << std::endl;
// //     SolverOrdnung.Heuner(1,2,yStartOrdnung,100,0);
// //     std::cout << std::endl;

// //     std::cout << "Euler mit 1000:" << std::endl;
// //     SolverOrdnung.Euler(1,2,yStartOrdnung,1000,0);
// //     std::cout << std::endl;

// //     std::cout << "Heuner mit 1000:" << std::endl;
// //     SolverOrdnung.Heuner(1,2,yStartOrdnung,1000,0);
// //     std::cout << std::endl;

// //     std::cout << "Euler mit 10000:" << std::endl;
// //     SolverOrdnung.Euler(1,2,yStartOrdnung,10000,0);
// //     std::cout << std::endl;

// //     std::cout << "Heuner mit 10000:" << std::endl;
// //     SolverOrdnung.Heuner(1,2,yStartOrdnung,10000,0);
// //     std::cout << std::endl;
//}

// void test_datei(string dateiname)
// {
//     cout << " Bei " << dateiname << endl;

//     // Lesen
//     vector<CKomplex> original = werte_einlesen(dateiname);

//     // Fourier transformieren
//     vector<CKomplex> fourierTrafo = fourier_hin(original);

//     double epsilons[] = {-1,0.001,0.01,0.1,1};

//     string namen[] = 
//     {"Standard-Epsilon: ",
//     "epsilon=0.001: ",
//     "epsilon=0.01: ",
//     "epsilon=0.1: ",
//     "epsilon=1: "};

//     string epsilonsDateiName[] = {"default", "0001", "001", "01", "10"};
//     for (int i = 0; i < 5; i++)
//     {

//         // erstelle datei
//         string ausgabe_name = dateiname + "_komp_" + epsilonsDateiName[i] + ".txt";

//         // komprimieren
//         if (i == 0) {
//             werte_ausgeben(ausgabe_name, fourierTrafo);
//         } else {
//             werte_ausgeben(ausgabe_name, fourierTrafo, epsilons[i]);
//         }

//         // komprimierte datei lesen
//         vector<CKomplex> kompDaten = werte_einlesen(ausgabe_name);

//         // rueck transformieren
//         vector<CKomplex> rueckTrafo = fourier_rueck(kompDaten);

//         // abweichung berechnen
//         double abweichung = maximale_abweichung(original, rueckTrafo);

//         std::cout << "Maximale Abweichung bei " << namen[i] << abweichung << std::endl;
//     }
//     cout << endl;
// }
void test_datei(string dateiname)
{
    cout << " Bei " << dateiname << endl;

    // 1. Lesen
    vector<CKomplex> original = werte_einlesen(dateiname);

    // 2. Fourier transformieren
    vector<CKomplex> fourierTrafo = fourier_hin(original);

    // 3. DIREKTE RÜCKTRANSFORMATION (Ohne Speichern, ohne Epsilon!)
    vector<CKomplex> direkt_rueck = fourier_rueck(fourierTrafo);

    // 4. Abweichung direkt berechnen
    double direkte_abweichung = maximale_abweichung(original, direkt_rueck);
    cout << "  -> DIREKTE Abweichung (ohne Speichern): " << direkte_abweichung << endl;
    
    // ... hier drunter kannst du deine alte Schleife erst mal so lassen wie sie ist ...
}
int main()
{
    test_datei("Daten_original1.txt");
    test_datei("Daten_original2.txt");

    return 0;
}