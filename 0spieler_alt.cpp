#include "spieler.hpp"

Spieler::Spieler() : name("Unbekannt") {}

Spieler::Spieler(std::string n) : name(n) {}

void Spieler::bekommtKarte(const Karte &k)
{
    hand.push_back(k); // Fügt eine Karte zur Hand hinzu
}

Karte Spieler::spieleKarte(int index)
{
    // Fehlerbehandlung: Prüfen ob der Index gültig ist
    if (index < 0 || index >= static_cast<int>(hand.size()))
    {
        return Karte();
    }
    Karte k = hand[index];
    hand.erase(hand.begin() + index); // Karte aus der Hand entfernen
    return k;
}

void Spieler::nimmtStich(const std::vector<Karte> &stich)
{
    for (const auto &k : stich)
    {
        gewonneneStiche.push_back(k); // Karten dem Punktekonto hinzufügen
    }
}

int Spieler::berechnePunkte() const
{
    int summe = 0;
    for (const auto &k : gewonneneStiche)
    {
        summe += k.getAugen(); // Augen der gewonnenen Karten summieren
    }
    return summe;
}

std::string Spieler::getName() const { return name; }

const std::vector<Karte> &Spieler::getHand() const { return hand; }