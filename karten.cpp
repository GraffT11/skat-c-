#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <string>

struct Karte {
    std::string name;
    std::string farbe;
    int augen;
    int staerke;
    int farbeID;
};

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
                } else if (neueKarte.name == "König") {
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
}

void mischDeck(std::vector<Karte>& deck) {
    std::random_device rd;
    unsigned seed = rd();
    std::default_random_engine generator(seed);
    std::shuffle(deck.begin(), deck.end(), generator);
}

struct Spieler {
    std::string name;
    std::vector<Karte> hand;
    std::vector<Karte> gewonneneStiche;
};

int main() {
    std::vector<Karte> deck = erstelleDeck();
    mischDeck(deck);

    Spieler s1;
    s1.name = "Spieler 1";
    Spieler s2;
    s2.name = "Spieler 2";
    Spieler s3;
    s3.name = "Spieler 3";

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

    std::cout << "Hand von " << s1.name << ":" << std::endl;
    for (int i = 0; i < s1.hand.size(); i++) {
        std::cout << "(" << i << ")" << s1.hand[i].farbe << " " << s1.hand[i].name << std::endl;
    }

    std::cout << "Hand von " << s2.name << ":" << std::endl;
    for (int i = 0; i < s2.hand.size(); i++) {
        std::cout << "(" << i << ")" << s2.hand[i].farbe << " " << s2.hand[i].name << std::endl;
    }

    std::cout << "Hand von " << s3.name << ":" << std::endl;
    for (int i = 0; i < s3.hand.size(); i++) {
        std::cout << "(" << i << ")" << s3.hand[i].farbe << " " << s3.hand[i].name << std::endl;
    }

    return 0;
}