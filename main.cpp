#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;
const int NUMOFSUITS = 4;
const int NUMPERSUIT = 13;
const float ADVATAGE [NUMPERSUIT] = {9.8f, 13.4f, 18.0f, 23.2f, 23.9f, 14.3f, 5.4f, -4.3f,
    -16.9f, -16.9f, -16.9f, -16.9f, -16.0f};
const int VALUES [NUMPERSUIT] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
const string NAMES [NUMPERSUIT] = {"ACE", "2", "3", "4", "5", "6", "7", "8", "9", "10", "JACK", "QUEEN", "KING"};
const string SUITS [NUMOFSUITS] = {"HEARTS", "DIAMONDS", "CLUBS", "SPADES"};
const string COLORS[2] = {"RED", "BLACK"};

struct card {
    int value;
    string name;
    string suit;
    string color;
};

struct player {
    string name;
    int count = 0;
    string status [2] = {"standing by...", "playing..."};
    float bet = 0;
    card mycards[10];
};

class deck {
private:
    card cards[NUMOFSUITS][NUMPERSUIT];
public:

    deck() {
        srand(static_cast<int> (time(0)));
        for (int i = 0; i < NUMOFSUITS; ++i) {
            for (int j = 0; j < NUMPERSUIT; ++j) {
                cards[i][j].suit = SUITS[i];
                cards[i][j].value = VALUES[j];
                cards[i][j].name = NAMES[j];
                if ((cards[i][j].suit == "DIAMONDS") || (cards[i][j].suit == "HEARTS")) cards[i][j].color = COLORS[0];
                else if ((cards[i][j].suit == "CLUBS") || (cards[i][j].suit == "SPADES")) cards[i][j].color = COLORS[1];
            }
        }
    }

    ~deck() {
    }

    card deliver() {
        card hand;
        hand = cards[rand() % NUMOFSUITS][rand() % NUMPERSUIT];
        return hand;
    }
};

class blackJack {
private:
    player players[2];
public:

    blackJack(string name, float bet) {
        this->players[0].name = "DEALER";
        this->players[1].name = name;
        this->players[0].bet = 100000.0f;
        this->players[1].bet = bet;
    }

    ~blackJack() {
    }

    void mainMenu(deck newDeck) {
        short int choice = 0;
        cout << "\n\n\t\t\t\tBLACK JACK\n\n\n\n\tPress 1 and enter to play or press any other number and enter to quit:   ";
        cin >> choice;
        switch (choice) {
            case 1: play(newDeck);
                break;
            default: cout << "\n\n\tOK, BYE...";
                break;
        }

    }

