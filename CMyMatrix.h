#pragma once
#include <vector>
#include "Vektor.h"

class CMyMatrix
{
    public:
        CMyMatrix(int zeile, int spalte)
        {
            // dimension
            matrixspalte = spalte;
            matrixzeile = zeile;

            //speicherplatz reserbvieren
            werte.resize(spalte*zeile);
        }

        int GetZeile(){return matrixzeile;}
        int GetSpalte(){return matrixspalte;}
        void SetWert(double data, int zeile, int spalte);
        double GetWert(int zeile, int spalte);
        CMyMatrix invers();
        CMyMatrix jacobi(CMyVektor x, CMyVektor (*funktion)(CMyVektor x));
        CMyVektor NewtonVerfahren(CMyVektor startwert, CMyVektor (*funktion)(CMyVektor x));
        void PrintMatrix();
        
    private:
        int matrixzeile;
        int matrixspalte;
        std::vector<double> werte;


    
};
CMyVektor operator*(CMyMatrix A, CMyVektor x);

