#include "MapLoader.h"
#include <fstream>
#include <sstream>

//Constructors
MapLoader::MapLoader() : map { nullptr } , fileName {nullptr}{}

//Copy constructor
MapLoader::MapLoader(const MapLoader &mapLoader) {
    this->map = new Map(*mapLoader.map);
    this->fileName = new std::string(*mapLoader.fileName);
}

//destructor
MapLoader::~MapLoader(){
    delete map;
    map = nullptr;
    delete fileName;
    fileName = nullptr;
}
//Checking if two adjacent territories are not in the continent, and make their continent adjacent to each other.
void MapLoader::adjacencyInContinents(int territoryFrom, int territoryTo) {
    int continentFrom = *(this->map->getAllTerritories()->at(territoryFrom - 1).getCorrespondingContinentID());
    int continentTo = *(this->map->getAllTerritories()->at(territoryTo - 1).getCorrespondingContinentID());
    std::vector<Continent*>* adjContPtrs = this->map->getAllContinents()->at(continentFrom- 1).getAdjContinentPtrs();
    //checking if continent was already pushed inside the adjacency list.
    bool contAlreadyPushed = find((*adjContPtrs).begin(), (*adjContPtrs).end(), &this->map->getAllContinents()->at(continentTo -1)) != (*adjContPtrs).end();
    if(continentFrom != continentTo && !contAlreadyPushed) {
        this->map->getAllContinents()->at(continentFrom- 1).getAdjContinentPtrs()->push_back(&this->map->getAllContinents()->at(continentTo -1));
    }
}

bool MapLoader::filterTerritoryBorders(const std::string& valueRead, int territoryTurn) {
    std::istringstream iStringStream(valueRead);
    int territoryId, adjacentTerritoryId;
    bool validLoad = false;
    try {
        if (valueRead.length() >= 3 && iStringStream >> territoryId) {
            if( territoryTurn != territoryId -1) { //
                throw std::exception();
            }
            validLoad = true;
            while (iStringStream >> adjacentTerritoryId) {
                this->map->getTerritoryAtPosition(territoryId - 1)->addAdjTerrPtr(this->map->getAllTerritories()->at(adjacentTerritoryId-1));
                adjacencyInContinents(territoryId, adjacentTerritoryId);
            }
        }
    }

    catch(std::istringstream::failure& e) {
        std::cout<<"Error loading borders.\n";
    }
    return validLoad;
}

/**
 * Iterate through the all territories form Map and fetch adjTerritoryIds
 * with proper integer values.
 * @param inFile
 */
void MapLoader::loadBorders(std::ifstream &inFile) {
    std::string stringValue;
    int territoryTurn = 0;
    try {
        while (getline(inFile, stringValue)) {
            if (!stringValue.empty() && stringValue.length() >= MIN_BORDER_LENGTH && filterTerritoryBorders(stringValue, territoryTurn)) {
                    territoryTurn++;
            }
        }
    }catch(std::istringstream::failure& e){}
}

bool MapLoader::filterContinentValues(const std::string& valueRead, int continentId, std::vector<Continent>& tempList) {
    std::istringstream iStringStream(valueRead);
    std::string continentName;
    bool validLoad = false;
    int continentBonus = 0;
    try {
        if (iStringStream >> continentName >> continentBonus) {
            tempList.push_back(Continent(continentId, continentName, continentBonus)); //FIXME:
            validLoad = true;
        }
    }catch(std::istringstream::failure& e) {
        std::cout << "A Continent or invalid value was encountered. \nCould not be loaded properly, ignoring..."<< std::endl;
        validLoad = false;
    }
    return validLoad;
}

bool MapLoader::filterTerritoryValues(const std::string &value, std::vector<Territory>& tempList) {
    std::istringstream iStringStream(value);
    std::string territoryName;
    int territoryId = 1;
    int continentId = 0;
    bool validLoad = false;
        if (iStringStream >> territoryId >> territoryName >> continentId && tempList.size() == territoryId -1 && !territoryName.empty()) {
            tempList.push_back(Territory(territoryId, territoryName, 0, continentId));
            validLoad = true;
        }
        else if(tempList.size() != territoryId -1 && !territoryName.empty()) { //
            throw std::exception();
        }
    return validLoad;
}

