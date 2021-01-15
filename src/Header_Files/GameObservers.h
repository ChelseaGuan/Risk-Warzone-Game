#ifndef MAIN_CPP_GAMEOBSERVERS_H
#define MAIN_CPP_GAMEOBSERVERS_H

#include "GameEngine.h"
#include <list>
#include <string>

class GameEngine;


class Observer {
public:
    ~Observer();
    virtual void update() = 0;
protected:
    Observer();
};



class Subject {
public:
    Subject();
    ~Subject();
    virtual void attach(Observer* o);
    virtual void detach(Observer* o);
    virtual void notify();
private:
    std::list<Observer*>* _observers;
};



class PhaseObserver : public Observer {
public:
    PhaseObserver();
    PhaseObserver(GameEngine* s);
    ~PhaseObserver();
    void update();
    void display(std::string playerName, std::string phaseName);
private:
    GameEngine* _subject;
};


class GameStatsObserver : public Observer {
public:
    GameStatsObserver();
    GameStatsObserver(GameEngine* s);
    ~GameStatsObserver();
    void update();
    void display();
private:
    GameEngine* _subject;
};





#endif //MAIN_CPP_GAMEOBSERVERS_H
