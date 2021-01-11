#ifndef COMP345_WARZONEGAME_MAP_H
#define COMP345_WARZONEGAME_MAP_H
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

/************************************************ TERRITORY ************************************************/

class Player;

class Territory {

private:
    int* territoryID;      // Unique number for each territory
    std::string* territoryName;     // Name of the territory
    int* numArmies;     // Number of armies contained on territory
    int* correspondingContinentID;     // ID of the continent to which the territory belongs
    std::vector<Territory*>* adjTerritoryPtrs;    // Pointers to each adjacent territory
    Player* owner;
    std::vector<int> adjTerrIds;
public:
    // Territory constructors
    Territory();
    Territory(int terrID, std::string terrName, int nArmies, int corrContID);
    Territory(const Territory &terr); // Copy constructor
    friend class GameEngine;
    void setOwner(Player& player);
    Player* getOwner();
    // Territory destructor
    ~Territory();

    // Territory assignment operator
    Territory& operator=(const Territory &terr);

    // Territory mutators and accessors
    std::vector<int> getAdjTerrIds();
    void addAdjTerrId(const int id);
    std::vector<Territory*>* getAdjTerritoryPtrs();
    void addAdjTerrPtr(Territory& territory);
    int* getTerritoryID();
    std::string* getTerritoryName();
    int* getNumArmies();
    void setNumArmies(int num);
    int* getCorrespondingContinentID();

    // Other Territory functions
    bool operator < (const Territory&  terr) const;
    // Territory insertion stream operator overload
    friend std::ostream& operator<<(std::ostream& output, const Territory &terr);
};


/************************************************ CONTINENT ************************************************/


class Continent {

private:
    int* continentID;       // Unique number for each continent
    std::string* continentName;     // Name of the continent
    int* continentBonus;    // Army value
    std::vector<Continent*>* adjContinentPtrs;      // Vector of pointers to each adjacent continent
    std::vector<Territory*>* territoriesInContinent;    // Vector of pointers to each territory contained in the continent
    Player* owner;
public:
    // Continent constructors
    Continent();
    Continent(int contID, std::string contName, int contPoints);
    Continent(const Continent &cont);
    void setOwner();
    // Continent destructor
    ~Continent();

    // Continent assignment operator
    Continent& operator=(const Continent &cont);


    // Continent mutators and accessors
    int* getContinentID();
    std::string* getContinentName();
    int* getContinentBonus();
    std::vector<Continent*>* getAdjContinentPtrs();
    std::vector<Territory*>* getTerritoriesInContinent();
    friend class GameEngine;

    // Other Continent functions
    void addReferencedOfTerritory(Territory& terr);

    // Continent insertion stream operator overload
    friend std::ostream& operator<<(std::ostream& output, const Continent &cont);
};


/*************************************************** MAP **************************************************/


class Map {

private:
    std::vector<Continent> allContinents;      // Vector of all the continents in the map
    std::vector<Territory> allTerritories;     // Vector of all the territories in the map

public:
    // Map constructors
    Map();
    Map(std::vector<Continent> allCont, std::vector<Territory> allTerr);
    Map(const Map &map);

    // Map destructor
    ~Map();

    // Map assignment operator
    Map &operator=(const Map &map);

    // Map mutators and accessors
    void setAllContinents(std::vector<Continent> allCont);
    std::vector<Continent>* getAllContinents();
    void setAllTerritories(std::vector<Territory> allTerr);
    std::vector<Territory>* getAllTerritories();


    // Other Map functions

    // Useful for MapLoader
    void setContinentTerritories();
    Continent* getContinentAtPosition(int position);
    Territory* getTerritoryAtPosition(int position);
    bool isContinentsEmpty();
    bool isTerritoriesEmpty();
    int getNumberOfContinents();
    int getNumberOfTerritories();

    // To find the continents adjacent to a given continent
    void dfsAdjContinents(int terrID, std::vector<Territory*> terrInCont, std::vector<Continent*>*, bool visited[]);

    // Validation functions
    bool validate();
    bool preValidate();
    bool isAdjacencyContinentValid();
    bool isAdjacencyTerritoryValid();
    bool validate1();
    void dfs1(int terrID, std::vector<Territory> allTerr, bool visited[]);
    int territoryIndexFromID(int terrID, std::vector<Territory> allTerr);
    bool validate2(Continent cont);
    void dfs2(int terrID, std::vector<Territory*> terrInCont, bool visited[]);
    int territoryIndexFromID(int terrID, std::vector<Territory*> terrInCont);
    bool validate3();

    // Map Insertion stream operator overload
    friend std::ostream &operator<<(std::ostream &output, const Map &map);
    friend class GameEngine;
};


#endif //COMP345_WARZONEGAME_MAP_H