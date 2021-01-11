#include "../Header_Files/MapLoader.h"

int main() {
    MapLoader* ml = new MapLoader();
    Map dominationMap = ml->loadMapFile("../src/_MapFiles/canada.map");
    std::cout << "\n" << dominationMap;
    if (dominationMap.validate()) {
        std::cout << "All three checks are respected. Therefore, canada.map is valid.\n\n";
    }
    else {
        std::cout << "canada.map is invalid\n\n";
    }

    std::cout << "\n\n\n";


    ConquestFileReader* cfr = new ConquestFileReader();
    ConquestFileReaderAdapter* adapter = new ConquestFileReaderAdapter(*cfr);
    Map conquestMap = adapter->loadMapFile("../src/_MapFiles/3D Cliff.map");
    std::cout << "\n" << conquestMap;
    if (conquestMap.validate()) {
        std::cout << "All three checks are respected. Therefore, 3D Cliff.map is valid.\n\n";
    }
    else {
        std::cout << "3D Cliff.map is invalid\n\n";
    }

    delete ml;
    delete cfr;
    delete adapter;
}