#pragma once
#include <vector>

class CMyVektor{

    public:

    //Kon
    CMyVektor(int d)
    {
        
        dimension = d;
        werte.resize(d,0.0);
    }

    //Methoden
    int GetDimension(){return dimension;}
    void SetWert(double data,int index);
    double GetWert(int index){return werte[index];}
    double CalcVektorLaenge();
    CMyVektor gradient(CMyVektor x, double (*funktion)(CMyVektor x));
    void Maximierung(double (*f)(CMyVektor x), CMyVektor x, double lambdainput);
    void printVektor(CMyVektor v); 

    private:
    int dimension;
    std::vector<double> werte;
};

CMyVektor operator+(CMyVektor a,CMyVektor b);
CMyVektor operator*(double lambda,CMyVektor a);
