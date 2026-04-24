#include "Vektor.h"
#include <iostream>
#include <cmath>
void CMyVektor::SetWert(double data, int index)
{
    werte[index] = data;
}

double CMyVektor::CalcVektorLaenge()
{
    double laenge = 0;

    for (int i = 0; i < GetDimension(); i++)
    {
        laenge += GetWert(i) * GetWert(i);
    }

    return sqrt(laenge);
}

void CMyVektor::Maximierung(double (*funktion)(CMyVektor x), CMyVektor x, double lambdainput = 1.0)
{
    for (int schritte = 0; schritte < 25; schritte++)
    {
        CMyVektor grad = gradient(x, funktion);

        
        //check ob schon da
        if(grad.CalcVektorLaenge() < 0.00001)
        {
            std::cout << "Ende nach " <<schritte<< " Schritten";
            break;
        }


        CMyVektor xneu = x + lambdainput * grad;

        // wenn richtig
        if (funktion(xneu) > funktion(x))
        {
            // teste ob doppelt funktoiniert
            CMyVektor xdoppelt = x + (lambdainput * 2.0) * grad;

            // check ob doppelt funktioniert
            if (funktion(xdoppelt) > funktion(xneu))
            {
                lambdainput *= 2.0;
                x = xdoppelt;
            }
            else
            {
                // setze den ersten schritt ohne doppelt als nächsten punkt
                x = xneu;
            }
        }
        // wenn falsch
        else
        {
            while (funktion(xneu) <= funktion(x))
            {
                lambdainput /= 2.0;
                xneu = x + lambdainput * grad;
            }

            x = xneu;
        }
    }
}

CMyVektor operator+(CMyVektor a, CMyVektor b)
{

    // checken ob gleiche dimension
    if (a.GetDimension() == b.GetDimension())
    {
        CMyVektor c(a.GetDimension());

        for (int i = 0; i < a.GetDimension(); i++)
        {
            c.SetWert(a.GetWert(i) + b.GetWert(i), i);
        }

        return c;
    }
    else
    {
        throw "falsche Dimension";
    }
}

CMyVektor operator*(double lambda, CMyVektor a)
{
    CMyVektor b(a.GetDimension());

    for (int i = 0; i < b.GetDimension(); i++)
    {
        double neuerWert = lambda * a.GetWert(i);
        b.SetWert(neuerWert, i);
    }

    return b;
}

CMyVektor CMyVektor::gradient(CMyVektor x, double (*funktion)(CMyVektor x))
{
    int n = x.GetDimension();

    CMyVektor ergebnis(n);

    double h = 0.00000001;

    double fx = funktion(x);

    for (int i = 0; i < x.GetDimension(); i++)
    {
        CMyVektor copyX = x;

        copyX.SetWert(h + copyX.GetWert(i), i);

        double fxmith = funktion(copyX);

        ergebnis.SetWert(((fxmith - fx) / h), i);
    }

    return ergebnis;
}
