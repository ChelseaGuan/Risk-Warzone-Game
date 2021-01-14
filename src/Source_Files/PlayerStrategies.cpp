
#include "PlayerStrategies.h"
#include "Player.h"
#include "Orders.h"

//#include <bits/stdc++.h>

// PlayerStrategy
PlayerStrategy::PlayerStrategy() {}

PlayerStrategy::PlayerStrategy(Map& game, Player& player){
    this->game = &game;
    this->player = &player;
}

PlayerStrategy::PlayerStrategy(Map& game, Player& player, std::string type){
    this->game = &game;
    this->player = &player;
    this->type = type;
}
//TODO: Check if destructor is inherited.
PlayerStrategy::~PlayerStrategy() {
    this->game = nullptr;
    this->player = nullptr;
}

PlayerStrategy::PlayerStrategy(const PlayerStrategy &otherStrategy) {
    this->game = otherStrategy.game;
    this->player = otherStrategy.player;
}

PlayerStrategy &PlayerStrategy::operator=(const PlayerStrategy &otherPlayer) {
    if(this != &otherPlayer){
        this->game = nullptr;
        this->game = otherPlayer.game;
        this->player = nullptr;
        this->player = otherPlayer.player;
    }
    return *this;
}


std::ostream &operator<<(std::ostream &output, const PlayerStrategy &strategy) {
    output << strategy.type;
    return output;
}


//1-HumanPlayerStrategy -  human player that requires user interaction to make decisions
HumanPlayerStrategy:: HumanPlayerStrategy(): PlayerStrategy() {}

HumanPlayerStrategy::HumanPlayerStrategy(Map& game, Player& player): PlayerStrategy(game, player, "Human Player Strategy") {}

HumanPlayerStrategy::~HumanPlayerStrategy() {}


HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy &otherStrategy): PlayerStrategy(otherStrategy) {}

HumanPlayerStrategy & HumanPlayerStrategy::operator=(const HumanPlayerStrategy &otherPlayer) {
    PlayerStrategy::operator=(otherPlayer);
    return *this;
}



//std::ostream &operator<<(std::ostream &output, const HumanPlayerStrategy &otherPlayer) {return output;}

std::vector<Territory*> HumanPlayerStrategy::toDefend(){
    //return players territories sorted by least number of armies.
    std::vector<Territory*> territoriesThatCanBeDefended;
    for(auto&& terr: *this->game->getAllTerritories()){
        if(terr.getOwner() == this->player){
            territoriesThatCanBeDefended.push_back(&terr);
        }
    }
    std::sort(territoriesThatCanBeDefended.begin(), territoriesThatCanBeDefended.end());
//    playersTerritories = territoriesThatCanBeDefended;
    return territoriesThatCanBeDefended;
}

std::vector<Territory*> HumanPlayerStrategy::toAttack(){
    std::vector<Territory*> territoriesThatCanBeAttacked;
    for(auto&& terr: *this->game->getAllTerritories()){
        if(terr.getOwner() != this->player) {
            territoriesThatCanBeAttacked.push_back(&terr);
        }
    }
//    attackingTerritories = territoriesThatCanBeAttacked;
    return territoriesThatCanBeAttacked;
}

