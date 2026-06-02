#pragma once
#include "Vektor.h"

class C_DGLSolver
{
    public:
    // erste Ordnung
    C_DGLSolver(CMyVektor (*f_DGL_System)(CMyVektor y, double x));
    //zweite Ordnung
    C_DGLSolver(double (*f_DGL_nterOrdnung)(CMyVektor y, double x));
    void SetIsDGL(bool input){isDGL = input;}
    bool GetIsDGL(){return isDGL;}
    void Euler(double xstart, double xEnd, CMyVektor ystart, int schritte, bool print);
    void Heuner(double xstart, double xEnd, CMyVektor ystart, int schritte, bool print);

    private:
    bool isDGL;
    CMyVektor (*attribut_f_DGL_System)(CMyVektor y, double x);
    double (*attribut_f_DGL_nterOrdnung)(CMyVektor y, double x);
    CMyVektor ableitungen(CMyVektor y, double x);
};