
#ifndef COMP345_WARZONEGAME_ORDERS_H
#define COMP345_WARZONEGAME_ORDERS_H
#include <vector>
#include <iostream>
//====================================ORDER CLASS====================================
class Territory;
class Player;
class Order {
public :
    Order();
    explicit Order(std::string name, Player& person);
    explicit Order(std::string name, Player& person, Territory& destination);
    explicit Order(std::string name, Player& person, Territory& destination, int numArmies);
    explicit Order(std::string name, Player& person, Territory& origin, Territory& destination, int numArmies);
    Order(const Order&); // copy constructor
    virtual ~Order();
    virtual bool validate() = 0;
    virtual void execute() = 0; // method to execute
    void fightSimulationMecanism();
    Order& operator = (const Order& o);
    friend std::ostream &operator << (std::ostream &output, Order &o);// stream output operator
    friend class GameEngine;

protected:
    std::string name;//Will become Obsolete
    Player* issuer;
    Territory* origin;
    Territory* destination;
    int numberOfArmiesToMove;
    std:: vector <Player*> listOfNegotiate;

};
//====================================ORDER Sub classes ====================================
class DeployOrder: public Order {
public:
    DeployOrder(Player& player, int numArmies, Territory& targetTerr);
    DeployOrder(const DeployOrder& other);
    friend std::ostream &operator << (std::ostream &output, DeployOrder &o);// stream output operator
    void execute();
    bool validate() override;

};


class AdvanceOrder: public Order {
public:
    AdvanceOrder(Player& player, int numArmies, Territory& origin, Territory& destination); //Add the possibility to pass a list
    AdvanceOrder(const AdvanceOrder& other);
    friend std::ostream &operator << (std::ostream &output, AdvanceOrder &o);// stream output operator
    void execute() override;
    bool validate() override;
};


class AirliftOrder: public Order {
public:
    AirliftOrder(Player& player, int numArmies, Territory& origin, Territory& destination);
    AirliftOrder(const AirliftOrder& other);
    friend std::ostream &operator << (std::ostream &output, AirliftOrder &o);// stream output operator
    void execute() override;
    bool validate() override;
};


class BombOrder: public Order {
public:
    BombOrder(Player& player, Territory& destination);
    BombOrder(const BombOrder& other);
//    ~BombOrder();
    friend std::ostream &operator << (std::ostream &output, BombOrder &o);// stream output operator
    void execute() override;
    bool validate() override;
};


class BlockadeOrder: public Order {
public:
    BlockadeOrder(Player& player, Territory& destination);
    BlockadeOrder(const BlockadeOrder& other);
//    ~BlockadeOrder();
    friend std::ostream &operator << (std::ostream &output, BlockadeOrder &o);// stream output operator
    void execute() override;
    bool validate() override;
};
class NegotiateOrder: public Order {
public:
    NegotiateOrder(Player& player, Player& targetPlayer);
    NegotiateOrder(const NegotiateOrder& other);
//    ~NegotiateOrder();
    NegotiateOrder& operator = (const NegotiateOrder& o);
    friend std::ostream &operator << (std::ostream &output, NegotiateOrder &o);// stream output operator
//    std:: vector<Player*> executeNegotiate();
    bool validate() override;
    void execute() override;
private:
    Player* targetPlayer;
};

//====================================ORDERLIST CLASS====================================
class OrdersList {
private:
    std::vector<Order*> listOfOrders; //list of Order objects
public:
    OrdersList();
    ~OrdersList();
    OrdersList(const OrdersList&);
    std::vector<Order*> getListOfOrders(); //
    void move(const Order& order, int new_position);// method to move //FIXME: to edit
    void deleteOrder(int position); // method to delete
    void add(Order* order); // method to add an order to the list, however this method may belong to "Player.cpp"
    OrdersList& operator=(const OrdersList &ordersList); //assignment operator
    friend std::ostream &operator << (std::ostream &output, OrdersList &o);// stream output operator
};


#endif //COMP345_WARZONEGAME_ORDERS_H
