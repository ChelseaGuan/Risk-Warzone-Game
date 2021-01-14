#include "GameEngine.h"
#include <dirent.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>    // std::random_shuffle
#include <iterator>
#include <random>


// Global variable obervers
PhaseObserver* phaseObs;
GameStatsObserver* gameStatsObs;

// GameEngine constructor.
GameEngine::GameEngine() {
    this->mapFileName = "";
    this->gameMap = nullptr; //Avoiding memory leak
    this->players = new std::vector<Player*>();
    this->numPlayers = 0;
    this->deck = new Deck();
    this->mapLoader = new MapLoader();
    this->phaseObserver = false;
    this->gameStatsObserver = false;
    this->initialArmies = false;
}

// GameEngine copy constructor.
GameEngine::GameEngine(const GameEngine& ge) {
    this->mapFileName = ge.mapFileName;
    this->gameMap = ge.gameMap;
    this->players =ge.players;
    this->numPlayers = ge.numPlayers;
    this->deck = ge.deck;
    this->phaseObserver = ge.phaseObserver;
    this->gameStatsObserver = ge.gameStatsObserver;
    this->initialArmies = ge.initialArmies;
    this->mapLoader = ge.mapLoader;
}

// GameEngine destructor.
GameEngine::~GameEngine() {
    delete gameMap;
    gameMap = nullptr;
    for (auto p : *players)
    {
        delete p;
    }
    players->clear();
    delete players;
    players = nullptr;
    delete deck;
    deck = nullptr;
    delete mapLoader;
    mapLoader = nullptr;
}



// GameEngine assignment operator
GameEngine& GameEngine::operator=(const GameEngine &ge) {
    if(&ge != this) {
        this->mapFileName =ge.mapFileName;
        delete gameMap;
        this->gameMap = new Map(*ge.gameMap);
        delete players;
        this->players = new std::vector<Player*>(*ge.players);
        this->numPlayers = ge.numPlayers;
        delete deck;
        this->deck = new Deck(*ge.deck);
        this->phaseObserver = ge.phaseObserver;
        this->gameStatsObserver = ge.gameStatsObserver;
        this->initialArmies = ge.initialArmies;
        this->mapLoader = ge.mapLoader;
    }
    return *this;
}

//GameEngine insertion stream operator
std::ostream& operator<<(std::ostream& output, const GameEngine &ge) {
    output << "MAP: " << ge.mapFileName << /*"\n" <<  *ge.gameMap << */"\n\nPLAYERS:\n";
    for (auto&& x : *ge.players)
        output << x->getPlayerName() << "\n";
    output << "\nDECK: " << *ge.deck << "\n\n";
    ge.phaseObserver ? output << "Phase observer is on.\n": output << "Phase observer is off.\n";
    ge.gameStatsObserver ? output << "Game statistics observer is on.\n\n": output << "Game statistics observer is off.\n\n";
    output << "The initial number of armies is " << ge.initialArmies << ".\n\n";
    return output;
}



// Accessors and mutators.

Map* GameEngine::getMap() {
    return gameMap;
}
std::vector<Player*>* GameEngine::getPlayers() {
    return players;
}
Deck* GameEngine::getDeck() {
    return deck;
}
bool GameEngine::getPhaseObserver() {
    return phaseObserver;
}
bool GameEngine::getGameStatsObserver() {
    return gameStatsObserver;
}

std::string GameEngine::getPlayerTurn() {
    return playerTurn;
}
std::string GameEngine::getPhaseName() {
    return phaseName;
}
bool GameEngine::getObserverType() {
    return observerType;
}



// Part 1: GameEngine start

void GameEngine::createGame(std::string dirName) {

    std::cout << "WARZONE GAME START\n\nMAPS\n";

    // Let user choose a map from the directory
    do {
        mapFileName = chooseMap(dirName);
    } while (!createValidMap());    // Create and validate the map chosen by user using MapLoader.

    // Let user choose the number of players.
    this->chooseNumPlayers();


    // Create the number of players requested by user.
    for (int i=0; i<numPlayers; i++) {
        (*players).push_back(new Player());
        (*players)[i]->setPlayerName(std::to_string(i));
        players->at(i)->setGameMap(*this->gameMap);
    }

    // Display the cards in deck.
    std::cout<<*this->getDeck()<<std::endl;

    this->turnOnOffObservers();
}