void HumanPlayerStrategy::issueOrder(){
    std::cout<<"\nHuman Player "<<this->player->getPlayerName()<<" Issuing an order...\n"<<std::endl;
    //ToDefend Territories
    std::cout<<"\nThese are your territories: "<<std::endl;
    auto defendList = toDefend();
    this->player->setPlayersTerritories(defendList);
    for(int i=0; i <= defendList.size() - 1 ; i++){
        std::cout<<(i+1)<<". "<<*defendList.at(i);
    }

    int terrId;
    int numArmies;
    int mockedReinforcementPool = this->player->getReinforcementPool();
    do {
        std::cout<<"Human Player "<<this->player->getPlayerName()<< " has "<<mockedReinforcementPool<<" armies in their reinforcement pool"<<std::endl;
        std::cout<<"Which territory you wish to deploy armies to? ";
        std::cin >> terrId;
        std::cout<<"\nHow many armies you wish to deploy? ";
        std::cin >> numArmies;
        mockedReinforcementPool -= numArmies;
        this->player->getPlayerOrdersList()->add(new DeployOrder(*this->player, numArmies, *this->player->getPlayersTerritories().at(terrId-1)));
        if(mockedReinforcementPool == 0) {
            break;
        }
    }while(this->player->getReinforcementPool() > 0);
    std::cout<<"\nNote. The territories will be updated during the order execution phase. "<<std::endl;

    //Attacking Territories
    std::cout<<"This is the territories you can attack: "<<std::endl;
    auto attackList = toAttack();
    this->player->setAttackingTerritories(attackList);
    for(int i=0; i <= attackList.size() - 1 ; i++){
        std::cout<<(i+1)<<".\t"<<*attackList.at(i);
    }

    int sourceTerrId;
    std::string wantsToAttackStr;
    do {
        std::cout<<"Do you wish to attack a territory ? (yes/y or no/n):"<<std::endl;
        std::cin>>wantsToAttackStr;
        if(wantsToAttackStr == "no" || wantsToAttackStr == "n"){
            break;
        }
        std::cout<<"From which of your territories you wish to attack with? ";
        std::cin >> sourceTerrId;
        //ToDo si on veut at the end: exception handling (when select # > # player territories)
        std::cout<<"\nWhich enemy territory you wish to attack? ";
        std::cin >> terrId;
        std::cout<<"\nHow many armies you wish to send to this territory? ";
        std::cin >> numArmies;
        mockedReinforcementPool -= numArmies;
        this->player->getPlayerOrdersList()->add(new AdvanceOrder(*this->player, numArmies, *defendList.at(sourceTerrId-1), *attackList.at(terrId - 1)));
    }while(1);
    std::cout<<"\nNote. The territories will be updated during the order execution phase. "<<std::endl;


    auto cardsList = *this->player->getHandOfCards()->getCardsInHand();
    if(cardsList.empty()){
        std::cout<<"You have no cards that you can play..."<<std::endl;
        return;
    }
    int cardId;
    do {
        std::cout << "Do you wish to play a card ? (yes/y or no/n):" << std::endl;
        std::cin >> wantsToAttackStr;
        if (wantsToAttackStr == "no" || wantsToAttackStr == "n") {
            break;
        }
        //Cards in hands
        std::cout<<"This is the cards in your hands: "<<std::endl;
        for(int i=0; i < cardsList.size() - 1 ; i++){
            std::cout<<(i+1)<<".\t"<<cardsList.at(i)<<std::endl;
        }
        std::cout<<"Which card do you wish to play?"<<std::endl;
        std::cin>>cardId;
        cardsList.at(cardId -1).play();
        cardsList.erase(cardsList.begin() + (cardId -1));
    }while(1);
    std::cout<<"This is the end of your issue order phase of human player. "<<std::endl;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}



//2-AggressivePlayerStrategy - an aggressive computer player that focuses
//on attack (reinforces its strongest country, then always attack with it until it cannot attack anymore, then fortifies in
//order to maximize aggregation of forces in one country)
AggressivePlayerStrategy::AggressivePlayerStrategy() : PlayerStrategy() {}

AggressivePlayerStrategy::AggressivePlayerStrategy(Map& game, Player& player) : PlayerStrategy(game, player, "Aggressive Player Strategy") {}

AggressivePlayerStrategy::~AggressivePlayerStrategy() {}

AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy &otherStrategy) : PlayerStrategy(otherStrategy) {}

AggressivePlayerStrategy & AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy &otherPlayer) {
    PlayerStrategy::operator=(otherPlayer);
    return *this;
}

//std::ostream &operator<<(std::ostream &output, const AggressivePlayerStrategy &otherPlayer) {return output;}

