#include "Karte.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// Konstruktor: Nimmt Werte und packt sie in die Variablen (mit :)
Karte::Karte() {}
Karte::Karte(std::string n, std::string f, int a, int s, int fID)
    : name(n), farbe(f), augen(a), staerke(s), farbeID(fID) {}

std::string Karte::getName() const {
    return name;
}
std::string Karte::getFarbe() const {
    return farbe;
}
int Karte::getAugen() const {
    return augen;
}
int Karte::getStaerke() const {
    return staerke;
}
int Karte::getFarbeID() const {
    return farbeID;
}

int berechneFarbeID(std::string name, int farbeID) {
    if (name == "Unter")
        return 4;
    else {
        return farbeID;
    }
}

int berechneAugen(std::string name) {
    if (name == "Ass") return 11;
    if (name == "Zehn") return 10;
    if (name == "Koenig") return 4;
    if (name == "Ober") return 3;
    if (name == "Unter") return 2;
    return 0;
}

int berechneStaerke(std::string name, std::string farbe) {
    if (name == "Unter") {
        if (farbe == "Eichel")
            return 12;
        else if (farbe == "Rot")
            return 11;
        else if (farbe == "Gruen")
            return 10;
        else
            return 9;
    }
    if (name == "Ass") return 7;
    if (name == "Zehn") return 6;
    if (name == "Koenig") return 5;
    if (name == "Ober") return 4;
    if (name == "Neun") return 3;
    if (name == "Acht") return 2;
    if (name == "Sieben") return 1;
    return 0;
}

std::vector<Karte> erstelleDeck() {
    std::vector<Karte> deck;
    std::vector<std::string> farben = {"Eichel", "Rot", "Gruen", "Schellen"};
    std::vector<std::string> namen = {"Sieben", "Acht", "Neun", "Ober", "Koenig", "Zehn", "Ass", "Unter"};

    for (int f = 0; f < 4; f++) {
        for (int n = 0; n < 8; n++) {
            int a = berechneAugen(namen[n]);
            int s = berechneStaerke(namen[n], farben[f]);
            int fID = berechneFarbeID(namen[n], f);
            deck.push_back(Karte(namen[n], farben[f], a, s, fID));
        }
    }
    return deck;
}

void mischDeck(std::vector<Karte>& deck) {
    std::random_device rd;
    unsigned seed = rd();
    std::default_random_engine generator(seed);
    std::shuffle(deck.begin(), deck.end(), generator);
}

int berechneSkatPunkte(const std::vector<Karte>& stapel) {
    int summe = 0;
    for (const auto& k : stapel) {
        summe += k.getAugen();
    }
    return summe;
}