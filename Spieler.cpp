#include "Spieler.hpp"

Spieler::Spieler() : name("Unbekannt") {}

Spieler::Spieler(std::string n) : name(n) {}

void Spieler::bekommtKarte(const Karte& k) {
    hand.push_back(k);
}

Karte Spieler::spieleKarte(int index) {
    if (index < 0 || index >= hand.size()) {
        return hand[0];
    }
    Karte k = hand[index];
    hand.erase(hand.begin() + index);
    return k;
}

void Spieler::nimmtStich(const std::vector<Karte>& stich) {
    for (const auto& k : stich) {
        gewonneneStiche.push_back(k);
    }
}

int Spieler::berechnePunkte() const {
    int summe = 0;
    for (const auto& k : gewonneneStiche) {
        summe += k.getAugen();
    }
    return summe;
}

std::string Spieler::getName() const {
    return name;
}

const std::vector<Karte>& Spieler::getHand() const {
    return hand;
}

void Spieler::reset() {
    gewonneneStiche.clear();
    hand.clear();
}
