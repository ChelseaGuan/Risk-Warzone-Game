#include "Map.h"


/************************************************ TERRITORY ************************************************/


// Territory constructors.

Territory::Territory() {
    Territory(0, "", 0, 0);
    this->adjTerritoryPtrs = new std::vector<Territory*>(0);
}

Territory::Territory(int terrID, std::string terrName, int nArmies, int corrContID) {
    this->territoryID = new int(terrID);
    this->territoryName = new std::string(terrName);
    this->numArmies = new int(nArmies);
    this-> correspondingContinentID = new int(corrContID);
    this->adjTerritoryPtrs = new std::vector<Territory*>();
    this->owner = nullptr;
}

// Territory copy constructor.
Territory::Territory(const Territory& terr) {
    this->territoryID = new int(*terr.territoryID);
    this->territoryName = new std::string(*terr.territoryName);
    this->numArmies = new int(*terr.numArmies);
    this->correspondingContinentID = new int(*terr.correspondingContinentID);
    this->adjTerritoryPtrs = new std::vector<Territory*>(*terr.adjTerritoryPtrs);
    this->owner = terr.owner;
    this->adjTerrIds = terr.adjTerrIds;
}

// Territory destructor.
Territory::~Territory() {
    delete territoryID;
    delete territoryName;
    delete numArmies;
    delete correspondingContinentID;
    adjTerritoryPtrs->clear();
    delete adjTerritoryPtrs;
    territoryID = nullptr;
    territoryName = nullptr;
    numArmies = nullptr;
    correspondingContinentID = nullptr;
    adjTerritoryPtrs = nullptr;
    owner = nullptr; // Pointer is a nullpointer since Player object is deleted after and outside ofTerritory.
}

// Territory assignment operator.
Territory& Territory::operator=(const Territory &terr) {
    if(&terr != this) {
        delete territoryID;
        territoryID = new int(*terr.territoryID);
        delete territoryName;
        territoryName = new std::string(*terr.territoryName);
        delete numArmies;
        numArmies = new int(*terr.numArmies);
        delete correspondingContinentID;
        correspondingContinentID = new int(*terr.correspondingContinentID);
        delete adjTerritoryPtrs;
        adjTerritoryPtrs = new std::vector<Territory*>(*terr.adjTerritoryPtrs);
        owner = terr.owner;
        adjTerrIds = terr.adjTerrIds;
    }
    return *this;
}

void Territory::setOwner(Player& player) {
    owner = &player;
}

Player* Territory::getOwner(){
    return owner;
}

void Territory::addAdjTerrId(const int id) {
    adjTerrIds.push_back(id);
}


// Territory mutators and accessors.
// Accessors return a reference to the attribute to allow the mutator to change the value. Otherwise, the mutators would be called on a copy.

int* Territory::getTerritoryID() {
    return territoryID;
}

std::string* Territory::getTerritoryName() {
    return territoryName;
}

void Territory::setNumArmies(int num) {
    *numArmies = num;
}
int* Territory::getNumArmies() {
    return numArmies;
}

int* Territory::getCorrespondingContinentID() {
    return correspondingContinentID;
}

void Territory::addAdjTerrPtr(Territory& territory) {
    adjTerritoryPtrs->push_back(&territory);
}
std::vector<Territory*>* Territory::getAdjTerritoryPtrs() {
    return adjTerritoryPtrs;
}

std::vector<int> Territory::getAdjTerrIds(){
    return adjTerrIds;
}


// Territory insertion stream operator overload.
std::ostream& operator<<(std::ostream& output, const Territory &terr) {
    output << "Territory " << *terr.territoryID << " " << *terr.territoryName << " | " << *terr.numArmies << " armies | Adjacent territories: ";
    for (auto&& x : *terr.adjTerritoryPtrs)
        output << *x->getTerritoryName() << " ";
    output << "\n";
    return output;
}

bool Territory::operator<(const Territory &terr) const {
    return (this->numArmies < terr.numArmies);
}


/************************************************ CONTINENT ************************************************/


// Continent constructors.

Continent::Continent() {
    Continent(0, "", 0);
    this->adjContinentPtrs = new std::vector<Continent*>();
    this->territoriesInContinent = new std::vector<Territory*>();
}

Continent::Continent(int contID, std::string contName, int contBonus) {
    this->continentID = new int(contID);
    this->continentName = new std::string(contName);
    this->continentBonus = new int(contBonus);
    this->adjContinentPtrs = new std::vector<Continent*>;
    this->territoriesInContinent = new std::vector<Territory*>;
}

