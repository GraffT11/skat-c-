#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "Karte.hpp"
#include "Spieler.hpp"

// Der Anfang des Spiels mit einer kleinen Einleitung

int main() {
    std::cout << "Willkommen zum Skatspiel." << std::endl;
    std::cout << std::endl;
    std::cout << "Gespielt wird im Ramsch. Das heisst: der Spieler, mit den meisten "
                 "Punkten, verliert das Spiel.\nAchtung: Buben sind natuerlich immer Trumpf und nicht die angezeigt "
                 "Farbe!\n Auch wichtig: um eine Karte zu legen, muss man die Zahl vor der eigentliche Karte schreiben "
                 "und keinerlei Buchstaben. \nGut Blatt :)"
              << std::endl;
    std::cout << std::endl;

    // Die Spieler werden nach ihren Namen gefragt

    std::string namen[3];
    for (int i = 0; i < 3; i++) {
        std::cout << "Spieler " << (i + 1) << ", wie moechtest du heissen? ";
        std::cin >> namen[i];
    }
    std::cout << std::endl;

    char weiterspielen;

    int startSpielerErsteRunde = 0;

    do {
        std::vector<Karte> deck = erstelleDeck();
        mischDeck(deck);
        std::vector<Karte> skat;

        std::vector<Spieler> spielerListe;
        spielerListe.push_back(Spieler(namen[0]));
        spielerListe.push_back(Spieler(namen[1]));
        spielerListe.push_back(Spieler(namen[2]));

        for (int i = 0; i < 32; i++) {
            if (i < 30) {
                spielerListe[i / 10].bekommtKarte(deck[i]);
            } else {
                skat.push_back(deck[i]);
            }
        }

        int vorhand = startSpielerErsteRunde;
        std::vector<std::string> positionen = {"Vorhand", "Mittelhand", "Hinterhand"};

        for (int s = 0; s < 10; s++) {
            std::vector<Karte> stich;
            for (int i = 0; i < 3; i++) {
                int aktuellerSpielerIndex = (vorhand + i) % 3;
                Spieler& aktuellerSpieler = spielerListe[aktuellerSpielerIndex];
                Karte gespielteKarte;
                bool zugGueltig = false;
                int wahl;
                do {
                    std::cout << aktuellerSpieler.getName() << " ist dran." << std::endl;
                    std::cout << std::endl;
                    std::cout << "Hand von " << aktuellerSpieler.getName() << ":" << std::endl;
                    std::cout << std::endl;
                    for (int k = 0; k < aktuellerSpieler.getHand().size(); k++) {
                        std::cout << "(" << k << ") " << aktuellerSpieler.getHand()[k].getFarbe() << " "
                                  << aktuellerSpieler.getHand()[k].getName() << std::endl;
                    }
                    std::cout << std::endl;

                    std::cin >> wahl;

                    if (wahl >= 0 && wahl < aktuellerSpieler.getHand().size()) {
                        Karte testKarte = aktuellerSpieler.getHand()[wahl];
                        gespielteKarte = aktuellerSpieler.getHand()[wahl];
                        if (darfKarteLegen(testKarte, stich, aktuellerSpieler.getHand()) == true) {
                            gespielteKarte = aktuellerSpieler.spieleKarte(wahl);
                            zugGueltig = true;
                        } else if (stich[0].getFarbeID() == 4) {
                            std::cout << "Du musst Trumpf bedienen!" << std::endl;
                            std::cout << std::endl;
                            zugGueltig = false;
                        } else {
                            std::cout << "Du musst " << stich[0].getFarbe() << " bedienen!" << std::endl;
                            std::cout << std::endl;
                            zugGueltig = false;
                        }
                    } else {
                        std::cout << "Falsche Eingabe, lege eine Karte, die existiert. (Die Zahl vor der Karte.)"
                                  << std::endl;
                        std::cout << std::endl;
                    }

                } while (zugGueltig == false);

                std::cout << aktuellerSpieler.getName() << " legt: " << gespielteKarte.getFarbe() << " "
                          << gespielteKarte.getName() << std::endl;
                std::cout << std::endl;
                stich.push_back(gespielteKarte);
            }
            int stichGewinner = bestimmeStichGewinner(stich);
            int gewinnerID = (vorhand + stichGewinner) % 3;
            Spieler& gewinner = spielerListe[gewinnerID];
            gewinner.nimmtStich(stich);
            std::cout << "-----Der Stich geht an die " << positionen[stichGewinner] << "!-----" << std::endl;
            std::cout << std::endl;
            vorhand = gewinnerID;
        }

        int punkteS1 = spielerListe[0].berechnePunkte();
        int punkteS2 = spielerListe[1].berechnePunkte();
        int punkteS3 = spielerListe[2].berechnePunkte();
        int skatPunkte = berechneSkatPunkte(skat);

        std::cout << "--- ENDERGEBNIS ---" << std::endl;
        std::cout << spielerListe[0].getName() << " " << punkteS1 << " Augen" << std::endl;
        std::cout << spielerListe[1].getName() << " " << punkteS2 << " Augen" << std::endl;
        std::cout << spielerListe[2].getName() << " " << punkteS3 << " Augen" << std::endl;
        std::cout << std::endl;

        for (int i = 0; i < skat.size(); i++) {
            std::cout << "Im Skat lag: " << skat[i].getFarbe() << " " << skat[i].getName() << std::endl;
        }
        std::cout << std::endl;
        if (punkteS1 > punkteS2 && punkteS1 > punkteS3) {
            std::cout << spielerListe[0].getName() << " verliert mit " << (punkteS1 + skatPunkte)
                      << " Augen, inklusive dem Skat!" << std::endl;
        } else if (punkteS2 > punkteS1 && punkteS2 > punkteS3) {
            std::cout << spielerListe[1].getName() << " verliert mit " << (punkteS2 + skatPunkte)
                      << " Augen inklusive dem Skat!" << std::endl;
        } else if (punkteS3 > punkteS1 && punkteS3 > punkteS2) {
            std::cout << spielerListe[2].getName() << " verliert mit " << (punkteS3 + skatPunkte)
                      << " Augen inklusive dem Skat!" << std::endl;
        } else {
            std::cout << "Unentschieden!" << std::endl;
        }

        startSpielerErsteRunde = (startSpielerErsteRunde + 1) % 3;
        std::cout << "Die Runde ist vorbei. Willst du noch eine spielen? (j/n): " << std::endl;
        std::cout << std::endl;
        std::cin >> weiterspielen;
    } while (weiterspielen == 'j');

    std::cout << "Gut Blatt!" << std::endl;
    return 0;
}