#include "../src/Header_Files/Cards.h"

int main(){

    Deck* deckOfCards = new Deck(); //Generating all different sort of cards  //Memory leak
    Card drawnCard = deckOfCards->draw(); //Drawing a card randomly
    Hand* hand = new Hand(); //Creating a Hand object //Memory leak
    hand->add(drawnCard);//Adding the card drawn in the hand
    hand->getCardsInHand()->at(0).play(); //Quite hard coded, but playing the card in hand.
}