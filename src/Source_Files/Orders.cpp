
#include "Orders.h"
#include <cstdlib>
#include "Player.h"
#include "Map.h"
#include <random>
//====================================ORDERLIST CLASS====================================
//Constructors
OrdersList::OrdersList() : listOfOrders{std::vector<Order*>()} {};
// Copy constructor for Order List
OrdersList::OrdersList(const OrdersList & oL) {
    listOfOrders = oL.listOfOrders;
}
//Destructor
OrdersList::~OrdersList() {
    for (auto order : listOfOrders)
    {
        delete order;
    }
    listOfOrders.clear();
}
// Assignment operator
OrdersList &OrdersList::operator=(const OrdersList &orderList) {
    if(this != &orderList){
        for(auto&& order: listOfOrders){
            delete order;
        }
        listOfOrders.clear();
        listOfOrders = orderList.listOfOrders;
    }
    return *this;
}
//Stream insertion operator
std::ostream &operator<<(std::ostream &output, OrdersList &oL) {
    int i = 1;
    for (auto&& order : oL.getListOfOrders()){
        output <<i<<".\t"<< *order << "\t[...]\n";
        i++;
    }
    return output;
}

std::vector<Order*> OrdersList::getListOfOrders()  {
    return listOfOrders;
}
//Method move FIXME: Incomplete
void OrdersList::move(const Order& order, int new_position) {
    try{
        if (new_position <= listOfOrders.size()){
            for (int i = 1; i <= listOfOrders.size(); i++) {
//            if (i == order.getIntType()) {
                listOfOrders.erase(listOfOrders.begin() + i);
//                listOfOrders->insert(listOfOrders->begin() + new_position - 1, order);
//                break;
//            }
            }
        }
    } catch (int new_position) {
        std::cout << "The position you entered is greater than the size of the list of orders";
        std::cout <<"The size is " << listOfOrders.size() << "\n";
        std::cout << "And the position you chose is " << new_position << std::endl;

    }
}
void OrdersList::deleteOrder(int position) {
    listOfOrders.erase(listOfOrders.begin() + (position));
}

void OrdersList::add(Order* order) { listOfOrders.push_back(order);
}

//====================================ORDER CLASS====================================
//Constructors
Order::Order(){ this->name = "Invalid"; }

Order::Order(std::string name, Player& person) {
    this->name = name;
    issuer = &person;
}

Order::Order(std::string name, Player& person, Territory& target, int numArmies) {
    this->name = name;
    this->issuer = &person;
    this->origin = nullptr;
    this->destination = &target;
    this->numberOfArmiesToMove = numArmies;
}
Order::Order(std::string name, Player& person, Territory& target) {
    this->name = name;
    this->issuer = &person;
    this->origin = nullptr;
    this->destination = &target;
}

Order::Order(std::string name, Player& person, Territory& origin, Territory& destination, int numArmies) {
    this->name = name;
    this->issuer = &person;
    this->origin = &origin;
    this->destination = &destination;
    this->numberOfArmiesToMove = numArmies;
}


// Copy constructor for Order object
Order::Order(const Order & other) {
    this->name = other.name;
    this->issuer = other.issuer;
    this->origin = other.origin;
    this->destination = other.destination;
    this->numberOfArmiesToMove = other.numberOfArmiesToMove;
}

void Order::fightSimulationMecanism() {

    this->origin->setNumArmies(*this->origin->getNumArmies() - this->numberOfArmiesToMove);

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> attackingRange(0, 100); // define the range
    std::uniform_int_distribution<> defendingRange(0, 100); // define the range
    while(this->numberOfArmiesToMove > 0 && *this->destination->getNumArmies() > 0){
        bool isDefendingKills = false;
        bool isAttackingKills = false;
        while(isDefendingKills == isAttackingKills){
            isAttackingKills = attackingRange(gen) <= 60;
            isDefendingKills = defendingRange(gen) <= 70;
        }
        if(isAttackingKills){
            //Have a decrement method
            this->destination->setNumArmies(*this->destination->getNumArmies() - 1);
        }
        else {
            this->numberOfArmiesToMove--;
        }
    }
    if(this->numberOfArmiesToMove  > *this->destination->getNumArmies()) {
        this->destination->setOwner(*this->origin->getOwner());
        this->destination->setNumArmies(this->numberOfArmiesToMove );
        this->origin->getOwner()->getHandOfCards()->add(Card(3, *this->origin->getOwner()));
    }
}