//bool compareTerritoriesByHighest (Territory* t1, Territory* t2) {
//    return t1->getNumArmies() > t2->getNumArmies();
//}

// sort using a custom function object
struct {
    bool operator()(Territory* t1, Territory* t2) const
    {
        return *t1->getNumArmies() > *t2->getNumArmies();
    }
} compareTerritoriesByHighest;

std::vector<Territory*> AggressivePlayerStrategy::toDefend(){
    //return players territories sorted by highest number of armies.
    std::vector<Territory*> territoriesThatCanBeDefended;
    for(auto&& terr: *this->game->getAllTerritories()){
        if(terr.getOwner() == this->player) {
                territoriesThatCanBeDefended.push_back(&terr);
        }
    }
    //sorting list by highest num of armies
    std::sort(territoriesThatCanBeDefended.begin(), territoriesThatCanBeDefended.end(), compareTerritoriesByHighest);

    return territoriesThatCanBeDefended;
}

std::vector<Territory*> AggressivePlayerStrategy::toAttack(){
    std::vector<Territory*> territoriesThatCanBeAttacked;
    for(auto&& terr: *this->game->getAllTerritories()){
        if(terr.getOwner() != this->player) {
            territoriesThatCanBeAttacked.push_back(&terr);
        }
    }
    return territoriesThatCanBeAttacked;
}

bool AggressivePlayerStrategy::reinforceStrongest() {
    bool found = false;
    for(auto&& terr: this->player->getPlayersTerritories()) {
        if(*terr->getNumArmies() != 0 && terr != this->player->getPlayersTerritories().at(0)) {
            found = true;
            this->player->getPlayerOrdersList()->add(new AdvanceOrder(*this->player, *terr->getNumArmies(), *terr, *this->player->getPlayersTerritories().at(0)));
        }
    }
    return found;
}

void AggressivePlayerStrategy::issueOrder(){
    std::cout<<"\nAggressive Player "<<this->player->getPlayerName()<<" Issuing an order...\n"<<std::endl;

    //ToDefend Territories
    auto defendList = toDefend();
    this->player->setPlayersTerritories(defendList);

    std::cout<<"This is your territories: "<<std::endl;
    for(int i=0; i <= defendList.size() - 1 ; i++){
        std::cout<<(i+1)<<".\t"<<*defendList.at(i);
    }



    int mockedReinforcementPool = this->player->getReinforcementPool();
    //Deploying to strongest territory
    std::cout<<"Aggressive Player "<<this->player->getPlayerName()<< " has "<<mockedReinforcementPool<<" armies in their reinforcement pool"<<std::endl;
    this->player->getPlayerOrdersList()->add(new DeployOrder(*this->player, mockedReinforcementPool, *defendList.at(0)));


    if(!reinforceStrongest()){
        //Attacking to first territory in Attacking list
        auto attackList = toAttack();
        this->player->setAttackingTerritories(attackList);
            this->player->getPlayerOrdersList()->add(new AdvanceOrder(*this->player, *defendList.at(0)->getNumArmies(), *defendList.at(0), *attackList.at(0)));
    };



//    this->player->getPlayerOrdersList()->add(new AdvanceOrder(*this->player, *defendList.at(0)->getNumArmies(), *defendList.at(0), *attackList.at(0)));

    std::cout<<"This is the end of your issue order phase of aggressive player. "<<std::endl;
}



//3-BenevolentPlayerStrategy - benevolent computer player that focuses on
//protecting its weak countries (reinforces its weakest countries, never attacks, then fortifies in order to move
//armies to weaker countries),
BenevolentPlayerStrategy::BenevolentPlayerStrategy(): PlayerStrategy() {}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Map& game, Player& player): PlayerStrategy(game, player, "Benevolent Player Strategy") {}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy &otherStrategy) : PlayerStrategy(otherStrategy) {}

BenevolentPlayerStrategy & BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy &otherPlayer) {
    PlayerStrategy::operator=(otherPlayer);
    return *this;
}

