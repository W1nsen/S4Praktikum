#include <iostream>
#include "Vektor.h" 
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

int main() 
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


    return 0;
}
