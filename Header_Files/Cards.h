#ifndef COMP345_WARZONEGAME_CARDS_H
#define COMP345_WARZONEGAME_CARDS_H
#include <vector>
#include <iostream>
#include <fstream>
#include "Orders.h"
enum CardType {
    Bomb = 0,
    Reinforcement =1,
    Blockade = 2,
    Airlift = 3,
    Diplomacy= 4
};
class Player;
class Order;
//====================================CARD CLASS====================================
class Card {
public:
    Card();
    explicit Card(int enumValue);
    explicit Card(int enumValue, Player& owner);
    Card(const Card &card);
    ~Card();
    void play();
    Order* getOrderFromCard();
    void setCardOwner(Player& player);
    Card& operator=(const Card &card); //assignment operator
    friend std::ostream& operator<<(std::ostream& output, const Card &card);//stream insertion operator


private:
    CardType* type; //type of card
    std::string* typeName; //type of the card in string (for output purposes)
    Player* owner;
};

//====================================DECK CLASS====================================
class Deck {
private:
    std::vector<Card> *cardsList; //cards contained within a deck
public:
    Deck();
    Deck(const Deck &deck);
    ~Deck();
    Card draw();
    Deck& operator=(const Deck &deck);
    friend std::ostream& operator<<(std::ostream& output, const Deck &deck);
};

//====================================Hand CLASS====================================
class Hand {
private:
    std::vector<Card> *cardsInHand; //cards that a hand has.
//    Player* owner;
public:
    Hand();
//    Hand(Player* player);
    Hand(const Hand &hand);
    ~Hand();
    void add(Card card);
    std::vector<Card> *getCardsInHand();
    Hand& operator=(const Hand &hand); //assignment operator
    friend std::ostream& operator<<(std::ostream& output, const Hand &hand); //stream insertion operator
    friend class Player;
};

#endif //COMP345_WARZONEGAME_CARDS_H