// Continent copy constructor.
Continent::Continent(const Continent &cont) {
    this->continentID = new int(*cont.continentID);
    this->continentName = new std::string(*cont.continentName);
    this->continentBonus = new int(*cont.continentBonus);
    this->adjContinentPtrs = new std::vector<Continent*>(*cont.adjContinentPtrs);
    this->territoriesInContinent = new std::vector<Territory*>(*cont.territoriesInContinent);
}

// Continent destructor.
Continent::~Continent() {
    delete continentID;
    delete continentName;
    delete continentBonus;
    adjContinentPtrs->clear(); //FIXME: To remove!
    delete adjContinentPtrs;
    continentID = nullptr;
    continentName = nullptr;
    continentBonus = nullptr;
    territoriesInContinent->clear();
    delete territoriesInContinent;
    territoriesInContinent = nullptr;
    adjContinentPtrs = nullptr;
}

// FIXME Once copy constructor is fixed, must update assignment operator too
// Continent assignment operator.
Continent& Continent::operator=(const Continent &cont) {
    if (&cont != this) {
        delete continentID;
        continentID = new int(*cont.continentID);
        delete continentName;
        continentName = new std::string(*cont.continentName);
        delete continentBonus;
        continentBonus = new int(*cont.continentBonus);
        delete territoriesInContinent;
        territoriesInContinent = new std::vector<Territory *>(*cont.territoriesInContinent);
        delete adjContinentPtrs;
        adjContinentPtrs = new std::vector<Continent *>(*cont.adjContinentPtrs);
    }
    return *this;
}


// Continent mutators and accessors.

int* Continent::getContinentID() {
    return continentID;
}

std::string* Continent::getContinentName() {
    return continentName;
}

int* Continent::getContinentBonus() {
    return continentBonus;
}

std::vector<Territory*>* Continent::getTerritoriesInContinent() {
    return territoriesInContinent;
}

std::vector<Continent*>* Continent::getAdjContinentPtrs() {
    return this->adjContinentPtrs;
}

void Continent::addReferencedOfTerritory(Territory& terr) {
    territoriesInContinent->push_back(&terr);
}


// Continent insertion stream operator overload.
std::ostream& operator<<(std::ostream& output, const Continent &cont) {
    output << "Continent " << *cont.continentID << " " << *cont.continentName << " | Worth " << *cont.continentBonus << " point(s) | Adjacent continent(s): ";
    for (auto&& x : *cont.adjContinentPtrs)
        std::cout << *x->getContinentName() << " ";
    std::cout << "\nTerritories contained: \n";
    for (auto&& x : *cont.territoriesInContinent)
        output << *x;
    return output;
}


/*************************************************** MAP ***************************************************/


// Map constructors.
Map::Map() {
//    allContinents = nullptr;
//    allTerritories = nullptr;
//    this->allContinents = new std::vector<Continent>(0);
//    this->allTerritories = new std::vector<Territory>(0);
}

Map::Map(std::vector<Continent> allCont, std::vector<Territory> allTerr) {
    allContinents = allCont;
    allTerritories = allTerr;
}

// Map copy constructor.
Map::Map(const Map &map) {
    this->allContinents = map.allContinents;
    this->allTerritories = map.allTerritories;
}

// Map destructor.
Map::~Map() {
    allContinents.clear();
    allTerritories.clear();
//    delete allContinents;
//    delete allTerritories;
//    allContinents = nullptr;
//    allTerritories = nullptr;
}

// Map assignment operator.
Map& Map::operator=(const Map &map) {
    if (&map != this) {
//        delete allContinents;
        allContinents = map.allContinents;
//        delete allTerritories;
        allTerritories = map.allTerritories;
    }
    return *this;
}


// Map mutators and accessors.

void Map::setAllContinents(const std::vector<Continent> allCont) {
    allContinents = allCont;
}
std::vector<Continent>* Map::getAllContinents() {
    return &allContinents;
}

void Map::setAllTerritories(const std::vector<Territory> allTerr) {
    allTerritories = allTerr;
}
std::vector<Territory>* Map::getAllTerritories() {
    return &allTerritories;
}



// Other Map functions


// Useful for MapLoader

void Map::setContinentTerritories() {
    for(auto&& territory: allTerritories) {
        allContinents.at(*territory.getCorrespondingContinentID() - 1).addReferencedOfTerritory(territory);
    }
}


bool Map::isContinentsEmpty() {
    return this->allContinents.size() == 0;
}
bool Map::isTerritoriesEmpty() {
    return this->allTerritories.size() == 0;
}

