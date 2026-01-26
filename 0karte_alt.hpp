#ifndef KARTE_HPP
#define KARTE_HPP

#include <string>
#include <vector>

class Karte
{
private:
    std::string name;
    std::string farbe;
    int augen;
    int staerke;
    int farbeID;

public:
    Karte() {}
    Karte(std::string n, std::string f, int a, int s, int id)
    {
        name = n;
        farbe = f;
        augen = a;
        staerke = s;
        farbeID = id;
    }
    std::string getName() const
    {
        return name;
    }
    std::string getFarbe() const
    {
        return farbe;
    }
    int getAugen() const
    {
        return augen;
    }
    int getStarke() const
    {
        return staerke;
    }
    int getFarbeID() const
    {
        return farbeID;
    }
};

/**
 * @class Karte
 * @brief Repräsentiert eine einzelne Skat-Karte.
 */
class Karte
{
private:
    std::string name;
    std::string farbe;
    int augen;
    int staerke;
    int farbeID;

public:
    Karte();

    /**
     * @brief Konstruktor für eine Karte.
     * @param n Name der Karte (z.B. "Ass")
     * @param f Farbe der Karte (z.B. "Eichel")
     * @param a Punktwert (Augen)
     * @param s Spielstärke für den Vergleich
     * @param id ID zur Farberkennung
     */
    Karte(std::string n, std::string f, int a, int s, int id);

    // Prototypen der Getter
    std::string getName() const;
    std::string getFarbe() const;
    int getAugen() const;
    int getStarke() const;
    int getFarbeID() const;
};

/**
 * @brief Erstellt ein vollständiges Skat-Deck mit 32 Karten.
 * @returns Ein Vektor mit allen initialisierten Karten.
 */
std::vector<Karte> erstelleDeck();

#endif