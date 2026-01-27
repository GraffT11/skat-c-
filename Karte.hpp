#ifndef KARTE_HPP
#define KARTE_HPP

#include <string>
#include <vector>

class Karte {
   private:
    std::string name;
    std::string farbe;
    int augen;
    int staerke;
    int farbeID;

   public:
    Karte();
    // Der Konstruktor nimmt ALLES entgegen und speichert es
    Karte(std::string n, std::string f, int a, int s, int fID);

    // Getter geben einfach nur den gespeicherten Wert zurück
    std::string getName() const;
    std::string getFarbe() const;
    int getAugen() const;
    int getStaerke() const;
    int getFarbeID() const;
};

/**
 * @brief Konstruktor für eine Karte.
 * @param n Name der Karte
 * @param f Farbe der Kart
 * @param a Punktwert
 * @param s Spielstärke für den Vergleich
 * @param fID ID um Buben die Trumpffarbe zuweisen zu können
 */

/**
 * @brief Erstellt ein vollständiges Skat-Deck mit 32 Karten
 * @returns Ein Vektor mit allen Karten
 */
std::vector<Karte> erstelleDeck();

#endif