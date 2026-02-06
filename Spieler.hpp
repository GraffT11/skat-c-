#ifndef SPIELER_HPP
#define SPIELER_HPP

#include <string>
#include <vector>

#include "Karte.hpp"

/**
 * @brief Repräsentiert einen Spieler im Skatspiel.
 *
 * Diese Klasse speichert den Namen des Spielers, verwaltet die Karten auf der Hand
 * und speichert die gewonnenen Stiche.
 */

class Spieler {
   private:
    std::string name;
    std::vector<Karte> hand;
    std::vector<Karte> gewonneneStiche;

   public:
    /**
     * @brief Standardkonstruktor.
     *
     * Erstellt einen Spieler mit dem Namen "Unbekannt" und mit leeren Kartenvektoren.
     */

    Spieler();

    /**
     * @brief Konstruktor mit Namensvergabe.
     *
     * Erstellt einen Spieler mit einem spezifischen Namen.
     *
     * @param n Der gewünschte Name des Spielers.
     */

    Spieler(std::string n);

    /**
     * @brief Fügt eine Karte zur Hand des Spielers hinzu.
     *
     * Wird beim Austeilen der Karten verwendet.
     *
     * @param k Die Karte, die aufgenommen werden soll.
     */

    void bekommtKarte(const Karte& k);

    /**
     * @brief Spielt eine Karte aus der Hand.
     *
     * Entfernt die Karte am angegebenen Index aus der Hand und gibt sie zurück.
     *
     * @param index Der Index der zu spielenden Karte in der Hand.
     * @returns Die Karte, die ausgespielt wurde.
     * @pre Der Index sollte innerhalb der Grenzen des Hand-Vektors liegen.
     */

    Karte spieleKarte(int index);

    /**
     * @brief Nimmt einen gewonnenen Stich an sich.
     *
     * Fügt alle Karten des Stichs dem Stapel der gewonnenen Stiche hinzu.
     *
     * @param stich Vektor mit den drei Karten des Stichs.
     */

    void nimmtStich(const std::vector<Karte>& stich);

    /**
     * @brief Berechnet die aktuelle Punktzahl des Spielers.
     *
     * Summiert die Augen aller Karten in den gewonnenen Stichen.
     *
     * @returns Die Summe der Augen (0 bis 120).
     */

    int berechnePunkte() const;

    /**
     * @brief Gibt den Namen des Spielers zurück.
     * @returns Der Name als String.
     */

    std::string getName() const;

    /**
     * @brief Gibt Zugriff auf die aktuelle Hand des Spielers.
     *
     * Wird verwendet, um die Hand anzuzeigen oder Regeln zu prüfen.
     *
     * @returns Konstante Referenz auf den Vektor der Handkarten.
     */

    const std::vector<Karte>& getHand() const;

    /**
     * @brief Setzt die Punkte zurück für die nächste Runde.
     *
     * Damit die Punkte aller Runden nicht insgesamt zusammengerechnet werden,
     * ist es nötig sie vor jeder neuen Runde zurückzusetzen.
     */

    void reset();
};

#endif