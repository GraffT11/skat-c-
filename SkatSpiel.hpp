#ifndef SKATSPIEL_HPP
#define SKATSPIEL_HPP

#include <vector>

#include "Karte.hpp"
#include "Spieler.hpp"

class SkatSpiel {
   private:
    std::vector<Spieler> spielerListe;
    std::vector<Karte> skat;
    std::vector<Karte> deck;
    int vorhand;  // Wer kommt raus?

    // Private Hilfsmethoden (Interne Logik)
    void erstelleUndMischeDeck();
    void verteileKarten();
    void spieleRunde();                 // Spielt EINE komplette Runde (10 Stiche)
    void spieleStich(int stichNummer);  // Spielt EINEN Stich (3 Karten)
    void werteSpielAus();               // Zählt Punkte und bestimmt Verlierer

    // Hilfsfunktionen für Regeln
    int bestimmeStichGewinner(const std::vector<Karte>& stich);
    bool darfKarteLegen(const Karte& karte, const std::vector<Karte>& stich, const std::vector<Karte>& hand);

    // Eingabe-Helfer (Löst auch dein Endlosschleifen-Problem!)
    int fordereKartenWahl(Spieler& s, const std::vector<Karte>& aktuellerStich);

   public:
    SkatSpiel();
    void spielerAnmelden();
    void starten();
};

#endif