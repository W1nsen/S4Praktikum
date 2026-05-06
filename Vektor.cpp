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

void CMyVektor::Maximierung(double (*funktion)(CMyVektor x), CMyVektor x, double lambda = 1.0)
{
    

    for (int schritte = 0; schritte <= 25; schritte++)
    {
        // gradient
        CMyVektor grad = gradient(x, funktion);
        double gradLaenge = grad.CalcVektorLaenge();

        // aktueller Schritt ausgabe
        std::cout << "Schritt " << schritte << ":" << std::endl;
        printVektor(x); std::cout << std::endl;
        std::cout << " l " << lambda << std::endl;
        std::cout << " f(x) " << funktion(x) << std::endl;
        std::cout << " grad "; printVektor(grad); std::cout << std::endl;
        std::cout << " ||grad|| " << gradLaenge << std::endl << std::endl;

        // abbruch-check
        if (gradLaenge < 0.00001)
        {
            std::cout << "Ende wegen ||grad f(x)||<1e-5" << std::endl;
            printVektor(x); std::cout << std::endl;
            std::cout << " l " << lambda << std::endl;
            std::cout << " f(x) " << funktion(x) << std::endl;
            std::cout << " grad "; printVektor(grad); std::cout << std::endl;
            std::cout << " ||grad|| " << gradLaenge << std::endl;
            break;
        }

        //maximierung
        CMyVektor xneu = x + lambda * grad;
        double f_xneu = funktion(xneu);

        //check ob neuer punkt > alter punkt
        if (f_xneu > funktion(x))
        {
            std::cout << " x_neu = ( " ; printVektor(xneu); std::cout << std::endl;
            std::cout << " f(x_neu) = "; std::cout << funktion(xneu) << std::endl;

            // teste doppel
            double lambda_test = lambda * 2.0;
            CMyVektor xtest = x + lambda_test * grad;
            double f_xtest = funktion(xtest);

            std::cout << " Test doppelter Schrittweite (l = " << lambda_test << "):" << std::endl;
            std::cout << " x_test = "; printVektor(xtest); std::cout << std::endl;
            std::cout << " f(x_test) = " << f_xtest << std::endl;

            //check ob doppel > neu
            if (f_xtest > f_xneu)
            {
                lambda = lambda_test;
                x = xtest;
                std::cout << " verdoppele Schrittweite" << std::endl << std::endl;
            }
            else
            {
                x = xneu;
                std::cout << " behalte alte Schrittweite" << std::endl << std::endl;
            }
        }
        else
        {
            // schritt halbieren, wenn 
            while (funktion(xneu) <= funktion(x))
            {
                //neu ausrechnen
                lambda /= 2.0;
                xneu = x + lambda * grad;
                
                std::cout << " halbiere Schrittweite (lambda = " << lambda << "):" << std::endl;
                std::cout << " x_neu = ( " ; printVektor(xneu); std::cout << std::endl;
                std::cout << " f(x_neu) = " << funktion(xneu) << std::endl << std::endl;
            }
            x = xneu;
        }

        if(schritte == 25)
        {
            std::cout << "Ende wegen 25 Schritte"<<std::endl;

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

void CMyVektor::printVektor(CMyVektor v) 
{
    std::cout << "(";
    
    for (int i = 0; i < v.GetDimension(); i++) 
    {
        // Den aktuellen Wert ausgeben
        std::cout << v.GetWert(i);
        
        // check ob leztes element
        if (i < v.GetDimension() - 1) 
        {
            //wenn noch elemente dann trennen
            std::cout << "; ";
        }
        
    }
    
    std::cout << ")";
}