Continent* Map::getContinentAtPosition(int position){
    if(isContinentsEmpty()) {
        return nullptr;
    }
    else if(position <= this->allContinents.size() && position >=0){
        return &this->allContinents.at(position);
    }
    else {
        return nullptr;
    }
}

Territory* Map::getTerritoryAtPosition(int position) {
    if(isTerritoriesEmpty()) {
        return nullptr;
    }
    else if(position <= this->allTerritories.size() && position >=0){
        return &this->allTerritories.at(position);
    }
    else {
        return nullptr;
    }
}

int Map::getNumberOfContinents() {
    return this->allContinents.size();
}
int Map::getNumberOfTerritories() {
    return this->allTerritories.size();
}




// To find the continents adjacent to a given continent.

//void Map::determineAdjContinents(Continent cont) {
//    std::vector<Territory*> terrInCont = *cont.getTerritoriesInContinent();
//    std::vector<Continent*>* adjContRecorded = new std::vector<Continent*>();
//    int numTerr = terrInCont.size();
//    bool visited[numTerr];
//    memset(visited, false, sizeof visited);     // Marking all territories as not visited.
//
//    dfsAdjContinents(*(*terrInCont[0]).getTerritoryID(), terrInCont, adjContRecorded, visited);
//    (*(*this).getAllContinents())[*cont.getContinentID()].setAdjContinentPtrs(*adjContRecorded);
//    adjContRecorded->clear();
//    delete adjContRecorded;
//    adjContRecorded = nullptr;
//}

void Map::dfsAdjContinents(int terrID, std::vector<Territory*> terrInCont, std::vector<Continent*>* adjContRecorded, bool visited[]) {
    // Mark the current territory as visited and print it.
    visited[territoryIndexFromID(terrID, terrInCont)] = true;
    std::vector<Territory*> adjTerrPtrs = *terrInCont[territoryIndexFromID(terrID, terrInCont)]->getAdjTerritoryPtrs();
    // Recur for all the vertices adjacent to this vertex.
    for (auto&& x : adjTerrPtrs) {

        int contIDCurrent = *(*getAllTerritories())[territoryIndexFromID(*x->getTerritoryID(), *getAllTerritories())].getCorrespondingContinentID();       // ID of the continent containing the territory being examined for adjacency with the passed continent.
        int contIDPassed = *(*getAllTerritories())[territoryIndexFromID(terrID, *getAllTerritories())].getCorrespondingContinentID();       // ID of the continent for which we are looking for adjacent continents.

        // So far, we've only done one way adjacency by looking at a given territory's vector of adjacent territories.
        // To confirm mutual adjacency, we must also make sure that the adjacent territory's adjacent territory vector contains the given vector.
        bool mutualAdj = false;
        Territory terrCurrent = (*getAllTerritories())[territoryIndexFromID(*x->getTerritoryID(), *getAllTerritories())];
        Territory terrPassed = (*getAllTerritories())[territoryIndexFromID(terrID, *getAllTerritories())];
        for (auto&& y : *terrCurrent.getAdjTerritoryPtrs()) {
            if (*terrPassed.getTerritoryID() == *(*y).getTerritoryID()) {
                mutualAdj = true;
                break;
            }
        }

        // If a territory and its adjacent territory are in different continents AND if they are mutually adjacent AND if that continent has not already been recorded as an adjacent continent.
        bool contAlreadyRecored = (find((*adjContRecorded).begin(), (*adjContRecorded).end(), getContinentAtPosition(contIDCurrent)) != (*adjContRecorded).end());
        if (contIDCurrent != contIDPassed/* && mutualAdj*/ && !contAlreadyRecored) {
            (*adjContRecorded).push_back(getContinentAtPosition(contIDCurrent));
        }

        if (!visited[territoryIndexFromID(*x->getTerritoryID(), terrInCont)])
            dfsAdjContinents(*x->getTerritoryID(), terrInCont, adjContRecorded, visited);
    }
}


