#include "CMyMatrix.h"
#include <iostream>
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

    inverted.SetWert(a * vorfaktor,1,1);
    inverted.SetWert(-b* vorfaktor,0,1);
    inverted.SetWert(-c* vorfaktor,1,0);
    inverted.SetWert(d * vorfaktor,0,0);

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