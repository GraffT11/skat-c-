#include <iostream>
#include <string>
#include <vector>

#include "Karte.hpp"
#include "SkatSpiel.hpp"
#include "Spieler.hpp"

/**
 * @brief Hauptprogramm für das Skatspiel.
 *
 * Initialisiert das Spielobjekt, führt die Abfragen der Spielernamen durch und
 * startet die Spielschleife. Gibt eine kurze Begrüßung aus.
 *
 * @returns 0 bei erfolgreicher Ausführung.
 */
int main() {
    std::cout << "Willkommen zum Skatspiel. Gespielt wird im Ramsch, das heisst: jeder gegen Jeden, Unter sind Trumpf "
                 "und der Spieler, mit den wenigsten Punkten gewinnt das Spiel."
              << std::endl;
    std::cout << "Unter stechen in der Reihenfolge: Eichel > Rot > Gruen > Schellen." << std::endl;
    std::cout << "Gut Blatt!\n" << std::endl;

    // 1. Das Spiel-Objekt erstellen
    SkatSpiel spiel;

    // 2. Die Namen der Spieler abfragen
    spiel.spielerAnmelden();

    // 3. Die eigentliche Spiel-Schleife starten
    spiel.starten();

    return 0;
}