//Destructor
Order::~Order() {}


// Stream output operator
std::ostream &operator<<(std::ostream &output, Order &o) {
    output << o.name;
    return output;
}

// Assignment operator
Order &Order::operator=(const Order &o) {
    if(this != &o){
        name = o.name;
        issuer = o.issuer;
        origin = o.origin;
        destination = o.destination;
        numberOfArmiesToMove = o.numberOfArmiesToMove;
    }
    return *this;
}

//====================================ORDER sub CLASSES====================================
//TRick...
DeployOrder::DeployOrder(Player& player, int numArmies, Territory& target) : Order("DeployOrder", player, target, numArmies){}

DeployOrder::DeployOrder(const DeployOrder &other) : Order(other){}

//DeployOrder::~DeployOrder() = default;

// Stream insertion operator
std::ostream &operator<<(std::ostream &output, DeployOrder &o) {
    output << o.name;
    return output;
}

bool DeployOrder::validate() {
    std::string namePlayer  = issuer->getPlayerName();
    std::string nameOwner = destination->getOwner()->getPlayerName();
    return nameOwner == namePlayer;
}
void DeployOrder::execute() {
    if(validate()) {
        issuer->removeInReinforcementPool(numberOfArmiesToMove);
        destination->setNumArmies(*destination->getNumArmies() + numberOfArmiesToMove);
    }
    else {
        std::cout << issuer->getPlayerName() << " issued an invalid Deploy order. Cannot be executed." << std::endl;
    }
}


AdvanceOrder::AdvanceOrder(Player& player,  int numArmies, Territory& origin, Territory& destination) : Order("AdvanceOrder", player, origin, destination, numArmies){}


AdvanceOrder::AdvanceOrder(const AdvanceOrder &other) : Order(other){}

//AdvanceOrder::~AdvanceOrder() = default;

// Stream insertion operator
std::ostream &operator<<(std::ostream &output, AdvanceOrder &o) {
    output << o.name;
    return output;
}
bool AdvanceOrder::validate() {
    std::string namePlayer  = issuer->getPlayerName();
    std::string nameOwner = origin->getOwner()->getPlayerName();
    return namePlayer == nameOwner;
}

void AdvanceOrder::execute() {
    if(validate()) {
        if(this->destination->getOwner() == this->issuer){
            //Substracting the number of armies in the source territory
            if(*this->origin->getNumArmies() <= this->numberOfArmiesToMove) {
                this->origin->setNumArmies(0);
                this->destination->setNumArmies(*this->destination->getNumArmies() + *this->origin->getNumArmies());
            }
            else {
                this->destination->setNumArmies(*this->destination->getNumArmies() + this->numberOfArmiesToMove);
            }
            return;
        }
        else if(issuer->isNegotiatePlayer(*this->destination->getOwner())){
            return;
        }
        if(*this->origin->getNumArmies() <= this->numberOfArmiesToMove) {
            this->numberOfArmiesToMove = *this->origin->getNumArmies();
//            this->origin->setNumArmies(0);
//            this->destination->setNumArmies(*this->destination->getNumArmies() + *this->origin->getNumArmies());
        }
        fightSimulationMecanism();
    }
}

AirliftOrder::AirliftOrder(Player& player,  int numArmies, Territory& origin, Territory& destination) : Order("AirliftOrder", player, origin, destination, numArmies){}

AirliftOrder::AirliftOrder(const AirliftOrder &other) : Order(other){}

//AirliftOrder::~AirliftOrder() = default;

// Stream insertion operator
std::ostream &operator<<(std::ostream &output, AirliftOrder &o) {
    output << o.name;
    return output;
}

bool AirliftOrder::validate() {
    // * Needs the source territory and target territory (will check if one of them belongs to the issue)
    std::string namePlayer  = issuer->getPlayerName();
    std::string nameOwnerOfSourceTerr = origin->getOwner()->getPlayerName();
    return namePlayer == nameOwnerOfSourceTerr;

}

