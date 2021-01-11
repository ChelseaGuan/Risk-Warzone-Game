#ifndef COMP345_WARZONEGAME_GAMEENGINE_H
#define COMP345_WARZONEGAME_GAMEENGINE_H

#include "Map.h" //territories
#include "Cards.h" //cards
#include "Orders.h"
#include "Player.h"
#include "GameObservers.h"
#include "MapLoader.h"
#include "PlayerStrategies.h"

namespace Core {
    class GameEngine;
}

class GameEngine : public Subject {

private:
    std::string mapFileName;
    Map* gameMap;
    std::vector<Player*>* players; //FIXME: should be sorted with the correct order
    int numPlayers; //kinda useless... you can just use the size of the players
    Deck* deck;
    bool phaseObserver;
    bool gameStatsObserver;
    int initialArmies;//initial army of a player
    int reinforcementPhase();
    int issueOrdersPhase();
    void executeOrdersPhase();
    int isPlayerOwningContinent(Player& p);
    MapLoader* mapLoader;

public:
    // Constructors and destructor
    GameEngine();
    GameEngine(const GameEngine& ge);
    ~GameEngine();

    // Operator overload
    GameEngine& operator=(const GameEngine &ge);
    friend std::ostream& operator<<(std::ostream& output, const GameEngine &ge);

    void setPlayerStrategy(Player& player, int strategyId);
    void settingStrategies();
    // Accessors and mutators
    Map* getMap();
    std::vector<Player*>* getPlayers();
    Deck* getDeck();
    bool getPhaseObserver();
    bool getGameStatsObserver();
    int isThereEmptyPlayers();
    void initNumArmies();
    const int MIN_REINFORCEMENT = 3;
    const std::vector<std::string> orderPriority = { "DeployOrder", "AdvanceOrder", "AirliftOrder", "BombOrder", "BlockadeOrder","NegotiateOrder"};
    int hasOrderOfPriority(Player& player, std::string orderName);
    int executeOrderWithPriority(std::string orderPriority);
    bool isPlayerOwningAllContinents();
    void playersHaveMinTerritories();

    void clearAllNegotiation();

    std::string chooseMap(std::string dirName);
    bool createValidMap();
    void chooseNumPlayers();
    void turnOnOffObservers();

    // Part 1
    void createGame(std::string dirName);
    //Part 2: GameEngine play: game startup phase
    void startupPhase();
    //Part 3: Gameplay: Main GameEngine loop
    void mainGameLoop();

    void updateStrategy();
};


#endif //COMP345_WARZONEGAME_GAMEENGINE_H