    void play(deck newDeck) {
        int choice2 = 1;
        int lucky = 0;
        int showing = 3;
        int numOfLucky = 0;
        float probability = 0;
        switch (choice2) {
            case 1:
                players[0].mycards[0] = newDeck.deliver();
                players[0].mycards[1] = newDeck.deliver();
                players[0].count = players[0].mycards[0].value + players[0].mycards[1].value;
                cout << "\n\nPlayer: " << players[0].name << "\nCount: ***" << "\nStatus: " << players[0].status[1] << "\nBank: $" << fixed << std::setprecision(2) << players[0].bet;
                cout << "\n\n" << players[0].name << "\'s hand: " << players[0].mycards[1].name << " of " << players[0].mycards[1].suit << " and [HIDDEN CARD]";
                cout << "\n\n\tPress 1 and enter to play this hand or press any other number and enter to quit:  ";
                cin >> choice2;
                if (choice2 != 1) {
                    cout << "\n\n\tOK, BYE...";
                    break;
                }
                players[1].mycards[0] = newDeck.deliver();
                players[1].mycards[1] = newDeck.deliver();
                players[1].count = players[1].mycards[0].value + players[1].mycards[1].value;
                cout << "\n\nPlayer: " << players[1].name << "(YOU)\nCount: " << players[1].count << "\nStatus: " << players[1].status[1] << "\nBank: $" << fixed << std::setprecision(2) << players[1].bet;
                cout << "\n\n" << players[1].name << "\'s hand: " << players[1].mycards[0].name << " of " << players[1].mycards[0].suit << " and " << players[1].mycards[1].name << " of " << players[1].mycards[1].suit;
                lucky = 21 - players[1].count;
                if (lucky > 10) {
                    lucky = 10;
                }
                for (int i = 0; i < 2; ++i) {
                    if ((players[0].mycards[i].value == lucky) || (players[1].mycards[i].value == lucky)) {
                        numOfLucky++;
                    }
                }
                probability = 4 - numOfLucky;
                probability /= (52 - showing);
                cout << "\n\n\t\tYour advantage vs. the dealer based on the dealer's up card:  " << fixed << std::setprecision(2) << playerAdvantage(players[0].mycards[1].value) << "%.";
                cout << "\n\n\t\tThe probability of you getting " << lucky << " as your next card is " << fixed << std::setprecision(3) << (probability * 100) << "%.";
                cout << "\n\n\tPress 1 and enter to play this hand or press any other number and enter to quit:  ";
                cin >> choice2;
                if (choice2 == 1) {
                    handlePlay(newDeck, 2);
                } else {
                    cout << "\n\n\tOK, BYE...";
                    break;
                }
                break;
            case 2:
                mainMenu(newDeck);
                break;
            default: mainMenu(newDeck);
        }
    }

    float playerAdvantage(int card) {
        float adv = 0;
        for (int i = 0; i < NUMPERSUIT; ++i) {
            if (card == VALUES[i]) {
                if (VALUES[i] == 1) {
                    adv = -16.0f;
                } else if (VALUES[i] == 8) {
                    adv = -16.9f;
                } else {
                    adv = ADVATAGE[i - 1];
                }
            }
        }
        return adv;
    }

