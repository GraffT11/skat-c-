#include "SkatSpiel.hpp"

#include <algorithm>
#include <iostream>

// Konstruktor
SkatSpiel::SkatSpiel() : vorhand(0) {}

void SkatSpiel::starten() {
    char weiterspielen;
    do {
        erstelleUndMischeDeck();
        verteileKarten();
        spieleRunde();
        werteSpielAus();

        vorhand = (vorhand + 1) % 3;

        std::cout << "Noch eine Runde? (j/n): ";
        std::cin >> weiterspielen;
    } while (weiterspielen == 'j');
}

void SkatSpiel::spieleRunde() {
    for (int i = 0; i < 10; i++) {
        spieleStich(i);
    }
}

void SkatSpiel::spieleStich(int stichNummer) {
    std::vector<Karte> stich;
    int aktuellerSpielerIdx = vorhand;

    for (int i = 0; i < 3; i++) {
        int index = (aktuellerSpielerIdx + i) % 3;
        Spieler& s = spielerListe[index];

        int kartenIndex = fordereKartenWahl(s, stich);

        Karte k = s.spieleKarte(kartenIndex);
        std::cout << s.getName() << " legt: " << k.getFarbe() << " " << k.getName() << "\n";
        stich.push_back(k);
    }

    // Auswertung wer den Stich bekommt
    int gewinnerRelativ = bestimmeStichGewinner(stich);
    int gewinnerAbsolut = (aktuellerSpielerIdx + gewinnerRelativ) % 3;

    std::cout << "Stich geht an: " << spielerListe[gewinnerAbsolut].getName() << "\n\n";

    spielerListe[gewinnerAbsolut].nimmtStich(stich);

    // WICHTIG: Der Gewinner kommt beim nächsten Stich raus!
    vorhand = gewinnerAbsolut;

    // WICHTIG FÜR AUFGABE: Wenn es der letzte Stich war (Nr. 9), kriegt er den Skat!
    if (stichNummer == 9) {
        std::cout << "Der letzte Stich nimmt den Skat mit!\n";
        spielerListe[gewinnerAbsolut].nimmtStich(skat);
    }
}

// Hier fixen wir dein Problem mit der Buchstabeneingabe (Robustheit)
int SkatSpiel::fordereKartenWahl(Spieler& s, const std::vector<Karte>& aktuellerStich) {
    int wahl = -1;
    bool zugGueltig = false;

    do {
        // Hand ausgeben (könnte man auch in eine eigene Void-Funktion packen "zeigeHand")
        std::cout << s.getName() << " ist dran. Deine Hand:\n";
        const auto& hand = s.getHand();
        for (size_t i = 0; i < hand.size(); ++i) {
            std::cout << "(" << i << ") " << hand[i].getFarbe() << " " << hand[i].getName() << "\n";
        }

        std::cout << "Karte waehlen: ";
        std::cin >> wahl;

        // FEHLERBEHANDLUNG (Source 7 Problem):
        if (std::cin.fail()) {
            std::cin.clear();             // Fehlerzustand löschen
            std::cin.ignore(1000, '\n');  // Eingabepuffer leeren
            std::cout << "Bitte eine ZAHL eingeben!\n";
            continue;
        }

        // Logik-Prüfung
        if (wahl >= 0 && wahl < hand.size()) {
            if (darfKarteLegen(hand[wahl], aktuellerStich, hand)) {
                zugGueltig = true;
            } else {
                std::cout << "Du musst bedienen! \n";
            }
        } else {
            std::cout << "Ungueltiger Index.\n";
        }

    } while (!zugGueltig);

    return wahl;
}