#include "SkatSpiel.hpp"

#include <iostream>

SkatSpiel::SkatSpiel() : vorhand(0) {}

void SkatSpiel::spielerAnmelden() {
    for (int i = 0; i < 3; i++) {
        std::string n;
        std::cout << "Spieler " << (i + 1) << ", Name: ";
        std::cin >> n;
        spielerListe.push_back(Spieler(n));
    }
    std::cout << std::endl;
}

void SkatSpiel::erstelleUndMischeDeck() {
    deck = erstelleDeck();
    mischDeck(deck);
}

void SkatSpiel::verteileKarten() {
    skat.clear();
    // Neue Handkarten fuer alle (Logik vereinfacht fuer Ramsch)
    for (int i = 0; i < 32; i++) {
        if (i < 30)
            spielerListe[i / 10].bekommtKarte(deck[i]);
        else
            skat.push_back(deck[i]);
    }
}

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
        int wahl = fordereKartenWahl(s, stich);

        Karte k = s.spieleKarte(wahl);
        std::cout << s.getName() << " legt: " << k.getFarbe() << " " << k.getName() << "\n\n";
        stich.push_back(k);
    }

    int gewinnerRel = bestimmeStichGewinner(stich);
    int gewinnerAbs = (aktuellerSpielerIdx + gewinnerRel) % 3;

    std::cout << "--- der Stich geht an " << spielerListe[gewinnerAbs].getName() << " ---\n\n";
    spielerListe[gewinnerAbs].nimmtStich(stich);
    vorhand = gewinnerAbs;  // Gewinner kommt raus

    // Letzter Stich kriegt den Skat [cite: 752]
    if (stichNummer == 9) {
        std::cout << "Der Skat geht an " << spielerListe[gewinnerAbs].getName() << "!\n";
        spielerListe[gewinnerAbs].nimmtStich(skat);
    }
}

// --- Aufgeteilte Hilfsfunktionen (<20 Zeilen) ---

void SkatSpiel::zeigeHand(const Spieler& s) const {
    std::cout << s.getName() << " ist dran. \n Deine Hand:\n";
    std::cout << std::endl;
    const auto& hand = s.getHand();
    for (size_t k = 0; k < hand.size(); k++) {
        std::cout << "(" << k << ") " << hand[k].getFarbe() << " " << hand[k].getName() << "\n";
    }
}

int SkatSpiel::leseZahlEingabe() {
    int wahl;
    std::cout << std::endl;
    std::cout << "Welche Karte willst du spielen? ";
    std::cin >> wahl;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return -1;
    }
    return wahl;
}

int SkatSpiel::fordereKartenWahl(Spieler& s, const std::vector<Karte>& stich) {
    int wahl = -1;
    bool valid = false;
    do {
        zeigeHand(s);
        wahl = leseZahlEingabe();
        if (wahl >= 0 && wahl < s.getHand().size()) {
            if (darfKarteLegen(s.getHand()[wahl], stich, s.getHand())) {
                valid = true;
            } else {
                if (stich[0].getFarbeID() == 4) {
                    std::cout << "Du musst Trumpf bedienen!";
                } else {
                    std::cout << "Du musst " << stich[0].getFarbe() << " bedienen!\n\n";
                }
            }
        } else {
            std::cout << "Ungueltige Eingabe.\n\n";
        }
    } while (!valid);
    return wahl;
}

// --- Regellogik ---

bool SkatSpiel::darfKarteLegen(const Karte& k, const std::vector<Karte>& stich, const std::vector<Karte>& hand) {
    if (stich.empty()) return true;
    if (k.getFarbeID() == stich[0].getFarbeID()) return true;

    // Pruefen ob Farbe vorhanden
    for (const auto& hk : hand) {
        if (hk.getFarbeID() == stich[0].getFarbeID()) return false;
    }
    return true;
}

int SkatSpiel::bestimmeStichGewinner(const std::vector<Karte>& stich) {
    int gewinner = 0;
    for (int i = 1; i < 3; i++) {
        // Trumpf (ID 4 = Unter) sticht Nicht-Trumpf
        if (stich[i].getFarbeID() == 4) {
            if (stich[gewinner].getFarbeID() != 4 || stich[i].getStaerke() > stich[gewinner].getStaerke()) {
                gewinner = i;
            }
        }
        // Farbe bedient und hoeher
        else if (stich[i].getFarbeID() == stich[0].getFarbeID()) {
            if (stich[gewinner].getFarbeID() != 4 && stich[i].getStaerke() > stich[gewinner].getStaerke()) {
                gewinner = i;
            }
        }
    }
    return gewinner;
}

void SkatSpiel::werteSpielAus() {
    std::cout << "--- ENDERGEBNIS ---\n";
    int maxPunkte = -1;
    int verliererIndex = -1;

    for (int i = 0; i < 3; ++i) {
        int p = spielerListe[i].berechnePunkte();
        std::cout << spielerListe[i].getName() << ": " << p << " Augen\n";

        // Simpler Vergleich fuer Ramsch-Verlierer
        if (p > maxPunkte) {
            maxPunkte = p;
            verliererIndex = i;
        }
    }
    std::cout << "\nVerloren hat: " << spielerListe[verliererIndex].getName() << "\n\n";
}