// Returns the file name corresponding to the map the user wants.
std::string GameEngine::chooseMap(std::string dirName) {
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(dirName.c_str())) != NULL) {
        std::vector<std::string> mapNames = std::vector<std::string>();
        int i = 1;
        /* print all the files within directory and store them inside a vector of strings*/
        while ((entry = readdir(dir)) != NULL) {
            std::string name = entry->d_name;
            // Ignore hidden files "." (which represents the current directory) and ".." (which represents the parent directory).
            if (name[0] != '.') {
                mapNames.push_back(name);
                std::cout << i++ << ". " << name << std::endl;
            }
        }
        closedir(dir);

        // Let user choose which map they would like to play on.
        int chosenMapNum;
        while (1) {
            std::cout << "Choose a map to play on by entering its corresponding number: ";
            if (std::cin >> chosenMapNum && chosenMapNum >= 1 && chosenMapNum <= mapNames.size())   // Validates that the map number chosen was one of the provided options
                break;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::string chosenMapFile = "../src/_MapFiles/" + mapNames[chosenMapNum - 1];
        std::cout << "You've chosen " << chosenMapFile << "\n\n";

        return chosenMapFile;
    }
    return "";
}

// Creates Map instance corresponding to the map chosen by user using MapLoader and validates it.
bool GameEngine::createValidMap() {

    // To determine whether mapFileName corresponds to a domination map file or a conquest map file, must check for both cases.

    // Verify if the Map gameMap is loaded from a valid domination map file.
    gameMap = new Map(this->mapLoader->loadMapFile(mapFileName));
    if (gameMap->validate()) {
        std::cout << "All three checks are respected. Therefore, " << mapFileName << " is valid.\n\n";
        std::cout << *gameMap;
        return true;
    }

    // Since gameMap->validate() evaluated to false, it is an invalid domination map. We delete the instances related to domination map loading
    // and try to read the file as a conquest map.
    delete mapLoader;
    delete gameMap;

    // Verify if the Map gameMap is loaded from a valid conquest map file.
    ConquestFileReader* cfr = new ConquestFileReader();
    ConquestFileReaderAdapter* adapter = new ConquestFileReaderAdapter(*cfr);
    gameMap = new Map(adapter->loadMapFile(mapFileName));

    if (gameMap->validate()) {
        std::cout << "All three checks are respected. Therefore, " << mapFileName << " is valid.\n\n";
        std::cout << *gameMap;
        return true;
    }

    // Since both verifications returned false, mapFileName corresponds to an invalid file.
    else {
        std::cout << "Not all three checks are respected. Therefore, " << mapFileName << " is invalid.\n\n";
        delete cfr;
        delete adapter;
        delete gameMap;
        return false;
    }
}

