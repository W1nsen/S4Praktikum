#include <iostream>
#include "Vektor.h" 
#include "CMyMatrix.h"
#include <cmath>

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




int main() 
{
    p2aufgabe2();

    return 0;
}
