#include <iostream>
#include "Vektor.h" // Achte auf den exakten Dateinamen

int main() {
    try {
        // 1. Vektoren anlegen (Dimension 3)
        CMyVektor v1(3);
        CMyVektor v2(3);

        // 2. Werte setzen
        v1.SetWert(1.0, 0);
        v1.SetWert(2.0, 1);
        v1.SetWert(2.0, 2); // Vektor (1, 2, 2)

        v2.SetWert(5.0, 0);
        v2.SetWert(0.0, 1);
        v2.SetWert(-1.0, 2); // Vektor (5, 0, -1)

        // 3. Test: Länge berechnen
        // Erwartet: sqrt(1^2 + 2^2 + 2^2) = sqrt(9) = 3
        std::cout << "Laenge von v1: " << v1.CalcVektorLaenge() << std::endl;

        // 4. Test: Skalare Multiplikation
        // Erwartet: 2 * (1, 2, 2) = (2, 4, 4)
        CMyVektor vSkalar = 2.0 * v1;
        std::cout << "Skalierung (2*v1) Komponente 0: " << vSkalar.GetWert(0) << " (erwartet: 2)" << std::endl;

        // 5. Test: Addition
        // Erwartet: (1,2,2) + (5,0,-1) = (6,2,1)
        CMyVektor vSumme = v1 + v2;
        std::cout << "Summe Komponente 0: " << vSumme.GetWert(0) << " (erwartet: 6)" << std::endl;
        std::cout << "Summe Komponente 2: " << vSumme.GetWert(2) << " (erwartet: 1)" << std::endl;

        // 6. Test: Fehlerfall (unterschiedliche Dimensionen)
        CMyVektor vFehler(2);
        std::cout << "Proviziere Fehler..." << std::endl;
        CMyVektor vTest = v1 + vFehler; 

    }
    catch (const char* msg) {
        std::cerr << "Fehler gefangen: " << msg << std::endl;
    }

    return 0;
}
