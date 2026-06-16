#pragma once
#include <vector>
#include <string>

class CKomplex
{
    public:
    CKomplex();
    CKomplex(double a, double b);
    CKomplex(double phi);
    double re(){return real;}
    double im(){return imagine;}
    double abs();

    private:
    double real;
    double imagine;

};
CKomplex operator+(CKomplex a, CKomplex b);
CKomplex operator*(CKomplex a, CKomplex b);
CKomplex operator*(double a, CKomplex b);
CKomplex operator*(CKomplex b,double a);


std::vector<CKomplex> werte_einlesen(const std::string dateiname);
void werte_ausgeben(const std::string dateiname, std::vector<CKomplex> werte, double epsilon = -1.0);

std::vector<CKomplex> fourier_hin(std::vector<CKomplex>& input);
std::vector<CKomplex> fourier_rueck(std::vector<CKomplex>& input);
double maximale_abweichung(std::vector<CKomplex>& original, std::vector<CKomplex>& komprimiert);

