#include "karte.hpp"

Karte::Karte() : augen(0), staerke(0), farbeID(0) {}

Karte::Karte(std::string n, std::string f, int a, int s, int id)
    : name(n), farbe(f), augen(a), staerke(s), farbeID(id) {}

std::string Karte::getName() const { return name; }
std::string Karte::getFarbe() const { return farbe; }
int Karte::getAugen() const { return augen; }
int Karte::getStarke() const { return staerke; }
int Karte::getFarbeID() const { return farbeID; }

int bestimmeAugen(std::string name)
{
    {
        if (name == "Ass")
            return 11;
        if (name == "Zehn")
            return 10;
        if (name == "Koenig")
            return 4;
        if (name == "Dame")
            return 3;
        if (name == "Bube")
            return 2;
        return 0;
    }
}

int bestimmeStarke(const std::string &name)
{
    if (name == "Bube")
        return 7;
    if (name == "Ass")
        return 6;
    if (name == "Zehn")
        return 5;
    if (name == "Koenig")
        return 4;
    if (name == "Dame")
        return 3;
    if (name == "Neun")
        return 2;
    if (name == "Acht")
        return 1;
    return 0;
}

int bestimmeFarbeID(const std::string &name, int standardFarbeID)
{
    if (name == "Bube")
        return 4;
    return standardFarbeID;
}

std::vector<Karte> erstelleDeck()
{
    std::vector<Karte> deck;
    std::vector<std::string> farben = {"Kreuz", "Pik", "Herz", "Karo"};
    std::vector<std::string> namen = {"Sieben", "Acht", "Neun", "Dame", "Koenig", "Zehn", "Ass", "Bube"};

    for (int f = 0; f < 4; f++)
    {
        for (int n = 0; n < 8; n++)
        {
            int a = bestimmeAugen(namen[n]);
            int s = bestimmeStarke(staerke[])
                    // Hier käme noch deine Logik für Stärke/ID rein...
                    deck.push_back(Karte(namen[n], farben[f], a, n, f));
        }
    }
    return deck;
}