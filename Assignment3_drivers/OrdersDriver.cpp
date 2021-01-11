
#include "../src/Header_Files/Orders.h"
#include <iostream>

int main() {

    int chosen_order_number = 0;
    int position_number = 0;
    std::string done1 = "n";
    std::string done2 = "n";
    Order *o;
    Order *replacement;
    OrdersList *oL;
    oL = new OrdersList(); //Memory Leak
    //Added by A. J
    for (int i =0; i < 8; i++) {
        oL->add(Order(i+1));
    }

    int order_number = 0;
    int orderListSize = oL->getListOfOrders()->size();
    std::cout<<"What order do you choose for this round?\n(Enter the number of the option)\n"
        <<*oL;
    do {
        std::cout<<"\nInput: ";
        std::cin >> order_number;
        if(order_number > 0 && order_number <= orderListSize) {
            std::cout << "You chose the order " << oL->getListOfOrders()->at(order_number - 1) << "\n"
                      << std::endl;
            std::cout << "Are you sure with your choice? (y/n)\n";
            std::cin >> done1;
        }
        else {
            std::cout<<"Invalid choice, try again.";
        }
    }while((order_number < 0 || order_number > orderListSize) && done1 != "y");

    do {
        int option_number = 0;
        while (option_number <= 0 || option_number > orderListSize) {
            std::cout << "What option do you choose for this order? (Enter the number of the option)"
                      << "\n 1. Move [...]"
                      << "\n 2. Delete [...]"
                      << "\n 3. Execute [...]"
                      << "\n";
            std::cin >> option_number;
            std::cout << "Your chose the option " << option_number << "\n" << std::endl;

            switch (option_number) {
                case 1:
                    std::cout << "At what position do you wish to move it\n";
                    std::cin >> position_number;
                    oL->move(Order(order_number), position_number);
                    std::cout<<*oL;// move method - gucci
                    break;
                case 2:
                    oL->deleteOrder(order_number); // delete method - gucci
                    std::cout<<*oL<<"\n"<<std::endl; //replaced printOrders
                    break;
                case 3:
                    Order(order_number).execute(); //validate method of the Order - gucci
                    break;

                default:
                    std::cout << "Sorry buddy your answer was not registered";
            }
        }
        std::cout << "" << std::endl;
        std::cout << "Are you done with your choice? (y/n)\n";
        std::cin >> done2;
    }while(done2 == "n");

    std :: cout << "Thank you for playing my g!" << std::endl;
}
