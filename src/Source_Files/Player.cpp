#include "Player.h"
#include <random>
#include <algorithm>

// Default constructor
Player::Player(){
    playerName = new std::string("");
    handOfCards= new Hand();
    playerOrdersList= new OrdersList();
    reinforcementPool = 0;
    gameMap = nullptr;
    playerStrategy = nullptr;
}
// Constructor
Player::Player(std::string id) {
    playerName = new std::string(id);
    handOfCards= new Hand();
    playerOrdersList= new OrdersList();
    reinforcementPool = 0;
    gameMap = nullptr;
    playerStrategy = nullptr;
}
//Copy constructor
Player::Player(const Player &player) {
    this->playerName = new std::string(*(player.playerName));
    this->handOfCards = new Hand(*(player.handOfCards));
    this->playerOrdersList = new OrdersList(*(player.playerOrdersList));
    this->playersTerritories = player.playersTerritories;
    this->attackingTerritories = player.attackingTerritories;
    this->reinforcementPool = player.reinforcementPool;
    this->negotiatePlayers = player.negotiatePlayers;
    this->gameMap = player.gameMap;

}
//Destructor
 Player::~Player() {
    delete playerName;
    delete handOfCards;
    delete playerOrdersList;
    playersTerritories.clear();
    attackingTerritories.clear();
    gameMap = nullptr; // Pointer is set to a nullpointer since Player object is deleted after and outside of Player.
    delete playerStrategy;
}
// Assignment operator
Player& Player::operator=(const Player &player) {
    if(&player != this) {
        delete playerName;
        playerName = nullptr;
        playerName = new std::string(*player.playerName);
        delete handOfCards;
        handOfCards = nullptr;
        handOfCards = new Hand(*player.handOfCards);
        delete playerOrdersList;
        playerOrdersList = nullptr;
        playerOrdersList = new OrdersList(*player.playerOrdersList);
        playersTerritories = player.playersTerritories;
        attackingTerritories = player.attackingTerritories;
        gameMap = player.gameMap;
        //strategy pattern-------------------------------------------------
        delete playerStrategy;
        playerStrategy = nullptr;
        this->negotiatePlayers = player.negotiatePlayers;
    }
    return *this;
}

void Player::addArmiesToReinforcementPool(const int val) {
    reinforcementPool+=val;
}

void Player::addNegotiatePlayer(Player& other) {
    negotiatePlayers.push_back(&other);
}

void Player::clearNegotiatePlayer(){
    for(auto&& player: negotiatePlayers) {
        player = nullptr;
    }
    negotiatePlayers.clear();
}

bool Player::isNegotiatePlayer(Player& other) {
    for(auto&& otherPlayer: negotiatePlayers){
        if(otherPlayer->getPlayerName() == other.getPlayerName()){
            return true;
        }
    }
    return false;
}

void Player::randomizeTerritories(std::vector<int> &defend, std::vector<int> &attack) {
    std::iota (std::begin(defend), std::end(defend), 0);
    std::iota (std::begin(attack), std::end(attack), 0);
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(defend), std::end(defend), rng);
    std::shuffle(std::begin(attack), std::end(attack), rng);
}

void Player::setPlayersTerritories(std::vector<Territory *> territories) {
    playersTerritories = territories;
}

void Player::setAttackingTerritories(std::vector<Territory *> territories) {
    attackingTerritories = territories;
}


bool Player::isAdjacentTerritory(int adjTerrId){
    for(auto&& otherTerr: this->gameMap->getTerritoryAtPosition(adjTerrId - 1)->getAdjTerrIds()) {
        for(auto&& owningTerr: playersTerritories){
            if(*owningTerr->getTerritoryID() == otherTerr) {
                return true;
            }
        }
    }
    return false;
}

