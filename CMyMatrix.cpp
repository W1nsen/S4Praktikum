#include "CMyMatrix.h"
#include "Vektor.h"      
#include <iostream>
#include <cmath>


double CMyMatrix::GetWert(int zeile, int spalte)
{
    int index = zeile * matrixspalte + spalte;

    return werte[index];
}

void CMyMatrix::SetWert(double data, int zeile, int spalte)
{
    int index = zeile * matrixspalte + spalte;

    werte[index] = data;
}

CMyMatrix CMyMatrix::invers()
{
    double a,b,c,d;

    //zeile=y spalte=x
    a = GetWert(0,0);
    b = GetWert(0,1);
    c = GetWert(1,0);
    d = GetWert(1,1);

    double det = a * d - b * c;

    //Fehlerabbruch
    if(det == 0)
    {
        std::cout << "Fehler: det = 0";
        return CMyMatrix(0,0);
    }

    //crete inverted
    CMyMatrix inverted(2,2);

    double vorfaktor = 1.0 / det;

    inverted.SetWert(-b* vorfaktor,0,1);
    inverted.SetWert(-c* vorfaktor,1,0);
    inverted.SetWert(d * vorfaktor,0,0);
    inverted.SetWert(a * vorfaktor,1,1);


    return inverted;
}

CMyMatrix CMyMatrix::jacobi(CMyVektor x, CMyVektor (*funktion)(CMyVektor x))
{
    //vektor in matrix ändern
    int spalte = x.GetDimension();
    CMyVektor fx = funktion(x);
    int zeile = fx.GetDimension();

    CMyMatrix ergebnis(zeile,spalte);
    double h =  0.0001;

    //jede spalte
    for (int i = 0; i < spalte; i++)
    {
        CMyVektor copyX = x;

        //funktion mit h
        copyX.SetWert(h + copyX.GetWert(i), i);
        CMyVektor fxmith = funktion(copyX);

        //jede zeile
        for (int j = 0; j < zeile; j++)
        {
            //ableitung mit näherung
            double ableitung = (fxmith.GetWert(j) - fx.GetWert(j)) / h;  
            ergebnis.SetWert(ableitung,j,i);      
        }
        
    }
    
    return ergebnis;
}


CMyVektor CMyMatrix::NewtonVerfahren(CMyVektor x, CMyVektor(*funktion)(CMyVektor x))
{
    //aktuellen funktionswert berechnen
    CMyVektor fx = funktion(x);
    // jacobi aufstellen
    CMyMatrix j = jacobi(x,funktion);
    int schritte = 0;

    // mit jacobimatrix den aktuellen punkt berehcnen
    while((fx.CalcVektorLaenge() >=  0.00001) && schritte < 50)
    {
        std::cout << "Schritt: " << schritte << std::endl;

        std::cout << "x = "; x.printVektor(x); std::cout << std::endl;

        std::cout << "Fx = "; fx.printVektor(fx); std::cout << std::endl<<std::endl;

        std::cout << "Jacobi = "<< std::endl; j.PrintMatrix(); std::cout << std::endl;


        // jacobi invertieren
        CMyMatrix jinvers = j.invers();

        std::cout << "Jacobi Invers = " << std::endl; jinvers.PrintMatrix(); std::cout << std::endl;
    
        // matrix mit vektor muliplizeren
        CMyVektor dx = jinvers * fx;

        std::cout << "dx = "; dx.printVektor(dx); std::cout << std::endl;

        std::cout << "||fx|| = " << fx.CalcVektorLaenge(); std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        // abziehen vom alten punkt
        for (int i = 0; i < x.GetDimension(); i++)
        {
            //von allen komponenten
            x.SetWert(x.GetWert(i)- dx.GetWert(i),i);
        }

        // neu berechen für nächsten puhnkt
        fx = funktion(x);
        j = jacobi(x,funktion);

        schritte++;
    }

    if(fx.CalcVektorLaenge() < 0.00001)
    {
        std::cout << "Ende wegen Länge: " << std::endl;

        x.printVektor(x);
        std::cout << std::endl;

        std::cout << "Fx = "; fx.printVektor(fx); std::cout << std::endl;

        std::cout << "||fx|| = " << fx.CalcVektorLaenge(); std::cout << std::endl;

    }else if(schritte >= 50)
    {
        std::cout << "Ende wegen Schritte: " << std::endl;

        x.printVektor(x);
        std::cout << std::endl;

        std::cout << "Fx = "; fx.printVektor(fx); std::cout << std::endl;

        std::cout << "||fx|| = " << fx.CalcVektorLaenge(); std::cout << std::endl;

    }
    
    return x;
}

CMyVektor operator*(CMyMatrix A, CMyVektor x)
{
    CMyVektor ergebnis(A.GetZeile());

    for (int i = 0; i < A.GetZeile(); i++)
    {
        double summe = 0.0;

        for (int j = 0; j < A.GetSpalte(); j++)
        {
            summe += A.GetWert(i,j) * x.GetWert(j);
        }
        
        ergebnis.SetWert(summe,i);
    }
    
    return ergebnis;
}

void CMyMatrix::PrintMatrix()
{
    
    for (int i = 0; i < matrixzeile; i++)
    {
        
        for (int j = 0; j < matrixspalte; j++) 
        {
            std::cout << GetWert(i, j) << " ; ";
        }
        
        std::cout << std::endl;
    }
}

