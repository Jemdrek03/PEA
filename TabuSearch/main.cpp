#include <iostream>
#include "ConfigFile.h"
#include "DataReader.h"
#include "TabuSearch.h"
#include "NN.h"
#include "testing.h"



int main() {

   //plik 1
   Config config;
    // Wczytanie konfiguracji
    if (!config.loadConfig("config.txt")) {
        std::cerr << "Nie udało się załadować pliku konfiguracyjnego.\n";
    }

//    std::vector<std::vector<int>> distanceMatrix;
//    if (!DataRead(config.File, distanceMatrix)) {
//        std::cerr << "Nie udało się załadować pliku danych.\n";
//    }
//
//    std::vector<int> bestPath;
//    int mincost;
//
//    if(config.readyResult == 1)
//    {
//        nearestNeighborTSP(distanceMatrix,mincost,bestPath);
//    }
//    else
//    {
//        // Wylosuj losową ścieżkę
//        std::vector<int> allVertices;
//        for (int i = 1; i < config.howBig; ++i) {
//            allVertices.push_back(i);
//        }
//
//        // Losowe tasowanie wierzchołków (pomijając 0)
//        std::random_device rd;
//        std::mt19937 g(rd());
//        std::shuffle(allVertices.begin(), allVertices.end(), g);
//        // Utwórz pełną ścieżkę z 0 na początku i końcu
//        bestPath.clear();
//        bestPath.push_back(0); // Początek
//        bestPath.insert(bestPath.end(), allVertices.begin(), allVertices.end());
//        bestPath.push_back(0); // Koniec
//
//    }
//
//    for(int i = 0; i < config.numTries; i++) {
//        solveTSP_TS(config, distanceMatrix, mincost, bestPath, config.whichOpt);
//    }


   config.File = "data1.txt";
   config.howBig = 48;
   config.tabuListSize = config.howBig * 0.4;
   config.opt = 1776;

   //1. 3opt dla nn
   config.whichOpt = 3;
   config.readyResult = 1;

   doReady(config);


   //2. 3opt dla random
    config.readyResult = 0;
    doRandom(config);

   //3. 2opt dla nn
    config.whichOpt = 2;
    config.readyResult = 1;
    doReady(config);

   //4. 2opt dla random
    config.readyResult = 0;
    doRandom(config);



    //plik 2
    config.File = "data2.txt";
    config.howBig = 171;
    config.tabuListSize = config.howBig * 0.4;
    config.opt = 2755;

    //1. 3opt dla nn
    config.whichOpt = 3;
    config.readyResult = 1;

    doReady(config);


    //2. 3opt dla random
    config.readyResult = 0;
    doRandom(config);

    //3. 2opt dla nn
    config.whichOpt = 2;
    config.readyResult = 1;
    doReady(config);

    //4. 2opt dla random
    config.readyResult = 0;
    doRandom(config);


    //plik 3
    config.File = "data3.txt";
    config.howBig = 403;
    config.tabuListSize = config.howBig * 0.4;
    config.opt = 2465;

    //1. 3opt dla nn
    config.whichOpt = 3;
    config.readyResult = 1;

    doReady(config);


    //2. 3opt dla random
    config.readyResult = 0;
    doRandom(config);

    //3. 2opt dla nn
    config.whichOpt = 2;
    config.readyResult = 1;
    doReady(config);

    //4. 2opt dla random
    config.readyResult = 0;
    doRandom(config);


    return 0;
}
