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
    std::cout << std::endl;
    for (int i = 0; i < s1.hand.size(); i++) {
        std::cout << "(" << i << ")" << s1.hand[i].farbe << " " << s1.hand[i].name << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Hand von " << s2.name << ":" << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < s2.hand.size(); i++) {
        std::cout << "(" << i << ")" << s2.hand[i].farbe << " " << s2.hand[i].name << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Hand von " << s3.name << ":" << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < s3.hand.size(); i++) {
        std::cout << "(" << i << ")" << s3.hand[i].farbe << " " << s3.hand[i].name << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Der Skat: " << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < skat.size(); i++) {
        std::cout << "(" << i << ")" << skat[i].farbe << " " << skat[i].name << std::endl;
    };
    std::cout << std::endl;
    std::cout << "Lass das Spiel beginnen. Spieler 1 startet." << std::endl;
    std::cout << std::endl;

    for (int s = 0; s < 10; s++) {
        std::vector<Karte> stich;
        Karte gespielteKarte;
        bool zugGueltig = false;
        int wahl;
        do {
            std::cout << "Spieler 1 du bist am Zug, hier ist dein Blatt, welche Karte willst du spielen?" << std::endl;
            std::cout << std::endl;
            std::cout << "Hand von " << s1.name << ":" << std::endl;
            std::cout << std::endl;
            for (int i = 0; i < s1.hand.size(); i++) {
                std::cout << "(" << i << ")" << s1.hand[i].farbe << " " << s1.hand[i].name << std::endl;
            }
            std::cout << std::endl;
            std::cin >> wahl;
            if (wahl >= 0 && wahl < s1.hand.size()) {
                gespielteKarte = s1.hand[wahl];
                if (darfKarteLegen(gespielteKarte, stich, s1.hand) == true) {
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
                std::cout << "Falsche Eingabe, lege eine Karte, die existiert. (Die Zahl vor der Karte)" << std::endl;
            };
        } while (zugGueltig == false);
        std::cout << "Spieler 1 legt die Karte \"" << gespielteKarte.farbe << " " << gespielteKarte.name << "\""
                  << std::endl;
        std::cout << std::endl;
        stich.push_back(gespielteKarte);
        s1.hand.erase(s1.hand.begin() + wahl);

        // Spieler 2 am Zug
        zugGueltig = false;
        do {
            std::cout << "Spieler 2 du bist am Zug, hier ist dein Blatt, welche Karte willst du spielen?" << std::endl;
            std::cout << std::endl;
            std::cout << "Hand von " << s2.name << ":" << std::endl;
            std::cout << std::endl;
            for (int i = 0; i < s2.hand.size(); i++) {
                std::cout << "(" << i << ")" << s2.hand[i].farbe << " " << s2.hand[i].name << std::endl;
            }
            std::cout << std::endl;
            std::cin >> wahl;
            if (wahl >= 0 && wahl < s2.hand.size()) {
                gespielteKarte = s2.hand[wahl];
                if (darfKarteLegen(gespielteKarte, stich, s2.hand) == true) {
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
                std::cout << "Falsche Eingabe, lege eine Karte, die existiert. (Die Zahl vor der Karte)" << std::endl;
            };
        } while (zugGueltig == false);
        std::cout << "Spieler 2 legt die Karte \"" << gespielteKarte.farbe << " " << gespielteKarte.name << "\""
                  << std::endl;
        std::cout << std::endl;
        stich.push_back(gespielteKarte);
        s2.hand.erase(s2.hand.begin() + wahl);

        // Spieler 3 am Zug
        zugGueltig = false;
        do {
            std::cout << "Spieler 3 du bist am Zug, hier ist dein Blatt, welche Karte willst du spielen?" << std::endl;
            std::cout << std::endl;
            std::cout << "Hand von " << s3.name << ":" << std::endl;
            std::cout << std::endl;
            for (int i = 0; i < s3.hand.size(); i++) {
                std::cout << "(" << i << ")" << s3.hand[i].farbe << " " << s3.hand[i].name << std::endl;
            }
            std::cout << std::endl;
            std::cin >> wahl;
            if (wahl >= 0 && wahl < s3.hand.size()) {
                gespielteKarte = s3.hand[wahl];
                if (darfKarteLegen(gespielteKarte, stich, s3.hand) == true) {
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
                std::cout << "Falsche Eingabe, lege eine Karte, die existiert. (Die Zahl vor der Karte)" << std::endl;
            };
        } while (zugGueltig == false);
        std::cout << "Spieler 3 legt die Karte \"" << gespielteKarte.farbe << " " << gespielteKarte.name << "\""
                  << std::endl;
        std::cout << std::endl;
        stich.push_back(gespielteKarte);
        s3.hand.erase(s3.hand.begin() + wahl);

        // Auswertung

        int gewinnerIndex = bestimmeStichGewinner(stich);
        std::vector<std::string> positionen = {"Vorhand", "Mittelhand", "Hinterhand"};
        std::cout << "Der Stich geht an die " << positionen[gewinnerIndex] << "!" << std::endl;
        std::cout << std::endl;
    }
    std::cout << "Das Spiel ist vorbei! Tippe 'x' und Enter zum Beenden." << std::endl;
    std::cout << std::endl;
    char ende;
    std::cin >> ende;
    return 0;
}