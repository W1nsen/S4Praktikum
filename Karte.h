#pragma once
#include <vector>


class Karte
{
    public:
    Karte(int a, int b);
    int getWert(){return wert;};
    void setWert(int zahl){wert = zahl;};
    int getFarbe(){return farbe;};
    void setFarbe(int farbeZahl){farbe = farbeZahl;};
    std::vector<Karte> KartenZiehen();
    void checkPaar(std::vector<Karte> hand, int& paare, int& drillinge);


    private:
    int wert;
    //Kreuz = 0  Pik = 1  Herz = 2   Karo = 3
    int farbe;

    
};
bool operator==(Karte K1, Karte K2);
