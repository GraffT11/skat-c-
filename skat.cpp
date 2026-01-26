#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <string>

// Der Aufbaue der Skat-Karten

class Karte {
   private:
    std::string name;
    std::string farbe;
    int augen;
    int staerke;
    int farbeID;

   public:
    Karte() {}
    Karte(std::string n, std::string f, int a, int s, int id) {
        name = n;
        farbe = f;
        augen = a;
        staerke = s;
        farbeID = id;
    }
    std::string bekommtName() const {
        return name;
    }
    std::string bekommtFarbe() const {
        return farbe;
    }
    int bekommtAugen() const {
        return augen;
    }
    int bekommtStarke() const {
        return staerke;
    }
    int bekommtFarbeID() const {
        return farbeID;
    }
};

// Automatische Deck-Erstellung

std::vector<Karte> erstelleDeck() {
    std::vector<Karte> deck;
    std::vector<std::string> farben = {"Kreuz", "Pik", "Herz", "Karo"};
    std::vector<std::string> namen = {"Sieben", "Acht", "Neun", "Dame", "Koenig", "Zehn", "Ass", "Bube"};
    for (int f = 0; f < farben.size(); f++) {
        for (int n = 0; n < namen.size(); n++) {
            int tempAugen = 0;
            int tempStaerke = 0;
            int tempFarbeID = f;
            if (namen[n] == "Bube") {
                tempFarbeID = 4;
                tempStaerke = 10 + (3 - f);
                tempAugen = 2;
            } else {
                if (namen[n] == "Sieben") {
                    tempStaerke = 0;
                    tempAugen = 0;
                } else if (namen[n] == "Acht") {
                    tempStaerke = 1;
                    tempAugen = 0;
                } else if (namen[n] == "Neun") {
                    tempStaerke = 2;
                    tempAugen = 0;
                } else if (namen[n] == "Dame") {
                    tempStaerke = 3;
                    tempAugen = 3;
                } else if (namen[n] == "Koenig") {
                    tempStaerke = 4;
                    tempAugen = 4;
                } else if (namen[n] == "Zehn") {
                    tempStaerke = 5;
                    tempAugen = 10;
                } else if (namen[n] == "Ass") {
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

void mischDeck(std::vector<Karte>& deck) {
    std::random_device rd;
    unsigned seed = rd();
    std::default_random_engine generator(seed);
    std::shuffle(deck.begin(), deck.end(), generator);
}

// Der Aufbau der Spieler

class Spieler {
   private:
    std::string name;
    std::vector<Karte> hand;
    std::vector<Karte> gewonneneStiche;

   public:
    Spieler() {}

    Spieler(std::string n) {
        name = n;
    };

    std::string bekommtName() const {
        return name;
    }

    const std::vector<Karte>& zeigeHand() const {
        return hand;
    }

    void bekommtKarte(Karte k) {
        hand.push_back(k);
    }

    void entferntKarte(int i) {
        if (i >= 0 && i < hand.size()) {
            hand.erase(hand.begin() + i);
        }
    }

    void bekommtStich(std::vector<Karte> stich) {
        for (const auto& k : stich) {
            gewonneneStiche.push_back(k);
        }
    }

    const std::vector<Karte>& getGewonneneStiche() const {
        return gewonneneStiche;
    }
};

// Man checkt, ob der Spieler, die Karte legen darf oder nicht

bool darfKarteLegen(Karte karte, std::vector<Karte> stich, std::vector<Karte> hand) {
    if (stich.size() == 0) {
        return true;
    } else if (karte.bekommtFarbeID() == stich[0].bekommtFarbeID()) {
        return true;
    } else {
        for (int i = 0; i < hand.size(); i++) {
            if (hand[i].bekommtFarbeID() == stich[0].bekommtFarbeID()) {
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
        if (stich[i].bekommtFarbeID() == 4) {
            if (stich[gewinnerIndex].bekommtFarbeID() != 4) {
                gewinnerIndex = i;
            } else if (stich[i].bekommtStarke() > stich[gewinnerIndex].bekommtStarke()) {
                gewinnerIndex = i;
            }
        } else if (stich[i].bekommtFarbeID() == stich[0].bekommtFarbeID()) {
            if (stich[gewinnerIndex].bekommtFarbeID() != 4) {
                if (stich[i].bekommtStarke() > stich[gewinnerIndex].bekommtStarke()) {
                    gewinnerIndex = i;
                }
            }
        }
    }
    return gewinnerIndex;
}

int zaehltAugen(std::vector<Karte> stapel) {
    int summe = 0;
    for (int i = 0; i < stapel.size(); i++) {
        summe += stapel[i].bekommtAugen();
    }
    return summe;
}

// Das Spiel selber

int main() {
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

    do {
        std::vector<Karte> deck = erstelleDeck();
        mischDeck(deck);
        std::vector<Karte> skat;

        Spieler s1;
        s1.name = spieler1Name;
        Spieler s2;
        s2.name = spieler2Name;
        Spieler s3;
        s3.name = spieler3Name;

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

        std::vector<Spieler*> spielerListe = {&s1, &s2, &s3};
        int vorhand = startSpielerErsteRunde;
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
                    for (int k = 0; k < aktuellerSpieler->zeigeHand().size(); k++) {
                        std::cout << "(" << k << ") " << aktuellerSpieler->hand[k].farbe << " "
                                  << aktuellerSpieler->hand[k].name << std::endl;
                    }
                    std::cout << std::endl;

                    std::cin >> wahl;

                    if (wahl >= 0 && wahl < aktuellerSpieler->hand.size()) {
                        gespielteKarte = aktuellerSpieler->hand[wahl];
                        if (darfKarteLegen(gespielteKarte, stich, aktuellerSpieler->hand) == true) {
                            zugGueltig = true;
                        } else if (stich[0].bekommtFarbeID() == 4) {
                            std::cout << "Du musst Trumpf bedienen!" << std::endl;
                            std::cout << std::endl;
                            zugGueltig = false;
                        } else {
                            std::cout << "Du musst " << stich[0].bekommtFarbe() << " bedienen!" << std::endl;
                            std::cout << std::endl;
                            zugGueltig = false;
                        }
                    } else {
                        std::cout << "Falsche Eingabe, lege eine Karte, die existiert. (Die Zahl vor der Karte.)"
                                  << std::endl;
                        std::cout << std::endl;
                    }

                } while (zugGueltig == false);

                std::cout << "Spieler " << (aktuellerSpielerIndex + 1) << " legt: " << gespielteKarte.bekommtFarbe()
                          << " " << gespielteKarte.name << std::endl;
                std::cout << std::endl;
                stich.push_back(gespielteKarte);
                aktuellerSpieler->hand.erase(aktuellerSpieler->hand.begin() + wahl);
            }
            int stichGewinner = bestimmeStichGewinner(stich);
            int gewinnerID = (vorhand + stichGewinner) % 3;
            Spieler* gewinner = spielerListe[gewinnerID];
            for (int k = 0; k < stich.size(); k++) {
                gewinner->gewonneneStiche.push_back(stich[k]);
            }
            std::cout << "-----Der Stich geht an die " << positionen[stichGewinner] << "!-----" << std::endl;
            std::cout << std::endl;
            vorhand = gewinnerID;
        }
        int punkteS1 = zaehltAugen(s1.gewonneneStiche);
        int punkteS2 = zaehltAugen(s2.gewonneneStiche);
        int punkteS3 = zaehltAugen(s3.gewonneneStiche);
        int skatPunkte = zaehltAugen(skat);

        std::cout << "--- ENDERGEBNIS ---" << std::endl;
        std::cout << spieler1Name << " " << punkteS1 << " Augen" << std::endl;
        std::cout << spieler2Name << " " << punkteS2 << " Augen" << std::endl;
        std::cout << spieler3Name << " " << punkteS3 << " Augen" << std::endl;
        std::cout << std::endl;

        for (int i = 0; i < skat.size(); i++) {
            std::cout << "Im Skat lag: " << skat[i].bekommtFarbe() << " " << skat[i].name << std::endl;
        }
        std::cout << std::endl;
        if (punkteS1 > punkteS2 && punkteS1 > punkteS3) {
            int endPunkteS1;
            endPunkteS1 = punkteS1 + skatPunkte;
            std::cout << spieler1Name << " hat das Spiel verloren!" << std::endl;
            std::cout << std::endl;
            std::cout << "Die Anzahl der Punkte im Skat (" << skatPunkte << ") werden zu dazugerechnet." << std::endl;
            std::cout << std::endl;
            std::cout << spieler1Name << " verliert das Spiel mit " << endPunkteS1 << " Augen!" << std::endl;
            std::cout << std::endl;
        } else if (punkteS2 > punkteS1 && punkteS2 > punkteS3) {
            int endPunkteS2;
            endPunkteS2 = punkteS2 + skatPunkte;
            std::cout << spieler2Name << " hat das Spiel verloren!" << std::endl;
            std::cout << std::endl;
            std::cout << "Die Anzahl der Punkte im Skat (" << skatPunkte << ") werden zu dazugerechnet." << std::endl;
            std::cout << std::endl;
            std::cout << spieler2Name << " verliert das Spiel mit " << endPunkteS2 << " Augen!" << std::endl;
            std::cout << std::endl;
        } else if (punkteS3 > punkteS1 && punkteS3 > punkteS2) {
            int endPunkteS3;
            endPunkteS3 = punkteS3 + skatPunkte;
            std::cout << spieler3Name << " hat das Spiel verloren!" << std::endl;
            std::cout << std::endl;
            std::cout << "Die Anzahl der Punkte im Skat (" << skatPunkte << ") werden zu dazugerechnet." << std::endl;
            std::cout << std::endl;
            std::cout << spieler3Name << " verliert das Spiel mit " << endPunkteS3 << " Augen!" << std::endl;
            std::cout << std::endl;
        }

        startSpielerErsteRunde = (startSpielerErsteRunde + 1) % 3;
        std::cout << "Die Runde ist vorbei. Willst du noch eine spielen? (j/n): " << std::endl;
        std::cout << std::endl;
        std::cin >> weiterspielen;
    } while (weiterspielen == 'j');

    std::cout << "Gut Blatt!" << std::endl;
    return 0;
}