#include "C_DGLSolver.h"
#include <iostream>


C_DGLSolver::C_DGLSolver(CMyVektor (*f_DGL_System)(CMyVektor y, double x))
{
    isDGL = true;
    attribut_f_DGL_nterOrdnung = nullptr;
    attribut_f_DGL_System = f_DGL_System;
}

C_DGLSolver::C_DGLSolver(double (*f_DGL_nterOrdnung)(CMyVektor y, double x))
{
    isDGL = false;
    attribut_f_DGL_nterOrdnung = f_DGL_nterOrdnung;
    attribut_f_DGL_System = nullptr;
}

CMyVektor C_DGLSolver::ableitungen(CMyVektor y, double x)
{
    if(isDGL == true)
    {
        // wenn erste ordnung
        return attribut_f_DGL_System(y,x);
    }
    else
    {
        //wenn nte ordnung

        CMyVektor dy(y.GetDimension());

        for (int i = 0; i < y.GetDimension()-1; i++)
        {
            dy.SetWert(y.GetWert(i+1),i);
        }
        
        //setze letzte ordnung mit der DGL
        dy.SetWert(attribut_f_DGL_nterOrdnung(y,x),y.GetDimension()-1);

        return dy;
    }
}

void C_DGLSolver::Euler(double xstart, double xEnd, CMyVektor ystart, int schritte, bool print)
{
    double h = (xEnd - xstart) /schritte;

    double x = xstart;
    CMyVektor y = ystart;

    for (int i = 0; i < schritte; i++)
    {
        //ableitung berechnen
        CMyVektor ystrich = ableitungen(y,x);

        

        if(print)
        {
            std::cout << " h = " << h << std::endl << "Schritt " << i << std::endl;
            std::cout << "x = " << x << std::endl;

            std::cout << "y = "; y.printVektor(y); std::cout << std::endl;

            std::cout << "y' = "; ystrich.printVektor(ystrich); std::cout << std::endl;

        }

        // neues y
        y = y + (h * ystrich);

        //neues x
        x = x + h;
    }

    double exakteLoesung = 0.5;
    double abweichung = y.GetWert(0) - exakteLoesung;
    std::cout << "Abweichung bei Euler bei " << schritte << " Schritten: " << abweichung << std::endl;
    
}

void C_DGLSolver::Heuner(double xstart, double xEnd, CMyVektor ystart, int schritte, bool print)
{
    double h = (xEnd - xstart) /schritte;

    double x = xstart;
    CMyVektor y = ystart;

    for (int i = 0; i < schritte; i++)
    {
        //hole steigung
        CMyVektor steigung = ableitungen(y,x);

        //mache test euler
        CMyVektor test = y + (h * steigung);

        // zweite steigung berechnen
        CMyVektor steigung2 = ableitungen(test,x+h);

        CMyVektor ystrichmittel = 0.5 * (steigung + steigung2);

        if(print)
        {
            std::cout << " h = " << h << std::endl << "Schritt " << i << std::endl;
            std::cout << "x = " << x << std::endl;

            std::cout << "y = "; y.printVektor(y); std::cout << std::endl;

            std::cout << "y'orig = "; steigung.printVektor(steigung); std::cout << std::endl;

            std::cout << "  y_Test = "; test.printVektor(test); std::cout << std::endl;
            std::cout << "  y'_Test = "; steigung2.printVektor(steigung2); std::cout << std::endl;
            std::cout << std::endl;

            std::cout << "  y'_Mittel = "; ystrichmittel.printVektor(ystrichmittel); std::cout << std::endl;
        }


        y = y + (h * ystrichmittel);

        x = x + h;

    }
    
    double exakteLoesung = 0.5;
    double abweichung = y.GetWert(0) - exakteLoesung;
    std::cout << "Abweichung bei Heun  bei " << schritte << " Schritten: " << abweichung << std::endl;
}