void AirliftOrder::execute() {
    if(validate()) {
        if(this->destination->getOwner() == this->issuer){
            //Substracting the number of armies in the source territory
            if(*this->origin->getNumArmies() <= this->numberOfArmiesToMove) {
                this->origin->setNumArmies(0);
                this->destination->setNumArmies(*this->destination->getNumArmies() + *this->origin->getNumArmies());
            }
            else {
                this->destination->setNumArmies(*this->destination->getNumArmies() + this->numberOfArmiesToMove);
                return;
            }
        }
        else if(*this->origin->getNumArmies() <= this->numberOfArmiesToMove) {
            this->origin->setNumArmies(0);
            this->destination->setNumArmies(*this->destination->getNumArmies() + *this->origin->getNumArmies());
            return;
        }
        else if(issuer->isNegotiatePlayer(*this->destination->getOwner())){
            return;
        }
        fightSimulationMecanism();
    }
}

BombOrder::BombOrder(Player& player, Territory& target) : Order("BombOrder", player, target){}

BombOrder::BombOrder(const BombOrder &other) : Order(other){}

//BombOrder::~BombOrder() = default;

// Stream insertion operator
std::ostream &operator<<(std::ostream &output, BombOrder &o) {
    output << o.name;
    return output;
}
bool BombOrder::validate() {
    std::string namePlayer  = issuer->getPlayerName();
    std::string nameOwner = destination->getOwner()->getPlayerName();
    return nameOwner != namePlayer;
}

void BombOrder::execute() {
    if (validate()){
        if(issuer->isNegotiatePlayer(*this->destination->getOwner())){
            return;
        }
        destination->setNumArmies(floor((*destination->getNumArmies())/2));
    }
}

BlockadeOrder::BlockadeOrder(Player& player, Territory& target) : Order("BlockadeOrder", player, target, -1){}

BlockadeOrder::BlockadeOrder(const BlockadeOrder &other) : Order(other){

}

//BlockadeOrder::~BlockadeOrder() = default;

// Stream insertion operator
std::ostream &operator<<(std::ostream &output, BlockadeOrder &o) {
    output << o.name;
    return output;
}
bool BlockadeOrder::validate() {
// *Needs the territory of an enemy player (hence another player object)
    std::string namePlayer  = issuer->getPlayerName();
    std::string nameOwner = destination->getOwner()->getPlayerName();
    return namePlayer == nameOwner;
}

//TODO: Neutral player needs to be implemented in this order logic.
void BlockadeOrder::execute() {
    if(validate()) {
        destination->setNumArmies(*destination->getNumArmies() * 2);
    }
}

NegotiateOrder::NegotiateOrder(Player& player, Player& targetPlayer) : Order("NegotiateOrder", player){
    this->targetPlayer = &targetPlayer;
}

NegotiateOrder::NegotiateOrder(const NegotiateOrder &other) : Order(other){
    this->targetPlayer = other.targetPlayer;
}

bool NegotiateOrder::validate() {
    return this->issuer != this->targetPlayer;
}

void NegotiateOrder::execute() {
    if(validate()){
        this->issuer->addNegotiatePlayer(*this->targetPlayer);
        this->targetPlayer->addNegotiatePlayer(*this->issuer);
    }
}

NegotiateOrder & NegotiateOrder::operator=(const NegotiateOrder &o) {
    if(this != &o){
        Order::operator=(o);
        this->targetPlayer = o.targetPlayer;
    }
    return *this;
}

//NegotiateOrder::~NegotiateOrder() = default;


// Stream insertion operator
std::ostream &operator<<(std::ostream &output, NegotiateOrder &o) {
    output << o.name;
    return output;
}
//std::vector<Player *> NegotiateOrder::executeNegotiate() {
//    std::vector<Player *> negotiateList;
//    if(validate()) {
//        negotiateList.push_back(issuer);
//        negotiateList.push_back(targetPlayer);
//        return negotiateList;
//    }
//}




//Generates a random Order of any type except Deploy.
//Order* Order::generateRandomOrder() {
//    srand(time(NULL));
//    int randomInt = rand() % 5 + 1;
//    switch(randomInt){
//        case 1:
//            return new AdvanceOrder();
//        case 2:
//            return new AirliftOrder();
//        case 3:
//            return new BombOrder();
//        case 4:
//            return new BlockadeOrder();
//        case 5:
//            return new NegotiateOrder();
//        default:
//            return nullptr;
//    }
//}



