#ifndef SKATSPIEL_HPP
#define SKATSPIEL_HPP

#include <string>
#include <vector>

#include "Karte.hpp"
#include "Spieler.hpp"

/**
 * @brief Hauptklasse für die Steuerung des Skatspiels (Ramsch-Modus).
 *
 * Verwaltet den Spielablauf, die Spieler, das Deck und die Regelprüfung.
 */
class SkatSpiel {
   private:
    std::vector<Spieler> spielerListe;
    std::vector<Karte> skat;
    std::vector<Karte> deck;
    int vorhand;  // Index des Spielers, der rauskommt

    // --- Private Hilfsmethoden (Interne Logik) ---

    /**
     * @brief Erstellt ein neues Deck und mischt es.
     *
     * Nutzt die globalen Funktionen aus Karte.hpp.
     */
    void erstelleUndMischeDeck();

    /**
     * @brief Verteilt die 32 Karten an die 3 Spieler und den Skat.
     *
     * Jeder Spieler erhält 10 Karten, 2 gehen in den Skat.
     */
    void verteileKarten();

    /**
     * @brief Führt eine komplette Spielrunde durch.
     *
     * Ruft 10-mal spieleStich auf.
     */
    void spieleRunde();

    /**
     * @brief Spielt einen einzelnen Stich (3 Karten).
     *
     * Fordert die Spieler nacheinander auf, eine Karte zu legen, ermittelt den Gewinner
     * und weist den Stich zu.
     *
     * @param stichNummer Die Nummer des aktuellen Stichs (0-9). Wichtig für die Skat-Vergabe am Ende.
     */
    void spieleStich(int stichNummer);

    /**
     * @brief Wertet das Spiel am Ende aus.
     *
     * Berechnet die Punkte aller Spieler, zeigt den Skat an und ermittelt den Verlierer (Ramsch).
     */
    void werteSpielAus();

    // --- Hilfsfunktionen für Regeln ---

    /**
     * @brief Ermittelt den Gewinner eines Stichs.
     *
     * Prüft Bedienpflicht, Trumpf (Unter) und Kartenstärke.
     *
     * @param stich Vektor der 3 gespielten Karten.
     * @returns Der Index (0-2) des Gewinners relativ zum Spieler, der rausgekommen ist.
     */
    int bestimmeStichGewinner(const std::vector<Karte>& stich);

    /**
     * @brief Prüft, ob eine gewählte Karte regelkonform gelegt werden darf.
     *
     * Überprüft insbesondere die Bedienpflicht (Farbe bekennen).
     *
     * @param karte Die Karte, die gespielt werden soll.
     * @param stich Der aktuelle Stich (um die geforderte Farbe zu sehen).
     * @param hand Die gesamte Hand des Spielers (um zu prüfen, ob er bedienen könnte).
     * @returns true, wenn der Zug gültig ist, sonst false.
     */
    bool darfKarteLegen(const Karte& karte, const std::vector<Karte>& stich, const std::vector<Karte>& hand);

    // --- Eingabe-Helfer ---

    /**
     * @brief Gibt die Karten eines Spielers auf der Konsole aus.
     *
     * @param s Der Spieler, dessen Hand angezeigt werden soll.
     */
    void zeigeHand(const Spieler& s) const;

    /**
     * @brief Liest eine Ganzzahl von der Konsole ein.
     *
     * Behandelt Eingabefehler (z.B. Buchstaben statt Zahlen) robust.
     *
     * @returns Die eingelesene Zahl oder -1 bei Fehler.
     */
    int leseZahlEingabe();

    /**
     * @brief Führt den Dialog zur Kartenwahl mit einem Spieler.
     *
     * Zeigt die Hand, fordert zur Eingabe auf und wiederholt dies so lange,
     * bis eine gültige (regelkonforme) Karte gewählt wurde.
     *
     * @param s Referenz auf den Spieler, der dran ist.
     * @param aktuellerStich Vektor der bereits liegenden Karten (für Regelprüfung).
     * @returns Der Index der gewählten Karte in der Hand.
     */
    int fordereKartenWahl(Spieler& s, const std::vector<Karte>& aktuellerStich);

   public:
    /**
     * @brief Standardkonstruktor.
     *
     * Initialisiert das Spiel, setzt 'vorhand' auf 0.
     */
    SkatSpiel();

    /**
     * @brief Fragt die Namen der drei Spieler ab und erstellt die Spieler-Objekte.
     */
    void spielerAnmelden();

    /**
     * @brief Startet die Hauptschleife des Spiels.
     *
     * Steuert den Ablauf: Mischen -> Verteilen -> Spielen -> Auswerten -> Wiederholen.
     */
    void starten();

    /**
     * @brief Gibt den Inhalt des Skats als String zurück (Debug/Info).
     * @returns String-Repräsentation des Skats.
     */
    std::string getSkat() const;
};

#endif