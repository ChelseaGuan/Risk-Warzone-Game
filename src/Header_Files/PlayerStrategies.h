#include <iostream>
#include "Map.h"
class Player;
class Territory;

class PlayerStrategy {
protected:
    Map* game;
    Player* player;
    std::string type;
public:
    PlayerStrategy();
    PlayerStrategy(Map& game, Player& player);
    PlayerStrategy(Map& game, Player& player, std::string type);
    ~PlayerStrategy();
    PlayerStrategy(const PlayerStrategy &otherStrategy);
    PlayerStrategy& operator=(const PlayerStrategy &otherPlayer);
    friend std::ostream& operator<<(std::ostream& output, const PlayerStrategy &otherPlayer);
    virtual std::vector<Territory*> toDefend()=0;
    virtual std::vector<Territory*> toAttack()=0;
    virtual void issueOrder()=0;
};

class HumanPlayerStrategy: public PlayerStrategy{
public:
    HumanPlayerStrategy();
    HumanPlayerStrategy(Map& game, Player& player);
    ~HumanPlayerStrategy();
    HumanPlayerStrategy(const HumanPlayerStrategy &otherStrategy);
    HumanPlayerStrategy& operator=(const HumanPlayerStrategy &otherPlayer);
//    friend std::ostream& operator<<(std::ostream& output, const HumanPlayerStrategy &otherPlayer);
    std::vector<Territory*> toDefend();
    std::vector<Territory*> toAttack();
    void issueOrder();
};

class AggressivePlayerStrategy: public PlayerStrategy{
public:
    AggressivePlayerStrategy();
    AggressivePlayerStrategy(Map& game, Player& player);
    ~AggressivePlayerStrategy();
    AggressivePlayerStrategy(const AggressivePlayerStrategy &otherStrategy);
    AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy &otherPlayer);
    bool reinforceStrongest();
//    friend std::ostream& operator<<(std::ostream& output, const AggressivePlayerStrategy &otherPlayer);
    std::vector<Territory*> toDefend();
    std::vector<Territory*> toAttack();
    void issueOrder();
};

class BenevolentPlayerStrategy: public PlayerStrategy{
public:
    BenevolentPlayerStrategy();
    BenevolentPlayerStrategy(Map& game, Player& player);
    ~BenevolentPlayerStrategy();
    BenevolentPlayerStrategy(const BenevolentPlayerStrategy &otherStrategy);
    BenevolentPlayerStrategy& operator=(const BenevolentPlayerStrategy &otherPlayer);
    void reinforceWeakest();
//    friend std::ostream& operator<<(std::ostream& output, const BenevolentPlayerStrategy &otherPlayer);
    std::vector<Territory*> toDefend();
    std::vector<Territory*> toAttack();
    void issueOrder();
};

class NeutralPlayerStrategy: public PlayerStrategy{
public:
    NeutralPlayerStrategy();
    NeutralPlayerStrategy(Map& game, Player& player);
    ~NeutralPlayerStrategy();
    NeutralPlayerStrategy(const NeutralPlayerStrategy &otherStrategy);
    NeutralPlayerStrategy& operator=(const NeutralPlayerStrategy &otherPlayer);
//    friend std::ostream& operator<<(std::ostream& output, const NeutralPlayerStrategy &otherPlayer);
    std::vector<Territory*> toDefend();
    std::vector<Territory*> toAttack();
    void issueOrder();
};