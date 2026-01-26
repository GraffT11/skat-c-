#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "karte.hpp"
#include "spieler.hpp"

// Automatische Deck-Erstellung

std::vector<Karte> erstelleDeck()
{
    std::vector<Karte> deck;
    std::vector<std::string> farben = {"Kreuz", "Pik", "Herz", "Karo"};
    std::vector<std::string> namen = {"Sieben", "Acht", "Neun", "Dame", "Koenig", "Zehn", "Ass", "Bube"};
    for (int f = 0; f < farben.size(); f++)
    {
        for (int n = 0; n < namen.size(); n++)
        {
            int tempAugen = 0;
            int tempStaerke = 0;
            int tempFarbeID = f;
            if (namen[n] == "Bube")
            {
                tempFarbeID = 4;
                tempStaerke = 10 + (3 - f);
                tempAugen = 2;
            }
            else
            {
                if (namen[n] == "Sieben")
                {
                    tempStaerke = 0;
                    tempAugen = 0;
                }
                else if (namen[n] == "Acht")
                {
                    tempStaerke = 1;
                    tempAugen = 0;
                }
                else if (namen[n] == "Neun")
                {
                    tempStaerke = 2;
                    tempAugen = 0;
                }
                else if (namen[n] == "Dame")
                {
                    tempStaerke = 3;
                    tempAugen = 3;
                }
                else if (namen[n] == "Koenig")
                {
                    tempStaerke = 4;
                    tempAugen = 4;
                }
                else if (namen[n] == "Zehn")
                {
                    tempStaerke = 5;
                    tempAugen = 10;
                }
                else if (namen[n] == "Ass")
                {
                    tempStaerke = 6;
                    tempAugen = 11;
                }
            }
            Karte neueKarte(namen[n], farben[f], tempAugen, tempStaerke, tempFarbeID);
            deck.push_back(neueKarte);
        }
    }
    return deck;
};

// Random Faktor des Geräts nehmen, um das Deck zu mischen

void mischDeck(std::vector<Karte> &deck)
{
    std::random_device rd;
    unsigned seed = rd();
    std::default_random_engine generator(seed);
    std::shuffle(deck.begin(), deck.end(), generator);
}

// Man checkt, ob der Spieler, die Karte legen darf oder nicht

bool darfKarteLegen(Karte karte, std::vector<Karte> stich, std::vector<Karte> hand)
{
    if (stich.size() == 0)
    {
        return true;
    }
    else if (karte.getFarbeID() == stich[0].getFarbeID())
    {
        return true;
    }
    else
    {
        for (int i = 0; i < hand.size(); i++)
        {
            if (hand[i].getFarbeID() == stich[0].getFarbeID())
            {
                return false;
            }
        }
        return true;
    }
}

// Man checkt, wer den Stich am Ende gewinnt

int bestimmeStichGewinner(std::vector<Karte> stich)
{
    int gewinnerIndex = 0;

    for (int i = 1; i < 3; i++)
    {
        if (stich[i].getFarbeID() == 4)
        {
            if (stich[gewinnerIndex].getFarbeID() != 4)
            {
                gewinnerIndex = i;
            }
            else if (stich[i].getStarke() > stich[gewinnerIndex].getStarke())
            {
                gewinnerIndex = i;
            }
        }
        else if (stich[i].getFarbeID() == stich[0].getFarbeID())
        {
            if (stich[gewinnerIndex].getFarbeID() != 4)
            {
                if (stich[i].getStarke() > stich[gewinnerIndex].getStarke())
                {
                    gewinnerIndex = i;
                }
            }
        }
    }
    return gewinnerIndex;
}

int berechneKartenStapelPunkte(const std::vector<Karte> &stapel)
{
    int summe = 0;
    for (const auto &k : stapel)
    {
        summe += k.getAugen();
    }
    return summe;
}

// Das Spiel selber