    void handlePlay(deck newDeck, int c) {
        int choice = 0;
        int cards = c;
        int lucky = 0;
        int showing = (c * 2) - 1;
        int numOfLucky = 0;
        float probability = 0;
        cout << "\n\n1. To Take another card from the dealer.\n2. To stay and show cards.\n5. To surrender press any number and enter.\n\tCHOICE:  ";
        cin >> choice;
        switch (choice) {
            case 1:
            {
                players[0].mycards[cards] = newDeck.deliver();
                players[1].mycards[cards] = newDeck.deliver();
                players[0].count += players[0].mycards[cards].value;
                players[1].count += players[1].mycards[cards].value;
                ++cards;
                cout << "\n\nPlayer: " << players[1].name << "(YOU)\nCount: " << players[1].count << "\nBank: $" << fixed << std::setprecision(2) << players[1].bet;
                cout << "\n\n" << players[1].name << "\'s hand: \n";
                for (int i = 0; i < cards; ++i) {
                    cout << players[1].mycards[i].name << " of " << players[1].mycards[i].suit << "\n";
                }
                lucky = 21 - players[1].count;
                if (lucky > 10) {
                    lucky = 10;
                }
                for (int i = 0; i < cards; ++i) {
                    if ((players[0].mycards[i].value == lucky) || (players[1].mycards[i].value == lucky)) {
                        numOfLucky++;
                    }
                }
                probability = 4 - numOfLucky;
                probability = probability / (52 - showing);
                cout << "\n\n\t\tYour advantage vs. the dealer based on the dealer's up card:  " << fixed << std::setprecision(2) << playerAdvantage(players[0].mycards[1].value) << "%.";
                cout << "\n\n\t\tThe probability of you getting " << lucky << " as your next card is " << fixed << std::setprecision(3) << (probability * 100) << "%.";
                if (players[0].count >= 21 || players[1].count >= 21) break;
                else handlePlay(newDeck, cards);
            }
                break;
            case 2:
            {
                cout << "\n\n\tOK...";
            }
                break;
            default: mainMenu(newDeck);
        }
        if (((players[0].count <= 21) && (players[0].count > players[1].count)) || (players[1].count > 21)) {
            players[0].bet += players[1].bet;
            players[1].bet -= players[1].bet;
            cout << "\n\n\t THE HOUSE WINS!! SORRY!";
            cout << "\n\nPlayer: " << players[0].name << "\nCount: " << players[0].count << "\nBank: $" << fixed << std::setprecision(2) << players[0].bet;
            cout << "\n\n" << players[0].name << "\'s hand: \n";
            for (int i = 0; i < cards; ++i) {
                cout << players[0].mycards[i].name << " of " << players[0].mycards[i].suit << "\n";
            }
            cout << "\n\nPlayer: " << players[1].name << "(YOU)\nCount: " << players[1].count << "\nBank: $" << fixed << std::setprecision(2) << players[1].bet;
            cout << "\n\n" << players[1].name << "\'s hand: \n";
            for (int i = 0; i < cards; ++i) {
                cout << players[1].mycards[i].name << " of " << players[1].mycards[i].suit << "\n";
            }
        } else if (((players[1].count <= 21) && (players[1].count > players[0].count)) || (players[0].count > 21)) {
            players[0].bet -= players[1].bet;
            players[1].bet += players[1].bet;
            cout << "\n\n\tCONGRATULATIONS YOU WIN!!";
            cout << "\n\nPlayer: " << players[0].name << "\nCount: " << players[0].count << "\nBank: $" << fixed << std::setprecision(2) << players[0].bet;
            cout << "\n\n" << players[0].name << "\'s hand: \n";
            for (int i = 0; i < cards; ++i) {
                cout << players[0].mycards[i].name << " of " << players[0].mycards[i].suit << "\n";
            }
            cout << "\n\nPlayer: " << players[1].name << "(YOU)\nCount: " << players[1].count << "\nBank: $" << fixed << std::setprecision(2) << players[1].bet;
            cout << "\n\n" << players[1].name << "\'s hand: \n";
            for (int i = 0; i < cards; ++i) {
                cout << players[1].mycards[i].name << " of " << players[1].mycards[i].suit << "\n";
            }
        } else {
            cout << "\n\n\tNOBODY WINS!!";
            cout << "\n\nPlayer: " << players[0].name << "\nCount: " << players[0].count << "\nBank: $" << fixed << std::setprecision(2) << players[0].bet;
            cout << "\n\n" << players[0].name << "\'s hand: \n";
            for (int i = 0; i < cards; ++i) {
                cout << players[0].mycards[i].name << " of " << players[0].mycards[i].suit << "\n";
            }
            cout << "\n\nPlayer: " << players[1].name << "(YOU)\nCount: " << players[1].count << "\nBank: $" << fixed << std::setprecision(2) << players[1].bet;
            cout << "\n\n" << players[1].name << "\'s hand: \n";
            for (int i = 0; i < cards; ++i) {
                cout << players[1].mycards[i].name << " of " << players[1].mycards[i].suit << "\n";
            }
        }
        cout << "\n\n";
        if (players[0].bet == 0) {
            cout << "\n\n\tWe're sorry, but the house is bankrupt.";
        }
        while (players[1].bet == 0) {
            cout << "\n\n\tHow much would you like to add to your bank:  $";
            cin >> players[1].bet;
        }
        mainMenu(newDeck);
    }
};

int main(int argc, char** argv) {
    string name;
    float bet = 0.0f;
    deck newDeck = deck();
    cout << "\nWhat is your name:  ";
    cin >> name;
    cout << "\nHow much are you willing to bet:  ";
    cin >> bet;
    blackJack newBlackJack = blackJack(name, bet);
    newBlackJack.mainMenu(newDeck);

    return 0;
}


