
#ifndef COMP345_WARZONEGAME_MAPLOADER_H
#define COMP345_WARZONEGAME_MAPLOADER_H
#include "Map.h"
#include <fstream>

/**
 * constant values instantiated in unnamed namespace
 * Better used here since I could use them without restriction in the cpp file
 * Having them as data member makes the code bloated.
 */
namespace {
    const char* CONTINENT = "continent";
    const char* TERRITORY = "countries";
    const char* BORDER = "borders";
    const int MIN_CONTINENT_LENGTH = 3;
    const int MIN_TERRITORY_LENGTH = 5;
    const int MIN_BORDER_LENGTH = 3;

    const char *CONQUEST_CONTINENT = "Continent";
    const char *CONQUEST_TERRITORY = "Territories";
}


// TARGET
class MapLoader {
private:
    Map* map; //Pointer to map object
    std::string* fileName; //Name of file being load
    void loadContinents(std::ifstream& inFile); //load continents
    void loadTerritories(std::ifstream& inFile); //load territories
    void loadBorders(std::ifstream& inFile); //load territory adjacency
    void adjacencyInContinents(int continentFrom, int continentTo); //creating adjacency b/w continents
    bool filterContinentValues(const std::string& valueRead, int continentId, std::vector<Continent>& tempList); // Fetching data
    bool filterTerritoryValues(const std::string& value, std::vector<Territory>& tempList); // Fetching data
    bool filterTerritoryBorders(const std::string& value, int territoryTurn); // Fetching data

public:
    MapLoader(); //default constructor
    MapLoader(const MapLoader &mapLoader); //copy constructor
    ~MapLoader(); //destructor
    Map loadMapFile(std::string fileName); //starting method
    MapLoader& operator=(const MapLoader &mapLoader); //assignment operator
    friend std::ostream& operator<<(std::ostream& output, const MapLoader &mapLoader);//stream insertion operator
};




// ADAPTEE
class ConquestFileReader {
private:
    Map* conquestMap; //Pointer to map object
    std::string* conquestFileName; //Name of file being loaded
    std::vector<std::vector<std::string>> territoriesAdjacentTerritories;   // A vector of vector of adjacent territory names for each territory.
    void loadConquestContinents(std::ifstream& inFile); //load continents
    bool filterConquestContinentValues(const std::string& valueRead, int continentId, std::vector<Continent>& tempList); // Fetching data
    void loadConquestTerritories(std::ifstream& inFile); //load territories
    bool filterConquestTerritoryValues(const std::string& value, int territoryId, std::vector<Territory>& tempList); // Fetching data
    void adjacencyInContinents(int territoryFrom, int territoryTo);
    int getContinentIdFromName (std::string continentName);
    int getTerritoryIdFromName (std::string terrName);

public:
    ConquestFileReader(); //default constructor
    ConquestFileReader(const ConquestFileReader &conquestFileReader); //copy constructor
    ~ConquestFileReader(); //destructor
    Map loadConquestFile(std::string fileName); //starting method
    ConquestFileReader& operator=(const ConquestFileReader &conquestFileReader); //assignment operator
    friend std::ostream& operator<<(std::ostream& output, const ConquestFileReader &conquestFileReader); //stream insertion operator

};



// ADAPTER
class ConquestFileReaderAdapter : public MapLoader {
private:
    ConquestFileReader* conquestFileReader;
public:
    ConquestFileReaderAdapter(ConquestFileReader conq); // Parametrized constructor
    ConquestFileReaderAdapter(const ConquestFileReaderAdapter &conquestFileReaderAdapter);  // Copy constuctor
    ~ConquestFileReaderAdapter();    // Destructor
    Map loadMapFile(std::string fileName);    // Starting method inherited from MapLoader
    ConquestFileReaderAdapter& operator=(const ConquestFileReaderAdapter &conquestFileReaderAdapter);   // Assignment operator
    friend std::ostream& operator<<(std::ostream& output, const ConquestFileReaderAdapter &conquestFileReaderAdapter);  // Stream insertion operator
};


#endif //COMP345_WARZONEGAME_MAPLOADER_H