#include <iostream>
#include "../Header_Files/Map.h"

int main()
{
    /*
     * Let territories 0, 1 and 2 be in continent 0, and territories 3, 4, 5 and 6 be in continent 1
     * 0---1---2
     * | \
     * |  \
     * 3---4---5---6
     */

    // Create a graph given in the above diagram

    std::cout << "\nTEST 1: Valid map\n\n";

    // Create 7 Territory objects.
    Territory terr0 = Territory(0, "terr0", 0, 0);
    Territory terr1 = Territory(1, "terr1", 0, 0);
    Territory terr2 = Territory(2, "terr2", 0, 0);
    Territory terr3 = Territory(3, "terr3", 0, 1);
    Territory terr4 = Territory(4, "terr4", 0, 1);
    Territory terr5 = Territory(5, "terr5", 0, 1);
    Territory terr6 = Territory(6, "terr6", 0, 1);

    // Assign respective adjacent territories.
    std::vector<Territory*> t0AdjTerrPtrs = {&terr1, &terr3, &terr4};
    terr0.addAdjTerritoryPointers(t0AdjTerrPtrs);
    terr1.addAdjTerritoryPointers({&terr0, &terr2});
    terr2.addAdjTerritoryPointers({&terr1});
    terr3.addAdjTerritoryPointers({&terr0, &terr4});
    terr4.addAdjTerritoryPointers({&terr0, &terr3, &terr5});
    terr5.addAdjTerritoryPointers({&terr4, &terr6});
    terr6.addAdjTerritoryPointers({&terr5});


    // Group the Territory objects in vectors according to their continents.
    std::vector<Territory*> cont0Terr = {&terr0, &terr1, &terr2};
    std::vector<Territory*> cont1Terr = {&terr3, &terr4, &terr5, &terr6};

    // Create 2 Continent objects with the Territory vectors as attributes.
    Continent cont0 = Continent(0, "cont0", 6);
    Continent cont1 = Continent(1, "cont1", 8);

    cont0.setTerritoriesInContinent(cont0Terr);
    cont1.setTerritoriesInContinent(cont1Terr);
    cont0.setAdjContinentPtrs({&cont1});
    cont1.setAdjContinentPtrs({&cont0});

    // Group the Continent objects in one vector.
    std::vector<Continent> allCont = {cont0, cont1};

    // Group all the Territory objects in one vector for easier access.
    std::vector<Territory> allTerr = {terr0, terr1, terr2, terr3, terr4, terr5, terr6};

    // Create a Map object with the Continent vector and Territory vector as attributes.
    Map map = Map(allCont, allTerr);
    std::cout << "MAP\n\n" << map;

    // Test Map copy constructor.
    std::cout << "TESTING COPY CONSTRUCTOR\n\n";
    Map map2 = map;
    map2.setAllContinents({cont0});
    std::cout << "MAP2\n" << map2;
    // Test Map class stream insertion operator after overload.
    std::cout << "MAP\n" << map << "\n";

    // Test validate method with created Map object.
    if (map.validate()) {
        std::cout << "All three checks are respected. Therefore, map is valid.\n\n";
    }
    else
        std::cout << "Map is invalid\n\n";




    /*
    * Let territories 0, 2 and 3 be in continent 0, and territory 1 be in continent 1, and territory 4 be in continent 2
    * 0   1
    * | \
    * |  \
    * 2---3---4    <-- not a connected graph
    */

    std::cout << "\nTEST 2: Invalid because map is not a connected graph\n\n";

    Territory t0 = Territory(0, "t0", 0, 0);
    Territory t1 = Territory(1, "t1", 0, 1);
    Territory t2 = Territory(2, "t2", 0, 0);
    Territory t3 = Territory(3, "t3", 0, 0);
    Territory t4 = Territory(4, "t4", 0, 2);

    t0.addAdjTerritoryPointers({&t2, &t3});
    t1.addAdjTerritoryPointers({});
    t2.addAdjTerritoryPointers({&t0, &t3});
    t3.addAdjTerritoryPointers({&t2, &t4});
    t4.addAdjTerritoryPointers({&t3});

    std::vector<Territory*> c0Terr = {&t0, &t2, &t3};
    std::vector<Territory*> c1Terr = {&t1};
    std::vector<Territory*> c2Terr = {&t4};

    Continent c0 = Continent(0, "c0", 6);
    Continent c1 = Continent(1, "c1", 2);
    Continent c2 = Continent(2, "c2", 2);

    c0.setTerritoriesInContinent(c0Terr);
    c1.setTerritoriesInContinent(c1Terr);
    c2.setTerritoriesInContinent(c2Terr);

    std::vector<Continent> allC = {c0, c1, c2};

    std::vector<Territory> allT = {t0, t1, t2, t3, t4};

    Map m = Map(allC, allT);

    // Using method determineAdjContinents() to set adjacent continent values instead of setting them explicitly.
    m.determineAdjContinents(c0);
    m.determineAdjContinents(c1);
    m.determineAdjContinents(c2);

    std::cout << "MAP\n\n" << m;

    if (m.validate()) {
        std::cout << "All three checks are respected. Therefore, map is valid.\n\n";
    }
    else
        std::cout << "Map is invalid\n\n";





    /*
     * Let territories 0 and 1 be in continent 0, and territories 2, 3 and 4 be in continent 1
     * 0---1
     * | \
     * |  \
     * 2---3   4    <-- not a connected subgraph, therefore not a connect graph
     */

    std::cout << "\nTEST 3: Invalid because continent is not a connected subgraph, therefore, map is not a connected graph\n\n";

    Territory tt0 = Territory(0, "tt0", 0, 0);
    Territory tt1 = Territory(1, "tt1", 0, 0);
    Territory tt2 = Territory(2, "tt2", 0, 1);
    Territory tt3 = Territory(3, "tt3", 0, 1);
    Territory tt4 = Territory(4, "tt4", 0, 1);

    tt0.addAdjTerritoryPointers({&tt1, &tt2, &tt3});
    tt1.addAdjTerritoryPointers({&tt0});
    tt2.addAdjTerritoryPointers({&tt0, &tt3});
    tt3.addAdjTerritoryPointers({&tt2});
    tt4.addAdjTerritoryPointers({});

    std::vector<Territory*> cc0Terr = {&tt0, &tt1};
    std::vector<Territory*> cc1Terr = {&tt2, &tt3, &tt4};

    Continent cc0 = Continent(0, "cc0", 4);
    Continent cc1 = Continent(1, "cc1", 6);

    cc0.setTerritoriesInContinent(cc0Terr);
    cc1.setTerritoriesInContinent(cc1Terr);

    std::vector<Continent> allCC = {cc0, cc1};

    std::vector<Territory> allTT = {tt0, tt1, tt2, tt3, tt4};

    Map mm = Map(allCC, allTT);

    // Using method determineAdjContinents() to set adjacent continent values instead of settingthe explicitly.
    mm.determineAdjContinents(cc0);
    mm.determineAdjContinents(cc1);

    std::cout << "MAP\n\n" << mm;

    if (mm.validate()) {
        std::cout << "All three checks are respected. Therefore, map is valid.\n\n";
    }
    else
        std::cout << "Map is invalid\n\n";




    /*
    * Let territories 0 and 1 and 2 be in continent 0, and territories 2, 3 and 4 be in continent 1
    * 0---1
    * | \
    * |  \
    * 2---3---4    Territory 0 is in two continents
    */

    std::cout << "\nTEST 4: Invalid because territories do not belong to exactly one continent\n\n";

    Territory ttt0 = Territory(0, "ttt0", 0, 0);
    Territory ttt1 = Territory(1, "ttt1", 0, 0);
    Territory ttt2 = Territory(2, "ttt2", 0, 1);
    Territory ttt3 = Territory(3, "ttt3", 0, 1);
    Territory ttt4 = Territory(4, "ttt4", 0, 1);

    ttt0.addAdjTerritoryPointers({&tt1, &tt2, &tt3});
    ttt1.addAdjTerritoryPointers({&tt0});
    ttt2.addAdjTerritoryPointers({&tt0, &ttt3});
    ttt3.addAdjTerritoryPointers({&tt2, &ttt4});
    ttt4.addAdjTerritoryPointers({&ttt3});

    std::vector<Territory*> ccc0Terr = {&ttt0, &ttt1, &ttt2};
    std::vector<Territory*> ccc1Terr = {&ttt2, &ttt3, &ttt4};

    Continent ccc0 = Continent(0, "ccc0", 6);
    Continent ccc1 = Continent(1, "ccc1", 6);

    ccc0.setTerritoriesInContinent(ccc0Terr);
    ccc1.setTerritoriesInContinent(ccc1Terr);

    std::vector<Continent> allCCC = {ccc0, ccc1};

    std::vector<Territory> allTTT = {ttt0, ttt1, ttt2, ttt3, ttt4};

    Map mmm = Map(allCCC, allTTT);

    mmm.determineAdjContinents(cc0);
    mmm.determineAdjContinents(cc1);

    std::cout << "MAP\n\n" << mmm;

    if (mmm.validate()) {
        std::cout << "All three checks are respected. Therefore, map is valid.\n\n";
    }
    else
        std::cout << "Map is invalid\n\n";



    return 0;
}


