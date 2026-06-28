#include "CZufall.h"
using namespace std;

int CZufall::wert(int a, int b)
{
    int range = b - a + 1;

    int erg = (rand() % range) + a;

    return erg;
}

void CZufall::initialisiere(int s)
{
    srand(s);
}

void CZufall::test(int a, int b , int N)
{
    int range = b - a + 1;

    vector<int> haufigkeiten(range,0);

    for (int i = 0; i < N; i++)
    {
        int randomZahl = wert(a,b);

        haufigkeiten[randomZahl - a]++;
    }
    
    for (int i = 0; i < range; i++)
    {
        cout << "Wert " << (i + a) << " kommt " << haufigkeiten[i] << " auf" << endl;
    }
    
}

void CZufall::test_falsch(int a, int b, int N)
{
    int range = b - a + 1;

    vector<int> haufigkeiten(range,0);

    for (int i = 0; i < N; i++)
    {
        initialisiere(time(NULL));
        int randomZahl = wert(a,b);

        haufigkeiten[randomZahl - a]++;
    }
    
    for (int i = 0; i < range; i++)
    {
        cout << "Wert " << (i + a) << " kommt " << haufigkeiten[i] << " auf" << endl;
    }
}