bool Map::validate() {

    if (preValidate())
    {
        // CHECK 1.
        std::cout << "\nChecking if map is a connected graph\n";
        bool valid1 = (*this).validate1();
        if (valid1)
            std::cout << "The map is a connected graph.\n\n";
        else
            std::cout << "The map is not a connected graph.\n\n";

        // CHECK 2.
        bool valid2 = true;     // valid2 is initialized to true and as soon as one continent proves to not be a subgraph, it is set to false.
        std::cout << "Checking if continents are connected subgraphs\n\n";
        for (auto &&x : *(*this).getAllContinents()) {
            if ((*this).validate2(x))
                std::cout << "Continent " << *x.getContinentID() << " is a connected subgraph.\n\n";
                // It only takes one continent to not be a connected subgraph for validation 2 to be false.
            else {
                valid2 = false;
                std::cout << "Continent " << *x.getContinentID() << " is a not connected subgraph.\n\n";
            }
        }

        // CHECK 3.
        std::cout << "Checking if territory belongs to one and only one continent\n";
        bool valid3 = (*this).validate3();
        std::cout << "\n";


        return valid1 && valid2 && valid3;
    }

    else
        return false;
}

// Checks for valid continent and territory sizes and adjacency
bool Map::preValidate() {
    if(!((this->allContinents.size()  <= this->allTerritories.size()) && (this->allContinents.size() != 0 && this->allTerritories.size() != 0))) {
        return false;
    }
//    if(!(isAdjacencyContinentValid() && isAdjacencyTerritoryValid())){
//        return false;
//    }
    return true;
}


// Helper methods to preValidate()

bool Map::isAdjacencyTerritoryValid() {
    int numberOfTerritories = this->allTerritories.size();
    bool isMutual[numberOfTerritories];
    bool found = false;
    memset(isMutual, false, sizeof isMutual);
    for(auto&& territory : this->allTerritories){
        // if one of the adj territory is empty, then file is invalid.
        if(territory.getAdjTerritoryPtrs()->empty()){
            return false;
        }
        // Check for mutual relationship adjacent between territory.
        for(auto&& adjacentContinent : *territory.getAdjTerritoryPtrs()){
            found = false;
            for(auto&& adjacentTerritoryCheck : *adjacentContinent->getAdjTerritoryPtrs()){
                if(*territory.getTerritoryID() == *adjacentTerritoryCheck->getTerritoryID()) {
                    found = true;
                    break;
                }
            }
            if(!found) {
                return false;
            }
        }
    }
    return true;
}

bool Map::isAdjacencyContinentValid() {
    int numberOfContinent = this->allContinents.size();
    bool isMutual[numberOfContinent];
    bool found = false;
    memset(isMutual, false, sizeof isMutual);
    for(auto&& continent : this->allContinents){
        //if one of the adj continent is empty, then file is invalid.
        if(continent.getAdjContinentPtrs()->empty()){
            return false;
        }
        //Check for mutual relationship adjacent between continent.
        for(auto&& adjacentContinent : *continent.getAdjContinentPtrs()){
            found = false;
            for(auto&& adjacentTerritoryCheck : *adjacentContinent->getAdjContinentPtrs()){
                if(*continent.getContinentID() == *adjacentTerritoryCheck->getContinentID()) {
                    found = true;
                    break;
                }
            }
            if(!found) {
                return false;
            }
        }
    }
    return true;
}


// Validation check 1. The map is a connected graph.
bool Map::validate1() {
    std::vector<Territory> allTerr = *(*this).getAllTerritories();
    int numTerr = allTerr.size();
    bool visited[numTerr];
    memset(visited, false, sizeof visited);     // Marking all territories as not visited.
    std::cout << "The connected territories in the map are: ";

    dfs1(*allTerr[0].getTerritoryID(), allTerr, visited);
    std::cout << "\n";

    for (auto&& x : visited) {
        if (!x)
            return false;
    }

    return true;
}

// Helper function to validate1()
void Map::dfs1(int terrID, std::vector<Territory> allTerr, bool visited[]) {
    // Mark the current territory as visited and print it.
    visited[territoryIndexFromID(terrID, allTerr)] = true;
    std::cout << terrID << " ";
    std::vector<Territory*> adjTerrPtrs = *allTerr[territoryIndexFromID(terrID, allTerr)].getAdjTerritoryPtrs();
    // Recur for all the vertices adjacent to this vertex.
    for (auto&& x : adjTerrPtrs) {
        bool mutualAdj = false;
        Territory terrCurrent = (*getAllTerritories())[territoryIndexFromID(*x->getTerritoryID(), *getAllTerritories())];
        Territory terrPassed = (*getAllTerritories())[territoryIndexFromID(terrID, *getAllTerritories())];
        for (auto&& y : *terrCurrent.getAdjTerritoryPtrs()) {
            if (*terrPassed.getTerritoryID() == *(*y).getTerritoryID()) {
                mutualAdj = true;
                break;
            }
        }
        if (!visited[territoryIndexFromID(*x->getTerritoryID(), allTerr)] /*&& mutualAdj*/)
            dfs1(*x->getTerritoryID(), allTerr, visited);
    }
}

