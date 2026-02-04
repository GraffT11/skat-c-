#include "Karte.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// Implementierung der Konstruktoren

Karte::Karte() {}
Karte::Karte(std::string n, std::string f, int a, int s, int fID)
    : name(n), farbe(f), augen(a), staerke(s), farbeID(fID) {}

// Implementierung der Getter

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

/**
 * @brief Ermittelt die Farb-ID unter Berücksichtigung der Trumpf-Regel.
 *
 * Weist den "Unter"-Karten eine spezielle ID zu (4), damit diese logisch
 * als Trumpf behandelt werden können und nicht ihrer aufgedruckten Farbe folgen.
 *
 * @param name Name der Karte.
 * @param farbeID Die ursprüngliche ID der Farbe (0-3).
 * @returns 4 wenn die Karte ein Unter ist, sonst die ursprüngliche farbeID.
 */

int berechneFarbeID(std::string name, int farbeID) {
    if (name == "Unter")
        return 4;
    else {
        return farbeID;
    }
}

/**
 * @brief Bestimmt den Augenwert einer Karte.
 *
 * Ordnet jedem Kartennamen die entsprechenden Punkte im Skat zu
 * (z.B. Ass=11, Zehn=10, König=4, etc.).
 *
 * @param name Name der Karte.
 * @returns Die Punktzahl der Karte oder 0 bei unbekannten Namen/Nieten.
 */

int berechneAugen(std::string name) {
    if (name == "Ass") return 11;
    if (name == "Zehn") return 10;
    if (name == "Koenig") return 4;
    if (name == "Ober") return 3;
    if (name == "Unter") return 2;
    return 0;
}

/**
 * @brief Berechnet die Spielstärke einer Karte für den Stichvergleich.
 *
 * Definiert die Hierarchie der Karten. Besondere Behandlung für "Unter",
 * deren Stärke von der Farbe abhängt (Eichel > Rot > Grün > Schellen).
 *
 * @param name Name der Karte.
 * @param farbe Farbe der Karte (relevant für Unter).
 * @returns Ein Wert, der die Stärke repräsentiert (höher ist stärker).
 */

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

// Die Funktion baut das finale Deck mit den nötigen Eigenschaften

std::vector<Karte> erstelleDeck() {
    std::vector<Karte> deck;
    std::vector<std::string> farben = {"Eichel", "Rot", "Gruen", "Schellen"};
    std::vector<std::string> namen = {"Sieben", "Acht", "Neun", "Ober", "Koenig", "Zehn", "Ass", "Unter"};

    for (int f = 0; f < 4; f++) {
        for (int n = 0; n < 8; n++) {
            // Hilfsfunktionen aufrufen um Eigenschaften zu bestimmen
            int a = berechneAugen(namen[n]);
            int s = berechneStaerke(namen[n], farben[f]);
            int fID = berechneFarbeID(namen[n], f);
            deck.push_back(Karte(namen[n], farben[f], a, s, fID));
        }
    }
    return deck;
}

void mischDeck(std::vector<Karte>& deck) {
    // Verwendung der Systemzeit als Seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::shuffle(deck.begin(), deck.end(), generator);
}