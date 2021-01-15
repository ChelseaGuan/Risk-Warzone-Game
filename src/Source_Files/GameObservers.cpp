#include "GameEngine.h"
#include "GameObservers.h"
#include <iostream>


// OBSERVER

Observer::Observer(){
}
Observer::~Observer(){
}



// SUBJECT

Subject::Subject(){
    _observers = new std::list<Observer*>;
}
Subject::~Subject(){
    delete _observers;
}
void Subject::attach(Observer* o){
    _observers->push_back(o);
}
void Subject::detach(Observer* o){
    _observers->remove(o);
}
void Subject::notify(){
    std::list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->update();
}




// PHASE OBSERVER

// Constructors
PhaseObserver::PhaseObserver() {
}

PhaseObserver::PhaseObserver(GameEngine* s) {
    _subject = s;
    _subject->attach(this);
}

// Destructor
PhaseObserver::~PhaseObserver() {
    _subject->detach(this);
}


// Called by notify() when the phase changes
void PhaseObserver::update() {
    // If the observer needed is the phase observer, call the display method for it,
    // else skip for this iteration
    if (this->_subject->getObserverType() == 0)
        display(this->_subject->getPlayerTurn(), this->_subject->getPhaseName());
}



// Displays player's phase.
void PhaseObserver::display(std::string playerName, std::string phaseName) {
    std::cout << "\nv************************************************v\nPlayer " << playerName << ": " << phaseName << "\n";
    Player* p;
    for (auto &&player: *_subject->getPlayers()) {
        if (player->getPlayerName() == playerName)
            p = player;
    }

    if (phaseName == "Reinforcement phase") {
        std::cout << "Player " << playerName << " has " << p->getReinforcementPool() << " armies in their reinforcement pool.\n";
    }
    if (phaseName == "Issue orders phase") {
        std::cout << "Player " << playerName << "'s order list:\n" << *p->getPlayerOrdersList();
    }
    if (phaseName == "Execution phase") {
        std::cout << "Player " << playerName << " controls territories:\n";
        for (auto&& territory: p->toDefend())
            std::cout << *territory;

        std::cout << "\nPlayer " << playerName << " can attack territories:\n";
        for (auto&& territory: p->toAttack())
            std::cout << *territory;
    }

    std::cout << "^************************************************^\n\n";
}





// GAME STATISTICS OBSERVER

// Constructors
GameStatsObserver::GameStatsObserver() {
}

GameStatsObserver::GameStatsObserver(GameEngine* s) {
    _subject = s;
    _subject->attach(this);
}

// Destructor
GameStatsObserver::~GameStatsObserver() {
    _subject->detach(this);
}

// Called by notify() when the state of the map changes
void GameStatsObserver::update() {
    // If the observer needed is the game statistics observer, call the display method for it,
    // else skip for this iteration
    if (this->_subject->getObserverType() == 1)
        display();
}


// Displays players world domination view.
void GameStatsObserver::display() {
    std::cout << "\nv************************************************v\nPlayers world domination view\n";
    double totNumTerr = _subject->getMap()->getNumberOfTerritories();
    int playerNumTerr;
    for (auto&& x: *_subject->getPlayers()) {
        playerNumTerr = x->getPlayersTerritories().size();
        std::cout << "Player " << x->getPlayerName() << " controls " << static_cast<double>(playerNumTerr)/totNumTerr*100 << "% of the world.\n";
    }
    std::cout << "^************************************************^\n";
    if (_subject->getPlayers()->size() == 1)
        std::cout << "Congratulations, you win!\n\n";
}




