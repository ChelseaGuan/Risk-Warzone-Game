#include "Cards.h"
#include <cstdlib>
#include <ctime>

#include "Player.h"
class BombOrder;
class AirliftOrder;
class NegotiateOrder;
//class DeployOrder;

//==============================CARD==========================================
//Constructors
Card::Card(){
    type = nullptr;
    typeName = nullptr;
}

Card::Card(int enumValue) : type {new CardType }, typeName {new std::string("")}{
    //Taking advantage of the fact that enum in c++ have
    //an int equivalent. so we initialize the card with an integer
    //within the range : 0 to 6.
    //Why? This makes the code less hardcoded for the initializing of cards
    switch(enumValue) {
        case 0:
            this->typeName = new std::string("Bomb");
            *this->type =  Bomb;
            break;
        case 1:
            this->typeName = new std::string("Reinforcement");
            *this->type = Reinforcement;
            break;
        case 2:
            this->typeName = new std::string("Blockade");
            *this->type = Blockade;
            break;
        case 3:
            this->typeName = new std::string("Airlift");
            *this->type = Airlift;
            break;
        case 4:
            this->typeName = new std::string("Diplomacy");
            *this->type = Diplomacy;
            break;
        default:
            break;
    }
}

Card::Card(int enumValue, Player& player) : type {new CardType }, typeName {new std::string("")}{
    //Taking advantage of the fact that enum in c++ have
    //an int equivalent. so we initialize the card with an integer
    //within the range : 0 to 6.
    //Why? This makes the code less hardcoded for the initializing of cards
    switch(enumValue) {
        case 0:
            this->typeName = new std::string("Bomb");
            *this->type =  Bomb;
            break;
        case 1:
            this->typeName = new std::string("Reinforcement");
            *this->type = Reinforcement;
            break;
        case 2:
            this->typeName = new std::string("Blockade");
            *this->type = Blockade;
            break;
        case 3:
            this->typeName = new std::string("Airlift");
            *this->type = Airlift;
            break;
        case 4:
            this->typeName = new std::string("Diplomacy");
            *this->type = Diplomacy;
            break;
        default:
            break;
    }
    this->owner = &player;
}


//Destructor
Card::~Card() {
    //delete type; An enum is not dynamically allocated.
    // Thus, explicitly  calling delete on it won't work.
    delete typeName;
    type = nullptr;
    typeName = nullptr;
}

void Card::setCardOwner(Player& player) {
    owner = &player;
}

//copy constructor
Card::Card(const Card &card) {
    type = card.type;
    typeName = new std::string(*card.typeName);
    owner = card.owner;
}

//Assignment operator
Card& Card::operator=(const Card &card) {
    if(this != &card) {
        type = nullptr;
        delete typeName;
        typeName = nullptr;
        type = card.type;
        typeName = new std::string(*card.typeName);
        owner = card.owner;
    }
    return *this;
}
//Stream insertion operator
std::ostream& operator<<(std::ostream& output, const Card &card){
    output <<*card.typeName;
    return output;
}

Order* Card::getOrderFromCard(){
    if(owner->toAttack().empty()) {
        return nullptr;
    }
    int index = owner->toAttack().size()-1;
    switch(*this->type){
        case Bomb:
            return new BombOrder(*owner, *(owner->toAttack().at(index)));
//        case Reinforcement:
//            return new DeployOrder();
        case Airlift:
            return new AirliftOrder(*owner, 20, *owner->toDefend().at(0), *owner->toDefend().at(owner->toDefend().size()-1));
//        case Diplomacy:
//            return new NegotiateOrder();
        case Blockade:
            return new BlockadeOrder(*owner, *owner->toDefend().at(0));
        default:
            return nullptr;
    };
}
//Play method
void Card::play() {
    std::cout<<*this->typeName<<" is being played. Issuing Order."<<std::endl;
    this->owner->getPlayerOrdersList()->add(getOrderFromCard());
}

//==============================DECK==========================================
Deck::Deck() : cardsList {new std::vector<Card>}{
    //This causes the program to start generating numbers from
    // a different point in the sequence every time it is run,
    // making it appear to be less predictable.
    srand(time(NULL));

    //Filling the vector of Cards in the deck by adding
    // Cards with all possible values for the enum (type of cards).
    for(int i=0; i < 5; i++) {
        this->cardsList->push_back(Card(i));
    }
}

//Copy constructor
Deck::Deck(const Deck &deck) {
    cardsList = new std::vector<Card>(*deck.cardsList);
}

//Destructor
Deck::~Deck() {
    cardsList->clear();
    delete cardsList;
    cardsList = nullptr;
}

//Assignment operator
Deck& Deck::operator=(const Deck &deck) {
    if(this != &deck) {
        delete cardsList;
        cardsList = nullptr;
        cardsList = new std::vector<Card>(*deck.cardsList);
    }
    return *this;
}

//Draw method
Card Deck::draw() {
    int randomCardNumber = rand() % this->cardsList->size();
    Card cardDrawn =  this->cardsList->at(randomCardNumber);
    std::cout << "The deck has "<<this->cardsList->size()
    <<" cards & "<<*this<<"\nThe hand is drawing a card...The card drawn is: "<<cardDrawn;
    this->cardsList->erase(this->cardsList->begin() + randomCardNumber);
    std::cout<<"\nThe deck has now "<<this->cardsList->size()<< " cards. & "<<*this<<std::endl;
    return cardDrawn;
}

//Stream insertion operator
std::ostream& operator<<(std::ostream& output, const Deck &deck){
    output<<"The deck of cards has: ";
    for (auto&& element : *deck.cardsList) {
        output <<element << " | ";
    }
    return output;
}

//==============================HAND==========================================
//Constructors
Hand::Hand() : cardsInHand {new std::vector<Card>()}{
}

//Hand::Hand(Player* player) {
//    owner = player;
//}

//Copy constructor
Hand::Hand(const Hand &hand) {
    cardsInHand = new std::vector<Card>(*hand.cardsInHand);
}

//Destructor
Hand::~Hand() {
    cardsInHand->clear();
    delete cardsInHand;
    cardsInHand = nullptr;
    //FIXME: nebuleux tout ca....
//    if(owner != nullptr) {
//        delete owner;
//    }
}

void Hand::add(Card card) {
    this->cardsInHand->push_back(card);
}

//Getter
std::vector<Card> *Hand::getCardsInHand() {
    return cardsInHand;
}

//Assignment operator
Hand& Hand::operator=(const Hand &hand) {
    if(this != &hand){
        delete cardsInHand;
        cardsInHand = nullptr;
        cardsInHand = new std::vector<Card>(*hand.cardsInHand);
    }
    return *this;
}

//Stream insertion operator
std::ostream& operator<<(std::ostream& output, const Hand &hand){
    for(auto&& card: *hand.cardsInHand){
        output << card << "\t|\t";
    }
    return output;
}

