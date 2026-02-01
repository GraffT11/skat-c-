#ifndef KARTE_HPP
#define KARTE_HPP

#include <string>
#include <vector>

/**
 * @brief Repräsentiert eine einzelne Spielkarte im Skatspiel.
 *
 * Diese Klasse speichert die Eigenschaften einer Karte (Name, Farbe)
 * sowie die spielrelevanten Werte (Augen, Stärke) und ermöglicht den Zugriff darauf.
 */

class Karte {
   private:
    std::string name;
    std::string farbe;
    int augen;
    int staerke;
    int farbeID;

   public:
       /**
     * @brief Standardkonstruktor.
     *
     * Erstellt eine leere Karte ohne initialisierte Werte.
     */

    Karte();

    /**
     * @brief Initialisierender Konstruktor.
     *
     * Erstellt eine Karte mit allen notwendigen Eigenschaften für das Spiel.
     *
     * @param n Name der Karte (z.B. "Ass", "Koenig")
     * @param f Farbe der Karte (z.B. "Rot", "Eichel")
     * @param a Punktwert (Augen) der Karte für die Abrechnung
     * @param s Numerische Spielstärke für den Stichvergleich
     * @param fID Numerische ID der Farbe (wichtig für Bedienungspflicht)
     */

    Karte(std::string n, std::string f, int a, int s, int fID);

    /**
     * @brief Gibt den Namen der Karte zurück.
     * @returns Name als String (z.B. "Unter")
     */

    std::string getName() const;

    /**
     * @brief Gibt die Farbe der Karte zurück.
     * @returns Farbe als String (z.B. "Gruen")
     */

    std::string getFarbe() const;

    /**
     * @brief Gibt die Augen (Punktzahl) der Karte zurück.
     * @returns Punktzahl zwischen 0 und 11
     */

    int getAugen() const;

    /**
     * @brief Gibt die Spielstärke der Karte zurück.
     *
     * Die Stärke wird verwendet, um zu ermitteln, welche Karte einen Stich gewinnt.
     * @returns Integer-Wert der Stärke
     */

    int getStaerke() const;

    /**
     * @brief Gibt die Farb-ID zurück.
     *
     * Diese ID wird benötigt, um Farben logisch zu trennen. Unter haben hierbei oft
     * eine gesonderte ID, da sie als Trumpf gelten.
     * @returns Integer ID der Farbe
     */

    int getFarbeID() const;
};

/**
 * @brief Erstellt ein vollständiges Skat-Deck.
 *
 * Generiert einen Vektor mit allen 32 Karten (8 Karten je 4 Farben)
 * und initialisiert deren Werte (Augen, Stärke) korrekt.
 *
 * @returns Ein std::vector, der 32 Karten-Objekte enthält.
 */

std::vector<Karte> erstelleDeck();

/**
 * @brief Mischt ein gegebenes Kartendeck.
 *
 * Verwendet einen Zufallsgenerator (Mersenne Twister), um die Reihenfolge
 * der Karten im Vektor zufällig zu verändern.
 *
 * @param deck Referenz auf den Vektor mit Karten, der gemischt werden soll.
 */

void mischDeck(std::vector<Karte>& deck);

/**
 * @brief Berechnet die Punkte eines Kartenstapels.
 *
 * Summiert die Augen aller Karten in einem Vektor auf. Wird oft für
 * den Skat oder die Stiche am Ende des Spiels verwendet.
 *
 * @param stapel Vektor der Karten, deren Punkte gezählt werden sollen.
 * @returns Summe der Augen aller Karten im Stapel.
 */

int berechneSkatPunkte(const std::vector<Karte>& stapel);

#endif