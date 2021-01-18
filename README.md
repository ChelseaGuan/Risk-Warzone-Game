# Risk-Warzone-Game

## About the Project
Worked collaboratively in a team of four developers via Github to develop a C++ program compatible with the rules of the “Warzone” version of Risk, accessible at https://www.warzone.com/.
The objective of the game is to conquer all territories on the map.

### Development
This project was developed in the CLion IDE from JetBrains.

### Features

#### Map
* The world map is a connected graph of continents and continents are connected subgraphs of territories. Each node represents a territory and each edge represents adjacency between territories.  
* Validation methods are provided to check if a map is of the desired format using depth first search. A valid map is a connected graph, where the continents are connected subgraphs and each country belongs to one and only one continent. 
  
#### Map loader
* The map loader processes any .map file, rejecting the invalid ones, but creating a corresponding map object for the valid ones. 
* Utilizes the adapter pattern to accept any Domination or Conquest .map file found at http://domination.sourceforge.net/getmaps.shtml or http://www.windowsgames.co.uk/conquest.html.

#### Players
* Two to five users can play by placing armies on territories they own, from which they can attack adjacent territories to conquer them. 
* Utilizes the strategy pattern to implement different kinds of players that make different decisions during the issuing orders phase. 
* The kinds of players are  :
  * Human player that requires user interaction to make decisions.
  * Aggressive computer player that focuses on attack.
  * Benevolent computer player that focuses on protecting its weak countries.
  * Neutral player that never issues any order.
    
#### Orders
* The orders a user can play are :
  * Deployment orders
  * Advance orders
  * Special orders resulting from using cards:
    * Deploy: Place armies on one of the current player’s territories.
    * Advance: Move armies from one of the current player’s territories (source) to an adjacent territory (target). If the target territory belongs to the current player, the armies are moved to the target territory. If the target territory belongs to another player, an attack happens between the two territories.
    * Bomb: Destroy half of the armies located on an opponent’s territory that is adjacent to one of the current player’s territories.
    * Blockade: Triple the number of armies on one of the current player’s territories and make it a neutral territory.
    * Airlift: Advance armies from one of the current player’s territories to any another territory.
    * Negotiate: Prevent attacks between the current player and another player until the end of the turn. 
    
