#include "GameEngine.h"

int main() {
    GameEngine gamePart2;
    gamePart2.createGame("../src/_MapFiles");
    gamePart2.startupPhase();
    gamePart2.mainGameLoop();
}
