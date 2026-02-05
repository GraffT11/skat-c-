#include "SkatSpiel.hpp"

#include <iostream>

SkatSpiel::SkatSpiel() : vorhand(0) {}

void SkatSpiel::spielerAnmelden() {
    for (int i = 0; i < 3; i++) {
        std::string n;
        std::cout << "Spieler " << (i + 1) << ", wie willst du heissen? ";
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
    for (size_t i = 0; i < 32; i++) {
        if (i < 30)
            spielerListe[i / 10].bekommtKarte(deck[i]);
        else
            skat.push_back(deck[i]);
    }
}

void SkatSpiel::starten() {
    char weiterspielen;
    do {
        for (auto& s : spielerListe) {
            s.reset();
        }
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
        Spieler& s = spielerListe[static_cast<size_t>(index)];
        int wahl = fordereKartenWahl(s, stich);

        Karte k = s.spieleKarte(wahl);
        std::cout << std::endl;
        std::cout << s.getName() << " legt: " << k.getFarbe() << " " << k.getName() << "\n\n";
        stich.push_back(k);
    }

    int gewinnerRel = bestimmeStichGewinner(stich);
    int gewinnerAbs = (aktuellerSpielerIdx + gewinnerRel) % 3;

    std::cout << "--- der Stich geht an " << spielerListe[static_cast<size_t>(gewinnerAbs)].getName() << " ---\n\n";
    spielerListe[static_cast<size_t>(gewinnerAbs)].nimmtStich(stich);
    vorhand = gewinnerAbs;

    if (stichNummer == 9) {
        std::cout << std::endl;
        std::cout << std::endl;
        spielerListe[static_cast<size_t>(gewinnerAbs)].nimmtStich(skat);
    }
}

void SkatSpiel::zeigeHand(const Spieler& s) const {
    std::cout << s.getName() << " ist dran. \nDeine Hand:\n";
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
        if (wahl >= 0 && static_cast<size_t>(wahl) < s.getHand().size()) {
            if (darfKarteLegen(s.getHand()[static_cast<size_t>(wahl)], stich, s.getHand())) {
                valid = true;
            } else {
                if (stich[0].getFarbeID() == 4) {
                    std::cout << "\nDu musst Trumpf bedienen!\n\n";
                } else {
                    std::cout << "\nDu musst " << stich[0].getFarbe() << " bedienen!\n\n";
                }
            }
        } else {
            std::cout << "Ungueltige Eingabe.\n\n";
        }
    } while (!valid);
    return wahl;
}

bool SkatSpiel::darfKarteLegen(const Karte& k, const std::vector<Karte>& stich, const std::vector<Karte>& hand) {
    if (stich.empty()) return true;
    if (k.getFarbeID() == stich[0].getFarbeID()) return true;

    for (const auto& hk : hand) {
        if (hk.getFarbeID() == stich[0].getFarbeID()) return false;
    }
    return true;
}

int SkatSpiel::bestimmeStichGewinner(const std::vector<Karte>& stich) {
    int gewinner = 0;
    for (int i = 1; i < 3; i++) {
        size_t idx = static_cast<size_t>(i);
        size_t gewinnerIdx = static_cast<size_t>(gewinner);

        if (stich[idx].getFarbeID() == 4) {
            if (stich[gewinnerIdx].getFarbeID() != 4 || stich[idx].getStaerke() > stich[gewinnerIdx].getStaerke()) {
                gewinner = i;
            }
        } else if (stich[idx].getFarbeID() == stich[0].getFarbeID()) {
            if (stich[gewinnerIdx].getFarbeID() != 4 && stich[idx].getStaerke() > stich[gewinnerIdx].getStaerke()) {
                gewinner = i;
            }
        }
    }
    return gewinner;
}

void SkatSpiel::werteSpielAus() {
    for (size_t i = 0; i < skat.size(); i++) {
        std::cout << "Im Skat lag: " << skat[i].getFarbe() << " " << skat[i].getName() << " \n";
    }
    std::cout << "\n--- ENDERGEBNIS ---\n";
    int maxPunkte = 1000;
    int gewinnerIndex = -1;

    for (size_t i = 0; i < 3; ++i) {
        int p = spielerListe[i].berechnePunkte();
        std::cout << spielerListe[i].getName() << ": " << p << " Augen\n";

        if (p < maxPunkte) {
            maxPunkte = p;
            gewinnerIndex = static_cast<int>(i);
        }
    }
    std::cout << "\nGewonnen hat: " << spielerListe[static_cast<size_t>(gewinnerIndex)].getName() << "\n\n";
}