#### Game Engine
* Includes the game startup phase and the main game loop.
* Utilizes the observer pattern to display game statistics (which player owns what percentage of the world) and phases (which player's turn it is to).  
  
  
## Sample output  

```
WARZONE GAME START

MAPS
1. 3D Cliff.map
2. canada.map
3. canada_invalid.map
4. europass.map
5. Flower S.map
6. _62_ small - CASTLE MOONBAT.map
Choose a map to play on by entering its corresponding number: 1
You've chosen ../src/_MapFiles/3D Cliff.map

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Finishing to load ../src/_MapFiles/3D Cliff.map File...
An error occurred while fetching the file: ../src/_MapFiles/3D Cliff.map... File is probably invalid.
../src/_MapFiles/3D Cliff.map is not a domination map.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Finishing to load ../src/_MapFiles/3D Cliff.map File...

Checking if map is a connected graph
The connected territories in the map are: 1 2 3 4 21 19 18 17 12 11 10 9 13 14 15 16 5 6 8 7 20
The map is a connected graph.

Checking if continents are connected subgraphs

The connected territories in continent 1 are: 1 2 3 4
Continent 1 is a connected subgraph.

The connected territories in continent 2 are: 5 6 8 7
Continent 2 is a connected subgraph.

The connected territories in continent 3 are: 9 10 11 12
Continent 3 is a connected subgraph.

The connected territories in continent 4 are: 13 14 15 16
Continent 4 is a connected subgraph.

The connected territories in continent 5 are: 17 18 19 20 21
Continent 5 is a connected subgraph.

Checking if territory belongs to one and only one continent
Continent 1 contains Territories 1 2 3 4
Continent 2 contains Territories 5 6 7 8
Continent 3 contains Territories 9 10 11 12
Continent 4 contains Territories 13 14 15 16
Continent 5 contains Territories 17 18 19 20 21
Each territory belongs to one and only one continent.

All three checks are respected. Therefore, ../src/_MapFiles/3D Cliff.map is valid.

Continent 1 clifftop | Worth 4 point(s) | Adjacent continent(s): leftstair ledge rightstair
Territories contained:
Territory 1 topleft | 0 armies | Adjacent territories: topleftc fourthleft thirdleft ledgeleft
Territory 2 topleftc | 0 armies | Adjacent territories: topleft toprightc topright ledgecentre
Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
Territory 4 topright | 0 armies | Adjacent territories: topleftc toprightc fifthright thirdright ledgeright

Continent 2 ledge | Worth 3 point(s) | Adjacent continent(s): leftstair bottom rightstair
Territories contained:
Territory 5 ledgeleft | 0 armies | Adjacent territories: ledgecentre thirdleft secondleft bottomleft
Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
Territory 7 ledgeright | 0 armies | Adjacent territories: ledgecentre thirdright secondright bottomright
Territory 8 ledgefront | 0 armies | Adjacent territories: ledgecentre bottomleft bottomleftc bottomrightc bottomright

Continent 3 bottom | Worth 3 point(s) | Adjacent continent(s): leftstair ledge rightstair
Territories contained:
Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
Territory 10 bottomleftc | 0 armies | Adjacent territories: bottomleft bottomrightc firstleft ledgefront
Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
Territory 12 bottomright | 0 armies | Adjacent territories: bottomrightc firstright ledgefront ledgeright

Continent 4 leftstair | Worth 3 point(s) | Adjacent continent(s): bottom ledge rightstair clifftop
Territories contained:
Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
Territory 15 thirdleft | 0 armies | Adjacent territories: secondleft fourthleft ledgeleft thirdright
Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft

Continent 5 rightstair | Worth 3 point(s) | Adjacent continent(s): bottom ledge leftstair clifftop
Territories contained:
Territory 17 firstright | 0 armies | Adjacent territories: secondright bottomright
Territory 18 secondright | 0 armies | Adjacent territories: firstright thirdright ledgeright
Territory 19 thirdright | 0 armies | Adjacent territories: secondright fourthright ledgeright thirdleft
Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright

Enter number of players (2-5): 2
The deck of cards has: Bomb | Reinforcement | Blockade | Airlift | Diplomacy |

Would you like to turn on observers? (Y/N): y
Would you like to turn on phase observer? (Y/N): y
Phase observer is on.
Would you like to turn on game statistics observer? (Y/N): y
Game statistics observer is on.

List of strategies:
1. HumanPlayerStrategy
2. AggressivePlayerStrategy
3. BenevolentPlayerStrategy
4. NeutralPlayerStrategy
Which strategy would you like to use for Player 1? 3
List of strategies:
1. HumanPlayerStrategy
2. AggressivePlayerStrategy
3. BenevolentPlayerStrategy
4. NeutralPlayerStrategy
Which strategy would you like to use for Player 0? 2

Each players' territories:

=============   Player Name: 1  =============
Your hand of Warzone card: None
Your Order list:  None
Your collection of territories:
Territory 15 thirdleft | 0 armies | Adjacent territories: secondleft fourthleft ledgeleft thirdright
Territory 10 bottomleftc | 0 armies | Adjacent territories: bottomleft bottomrightc firstleft ledgefront
Territory 8 ledgefront | 0 armies | Adjacent territories: ledgecentre bottomleft bottomleftc bottomrightc bottomright
Territory 7 ledgeright | 0 armies | Adjacent territories: ledgecentre thirdright secondright bottomright
Territory 17 firstright | 0 armies | Adjacent territories: secondright bottomright
Territory 4 topright | 0 armies | Adjacent territories: topleftc toprightc fifthright thirdright ledgeright
Territory 19 thirdright | 0 armies | Adjacent territories: secondright fourthright ledgeright thirdleft
Territory 5 ledgeleft | 0 armies | Adjacent territories: ledgecentre thirdleft secondleft bottomleft
Territory 1 topleft | 0 armies | Adjacent territories: topleftc fourthleft thirdleft ledgeleft
Territory 12 bottomright | 0 armies | Adjacent territories: bottomrightc firstright ledgefront ledgeright
Territory 18 secondright | 0 armies | Adjacent territories: firstright thirdright ledgeright

=============   Player Name: 0  =============
Your hand of Warzone card: None
Your Order list:  None
Your collection of territories:
Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright
Territory 2 topleftc | 0 armies | Adjacent territories: topleft toprightc topright ledgecentre
Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft

Number of initial armies per player: 40
The order of play in a turn: 1 || 0 ||

Reinforcement Phase...


v************************************************v
Player 1: Reinforcement phase
Player 1 has 40 armies in their reinforcement pool.
^************************************************^


v************************************************v
Player 0: Reinforcement phase
Player 0 has 40 armies in their reinforcement pool.
^************************************************^

==================== ISSUING ORDER PHASE ===============

Benevolent Player 1 Issuing an order...

These are your territories:
1. Territory 1 topleft | 0 armies | Adjacent territories: topleftc fourthleft thirdleft ledgeleft
2. Territory 4 topright | 0 armies | Adjacent territories: topleftc toprightc fifthright thirdright ledgeright
3. Territory 5 ledgeleft | 0 armies | Adjacent territories: ledgecentre thirdleft secondleft bottomleft
4. Territory 7 ledgeright | 0 armies | Adjacent territories: ledgecentre thirdright secondright bottomright
5. Territory 8 ledgefront | 0 armies | Adjacent territories: ledgecentre bottomleft bottomleftc bottomrightc bottomright

6. Territory 10 bottomleftc | 0 armies | Adjacent territories: bottomleft bottomrightc firstleft ledgefront
7. Territory 12 bottomright | 0 armies | Adjacent territories: bottomrightc firstright ledgefront ledgeright
8. Territory 15 thirdleft | 0 armies | Adjacent territories: secondleft fourthleft ledgeleft thirdright
9. Territory 17 firstright | 0 armies | Adjacent territories: secondright bottomright
10. Territory 18 secondright | 0 armies | Adjacent territories: firstright thirdright ledgeright
11. Territory 19 thirdright | 0 armies | Adjacent territories: secondright fourthright ledgeright thirdleft
Benevolent Player 1 has 43 armies in their reinforcement pool

v************************************************v
Player 1: Issue orders phase
Player 1's order list:
1.      DeployOrder     [...]
^************************************************^


Aggressive Player 0 Issuing an order...

These are your territories:
1. Territory 2 topleftc | 0 armies | Adjacent territories: topleft toprightc topright ledgecentre
2. Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
3. Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
4. Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
5. Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
6. Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
7. Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
8. Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft
9. Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
10. Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright
Aggressive Player 0 has 43 armies in their reinforcement pool
This is the end of your issue order phase of aggressive player.

v************************************************v
Player 0: Issue orders phase
Player 0's order list:
1.      DeployOrder     [...]
2.      AdvanceOrder    [...]
^************************************************^

================== END ISSUING ORDER PHASE =============

====================ORDER EXECUTION PHASE ===============

Deploys first priority:


// ...


Player: 1-->DeployOrder


// ...


Player: 0-->DeployOrder

v************************************************v
Player 1: Execution phase
Player 1 controls territories:
Territory 1 topleft | 43 armies | Adjacent territories: topleftc fourthleft thirdleft ledgeleft
Territory 4 topright | 0 armies | Adjacent territories: topleftc toprightc fifthright thirdright ledgeright
Territory 5 ledgeleft | 0 armies | Adjacent territories: ledgecentre thirdleft secondleft bottomleft
Territory 7 ledgeright | 0 armies | Adjacent territories: ledgecentre thirdright secondright bottomright
Territory 8 ledgefront | 0 armies | Adjacent territories: ledgecentre bottomleft bottomleftc bottomrightc bottomright
Territory 10 bottomleftc | 0 armies | Adjacent territories: bottomleft bottomrightc firstleft ledgefront
Territory 12 bottomright | 0 armies | Adjacent territories: bottomrightc firstright ledgefront ledgeright
Territory 15 thirdleft | 0 armies | Adjacent territories: secondleft fourthleft ledgeleft thirdright
Territory 17 firstright | 0 armies | Adjacent territories: secondright bottomright
Territory 18 secondright | 0 armies | Adjacent territories: firstright thirdright ledgeright
Territory 19 thirdright | 0 armies | Adjacent territories: secondright fourthright ledgeright thirdleft

Player 1 can attack territories:
Territory 2 topleftc | 43 armies | Adjacent territories: topleft toprightc topright ledgecentre
Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft
Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright
^************************************************^


v************************************************v
Player 0: Execution phase
Player 0 controls territories:
Territory 2 topleftc | 43 armies | Adjacent territories: topleft toprightc topright ledgecentre
Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft
Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright

Player 0 can attack territories:
Territory 1 topleft | 43 armies | Adjacent territories: topleftc fourthleft thirdleft ledgeleft
Territory 4 topright | 0 armies | Adjacent territories: topleftc toprightc fifthright thirdright ledgeright
Territory 5 ledgeleft | 0 armies | Adjacent territories: ledgecentre thirdleft secondleft bottomleft
Territory 7 ledgeright | 0 armies | Adjacent territories: ledgecentre thirdright secondright bottomright
Territory 8 ledgefront | 0 armies | Adjacent territories: ledgecentre bottomleft bottomleftc bottomrightc bottomright
Territory 10 bottomleftc | 0 armies | Adjacent territories: bottomleft bottomrightc firstleft ledgefront
Territory 12 bottomright | 0 armies | Adjacent territories: bottomrightc firstright ledgefront ledgeright
Territory 15 thirdleft | 0 armies | Adjacent territories: secondleft fourthleft ledgeleft thirdright
Territory 17 firstright | 0 armies | Adjacent territories: secondright bottomright
Territory 18 secondright | 0 armies | Adjacent territories: firstright thirdright ledgeright
Territory 19 thirdright | 0 armies | Adjacent territories: secondright fourthright ledgeright thirdleft
^************************************************^


// ...


v************************************************v
Players world domination view
Player 1 controls 52.381% of the world.
Player 0 controls 47.619% of the world.
^************************************************^


// ...


====================END OF ORDER EXECUTION PHASE ===============

Player 1, do you wish to change strategy? (yes/y or no/n): n

Player 0, do you wish to change strategy? (yes/y or no/n): n


Reinforcement Phase...


v************************************************v
Player 1: Reinforcement phase
Player 1 has 0 armies in their reinforcement pool.
^************************************************^


v************************************************v
Player 0: Reinforcement phase
Player 0 has 0 armies in their reinforcement pool.
^************************************************^

==================== ISSUING ORDER PHASE ===============

Benevolent Player 1 Issuing an order...

These are your territories:
1. Territory 4 topright | 0 armies | Adjacent territories: topleftc toprightc fifthright thirdright ledgeright
2. Territory 5 ledgeleft | 0 armies | Adjacent territories: ledgecentre thirdleft secondleft bottomleft
3. Territory 7 ledgeright | 0 armies | Adjacent territories: ledgecentre thirdright secondright bottomright
4. Territory 8 ledgefront | 0 armies | Adjacent territories: ledgecentre bottomleft bottomleftc bottomrightc bottomright

5. Territory 10 bottomleftc | 0 armies | Adjacent territories: bottomleft bottomrightc firstleft ledgefront
6. Territory 12 bottomright | 0 armies | Adjacent territories: bottomrightc firstright ledgefront ledgeright
7. Territory 15 thirdleft | 0 armies | Adjacent territories: secondleft fourthleft ledgeleft thirdright
8. Territory 17 firstright | 0 armies | Adjacent territories: secondright bottomright
9. Territory 18 secondright | 0 armies | Adjacent territories: firstright thirdright ledgeright
10. Territory 19 thirdright | 0 armies | Adjacent territories: secondright fourthright ledgeright thirdleft
11. Territory 1 topleft | 43 armies | Adjacent territories: topleftc fourthleft thirdleft ledgeleft
Benevolent Player 1 has 3 armies in their reinforcement pool

v************************************************v
Player 1: Issue orders phase
Player 1's order list:
1.      DeployOrder     [...]
2.      AdvanceOrder    [...]
^************************************************^


Aggressive Player 0 Issuing an order...

These are your territories:
1. Territory 2 topleftc | 43 armies | Adjacent territories: topleft toprightc topright ledgecentre
2. Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
3. Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
4. Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
5. Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
6. Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
7. Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
8. Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft
9. Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
10. Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright
Aggressive Player 0 has 3 armies in their reinforcement pool
This is the end of your issue order phase of aggressive player.

v************************************************v
Player 0: Issue orders phase
Player 0's order list:
1.      DeployOrder     [...]
2.      AdvanceOrder    [...]
^************************************************^

================== END ISSUING ORDER PHASE =============

====================ORDER EXECUTION PHASE ===============

Deploys first priority:


// ...


Player: 1-->DeployOrder


// ...


Player: 0-->DeployOrder

v************************************************v
Player 1: Execution phase
Player 1 controls territories:
Territory 1 topleft | 43 armies | Adjacent territories: topleftc fourthleft thirdleft ledgeleft
Territory 4 topright | 3 armies | Adjacent territories: topleftc toprightc fifthright thirdright ledgeright
Territory 5 ledgeleft | 0 armies | Adjacent territories: ledgecentre thirdleft secondleft bottomleft
Territory 7 ledgeright | 0 armies | Adjacent territories: ledgecentre thirdright secondright bottomright
Territory 8 ledgefront | 0 armies | Adjacent territories: ledgecentre bottomleft bottomleftc bottomrightc bottomright
Territory 10 bottomleftc | 0 armies | Adjacent territories: bottomleft bottomrightc firstleft ledgefront
Territory 12 bottomright | 0 armies | Adjacent territories: bottomrightc firstright ledgefront ledgeright
Territory 15 thirdleft | 0 armies | Adjacent territories: secondleft fourthleft ledgeleft thirdright
Territory 17 firstright | 0 armies | Adjacent territories: secondright bottomright
Territory 18 secondright | 0 armies | Adjacent territories: firstright thirdright ledgeright
Territory 19 thirdright | 0 armies | Adjacent territories: secondright fourthright ledgeright thirdleft

Player 1 can attack territories:
Territory 2 topleftc | 46 armies | Adjacent territories: topleft toprightc topright ledgecentre
Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft
Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright
^************************************************^


v************************************************v
Player 0: Execution phase
Player 0 controls territories:
Territory 2 topleftc | 46 armies | Adjacent territories: topleft toprightc topright ledgecentre
Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft
Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright

Player 0 can attack territories:
Territory 1 topleft | 43 armies | Adjacent territories: topleftc fourthleft thirdleft ledgeleft
Territory 4 topright | 3 armies | Adjacent territories: topleftc toprightc fifthright thirdright ledgeright
Territory 5 ledgeleft | 0 armies | Adjacent territories: ledgecentre thirdleft secondleft bottomleft
Territory 7 ledgeright | 0 armies | Adjacent territories: ledgecentre thirdright secondright bottomright
Territory 8 ledgefront | 0 armies | Adjacent territories: ledgecentre bottomleft bottomleftc bottomrightc bottomright
Territory 10 bottomleftc | 0 armies | Adjacent territories: bottomleft bottomrightc firstleft ledgefront
Territory 12 bottomright | 0 armies | Adjacent territories: bottomrightc firstright ledgefront ledgeright
Territory 15 thirdleft | 0 armies | Adjacent territories: secondleft fourthleft ledgeleft thirdright
Territory 17 firstright | 0 armies | Adjacent territories: secondright bottomright
Territory 18 secondright | 0 armies | Adjacent territories: firstright thirdright ledgeright
Territory 19 thirdright | 0 armies | Adjacent territories: secondright fourthright ledgeright thirdleft
^************************************************^


Advance second priority:


// ...


Player: 1-->AdvanceOrder


// ...


Player: 0-->AdvanceOrder

v************************************************v
Player 1: Execution phase
Player 1 controls territories:
Territory 1 topleft | 6 armies | Adjacent territories: topleftc fourthleft thirdleft ledgeleft
Territory 4 topright | 3 armies | Adjacent territories: topleftc toprightc fifthright thirdright ledgeright
Territory 5 ledgeleft | 0 armies | Adjacent territories: ledgecentre thirdleft secondleft bottomleft
Territory 7 ledgeright | 0 armies | Adjacent territories: ledgecentre thirdright secondright bottomright
Territory 8 ledgefront | 0 armies | Adjacent territories: ledgecentre bottomleft bottomleftc bottomrightc bottomright
Territory 10 bottomleftc | 0 armies | Adjacent territories: bottomleft bottomrightc firstleft ledgefront
Territory 12 bottomright | 0 armies | Adjacent territories: bottomrightc firstright ledgefront ledgeright
Territory 15 thirdleft | 0 armies | Adjacent territories: secondleft fourthleft ledgeleft thirdright
Territory 17 firstright | 0 armies | Adjacent territories: secondright bottomright
Territory 18 secondright | 0 armies | Adjacent territories: firstright thirdright ledgeright
Territory 19 thirdright | 0 armies | Adjacent territories: secondright fourthright ledgeright thirdleft

Player 1 can attack territories:
Territory 2 topleftc | 3 armies | Adjacent territories: topleft toprightc topright ledgecentre
Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft
Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright
^************************************************^


v************************************************v
Player 0: Execution phase
Player 0 controls territories:
Territory 2 topleftc | 3 armies | Adjacent territories: topleft toprightc topright ledgecentre
Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft
Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright

Player 0 can attack territories:
Territory 1 topleft | 6 armies | Adjacent territories: topleftc fourthleft thirdleft ledgeleft
Territory 4 topright | 3 armies | Adjacent territories: topleftc toprightc fifthright thirdright ledgeright
Territory 5 ledgeleft | 0 armies | Adjacent territories: ledgecentre thirdleft secondleft bottomleft
Territory 7 ledgeright | 0 armies | Adjacent territories: ledgecentre thirdright secondright bottomright
Territory 8 ledgefront | 0 armies | Adjacent territories: ledgecentre bottomleft bottomleftc bottomrightc bottomright
Territory 10 bottomleftc | 0 armies | Adjacent territories: bottomleft bottomrightc firstleft ledgefront
Territory 12 bottomright | 0 armies | Adjacent territories: bottomrightc firstright ledgefront ledgeright
Territory 15 thirdleft | 0 armies | Adjacent territories: secondleft fourthleft ledgeleft thirdright
Territory 17 firstright | 0 armies | Adjacent territories: secondright bottomright
Territory 18 secondright | 0 armies | Adjacent territories: firstright thirdright ledgeright
Territory 19 thirdright | 0 armies | Adjacent territories: secondright fourthright ledgeright thirdleft
^************************************************^


v************************************************v
Players world domination view
Player 1 controls 52.381% of the world.
Player 0 controls 47.619% of the world.
^************************************************^


// ...

====================END OF ORDER EXECUTION PHASE ===============

Player 1, do you wish to change strategy? (yes/y or no/n): y
Your current strategy is Benevolent Player Strategy
List of strategies:
1. HumanPlayerStrategy
2. AggressivePlayerStrategy
3. BenevolentPlayerStrategy
4. NeutralPlayerStrategy
Your decision: 1

Player 0, do you wish to change strategy? (yes/y or no/n): n


Reinforcement Phase...


v************************************************v
Player 1: Reinforcement phase
Player 1 has 0 armies in their reinforcement pool.
^************************************************^


v************************************************v
Player 0: Reinforcement phase
Player 0 has 0 armies in their reinforcement pool.
^************************************************^

==================== ISSUING ORDER PHASE ===============

Human Player 1 Issuing an order...


These are your territories:
1. Territory 1 topleft | 6 armies | Adjacent territories: topleftc fourthleft thirdleft ledgeleft
2. Territory 4 topright | 3 armies | Adjacent territories: topleftc toprightc fifthright thirdright ledgeright
3. Territory 5 ledgeleft | 0 armies | Adjacent territories: ledgecentre thirdleft secondleft bottomleft
4. Territory 7 ledgeright | 0 armies | Adjacent territories: ledgecentre thirdright secondright bottomright
5. Territory 8 ledgefront | 0 armies | Adjacent territories: ledgecentre bottomleft bottomleftc bottomrightc bottomright

6. Territory 10 bottomleftc | 0 armies | Adjacent territories: bottomleft bottomrightc firstleft ledgefront
7. Territory 12 bottomright | 0 armies | Adjacent territories: bottomrightc firstright ledgefront ledgeright
8. Territory 15 thirdleft | 0 armies | Adjacent territories: secondleft fourthleft ledgeleft thirdright
9. Territory 17 firstright | 0 armies | Adjacent territories: secondright bottomright
10. Territory 18 secondright | 0 armies | Adjacent territories: firstright thirdright ledgeright
11. Territory 19 thirdright | 0 armies | Adjacent territories: secondright fourthright ledgeright thirdleft
Human Player 1 has 3 armies in their reinforcement pool

Which territory you wish to deploy armies to? 1

How many armies you wish to deploy? 3

Note. The territories will be updated during the order execution phase.
These are the territories you can attack:
1. Territory 2 topleftc | 3 armies | Adjacent territories: topleft toprightc topright ledgecentre
2. Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
3. Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
4. Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
5. Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
6. Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
7. Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
8. Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft
9. Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
10. Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright

Do you wish to attack a territory ? (yes/y or no/n): y

From which of your territories do you wish to attack with? 1

Which enemy territory do you wish to attack? 1

How many armies do you wish to send to this territory? 9

Do you wish to attack a territory ? (yes/y or no/n): n

Note. The territories will be updated during the order execution phase.
You have no cards that you can play...

v************************************************v
Player 1: Issue orders phase
Player 1's order list:
1.      DeployOrder     [...]
2.      AdvanceOrder    [...]
^************************************************^


Aggressive Player 0 Issuing an order...

These are your territories:
1. Territory 2 topleftc | 3 armies | Adjacent territories: topleft toprightc topright ledgecentre
2. Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
3. Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
4. Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
5. Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
6. Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
7. Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
8. Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft
9. Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
10. Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright
Aggressive Player 0 has 3 armies in their reinforcement pool
This is the end of your issue order phase of aggressive player.

v************************************************v
Player 0: Issue orders phase
Player 0's order list:
1.      DeployOrder     [...]
2.      AdvanceOrder    [...]
^************************************************^

================== END ISSUING ORDER PHASE =============

====================ORDER EXECUTION PHASE ===============

Deploys first priority:


// ...


Player: 1-->DeployOrder

v************************************************v
Player 0: Execution phase
Player 0 controls territories:
Territory 2 topleftc | 3 armies | Adjacent territories: topleft toprightc topright ledgecentre
Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft
Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright

Player 0 can attack territories:
Territory 1 topleft | 9 armies | Adjacent territories: topleftc fourthleft thirdleft ledgeleft
Territory 4 topright | 3 armies | Adjacent territories: topleftc toprightc fifthright thirdright ledgeright
Territory 5 ledgeleft | 0 armies | Adjacent territories: ledgecentre thirdleft secondleft bottomleft
Territory 7 ledgeright | 0 armies | Adjacent territories: ledgecentre thirdright secondright bottomright
Territory 8 ledgefront | 0 armies | Adjacent territories: ledgecentre bottomleft bottomleftc bottomrightc bottomright
Territory 10 bottomleftc | 0 armies | Adjacent territories: bottomleft bottomrightc firstleft ledgefront
Territory 12 bottomright | 0 armies | Adjacent territories: bottomrightc firstright ledgefront ledgeright
Territory 15 thirdleft | 0 armies | Adjacent territories: secondleft fourthleft ledgeleft thirdright
Territory 17 firstright | 0 armies | Adjacent territories: secondright bottomright
Territory 18 secondright | 0 armies | Adjacent territories: firstright thirdright ledgeright
Territory 19 thirdright | 0 armies | Adjacent territories: secondright fourthright ledgeright thirdleft
^************************************************^

Player: 0-->DeployOrder

v************************************************v
Player 1: Execution phase
Player 1 controls territories:
Territory 1 topleft | 9 armies | Adjacent territories: topleftc fourthleft thirdleft ledgeleft
Territory 4 topright | 3 armies | Adjacent territories: topleftc toprightc fifthright thirdright ledgeright
Territory 5 ledgeleft | 0 armies | Adjacent territories: ledgecentre thirdleft secondleft bottomleft
Territory 7 ledgeright | 0 armies | Adjacent territories: ledgecentre thirdright secondright bottomright
Territory 8 ledgefront | 0 armies | Adjacent territories: ledgecentre bottomleft bottomleftc bottomrightc bottomright
Territory 10 bottomleftc | 0 armies | Adjacent territories: bottomleft bottomrightc firstleft ledgefront
Territory 12 bottomright | 0 armies | Adjacent territories: bottomrightc firstright ledgefront ledgeright
Territory 15 thirdleft | 0 armies | Adjacent territories: secondleft fourthleft ledgeleft thirdright
Territory 17 firstright | 0 armies | Adjacent territories: secondright bottomright
Territory 18 secondright | 0 armies | Adjacent territories: firstright thirdright ledgeright
Territory 19 thirdright | 0 armies | Adjacent territories: secondright fourthright ledgeright thirdleft

Player 1 can attack territories:
Territory 2 topleftc | 6 armies | Adjacent territories: topleft toprightc topright ledgecentre
Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft
Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright
^************************************************^

// ...


Advance second priority:


// ...


Player: 1-->AdvanceOrder

v************************************************v
Player 0: Execution phase
Player 0 controls territories:
Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft
Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright

Player 0 can attack territories:
Territory 1 topleft | 0 armies | Adjacent territories: topleftc fourthleft thirdleft ledgeleft
Territory 2 topleftc | 2 armies | Adjacent territories: topleft toprightc topright ledgecentre
Territory 4 topright | 3 armies | Adjacent territories: topleftc toprightc fifthright thirdright ledgeright
Territory 5 ledgeleft | 0 armies | Adjacent territories: ledgecentre thirdleft secondleft bottomleft
Territory 7 ledgeright | 0 armies | Adjacent territories: ledgecentre thirdright secondright bottomright
Territory 8 ledgefront | 0 armies | Adjacent territories: ledgecentre bottomleft bottomleftc bottomrightc bottomright
Territory 10 bottomleftc | 0 armies | Adjacent territories: bottomleft bottomrightc firstleft ledgefront
Territory 12 bottomright | 0 armies | Adjacent territories: bottomrightc firstright ledgefront ledgeright
Territory 15 thirdleft | 0 armies | Adjacent territories: secondleft fourthleft ledgeleft thirdright
Territory 17 firstright | 0 armies | Adjacent territories: secondright bottomright
Territory 18 secondright | 0 armies | Adjacent territories: firstright thirdright ledgeright
Territory 19 thirdright | 0 armies | Adjacent territories: secondright fourthright ledgeright thirdleft
^************************************************^

Player: 0-->AdvanceOrder

v************************************************v
Player 1: Execution phase
Player 1 controls territories:
Territory 1 topleft | 0 armies | Adjacent territories: topleftc fourthleft thirdleft ledgeleft
Territory 2 topleftc | 2 armies | Adjacent territories: topleft toprightc topright ledgecentre
Territory 4 topright | 3 armies | Adjacent territories: topleftc toprightc fifthright thirdright ledgeright
Territory 5 ledgeleft | 0 armies | Adjacent territories: ledgecentre thirdleft secondleft bottomleft
Territory 7 ledgeright | 0 armies | Adjacent territories: ledgecentre thirdright secondright bottomright
Territory 8 ledgefront | 0 armies | Adjacent territories: ledgecentre bottomleft bottomleftc bottomrightc bottomright
Territory 10 bottomleftc | 0 armies | Adjacent territories: bottomleft bottomrightc firstleft ledgefront
Territory 12 bottomright | 0 armies | Adjacent territories: bottomrightc firstright ledgefront ledgeright
Territory 15 thirdleft | 0 armies | Adjacent territories: secondleft fourthleft ledgeleft thirdright
Territory 17 firstright | 0 armies | Adjacent territories: secondright bottomright
Territory 18 secondright | 0 armies | Adjacent territories: firstright thirdright ledgeright
Territory 19 thirdright | 0 armies | Adjacent territories: secondright fourthright ledgeright thirdleft

Player 1 can attack territories:
Territory 3 toprightc | 0 armies | Adjacent territories: topleftc topright
Territory 6 ledgecentre | 0 armies | Adjacent territories: ledgeleft ledgefront ledgeright bottomleft
Territory 9 bottomleft | 0 armies | Adjacent territories: bottomleftc firstleft ledgefront
Territory 11 bottomrightc | 0 armies | Adjacent territories: bottomleftc bottomright ledgefront
Territory 13 firstleft | 0 armies | Adjacent territories: secondleft bottomleft bottomleftc
Territory 14 secondleft | 0 armies | Adjacent territories: firstleft thirdleft ledgeleft
Territory 16 fourthleft | 0 armies | Adjacent territories: thirdleft topleft
Territory 20 fourthright | 0 armies | Adjacent territories: thirdright fifthright
Territory 21 fifthright | 0 armies | Adjacent territories: thirdright fourthright topright
^************************************************^


// ...


v************************************************v
Players world domination view
Player 1 controls 57.1429% of the world.
Player 0 controls 42.8571% of the world.
^************************************************^


// ...


====================END OF ORDER EXECUTION PHASE ===============

Player 1, do you wish to change strategy? (yes/y or no/n):

// ...
```
