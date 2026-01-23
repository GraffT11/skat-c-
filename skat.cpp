#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <string>

// Der Aufbaue der Skat-Karten

struct Karte {
    std::string name;
    std::string farbe;
    int augen;
    int staerke;
    int farbeID;
};

// Automatische Deck-Erstellung

std::vector<Karte> erstelleDeck() {
    std::vector<Karte> deck;
    std::vector<std::string> farben = {"Eichel", "Rot", "Gruen", "Schellen"};
    std::vector<std::string> namen = {"Sieben", "Acht", "Neun", "Ober", "Koenig", "Zehn", "Ass", "Unter"};
    for (int f = 0; f < farben.size(); f++) {
        for (int n = 0; n < namen.size(); n++) {
            Karte neueKarte;
            neueKarte.farbe = farben[f];
            neueKarte.name = namen[n];
            neueKarte.augen = 0;
            neueKarte.staerke = 0;
            if (neueKarte.name == "Unter") {
                neueKarte.farbeID = 4;
                neueKarte.staerke = 10 + (3 - f);
                neueKarte.augen = 2;
            } else {
                neueKarte.farbeID = f;
                if (neueKarte.name == "Sieben") {
                    neueKarte.staerke = 0;
                    neueKarte.augen = 0;
                } else if (neueKarte.name == "Acht") {
                    neueKarte.staerke = 1;
                    neueKarte.augen = 0;
                } else if (neueKarte.name == "Neun") {
                    neueKarte.staerke = 2;
                    neueKarte.augen = 0;
                } else if (neueKarte.name == "Ober") {
                    neueKarte.staerke = 3;
                    neueKarte.augen = 3;
                } else if (neueKarte.name == "Koenig") {
                    neueKarte.staerke = 4;
                    neueKarte.augen = 4;
                } else if (neueKarte.name == "Zehn") {
                    neueKarte.staerke = 5;
                    neueKarte.augen = 10;
                } else if (neueKarte.name == "Ass") {
                    neueKarte.staerke = 6;
                    neueKarte.augen = 11;
                }
            }
            deck.push_back(neueKarte);
        }
    }
    return deck;
};

// Random Faktor des Geräts nehmen, um das Deck zu mischen

void mischDeck(std::vector<Karte>& deck) {
    std::random_device rd;
    unsigned seed = rd();
    std::default_random_engine generator(seed);
    std::shuffle(deck.begin(), deck.end(), generator);
}

// Der Aufbau der Spieler

struct Spieler {
    std::string name;
    std::vector<Karte> hand;
    std::vector<Karte> gewonneneStiche;
};

// Man checkt, ob der Spieler, die Karte legen darf oder nicht

bool darfKarteLegen(Karte karte, std::vector<Karte> stich, std::vector<Karte> hand) {
    if (stich.size() == 0) {
        return true;
    } else if (karte.farbeID == stich[0].farbeID) {
        return true;
    } else {
        for (int i = 0; i < hand.size(); i++) {
            if (hand[i].farbeID == stich[0].farbeID) {
                return false;
            }
        }
        return true;
    }
}

// Man checkt, wer den Stich am Ende gewinnt

int bestimmeStichGewinner(std::vector<Karte> stich) {
    int gewinnerIndex = 0;

    for (int i = 1; i < 3; i++) {
        if (stich[i].farbeID == 4) {
            if (stich[gewinnerIndex].farbeID != 4) {
                gewinnerIndex = i;
            } else if (stich[i].staerke > stich[gewinnerIndex].staerke) {
                gewinnerIndex = i;
            }
        } else if (stich[i].farbeID == stich[0].farbeID) {
            if (stich[gewinnerIndex].farbeID != 4) {
                if (stich[i].staerke > stich[gewinnerIndex].staerke) {
                    gewinnerIndex = i;
                }
            }
        }
    }
    return gewinnerIndex;
}

// Das Spiel selber

int main() {
    std::vector<Karte> deck = erstelleDeck();
    mischDeck(deck);

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

    Spieler s1;
    s1.name = spieler1Name;
    Spieler s2;
    s2.name = spieler2Name;
    Spieler s3;
    s3.name = spieler3Name;

    std::vector<Karte> skat;

    for (int i = 0; i < 32; i++) {
        if (i < 10) {
            s1.hand.push_back(deck[i]);
        } else if (i < 20) {
            s2.hand.push_back(deck[i]);
        } else if (i < 30) {
            s3.hand.push_back(deck[i]);
        } else {
            skat.push_back(deck[i]);
        }
    }

    // Eine for-Schleife für das Spiel

    std::cout << "Spieler " << spieler1Name << " du spielst als erstes aus!" << std::endl;
    std::cout << std::endl;

    std::vector<Spieler*> spielerListe = {&s1, &s2, &s3};
    int vorhand = 0;
    std::vector<std::string> positionen = {"Vorhand", "Mittelhand", "Hinterhand"};

    for (int s = 0; s < 10; s++) {
        std::vector<Karte> stich;
        for (int i = 0; i < 3; i++) {
            int aktuellerSpielerIndex = (vorhand + i) % 3;
            Spieler* aktuellerSpieler = spielerListe[aktuellerSpielerIndex];
            Karte gespielteKarte;
            bool zugGueltig = false;
            int wahl;
            do {
                std::cout << "Spieler " << (aktuellerSpielerIndex + 1) << " ist dran." << std::endl;
                std::cout << std::endl;
                std::cout << "Hand von " << aktuellerSpieler->name << ":" << std::endl;
                std::cout << std::endl;
                for (int k = 0; k < aktuellerSpieler->hand.size(); k++) {
                    std::cout << "(" << k << ") " << aktuellerSpieler->hand[k].farbe << " "
                              << aktuellerSpieler->hand[k].name << std::endl;
                }
                std::cout << std::endl;

                std::cin >> wahl;

                if (wahl >= 0 && wahl < aktuellerSpieler->hand.size()) {
                    gespielteKarte = aktuellerSpieler->hand[wahl];
                    if (darfKarteLegen(gespielteKarte, stich, aktuellerSpieler->hand) == true) {
                        zugGueltig = true;
                    } else if (stich[0].farbeID == 4) {
                        std::cout << "Du musst Trumpf bedienen!" << std::endl;
                        std::cout << std::endl;
                        zugGueltig = false;
                    } else {
                        std::cout << "Du musst " << stich[0].farbe << " bedienen!" << std::endl;
                        std::cout << std::endl;
                        zugGueltig = false;
                    }
                } else {
                    std::cout << "Falsche Eingabe, lege eine Karte, die existiert. (Die Zahl vor der Karte)"
                              << std::endl;
                }

            } while (zugGueltig == false);

            std::cout << "Spieler " << (aktuellerSpielerIndex + 1) << " legt: " << gespielteKarte.farbe << " "
                      << gespielteKarte.name << std::endl;
            std::cout << std::endl;
            stich.push_back(gespielteKarte);
            aktuellerSpieler->hand.erase(aktuellerSpieler->hand.begin() + wahl);
        }
        int stichGewinner = bestimmeStichGewinner(stich);
        int gewinnerID = (vorhand + stichGewinner) % 3;
        std::vector<std::string> positionen = {"Vorhand", "Mittelhand", "Hinterhand"};
        std::cout << "Der Stich geht an die " << positionen[stichGewinner] << "!" << std::endl;
        std::cout << std::endl;
        vorhand = gewinnerID;
    }
    std::cout << "Das Spiel ist vorbei! Tippe 'x' und Enter zum Beenden." << std::endl;
    std::cout << std::endl;
    char ende;
    std::cin >> ende;
    return 0;
}