// Returns a number from 2 to 5 corresponding to the number of players
void GameEngine::chooseNumPlayers() {
    while (1) {
        std::cout << "Enter number of players (2-5): ";
        if (std::cin >> numPlayers && numPlayers >= 2 && numPlayers <= 5)
            break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


// Asks user whether they would like to turn on or off observers.
void GameEngine::turnOnOffObservers() {
    std::string input;
    // While loops are to keep prompting user in case they enter an invalid input.
    while (1) {
        std::cout << "\nWould you like to turn on observers? (Y/N): ";
        std::cin >> input;
        if (input == "y" || input == "Y") {
            while (1) {
                // Turn on/off phase observer.
                std::cout << "Would you like to turn on phase observer? (Y/N): ";
                std::cin >> input;
                if (input == "y" || input == "Y") {
                    phaseObserver = true;
                    std::cout << "Phase observer is on.\n";
                    phaseObs = new PhaseObserver(this);
                    break;
                }
                else if (input == "n" || input == "N") {
                    phaseObserver = false;
                    std::cout << "Phase observer is off.\n";
                    break;
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            while (1) {
                // Turn on/off game statistics observer.
                std::cout << "Would you like to turn on game statistics observer? (Y/N): ";
                std::cin >> input;
                if (input == "y" || input == "Y") {
                    gameStatsObserver = true;
                    std::cout << "Game statistics observer is on.\n\n";
                    gameStatsObs = new GameStatsObserver(this);
                    break;
                }
                else if (input == "n" || input == "N") {
                    gameStatsObserver = false;
                    std::cout << "Game statistics observer is off.\n\n";
                    break;
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            break;
        }

        // If user does not wish to turn on observers, output the current state of observers.
        else if (input == "n" || input == "N") {
            if (phaseObserver)
                std::cout << "Phase observer is on.\n";
            else
                std::cout << "Phase observer is off.\n";
            if (phaseObserver)
                std::cout << "GameEngine statistics observer is on.\n\n";
            else
                std::cout << "GameEngine statistics observer is off.\n\n";

            break;
        }
    }
}





// Part 2: GameEngine play: game startup phase
void GameEngine::startupPhase(){

    // Initialize random values.
    auto rd = std::random_device {};
    auto rng = std::default_random_engine {rd()};

    // Shuffle the players list and assign it a random order.
    std::shuffle(players->begin(), players->end(), rng);

    // Sequence 2
    std::vector<Territory>* allTerr = gameMap->getAllTerritories();
    double numTerritories (allTerr->size());
    double numRounds=ceil(numTerritories/(numPlayers));
    // Random numbers within a range
    std::uniform_int_distribution<> range(0, numTerritories-1);
    std::vector<int> duplicate;
    int random;
    // Add territories to each player in a random order in a round-robin fashion
    for (int i=0; i<numRounds;i++){
        for(int j=0; j<numPlayers;j++){
            random=range(rng);
            if(std::find(duplicate.begin(), duplicate.end(),random) == duplicate.end()) {
                allTerr->at(random).setOwner(*players->at(j));
                players->at(j)->addPlayersTerritories(&allTerr->at(random));
                duplicate.push_back(random);
            }
            else if (duplicate.size()==numTerritories){
                break;
            }
            else{
                j--;
                continue;
            }
        }
    }

    initNumArmies();

    // Ask the user to set the strategy of each player.
    this->settingStrategies();
    //to deliver
    //1)
    std::cout<<"Each players territory: "<<std::endl;
    int size;
    for(auto&& player: *players){
        std::cout<<*player<<std::endl;
        std::cout<<"Your collection of territories: \n";
        for(auto&& territory: player->playersTerritories){
            std::cout<<*territory;
        }
    }
    //2)
    std::cout << "\nNumber of initial armies per player: " << initialArmies << std::endl;
    //3)

    std::cout<<"The order of play in a turn: ";
    for (auto&& player : *players)
        std::cout << player->getPlayerName() << " || ";

}


// IMPLEMENT STRATEGY PATTERN

void GameEngine::setPlayerStrategy(Player& player, int strategyId){
    switch(strategyId) {
        case 1:
            player.setPlayerStrategy(new HumanPlayerStrategy(*this->gameMap, player));
            break;
        case 2:
            player.setPlayerStrategy(new AggressivePlayerStrategy(*this->gameMap, player));
            break;
        case 3:
            player.setPlayerStrategy(new BenevolentPlayerStrategy(*this->gameMap, player));
            break;
        case 4:
            player.setPlayerStrategy(new NeutralPlayerStrategy(*this->gameMap, player));
            break;
        default:
            return;
    }
}

void GameEngine::settingStrategies() {
    int strategyId;
    for(auto&& player: *players) {
        do {
            std::cout << "List of strategies:" << std::endl;
            std::cout << "1. HumanPlayerStrategy" << std::endl;
            std::cout << "2. AggressivePlayerStrategy" << std::endl;
            std::cout << "3. BenevolentPlayerStrategy" << std::endl;
            std::cout << "4. NeutralPlayerStrategy" << std::endl;
            std::cout << "Which strategy would you like to use for Player " << player->getPlayerName() << "? ";
            std::cin >> strategyId;
            if(strategyId >= 1 && strategyId <= 4) {
                setPlayerStrategy(*player, strategyId);
            }
            else{
                std::cout<<"Invalid value, please try again."<<std::endl;
            }
        }while(strategyId < 1 || strategyId > 4);
    }
}

void GameEngine::initNumArmies() {
    //sequence 3
    //setting up initial army of players
    switch (numPlayers){
        case 2:
            initialArmies=40;
            break;
        case 3:
            initialArmies=35;
            break;
        case 4:
            initialArmies=30;
            break;
        case 5:
            initialArmies=25;
            break;
        default:
            std::cout<<"Error, invalid number of players..."<<std::endl;
            return;
    }
    for(auto player: *players){
        player->addArmiesToReinforcementPool(initialArmies);
    }
}

void GameEngine::updateStrategy() {
    std::string userInput;
    for (auto &&player : *players) {
        std::cout << "\nPlayer " << player->getPlayerName() << ", do you wish to change strategy? (yes/y or no/n): ";
        std::cin >> userInput;
        if (userInput == "yes" || userInput == "y") {
            int value;
            do {
                std::cout << "Your current strategy is " << *player->getPlayerStrategy() << std::endl;
                std::cout << "List of strategies: " << std::endl;
                std::cout << "1. HumanPlayerStrategy" << std::endl;
                std::cout << "2. AggressivePlayerStrategy" << std::endl;
                std::cout << "3. BenevolentPlayerStrategy" << std::endl;
                std::cout << "4. NeutralPlayerStrategy" << std::endl;
                std::cout<< "Your decision: ";
                std::cin >> value;
                if (value >= 1 && value <= 4) {
                    setPlayerStrategy(*player, value);
                }
                else{
                    std::cout<<"Invalid value, please try again."<<std::endl;
                }
            } while (value < 1 || value > 4);

        }
    }
}

void GameEngine::mainGameLoop() {
    while(1){
        if (reinforcementPhase() == 0) {
            delete phaseObs;
            delete gameStatsObs;
            return;
        }
        if (issueOrdersPhase() == 0) {
            delete phaseObs;
            delete gameStatsObs;
            return;
        }
        executeOrdersPhase();
        updateStrategy();
    }
}

int GameEngine::isPlayerOwningContinent(Player& p) {
    auto copyTerrOfPlayer = p.getPlayersTerritories();
    std::sort(copyTerrOfPlayer.begin(), copyTerrOfPlayer.end());
    std::vector<Territory*> copyContinentTerr;
    int maxBonus = 0;
    for(auto&& continent: this->gameMap->allContinents){
        copyContinentTerr = *continent.getTerritoriesInContinent();
        std::sort(copyContinentTerr.begin(), copyContinentTerr.end());
        if(std::includes(copyTerrOfPlayer.begin(), copyTerrOfPlayer.end(), copyContinentTerr.begin(), copyContinentTerr.end())){
            maxBonus = *continent.getContinentBonus() > maxBonus ? *continent.getContinentBonus() : maxBonus;
        }
    }
    return maxBonus > 3 ? maxBonus : 3;
}
bool GameEngine::isPlayerOwningAllContinents() {
    for(auto&& player: *this->players) {
        if(player->toAttack().size() == this->gameMap->allTerritories.size()) {
            std::cout<<"Player "<<player->getPlayerName()<<"  owns all the territories and won. The game ends..."<<std::endl;
            return true;
        }
    }
    return false;
}

int GameEngine::isThereEmptyPlayers(){
    int playerId = 0;
    for(auto&& player: *this->players){
        if(player->toDefend().empty()){
            return playerId;
        }
        playerId++;
    }
    return -1;
}

void GameEngine::playersHaveMinTerritories() {
    int playerId = 0;
    for(auto&& player: *this->players){
        if(player->toDefend().empty()){
            std::cout<<"Player "<<player->getPlayerName()<<" has no territories, thus removed from the game."<<std::endl;
            players->erase(this->players->begin() + playerId);
            return;
        }
        playerId++;
    }
}


int GameEngine::reinforcementPhase() {
    std::cout<<std::endl<<"\nReinforcement Phase...\n"<<std::endl ;
    // Makes sure no one owns all territory
    if(isPlayerOwningAllContinents()){
        return 0;
    };
    // Checks if a player should get kicked out.
    do {
        playersHaveMinTerritories();
    }while(isThereEmptyPlayers() != -1);
        for(auto&& player: *players) {
            playerTurn = player->getPlayerName();
            phaseName = "Reinforcement phase";
            observerType = 0;
            notify();   // Phase observer
            int armiesFromTerr = std::floor(player->playersTerritories.size()/3);
            int continentOwnedBonus = isPlayerOwningContinent(*player);
            if(armiesFromTerr > MIN_REINFORCEMENT) {
                player->addArmiesToReinforcementPool(armiesFromTerr);
            }
            else {
                player->addArmiesToReinforcementPool(continentOwnedBonus);
            }
        }
    return 1;
}

int GameEngine::issueOrdersPhase() {
    std::cout<<"==================== ISSUING ORDER PHASE ===============\n";
    for (auto&& player : *players) {
        if(player->getPlayerStrategy()->toDefend().size() == this->gameMap->getAllTerritories()->size()){
            return 0;
        }
        player->getPlayerStrategy()->issueOrder();
        playerTurn = player->getPlayerName();
        phaseName = "Issue orders phase";
        observerType = 0;
        notify();   // Phase observer
    }
    std::cout<<"================== END ISSUING ORDER PHASE =============\n\n";
    return 1;
}

int GameEngine::hasOrderOfPriority(Player &player, std::string orderName) {
    auto orderList = player.getPlayerOrdersList()->getListOfOrders();
    int index = 0;
    bool found = false;
    for (auto&& order: orderList) {
        if (order->name == orderName) {
            found = true;
            return index;
        }
        index++;
    }
    if(index >= orderList.size() - 1 || !found) {
        return -1;
    }
}

int GameEngine::executeOrderWithPriority(std::string orderPriority) {
    int playersWithNonPrioritzedOrder = players->size();
    int index = 0;
    while(playersWithNonPrioritzedOrder > 0) {
        for (auto&& player : *players) {
            if(player->playersTerritories.size() == this->gameMap->getAllTerritories()->size()){
                std::cout<<"Player "<<player->getPlayerName()<<"  owns all the territories and won. The game ends..."<<std::endl;
                return 0;
            }
            playerTurn = player->getPlayerName();
            phaseName = "Execution phase";
            observerType = 0;
            notify();   // Phase observer

            index = hasOrderOfPriority(*player, orderPriority);
            if(index != -1) {
                player->getPlayerOrdersList()->getListOfOrders().at(index)->execute();
                std::cout<<"Player: "<<player->getPlayerName()<<"-->"<<player->getPlayerOrdersList()->getListOfOrders().at(index)->name<<"\n";
                player->getPlayerOrdersList()->deleteOrder(index);
            }
            else {
                playersWithNonPrioritzedOrder--;
            }
        }
    }
    return 1;
}

void GameEngine::clearAllNegotiation() {
    for(auto&& player: *players){
        player->clearNegotiatePlayer();
    }
}


void GameEngine::executeOrdersPhase() {
    int winner = -1;
    // Executing deploy order first
    std::cout<<"====================ORDER EXECUTION PHASE ===============\n";
    std::cout<<"\nDeploys first priority:\n";
    winner = executeOrderWithPriority("DeployOrder");

    if (winner == 0) {return;}
    std::cout<<"\nAdvance second priority:\n";
    winner = executeOrderWithPriority("AdvanceOrder");
    observerType = 1;
    notify();   // Game statistics observer
    if (winner == 0) {return;}
    std::cout<<"\nBomb third priority:\n";
    winner =  executeOrderWithPriority("BombOrder");

    if (winner == 0) {return;}
    std::cout<<"\nAirlift fourth priority:\n";
    winner =  executeOrderWithPriority("AirliftOrder");

    observerType = 1;
    notify();   // Game statistics observer

    if (winner == 0) {return;}
    winner =  executeOrderWithPriority("BlockadeOrder");

    observerType = 1;
    notify();   // Game statistics observer


    clearAllNegotiation();
    for(auto&& player: *players) {
        player->getHandOfCards()->getCardsInHand()->clear();
    }
    if(winner == 0) {return;}
    std::cout<<"====================END OF ORDER EXECUTION PHASE ===============\n";
}


