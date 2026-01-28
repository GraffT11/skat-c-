#ifndef SPIELER_HPP
#define SPIELER_HPP

#include <string>
#include <vector>

#include "Karte.hpp"

/**
 * @class Spieler
 * @brief Verwaltet die Handkarten und die gewonnenen Stiche eines Spielers.
 */

class Spieler {
   private:
    std::string name;
    std::vector<Karte> hand;
    std::vector<Karte> gewonneneStiche;

   public:
    Spieler();

    /**
     * @brief Konstruktor mit Namensvergabe.
     * @param n Der Name des Spielers.
     */
    Spieler(std::string n);

    // Methoden zur Spielsteuerung
    void bekommtKarte(const Karte& k);
    Karte spieleKarte(int index);
    void nimmtStich(const std::vector<Karte>& stich);

    // Getter und Auswertung
    int berechnePunkte() const;
    std::string getName() const;
    const std::vector<Karte>& getHand() const;
};

#endif