// Helper function to dfs1(). Given a territory ID and a vector of territories, returns the index of the territory corresponding to the ID.
int Map::territoryIndexFromID(int terrID, std::vector<Territory> allTerr) {
    for (int i=0; i<allTerr.size(); ++i) {
        if (*allTerr[i].getTerritoryID() == terrID)
            return i;
    }
    return 0;
}


// Validation check 2. Continents are connected subgraphs.
bool Map::validate2(Continent cont) {
    std::vector<Territory*> terrInCont = *cont.getTerritoriesInContinent();
    int numTerr = terrInCont.size();
    bool visited[numTerr];
    memset(visited, false, sizeof visited);     // Marking all territories as not visited.

    std::cout << "The connected territories in continent " << *cont.getContinentID() << " are: ";

    // Print all reachable vertices within cont.
    dfs2(*(*terrInCont[0]).getTerritoryID(), terrInCont, visited);
    std::cout << "\n";

    for (auto&& x : visited) {
        if (!x)
            return false;
    }

    return true;
}

// Helper function to validate2().
void Map::dfs2(int terrID, std::vector<Territory*> terrInCont, bool visited[]) {
    // Mark the current territory as visited and print it.
    visited[territoryIndexFromID(terrID, terrInCont)] = true;
    std::cout << terrID << " ";

    std::vector<Territory*> adjTerrPtrs = *(*terrInCont[territoryIndexFromID(terrID, terrInCont)]).getAdjTerritoryPtrs();
    // Recur for all the vertices adjacent to this vertex.
    for (auto&& x : adjTerrPtrs) {
        bool mutualAdj = false;
        Territory terrCurrent = (*getAllTerritories())[territoryIndexFromID(*x->getTerritoryID(), *getAllTerritories())];
        Territory terrPassed = (*getAllTerritories())[territoryIndexFromID(terrID, *getAllTerritories())];
        for (auto&& y : *terrCurrent.getAdjTerritoryPtrs()) {
            if (*terrPassed.getTerritoryID() == *(*y).getTerritoryID()) {
                mutualAdj = true;
                break;
            }
        }
        // Skip one iteration if the current territory examined is not in the same continent as the passed vector of Territory objects contTerr.
        if ((*(*this->getAllTerritories())[territoryIndexFromID(*x->getTerritoryID(), *getAllTerritories())].getCorrespondingContinentID()) != (*(*this->getAllTerritories())[territoryIndexFromID(terrID, *getAllTerritories())].getCorrespondingContinentID()))
            continue;
        if (!visited[territoryIndexFromID(*x->getTerritoryID(), terrInCont)]/* && mutualAdj*/)
            dfs2(*x->getTerritoryID(), terrInCont, visited);
    }
}


// Helper function to dfs2() and dsf3().
// Given a territory ID and a vector of territory pointers, returns the index to the corresponding territory.
int Map::territoryIndexFromID(int terrID, std::vector<Territory*> terrInCont) {
    for (int i=0; i<terrInCont.size(); ++i) {
        if (*(*terrInCont[i]).getTerritoryID() == terrID)
            return i;
    }
    return 0;
}


// Validation check 3. Each country belongs to one and only one continent.
bool Map::validate3() {
    int numTerr = (*getAllTerritories()).size();
    bool present[numTerr];      // Array present keeps track of whether a territory has been found in continent.
    memset(present, false, sizeof present);     // Marking all territories as initially not present in any continent.

    for (auto&& x : allContinents) {
        std::cout << "Continent " << *x.getContinentID() << " contains Territories ";
        for (auto&& y : *x.getTerritoriesInContinent()) {
            int terrID = *y->getTerritoryID();
            std::cout << terrID << " ";

            // Same territory is present in more than one continent.
            if (present[territoryIndexFromID(terrID, *getAllTerritories())]) {
                std::cout << "\nAt least one territory belongs to more than one continent.\n";
                return false;
            }
            present[territoryIndexFromID(terrID, *getAllTerritories())] = true;
        }
        std::cout << "\n";
    }

    // Territory not present in any continent.
    for (auto&& x : present) {
        if (!x) {
            std::cout << "At least one territory does not belong to any continent.\n";
            return false;
        }
    }

    std::cout << "Each territory belongs to one and only one continent.\n";
    return true;
}


// Map insertion stream operator overload.
std::ostream& operator<<(std::ostream& output, const Map &map) {
    for (auto&& x : map.allContinents)
        output << x << std::endl;
    return output;
}

