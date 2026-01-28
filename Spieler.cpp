#include "Spieler.hpp"

#include <iostream>
#include <string>
#include <vector>

Spieler::Spieler() : name("Unbekannt") {}

Spieler::Spieler(std::string n) : name(n) {}

void Spieler::bekommtKarte(const Karte& k) {
    hand.push_back(k);  // Fügt eine Karte zur Hand hinzu
}

Karte Spieler::spieleKarte(int index) {
    // Fehlerbehandlung: Prüfen ob der Index gültig ist
    if (index < 0 || index >= hand.size()) {
        return hand[0];
    }
    Karte k = hand[index];
    hand.erase(hand.begin() + index);  // Karte aus der Hand entfernen
    return k;
}

void Spieler::nimmtStich(const std::vector<Karte>& stich) {
    for (const auto& k : stich) {
        gewonneneStiche.push_back(k);  // Karten dem Punktekonto hinzufügen
    }
}

int Spieler::berechnePunkte() const {
    int summe = 0;
    for (const auto& k : gewonneneStiche) {
        summe += k.getAugen();  // Augen der gewonnenen Karten summieren
    }
    return summe;
}

std::string Spieler::getName() const {
    return name;
}

const std::vector<Karte>& Spieler::getHand() const {
    return hand;
}

bool darfKarteLegen(Karte karte, std::vector<Karte> stich, std::vector<Karte> hand) {
    if (stich.size() == 0) {
        return true;
    } else if (karte.getFarbeID() == stich[0].getFarbeID()) {
        return true;
    } else {
        for (int i = 0; i < hand.size(); i++) {
            if (hand[i].getFarbeID() == stich[0].getFarbeID()) {
                return false;
            }
        }
        return true;
    }
}

// Man schaut, wer am Ende den Stich gewinnt

int bestimmeStichGewinner(std::vector<Karte> stich) {
    int gewinnerIndex = 0;

    for (int i = 1; i < 3; i++) {
        if (stich[i].getFarbeID() == 4) {
            if (stich[gewinnerIndex].getFarbeID() != 4) {
                gewinnerIndex = i;
            } else if (stich[i].getStaerke() > stich[gewinnerIndex].getStaerke()) {
                gewinnerIndex = i;
            }
        } else if (stich[i].getFarbeID() == stich[0].getFarbeID()) {
            if (stich[gewinnerIndex].getFarbeID() != 4) {
                if (stich[i].getStaerke() > stich[gewinnerIndex].getStaerke()) {
                    gewinnerIndex = i;
                }
            }
        }
    }
    return gewinnerIndex;
}