/**
 * IMPORTANT NOTE: here the territoryIds start at 1, but the vector index is
 * actually continentId - 1
 * @param inFile
 */
void MapLoader::loadTerritories(std::ifstream &inFile) {
    std::string stringValue;
    std::vector<Territory> territoryList;
    try {
        while (getline(inFile, stringValue)) {
            if (stringValue.find(BORDER) != std::string::npos) {
                this->map->setAllTerritories(territoryList);
                this->map->setContinentTerritories();
                loadBorders(inFile);
                break;
            } else if (!stringValue.empty() && stringValue.length() >= MIN_TERRITORY_LENGTH) {
                filterTerritoryValues(stringValue, territoryList); //FIXME: Returns bool for what tho?
            }

        }
    }catch(std::exception &e) {
        this->map->setAllTerritories(std::vector<Territory>());
        std::cout << "A Territory or invalid value was encountered. \nCould not be loaded properly, ignoring..."<< std::endl;
    }

}

/**
 * IMPORTANT NOTE: here the continentIds start at 1, but the vector index is
 * actually continentId - 1 [A.J]
 * @param inFile
 */
void MapLoader::loadContinents(std::ifstream& inFile) {
    std::string valueRead;
    int continentCount = 1; //from continentCount
    std::vector<Continent> continentList;
    try {
        while (getline(inFile, valueRead)) {
            if (valueRead.find(TERRITORY) != std::string::npos) {
                this->map->setAllContinents(continentList);
                loadTerritories(inFile);
                break;
            } else if (!valueRead.empty() && valueRead.length() >= MIN_CONTINENT_LENGTH &&
                       (filterContinentValues(valueRead, continentCount, continentList))) {
                continentCount++;
            }
        }
    }catch(std::exception &e){
        this->map->setAllContinents(std::vector<Continent>());
        this->map->setAllTerritories(std::vector<Territory>());
        std::cout<<"An error occurred while fetching a Continent, file is invalid.";
    }
}

Map MapLoader::loadMapFile(const std::string fileName){
    this->map = new Map();
    this->fileName = new std::string(fileName);
    std::string valueRead;
    std::ifstream  inputFile;
    bool isFileOpened = false;
    inputFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try {
        // Opening file
        inputFile.open(fileName.c_str());
        isFileOpened = true;
        while (getline(inputFile, valueRead)) {
            if (valueRead.find(CONTINENT) != std::string::npos) {
                loadContinents(inputFile);
                break;
            }
        }
        inputFile.close();
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                     "Finishing to load "<<*this->fileName<<" File..."<< std::endl;
        return *this->map;

    } catch(std::exception &e){
        this->map->setAllContinents(std::vector<Continent>());
        this->map->setAllTerritories(std::vector<Territory>());
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                     "Finishing to load "<<*this->fileName<<" File..."<< std::endl;
        std::cout<<"An error occurred while fetching the file: "<<fileName<<"... File is probably invalid.\n";
        return *this->map;
    }
    catch(std::ifstream::failure& e) {
        if(!isFileOpened) {
            std::cout << "Unable to open file: " << fileName << std::endl;
            return *this->map;
        }else {
            this->map->setAllContinents(std::vector<Continent>());
            this->map->setAllTerritories(std::vector<Territory>());
            std::cout<<"An error occurred while fetching the file: "<<fileName<<"... File is probably invalid.\n";
            return *this->map;
        }
    }
}

//Assignment operator
MapLoader& MapLoader::operator=(const MapLoader &mapLoader) {
    if(&mapLoader != this) {
        delete map;
        map = new Map(*mapLoader.map);
    }
    return *this;
}
//Stream insertion operator
std::ostream& operator<<(std::ostream& output, const MapLoader &mapLoader) {
    output << "These are resulting  information about the map\n"
              "Number of Continents:\t"<<mapLoader.map->getNumberOfContinents()<<"\n"
              "Number of Territories:\t"<<mapLoader.map->getNumberOfTerritories()<<"\n"
               "\n~~~~~~~~~~~~~~~Detailed information~~~~~~~~~~~~~~~\n"<<*(mapLoader.map);
    return output;
}






