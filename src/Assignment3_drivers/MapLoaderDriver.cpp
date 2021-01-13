#include "../src/Header_Files/MapLoader.h"

int main() {
    auto mapLoaderValid1 = new MapLoader();
    auto mapLoaderValid2 = new MapLoader();
    auto mapLoaderInvalid = new MapLoader();
    Map mapFirst = mapLoaderValid1->loadMapFile("../Part02/canada.map");
    if (mapFirst.validate()) {
        std::cout << "All three checks are respected. Therefore, ../Part02/canada.map is valid.\n\n";
    }
    else {
        std::cout << "../Part02/canada.map is invalid\n\n";
    }
    Map mapSecond = mapLoaderValid2->loadMapFile("../Part02/europass.map");
    if (mapSecond.validate()) {
        std::cout << "All three checks are respected. Therefore, ../Part02/europass.map is valid.\n\n";
    }
    else {
        std::cout << "../Part02/europass.map is invalid\n\n";
    }
    Map mapThird = mapLoaderInvalid->loadMapFile("../Part02/canada_invalid.map");
    if (mapThird.validate()) {
        std::cout << *mapLoaderInvalid << std::endl;
        std::cout << "All three checks are respected. Therefore, ../Part02/canada_invalid.map is valid.\n\n";
    }
    else {
        std::cout << "\n../Part02/canada_invalid.map is invalid\n\n";
    }

}
