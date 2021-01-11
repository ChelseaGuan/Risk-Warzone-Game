
#ifndef COMP345_WARZONEGAME_PLAYER_H
#define COMP345_WARZONEGAME_PLAYER_H
#include "Map.h" //territories
#include "Cards.h" //cards
#include "Orders.h"
//#include "PlayerStrategies.h"
class Map;
class PlayerStrategy;
class Player {
private:
    //attributes
    std::string* playerName;
    std::vector<Territory*> playersTerritories; //Unused
    std::vector<Territory*> attackingTerritories;//Unused
    Hand* handOfCards;
    OrdersList* playerOrdersList;
    int reinforcementPool;
    Map* gameMap;
    //strategy pattern-------------------------------------------------
    PlayerStrategy *playerStrategy;
    std::vector<Player*> negotiatePlayers;
public:
    //Default constructors
    Player();
    //Constructor
    Player(std::string id);
    //copy constructor
    Player(const Player &player);
    //destructor
    ~Player();
    //assignment operator
    Player& operator=(const Player &player);
    void setGameMap(Map& map);
    //Part 4 methods
    std::vector<Territory*> toDefend(); //returns list of territories to be defended (arbitrary list)
    std::vector<Territory*> toAttack(); //returns list of territories to be attacked (arbitrary list)
    bool isAdjacentTerritory(int adjTerrId);
    void issueOrder(); //creates an Order object and puts it in the player’s list of orders

    void setPlayersTerritories(std::vector<Territory*> territories);
    void setAttackingTerritories(std::vector<Territory*> territories);
    void addNegotiatePlayer(Player& other);
    void clearNegotiatePlayer();
    bool isNegotiatePlayer(Player& other);
    //Player mutators and accessors
    void setPlayerName(std::string id);
    std::string getPlayerName();
    std::vector<Territory*> getPlayersTerritories();
    std::vector<Territory*> getAttackingTerritories();
    Hand *getHandOfCards();
    OrdersList *getPlayerOrdersList();
    int getReinforcementPool();
    void removeInReinforcementPool(int numArmies);
    void addPlayersTerritories(Territory*  territories);
    void addArmiesToReinforcementPool(const int val);
    void randomizeTerritories(std::vector<int>& defend, std::vector<int>& attack);
    //Insertion stream operator overload
    friend std::ostream& operator<<(std::ostream& output, const Player &player);
    friend class GameEngine;

    //strategy pattern-------------------------------------------------
    Player(PlayerStrategy *initStrategy);
    void setPlayerStrategy(PlayerStrategy *newStrategy);
    PlayerStrategy* getPlayerStrategy();
};


#endif //COMP345_WARZONEGAME_PLAYER_H