/************************************************ CONQUEST FILE READER (ADAPTEE) ************************************************/


//Constructors
ConquestFileReader::ConquestFileReader() {
    conquestMap = new Map();
    conquestFileName = new std::string();
}

//Copy consructor
ConquestFileReader::ConquestFileReader(const ConquestFileReader &conquestFileReader) {
    this->conquestMap = new Map(*conquestFileReader.conquestMap);
    this->conquestFileName = new std::string(*conquestFileReader.conquestFileName);
    this->territoriesAdjacentTerritories = std::vector<std::vector<std::string>>(conquestFileReader.territoriesAdjacentTerritories);
}


//Destructor
ConquestFileReader::~ConquestFileReader(){
    delete conquestMap;
    conquestMap = nullptr;
    delete conquestFileName;
    conquestFileName = nullptr;
}


//Assignment operator
ConquestFileReader& ConquestFileReader::operator=(const ConquestFileReader &conquestFileReader) {
    if(&conquestFileReader != this) {
        delete conquestMap;
        conquestMap = new Map(*conquestFileReader.conquestMap);
        delete conquestFileName;
        conquestFileName = new std::string(*conquestFileReader.conquestFileName);
    }
    return *this;
}

//Stream insertion operator
std::ostream& operator<<(std::ostream& output, const ConquestFileReader &conquestFileReader) {
    output << "These are resulting  information about the conquest map\n"
              "Number of Continents:\t"<<conquestFileReader.conquestMap->getNumberOfContinents()<<"\n"
                                                                                                  "Number of Territories:\t"<<conquestFileReader.conquestMap->getNumberOfTerritories()<<"\n"
                                                                                                                                                                                        "\n~~~~~~~~~~~~~~~Detailed information~~~~~~~~~~~~~~~\n"<<*(conquestFileReader.conquestMap);
    return output;
}



Map ConquestFileReader::loadConquestFile(std::string fileName) {
    this->conquestMap = new Map();
    this->conquestFileName = new std::string(fileName);
    std::string valueRead;
    std::ifstream  inputFile;
    bool isFileOpened = false;
    inputFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try {
        //Opening file
        inputFile.open(fileName.c_str());
        isFileOpened = true;

        while (getline(inputFile, valueRead)) {
            if (valueRead.find(CONQUEST_CONTINENT) != std::string::npos) {
                loadConquestContinents(inputFile);
                break;
            }
        }
        inputFile.close();
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                     "Finishing to load "<<*this->conquestFileName<<" File..."<< std::endl;
        return *this->conquestMap;
    }
    catch(std::exception &e){
        this->conquestMap->setAllContinents(std::vector<Continent>());
        this->conquestMap->setAllTerritories(std::vector<Territory>());
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                     "Finishing to load "<<*this->conquestFileName<<" File..."<< std::endl;
        std::cout<<"An error occurred while fetching the file: "<<fileName<<"... File is probably invalid.\n";
        return *this->conquestMap;
    }
    catch(std::ifstream::failure& e) {
        if(!isFileOpened) {
            std::cout << "Unable to open file: " << fileName << std::endl;
            return *this->conquestMap;
        }
        else {
            this->conquestMap->setAllContinents(std::vector<Continent>());
            this->conquestMap->setAllTerritories(std::vector<Territory>());
            std::cout<<"An error occurred while fetching the file: "<<fileName<<"... File is probably invalid.\n";
            return *this->conquestMap;
        }
    }
}



