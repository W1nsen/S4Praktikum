#include "Karte.h"
#include "CZufall.h"
using namespace std;

Karte::Karte(int a , int b)
{
    setWert(a);
    setFarbe(b);
}

bool operator==(Karte K1, Karte K2)
{
    if(K1.getWert() == K2.getWert() &&
       K1.getFarbe() == K2.getFarbe())
       {
         return true;
       }
       else return false;
}

vector<Karte> Karte::KartenZiehen()
{
    CZufall obj;
    vector<Karte> hand;

    while(hand.size() < 7)
    {
        // Ziehe Karte(Zahl)
        int zahl = obj.wert(0,12);

        // Ziehe Karte(Farbe)
        int farbe = obj.wert(0,3);

        Karte temp(zahl,farbe);



        bool schonVorhanden = false;

        // check auf karte schon vorhanden
        for (int i = 0; i < hand.size(); i++)
        {
            if(temp == hand[i])
            {
                schonVorhanden = true;
                break; 
            }
        }

        
        if (schonVorhanden == false)
        {
            hand.push_back(temp);
        }
    }
    
    
    return hand;
}

void Karte::checkPaar(vector<Karte> hand, int& gefundenepaare, int& gefundenedrillinge)
{
    int paare = 0, drillinge = 0;

    vector<int> werte(13,0);

    // Häufigkeiten zählen
    for (int i = 0; i < hand.size(); i++)
    {
        int kartenWert = hand[i].getWert();
        werte[kartenWert]++; 
    }

    for (int i = 0; i < werte.size(); i++)
    {
        if(werte[i] == 3)
        {
            drillinge++;
        }
        else if(werte[i] == 2)
        {
            paare++;
        }
        else if(werte[i] == 4)
        {
            paare += 2;
        }
    }
    
    gefundenepaare = paare;
    gefundenedrillinge = drillinge;

    //cout << "Paare: " << paare << endl<< " Drillinge: " << drillinge << endl;
}