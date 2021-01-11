//
// Created by user on 2020-09-30.
//

#include "../src/Header_Files/Player.h"
#include <iostream>

    int main() {
        std::string name;
        std::cout<<"Welcome, enter your players name:  ";
        std::cin>>name; std::cout<<std::endl;

        auto* player1 = new Player(name); //MEMORY LEAK
        player1->issueOrder();
        std::cout<<*player1;

        auto defendT = player1->toDefend();
        std::cout<<"\n\nThe Territories you are defending: \n";
        for(auto&& territory:defendT){
            std::cout<<*territory;
        }
        auto attackT = player1->toAttack();
        std::cout<<"\nThe Territories you are attacking: \n";
        for(auto&& territory:player1->toAttack()){
            std::cout<<*territory;
        }

    return 0;
}
