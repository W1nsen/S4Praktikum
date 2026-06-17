#include <iostream>
#include <cmath>
#include "CKomplex.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;

CKomplex::CKomplex()
{
    real = 0;
    imagine = 0;
}

CKomplex::CKomplex(double a ,double b)
{
    real = a;
    imagine = b;
}

CKomplex::CKomplex(double phi)
{
    real = cos(phi);
    imagine = sin(phi);
}

double CKomplex::abs()
{
    return sqrt((real*real) + (imagine*imagine));
}

CKomplex operator+(CKomplex a, CKomplex b)
{
    double erg_real = a.re() + b.re();
    double erg_imagine = a.im() + b.im();

    CKomplex erg(erg_real,erg_imagine);

    return erg;
}

CKomplex operator*(CKomplex aa, CKomplex bb)
{
    double a,b,c,d;
    a = aa.re();
    b = aa.im();
    c = bb.re();
    d = bb.im();

    double ergReal = (a*c) - (b*d);

    double ergImagine = (a*d) + (b*c);
    
    CKomplex erg(ergReal,ergImagine);

    return erg;
}

CKomplex operator*(double a, CKomplex b)
{
    double ergReal,ergImagine;

    ergReal = a * b.re();
    ergImagine = a * b.im();

    CKomplex erg(ergReal,ergImagine);

    return erg;
}

CKomplex operator*(CKomplex b, double a)
{
    double ergReal,ergImagine;

    ergReal = a * b.re();
    ergImagine = a * b.im();

    CKomplex erg(ergReal,ergImagine);

    return erg;
}

vector<CKomplex> werte_einlesen(const string dateiname)
{
    int i, N, idx;
	double re, im;
	vector<CKomplex> werte;
		// File oeffnen
	ifstream fp;
	fp.open(dateiname);
		// Dimension einlesen
	fp >> N;
		// Werte-Vektor anlegen
	werte.resize(N);
	CKomplex null(0,0);
	for (i = 0; i<N; i++)
		werte[i] = null;
		// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof())
	{
		fp >> idx >> re >> im;
		CKomplex a(re,im);
		werte[idx] = a;
	}
		// File schliessen
	fp.close();

	return werte;
}

void werte_ausgeben(const std::string dateiname, std::vector<CKomplex> werte, double epsilon)
{
	int i;
	int N = werte.size();
		// File oeffnen
	ofstream fp;
	fp.open(dateiname);
		// Dimension in das File schreiben
	fp << N << endl;
		// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << endl;
		// File schliessen
	fp.close();
}

vector<CKomplex> fourier_hin(vector<CKomplex>& input)
{
	int N = input.size();
	vector<CKomplex> ergebnis(N);

	for (int n = 0; n < N; n++)
	{
		CKomplex summe(0,0);

		for (int k = 0; k < N; k++)
		{
			// Phi berechnen
            double phi = - (2.0 * M_PI * n * k) / N;

            // Mit Phi die komplexe Zahl erstellen
            CKomplex e_hoch_j_phi(phi);

			//Multiplizieren und summieren
            summe = summe + (input[k] * e_hoch_j_phi);
		}


		//	1/Wurzel(N)
		double vorfaktor = 1.0 / std::sqrt(N);
        ergebnis[n] = vorfaktor * summe;
	}
	
	return ergebnis;
}

vector<CKomplex> fourier_rueck(vector<CKomplex>& input)
{
	int N = input.size();
	vector<CKomplex> ergebnis(N);

	for (int n = 0; n < N; n++)
	{
		CKomplex summe(0,0);

		for (int k = 0; k < N; k++)
		{
			// Phi berechnen
            double phi = (2.0 * M_PI * n * k) / N;

            // Mit Phi die komplexe Zahl erstellen
            CKomplex e_hoch_j_phi(phi);

			//Multiplizieren und summieren
            summe = summe + (input[k] * e_hoch_j_phi);
		}


		//	1/Wurzel(N)
		double vorfaktor = 1.0 / std::sqrt(N);
        ergebnis[n] = vorfaktor * summe;
	}
	
	return ergebnis;
}

double maximale_abweichung(std::vector<CKomplex>& original, std::vector<CKomplex>& komprimiert)
{
	double abweichung = 0.0;

	for (size_t i = 0; i < original.size(); i++)
    {
        // Differenz zwischen Original und Rekonstruktion bilden
        CKomplex diff = original[i] + (-1.0 * komprimiert[i]); // oder falls du operator- hast: orig[i] - rek[i]
        
        // Betrag der Differenz bestimmen
        double fehler = diff.abs();

        // Wenn dieser Fehler größer ist als der bisherige Höchstwert, merken
        if (fehler > abweichung)
        {
            abweichung = fehler;
        }
    }


	return abweichung;
}