void ConquestFileReader::loadConquestContinents(std::ifstream& inFile) {
    std::string valueRead;
    int continentCount = 1;
    std::vector<Continent> continentList;
    try {
        while (getline(inFile, valueRead)) {
            if (valueRead.find(CONQUEST_TERRITORY) != std::string::npos) {      // If the [Countries] section is reached.
                this->conquestMap->setAllContinents(continentList);
                loadConquestTerritories(inFile);
                break;
            } else if (!valueRead.empty() && valueRead.length() >= MIN_CONTINENT_LENGTH &&      // If you're still in the [Continents] section
                       (filterConquestContinentValues(valueRead, continentCount, continentList))) {
                continentCount++;
            }
        }
    } catch(std::exception &e){
        this->conquestMap->setAllContinents(std::vector<Continent>());
        this->conquestMap->setAllTerritories(std::vector<Territory>());
        std::cout<<"An error occurred while fetching a Continent, file is invalid.";
    }
}


bool ConquestFileReader::filterConquestContinentValues(const std::string& valueRead, int continentId, std::vector<Continent>& tempList) {
    std::istringstream iStringStream(valueRead);
    std::string continentName;
    bool validLoad = false;
    int continentBonus = 0;
    try {
        // Conquest continent names can haves spaces in them, so the continent bonus is separated from the continent name by an '='
        if (getline(iStringStream, continentName,'=') && iStringStream >> continentBonus) {
            tempList.push_back(Continent(continentId, continentName, continentBonus));
            validLoad = true;
        }
    } catch(std::istringstream::failure& e) {
        std::cout << "A Continent or invalid value was encountered. \nCould not be loaded properly, ignoring..."<< std::endl;
        validLoad = false;
    }
    return validLoad;
}


// Combine loading territories and loading borders, since in Conquest maps, they are in the same section
void ConquestFileReader::loadConquestTerritories(std::ifstream &inFile) {
    std::string stringValue;
    std::vector<Territory> territoryList;
    int territoryCount = 1;

    try {
        while (getline(inFile, stringValue)) {

            if (!stringValue.empty() && stringValue.length() >= MIN_TERRITORY_LENGTH) {      // While you're still in the [Territories] section
                filterConquestTerritoryValues(stringValue, territoryCount, territoryList);
                territoryCount++;
            }

            else if (stringValue.empty())
                continue;

            this->conquestMap->setAllTerritories(territoryList);
        }

        // Now that the file is done being read, we can organize the territories' adjacent borders.
        for (int i = 0; i < conquestMap->getNumberOfTerritories(); ++i) {
            for (auto&& terrName : territoriesAdjacentTerritories.at(i)) {
                this->conquestMap->getTerritoryAtPosition(*conquestMap->getAllTerritories()->at(i).getTerritoryID() - 1)->addAdjTerrPtr(this->conquestMap->getAllTerritories()->at(getTerritoryIdFromName(terrName) - 1));
                adjacencyInContinents(*conquestMap->getAllTerritories()->at(i).getTerritoryID(), getTerritoryIdFromName(terrName));
            }
        }
        this->conquestMap->setContinentTerritories();
    }

    catch(std::ios_base::failure& e) {
        std::string exception = e.what();
        if (exception == "basic_ios::clear: iostream error" || exception == "ios_base::clear: unspecified iostream_category error") {
            for (int i = 0; i < conquestMap->getNumberOfTerritories(); ++i) {
                for (auto &&terrName : territoriesAdjacentTerritories.at(i)) {
                    this->conquestMap->getTerritoryAtPosition(
                            *conquestMap->getAllTerritories()->at(i).getTerritoryID() - 1)->addAdjTerrPtr(
                            this->conquestMap->getAllTerritories()->at(getTerritoryIdFromName(terrName) - 1));
                    adjacencyInContinents(*conquestMap->getAllTerritories()->at(i).getTerritoryID(),
                                          getTerritoryIdFromName(terrName));
                }
            }
            this->conquestMap->setContinentTerritories();
        } else {
            this->conquestMap->setAllTerritories(std::vector<Territory>());
            std::cout << "A Territory or invalid value was encountered. \nCould not be loaded properly, ignoring..."
                      << std::endl;
        }
    }
    catch (std::exception &e) {
        this->conquestMap->setAllTerritories(std::vector<Territory>());
        std::cout << "A Territory or invalid value was encountered. \nCould not be loaded properly, ignoring..."<< std::endl;
    }
}