//std::ostream &operator<<(std::ostream &output, const BenevolentPlayerStrategy &otherPlayer) {
//    return output;
//}

// sort using a custom function object
struct {
    bool operator()(Territory* t1, Territory* t2) const
    {
        return *t1->getNumArmies() < *t2->getNumArmies();
    }
} compareTerritoriesByLowest;

std::vector<Territory*> BenevolentPlayerStrategy::toDefend(){
    //return players territories sorted by highest number of armies.
    std::vector<Territory*> territoriesThatCanBeDefended;
    for(auto&& terr: *this->game->getAllTerritories()){
        if(terr.getOwner() == this->player) {
            territoriesThatCanBeDefended.push_back(&terr);
        }
    }
    //sorting list by lowest num of armies
    std::sort(territoriesThatCanBeDefended.begin(), territoriesThatCanBeDefended.end(), compareTerritoriesByLowest);

    return territoriesThatCanBeDefended;
}

std::vector<Territory*> BenevolentPlayerStrategy::toAttack(){
    std::cout << "Called BenevolentPlayerStrategy's toAttack()" << std::endl;
}

void BenevolentPlayerStrategy::reinforceWeakest() {
    bool allEqual = true;
    auto defendList = this->player->getAttackingTerritories();
    for(int i = 0; i < defendList.size() - 1; i++) {
        if(*defendList.at(i)->getNumArmies() != *defendList.at(i+1)->getNumArmies()) {
            allEqual = false;
            break;
        }
    }
    //Then we must have a minimum, move it 1 army from the strongest to the weakest.
    if(!allEqual) {
        this->player->getPlayerOrdersList()->add(new AdvanceOrder(*this->player, 1, *defendList.at(defendList.size() -1), *defendList.at(defendList.size() -1)));
    }

}

void BenevolentPlayerStrategy::issueOrder(){
    std::cout<<"\nBenevolent Player "<<this->player->getPlayerName()<<" Issuing an order...\n"<<std::endl;

    //ToDefend Territories
    auto defendList = toDefend();
    this->player->setPlayersTerritories(defendList);

    std::cout<<"This is your territories: "<<std::endl;
    for(int i=0; i <= defendList.size() - 1 ; i++){
        std::cout<<(i+1)<<".\t"<<*defendList.at(i);
    }

    int mockedReinforcementPool = this->player->getReinforcementPool();
    //Deploying to strongest territory
    std::cout<<"Benevolent Player "<<this->player->getPlayerName()<< " has "<<mockedReinforcementPool<<" armies in their reinforcement pool"<<std::endl;
    this->player->getPlayerOrdersList()->add(new DeployOrder(*this->player, mockedReinforcementPool, *defendList.at(0)));

    reinforceWeakest();
}


//4-NeutralPlayerStrategy - neutral player that never issues any order
NeutralPlayerStrategy::NeutralPlayerStrategy():PlayerStrategy() {}

NeutralPlayerStrategy::NeutralPlayerStrategy(Map& game, Player& player):PlayerStrategy(game, player, "Neutral Player Strategy") {}

NeutralPlayerStrategy::~NeutralPlayerStrategy() {}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &otherStrategy): PlayerStrategy(otherStrategy) {}

NeutralPlayerStrategy & NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy &otherPlayer) {
    PlayerStrategy::operator=(otherPlayer);
    return *this;
}

//std::ostream &operator<<(std::ostream &output, const NeutralPlayerStrategy &otherPlayer) {return output;}

std::vector<Territory*> NeutralPlayerStrategy::toDefend(){
    std::vector<Territory*> mockList;
    return mockList;
}

std::vector<Territory*> NeutralPlayerStrategy::toAttack(){
    std::vector<Territory*> mockList;
    return mockList;
}

void NeutralPlayerStrategy::issueOrder(){
    std::cout << "\nCalled NeutralPlayerStrategy's... Does nothing..." << std::endl;
}