int main()
{
    std::cout << "Willkommen zum Skatspiel." << std::endl;
    std::cout << std::endl;
    std::cout << "Gespielt wird im Ramsch. Das heisst: der Spieler, mit den meisten "
                 "Punkten, verliert das Spiel.\nAchtung: Buben sind natuerlich immer Trumpf und nicht die angezeigt "
                 "Farbe!\nGut Blatt :)"
              << std::endl;
    std::cout << std::endl;

    // Ersteinmal den Spieler nach seinem Namen Fragen

    std::cout << "Spieler 1, wie moechtest du heissen?" << std::endl;
    std::cout << std::endl;
    std::string spieler1Name;
    std::cin >> spieler1Name;

    std::cout << "Spieler 2, wie moechtest du heissen?" << std::endl;
    std::cout << std::endl;
    std::string spieler2Name;
    std::cin >> spieler2Name;

    std::cout << "Spieler 3, wie moechtest du heissen?" << std::endl;
    std::cout << std::endl;
    std::string spieler3Name;
    std::cin >> spieler3Name;

    char weiterspielen;

    int startSpielerErsteRunde = 0;

    do
    {
        std::vector<Karte> deck = erstelleDeck();
        mischDeck(deck);
        std::vector<Karte> skat;

        std::vector<Spieler> spielerListe;
        spielerListe.push_back(Spieler(spieler1Name));
        spielerListe.push_back(Spieler(spieler2Name));
        spielerListe.push_back(Spieler(spieler3Name));

        for (int i = 0; i < 32; i++)
        {
            if (i < 30)
            {
                spielerListe[i / 10].bekommtKarte(deck[i]);
            }
            else
            {
                skat.push_back(deck[i]);
            }
        }
        // Eine for-Schleife für das Spiel

        int vorhand = startSpielerErsteRunde;
        std::vector<std::string> positionen = {"Vorhand", "Mittelhand", "Hinterhand"};

        for (int s = 0; s < 10; s++)
        {
            std::vector<Karte> stich;
            for (int i = 0; i < 3; i++)
            {
                int aktuellerSpielerIndex = (vorhand + i) % 3;
                Spieler &aktuellerSpieler = spielerListe[aktuellerSpielerIndex];
                Karte gespielteKarte;
                bool zugGueltig = false;
                int wahl;
                do
                {
                    std::cout << "Spieler " << (aktuellerSpielerIndex + 1) << " (" << aktuellerSpieler.getName()
                              << ") ist dran." << std::endl;
                    std::cout << std::endl;
                    std::cout << "Hand von " << aktuellerSpieler.getName() << ":" << std::endl;
                    std::cout << std::endl;
                    for (int k = 0; k < aktuellerSpieler.showHand().size(); k++)
                    {
                        std::cout << "(" << k << ") " << aktuellerSpieler.showHand()[k].getFarbe() << " "
                                  << aktuellerSpieler.showHand()[k].getName() << std::endl;
                    }
                    std::cout << std::endl;

                    std::cin >> wahl;

                    if (wahl >= 0 && wahl < aktuellerSpieler.showHand().size())
                    {
                        gespielteKarte = aktuellerSpieler.showHand()[wahl];
                        if (darfKarteLegen(gespielteKarte, stich, aktuellerSpieler.showHand()) == true)
                        {
                            zugGueltig = true;
                        }
                        else if (stich[0].getFarbeID() == 4)
                        {
                            std::cout << "Du musst Trumpf bedienen!" << std::endl;
                            std::cout << std::endl;
                            zugGueltig = false;
                        }
                        else
                        {
                            std::cout << "Du musst " << stich[0].getFarbe() << " bedienen!" << std::endl;
                            std::cout << std::endl;
                            zugGueltig = false;
                        }
                    }
                    else
                    {
                        std::cout << "Falsche Eingabe, lege eine Karte, die existiert. (Die Zahl vor der Karte.)"
                                  << std::endl;
                        std::cout << std::endl;
                    }

                } while (zugGueltig == false);

                std::cout << "Spieler " << (aktuellerSpielerIndex + 1) << " legt: " << gespielteKarte.getFarbe() << " "
                          << gespielteKarte.getName() << std::endl;
                std::cout << std::endl;
                stich.push_back(gespielteKarte);
                aktuellerSpieler.hand.erase(aktuellerSpieler.showHand().begin() + wahl);
            }
            int stichGewinner = bestimmeStichGewinner(stich);
            int gewinnerID = (vorhand + stichGewinner) % 3;
            Spieler &gewinner = spielerListe[gewinnerID];
            for (int k = 0; k < stich.size(); k++)
            {
                gewinner.getGewonneneStiche().push_back(stich[k]);
            }
            std::cout << "-----Der Stich geht an die " << positionen[stichGewinner] << "!-----" << std::endl;
            std::cout << std::endl;
            vorhand = gewinnerID;
        }

        int punkteS1 = spielerListe[0].berechnePunkte();
        int punkteS2 = spielerListe[1].berechnePunkte();
        int punkteS3 = spielerListe[2].berechnePunkte();
        int skatPunkte = berechneKartenStapelPunkte(skat);

        std::cout << "--- ENDERGEBNIS ---" << std::endl;
        std::cout << spieler1Name << " " << punkteS1 << " Augen" << std::endl;
        std::cout << spieler2Name << " " << punkteS2 << " Augen" << std::endl;
        std::cout << spieler3Name << " " << punkteS3 << " Augen" << std::endl;
        std::cout << std::endl;

        for (int i = 0; i < skat.size(); i++)
        {
            std::cout << "Im Skat lag: " << skat[i].getFarbe() << " " << skat[i].getName() << std::endl;
        }
        std::cout << std::endl;
        if (punkteS1 > punkteS2 && punkteS1 > punkteS3)
        {
            std::cout << spieler1Name << " verliert mit " << (punkteS1 + skatPunkte) << " Augen, inklusive dem Skat!"
                      << std::endl;
        }
        else if (punkteS2 > punkteS1 && punkteS2 > punkteS3)
        {
            std::cout << spieler2Name << " verliert mit " << (punkteS2 + skatPunkte) << " Augen inklusive dem Skat!"
                      << std::endl;
        }
        else if (punkteS3 > punkteS1 && punkteS3 > punkteS2)
        {
            std::cout << spieler3Name << " verliert mit " << (punkteS3 + skatPunkte) << " Augen inklusive dem Skat!"
                      << std::endl;
        }
        else
        {
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