bool ConquestFileReader::filterConquestTerritoryValues(const std::string &value, int territoryId, std::vector<Territory>& tempList) {
    std::istringstream iStringStream(value);
    std::string territoryName;
    std::string continentName = "";
    bool validLoad = false;
    std::string adjTerritoryName;
    std::vector<std::string> adjTerritoryNames;
    static const int max_line = 65536;
    // Format of [Territories] section:
    // territory_name, x-coordinate (ignore), x-coordinate (ignore), continent_name, adjacent_territory_name1, adjacent_territory_name2, ...
    // Start by reading the territory name and continent name.
    if (getline(iStringStream, territoryName,',') && iStringStream.ignore(max_line, ',') && iStringStream.ignore(max_line, ',') && getline(iStringStream, continentName,',')
        && tempList.size() == territoryId -1 && !territoryName.empty()) {
        tempList.push_back(Territory(territoryId, territoryName, 0, getContinentIdFromName(continentName)));
        validLoad = true;

        // Save the names of the adjacent territories in a vector.
        while (getline(iStringStream, adjTerritoryName, ',')) {
            adjTerritoryNames.push_back(adjTerritoryName);
        };
        territoriesAdjacentTerritories.push_back(adjTerritoryNames);
    }

    else if(tempList.size() != territoryId -1 && !territoryName.empty()) {
        throw std::exception();
    }
    return validLoad;
}


int ConquestFileReader::getContinentIdFromName (std::string continentName) {
    for (auto&& continent : *conquestMap->getAllContinents())
        if (*continent.getContinentName() == continentName)
            return *continent.getContinentID();
}

int ConquestFileReader::getTerritoryIdFromName (std::string terrName) {
    for (auto&& terr : *conquestMap->getAllTerritories())
        if (*terr.getTerritoryName() == terrName)
            return *terr.getTerritoryID();
}



void ConquestFileReader::adjacencyInContinents(int territoryFrom, int territoryTo) {
    int continentFrom = *(this->conquestMap->getAllTerritories()->at(territoryFrom - 1).getCorrespondingContinentID());
    int continentTo = *(this->conquestMap->getAllTerritories()->at(territoryTo - 1).getCorrespondingContinentID());
    std::vector<Continent*>* adjContPtrs = this->conquestMap->getAllContinents()->at(continentFrom- 1).getAdjContinentPtrs();
    //checking if continent was already pushed inside the adjacency list.
    bool contAlreadyPushed = find((*adjContPtrs).begin(), (*adjContPtrs).end(), &this->conquestMap->getAllContinents()->at(continentTo -1)) != (*adjContPtrs).end();
    if(continentFrom != continentTo && !contAlreadyPushed) {
        this->conquestMap->getAllContinents()->at(continentFrom- 1).getAdjContinentPtrs()->push_back(&this->conquestMap->getAllContinents()->at(continentTo -1));
    }
}










/*********************************** CONQUEST TO DOMINATION MAP READER (ADAPTER) ***********************************/

// Parametrized constructor
ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReader conq) {
    conquestFileReader = new ConquestFileReader(conq);
}

// Copy constructor
ConquestFileReaderAdapter::ConquestFileReaderAdapter(const ConquestFileReaderAdapter &conquestFileReaderAdapter) {
    this->conquestFileReader = new ConquestFileReader(*conquestFileReaderAdapter.conquestFileReader);
}

// Destructor
ConquestFileReaderAdapter::~ConquestFileReaderAdapter() {
    delete conquestFileReader;
    conquestFileReader = nullptr;
}

// Starting method
Map ConquestFileReaderAdapter::loadMapFile(std::string fileName) {
    return conquestFileReader->loadConquestFile(fileName);
}

// Assignment operator
ConquestFileReaderAdapter& ConquestFileReaderAdapter::operator=(const ConquestFileReaderAdapter &conquestFileReaderAdapter) {
    if (this != &conquestFileReaderAdapter) {
        delete conquestFileReader;
        this->conquestFileReader = new ConquestFileReader(*conquestFileReaderAdapter.conquestFileReader);
    }
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& output, const ConquestFileReaderAdapter &conquestFileReaderAdapter) {
    std::cout << *conquestFileReaderAdapter.conquestFileReader;
}