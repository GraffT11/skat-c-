#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "Karte.hpp"
#include "SkatSpiel.hpp"
#include "Spieler.hpp"

int main() {
    std::cout << "Willkommen zum Skatspiel. Gespielt wird im Ramsch, das heißt: jeder gegen Jeden, Unter sind Trumpf "
                 "und der Spieler, mit den meisten Punkten verliert das Spiel."
              << std::endl;
    std::cout << "Buben stechen in der Reihenfolge: Eichel > Rot > Gruen > Schellen." << std::endl;
    std::cout << "Gut Blatt!\n" << std::endl;

    // 1. Das Spiel-Objekt erstellen
    SkatSpiel spiel;

    // 2. Die Namen der Spieler abfragen
    spiel.spielerAnmelden();

    // 3. Die eigentliche Spiel-Schleife starten
    spiel.starten();

    return 0;
}