std::vector<Territory*> Player::toDefend(){
    // Returns players territories sorted by least number of armies.
    std::vector<Territory*> territoriesThatCanBeDefended;
    for(auto&& terr: *this->gameMap->getAllTerritories()){
        if(terr.getOwner() == this){
            territoriesThatCanBeDefended.push_back(&terr);
        }
    }
    std::sort(territoriesThatCanBeDefended.begin(), territoriesThatCanBeDefended.end());
    playersTerritories = territoriesThatCanBeDefended;
    return territoriesThatCanBeDefended;
}
// Returns the list of territory the player do not own, sorted by adjacent territory to non adjacent ones.
std::vector<Territory*> Player::toAttack(){ // Same as defending
    std::vector<Territory*> territoriesThatCanBeAttacked;
    for(auto&& terr: *this->gameMap->getAllTerritories()){
        if(terr.getOwner() != this) {
            if(isAdjacentTerritory(*terr.getTerritoryID())) {
                territoriesThatCanBeAttacked.insert(territoriesThatCanBeAttacked.begin(), &terr);
            }
            else {
                territoriesThatCanBeAttacked.push_back(&terr);
            }
        }
    }
    attackingTerritories = territoriesThatCanBeAttacked;
    return territoriesThatCanBeAttacked;
}
// Creates orders and adds them to players list of orders.
void Player::issueOrder(){

    auto defending = toDefend();
    auto attacking = toAttack();

    // Issues orders.
    int reinforcementPoolMockedValue = this->reinforcementPool;
    int index = 0;
    int defendingListSize =  defending.size();
    int attackingListSize =  attacking.size();
    while(reinforcementPoolMockedValue > 0) {
        if(index >=defendingListSize){
            index = 0;
        }
        else {
            this->playerOrdersList->add(new DeployOrder(*this, 3, *defending.at(index)));
            reinforcementPoolMockedValue -=3; // MIN_REINFORCEMENT
            index++;
        }
    }
    // Will allow each player to add up to 6 non deployment order. 3 AdvanceOrders and 3 others.
    // Randomize the advance order.
    std::random_device rd;  // Will be used to obtain a seed for the random number engine.
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd().
    std::uniform_int_distribution<> dis(0, 1);
    std::uniform_int_distribution<> randomDefValue(0, defendingListSize -1);
    std::uniform_int_distribution<> randomAttValue(0, attackingListSize -1);

    int randomValue;
    for(int i =0; i < defendingListSize; i++) {
        randomValue = dis(gen);
        if(randomValue == 0 && defendingListSize >= 2) {
            this->playerOrdersList->add(new AdvanceOrder(*this, 3, *defending.at(i), *defending.at(randomDefValue(gen))));
        }
        else if(randomValue == 1 && attackingListSize >=1){
            this->playerOrdersList->add(new AdvanceOrder(*this, 10, *defending.at(i), *attacking.at(randomAttValue(gen))));
        }
    }

    // Hard coded way to play cards... True implementation should reside in the card class.
    this->handOfCards->cardsInHand->push_back(Card(0, *this));
    this->handOfCards->cardsInHand->push_back(Card(0, *this));
    this->handOfCards->cardsInHand->push_back(Card(0, *this));
    this->handOfCards->cardsInHand->push_back(Card(3, *this));
    this->handOfCards->cardsInHand->push_back(Card(3, *this));
    for(auto&& card: *this->handOfCards->cardsInHand) {
            card.play();
    }
    }

//Player mutators and accessors
void Player::setPlayerName(std::string id){
   *playerName = id;
}

std::string Player::getPlayerName(){
    return *playerName;
}


std::vector<Territory*> Player::getPlayersTerritories(){
    return playersTerritories;
}
std::vector<Territory*> Player::getAttackingTerritories(){
    return attackingTerritories;
}

Hand *Player::getHandOfCards(){
    return handOfCards;
}

OrdersList *Player::getPlayerOrdersList() {
    return playerOrdersList;
}

int Player::getReinforcementPool() {
    return reinforcementPool;
}

void Player::setGameMap(Map &map) {
    gameMap = &map;
}

void Player::removeInReinforcementPool(int numArmies) {
    if(this->reinforcementPool <= numArmies) {
        this->reinforcementPool = 0;
    }
    else {
        this->reinforcementPool -= numArmies;
    }
}



//add a territory to the players list of territories
void Player::addPlayersTerritories(Territory*  territories){
    this->playersTerritories.push_back(territories);
}


//Insertion stream operator overload
std::ostream& operator<<(std::ostream& output, const Player &player){
    output <<"\n=============\tPlayer Name: " << *player.playerName <<"\t=============\n";

    output<<"Your hand of Warzone card: ";
    if(player.handOfCards->getCardsInHand() == nullptr ){
        output<<"None";
    }
    else if(player.handOfCards->getCardsInHand()->empty()) {
        output<<"None";
    }else {
        for (auto &&card: *player.handOfCards->getCardsInHand()) {
            output << card << ", ";
        }
    }

    output<<"\nYour Order list:  ";
    if(player.playerOrdersList->getListOfOrders().empty()){
        output<<"None";
    }
    else {
        for (auto &&order:player.playerOrdersList->getListOfOrders()) {
            output << *order << ", ";
        }
    }
    return output;
}
//strategy pattern-------------------------------------------------
Player::Player(PlayerStrategy *initStrategy) {
    this->playerStrategy = initStrategy;
}

void Player::setPlayerStrategy(PlayerStrategy *newStrategy) {
    delete this->playerStrategy;
    this->playerStrategy = newStrategy;
}

PlayerStrategy* Player::getPlayerStrategy(){
    return this->playerStrategy;
}
