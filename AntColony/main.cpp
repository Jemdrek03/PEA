#include <iostream>
#include "ConfigFile.h"
#include "testing.h"

int main() {


    //plik 1
    Config config;
    // Wczytanie konfiguracji
    if (!config.loadConfig("config.txt")) {
        std::cerr << "Nie udało się załadować pliku konfiguracyjnego.\n";
    }


    std::vector<std::vector<int>> distanceMatrix;
    if (!DataRead(config.File, distanceMatrix)) {
        std::cerr << "Nie udało się załadować pliku danych.\n";
    }

    std::vector<int> bestPath;
    int mincost;

    for(int i = 0; i < config.numTries; i++) {
        solveTSP_ACO(config, distanceMatrix, mincost, bestPath);
    }
























//    config.File = "data.txt";
//    config.howBig = 320;
//    config.opt = 1600;
//
//    //ants 5
//    config.numAnts = 5;
//    config.evaporationRate = 0.5;
//    config.alpha = 1.0;
//    config.beta = 10.0;
//    config.pheromoneMin = 0.1;
//    config.pheromoneMax = 7.0;
//    config.numIterations = 1500;
//    doReady(config);
//
//    //ants 10
//    config.numAnts = 10;
//    doReady(config);
//
//    //ants 50
//    config.numAnts = 50;
//    doReady(config);
//
//    //evap 0.2
//    config.numAnts = 10;
//    config.evaporationRate = 0.2;
//    doReady(config);
//
//    //evap 0.5
//    config.evaporationRate = 0.5;
//    doReady(config);
//
//
//    //evap 0.7
//    config.evaporationRate = 0.7;
//    doReady(config);
//
//    //apha 0.5
//    config.alpha = 0.5;
//    doReady(config);
//
//    //apha 1.0
//    config.alpha = 1.0;
//    doReady(config);
//
//    //alpha 10
//    config.alpha = 10.0;
//    doReady(config);
//
//    //beta 1.0
//    config.alpha = 1.0;
//    config.beta = 1.0;
//    doReady(config);
//
//    //beta 5.0
//    config.beta = 5.0;
//    doReady(config);
//
//    //beta 10.0
//    config.beta = 10.0;
//    doReady(config);
//
//    //min 0.1 max 10
//    config.pheromoneMin = 0.1;
//    config.pheromoneMax = 10.0;
//    doReady(config);
//
//    //min 4 max 10
//    config.pheromoneMin = 4.0;
//    config.pheromoneMax = 10.0;
//    doReady(config);
//
//    //min 4 max 6
//    config.pheromoneMin = 4.0;
//    config.pheromoneMax = 6.0;
//    doReady(config);
//
//    //min 1 max 10
//    config.pheromoneMin = 1.0;
//    config.pheromoneMax = 10.0;
//    doReady(config);
//
//    //min 1 max 5
//    config.pheromoneMin = 1.0;
//    config.pheromoneMax = 5.0;
//    doReady(config);
//
//    //min 0.1 max 5
//    config.pheromoneMin = 0.1;
//    config.pheromoneMax = 5.0;
//    doReady(config);
//
//    //iterations 100
//    config.numIterations = 100;
//    doReady(config);
//
//    //iteraition 1000
//    config.numIterations = 1000;
//    doReady(config);
//
//    //iterations 2000
//    config.numIterations = 200;
//    doReady(config);
//
//
//    //plik 2
//    config.File = "data2.txt";
//    config.howBig = 171;
//    config.opt = 2755;
//
//    //ants 5
//    config.numAnts = 5;
//    config.evaporationRate = 0.5;
//    config.alpha = 1.0;
//    config.beta = 10.0;
//    config.pheromoneMin = 0.1;
//    config.pheromoneMax = 7.0;
//    config.numIterations = 1500;
//    doReady(config);
//
//    //ants 10
//    config.numAnts = 10;
//    doReady(config);
//
//    //ants 50
//    config.numAnts = 50;
//    doReady(config);
//
//    //evap 0.2
//    config.numAnts = 10;
//    config.evaporationRate = 0.2;
//    doReady(config);
//
//    //evap 0.5
//    config.evaporationRate = 0.5;
//    doReady(config);
//
//
//    //evap 0.7
//    config.evaporationRate = 0.7;
//    doReady(config);
//
//    //apha 0.5
//    config.alpha = 0.5;
//    doReady(config);
//
//    //apha 1.0
//    config.alpha = 1.0;
//    doReady(config);
//
//    //alpha 10
//    config.alpha = 10.0;
//    doReady(config);
//
//    //beta 1.0
//    config.alpha = 1.0;
//    config.beta = 1.0;
//    doReady(config);
//
//    //beta 5.0
//    config.beta = 5.0;
//    doReady(config);
//
//    //beta 10.0
//    config.beta = 10.0;
//    doReady(config);
//
//    //min 0.1 max 10
//    config.pheromoneMin = 0.1;
//    config.pheromoneMax = 10.0;
//    doReady(config);
//
//    //min 4 max 10
//    config.pheromoneMin = 4.0;
//    config.pheromoneMax = 10.0;
//    doReady(config);
//
//    //min 4 max 6
//    config.pheromoneMin = 4.0;
//    config.pheromoneMax = 6.0;
//    doReady(config);
//
//    //min 1 max 10
//    config.pheromoneMin = 1.0;
//    config.pheromoneMax = 10.0;
//    doReady(config);
//
//    //min 1 max 5
//    config.pheromoneMin = 1.0;
//    config.pheromoneMax = 5.0;
//    doReady(config);
//
//    //min 0.1 max 5
//    config.pheromoneMin = 0.1;
//    config.pheromoneMax = 5.0;
//    doReady(config);
//
//    //iterations 100
//    config.numIterations = 100;
//    doReady(config);
//
//    //iteraition 1000
//    config.numIterations = 1000;
//    doReady(config);
//
//    //iterations 2000
//    config.numIterations = 200;
//    doReady(config);
//
//
//    //plik 3
//    config.File = "data3.txt";
//    config.howBig = 403;
//    config.opt = 2465;
//
//    //ants 5
//    config.numAnts = 5;
//    config.evaporationRate = 0.5;
//    config.alpha = 1.0;
//    config.beta = 10.0;
//    config.pheromoneMin = 0.1;
//    config.pheromoneMax = 7.0;
//    config.numIterations = 1500;
//    doReady(config);
//
//    //ants 10
//    config.numAnts = 10;
//    doReady(config);
//
//    //ants 50
//    config.numAnts = 50;
//    doReady(config);
//
//    //evap 0.2
//    config.numAnts = 10;
//    config.evaporationRate = 0.2;
//    doReady(config);
//
//    //evap 0.5
//    config.evaporationRate = 0.5;
//    doReady(config);
//
//
//    //evap 0.7
//    config.evaporationRate = 0.7;
//    doReady(config);
//
//    //apha 0.5
//    config.alpha = 0.5;
//    doReady(config);
//
//    //apha 1.0
//    config.alpha = 1.0;
//    doReady(config);
//
//    //alpha 10
//    config.alpha = 10.0;
//    doReady(config);
//
//    //beta 1.0
//    config.alpha = 1.0;
//    config.beta = 1.0;
//    doReady(config);
//
//    //beta 5.0
//    config.beta = 5.0;
//    doReady(config);
//
//    //beta 10.0
//    config.beta = 10.0;
//    doReady(config);
//
//    //min 0.1 max 10
//    config.pheromoneMin = 0.1;
//    config.pheromoneMax = 10.0;
//    doReady(config);
//
//    //min 4 max 10
//    config.pheromoneMin = 4.0;
//    config.pheromoneMax = 10.0;
//    doReady(config);
//
//    //min 4 max 6
//    config.pheromoneMin = 4.0;
//    config.pheromoneMax = 6.0;
//    doReady(config);
//
//    //min 1 max 10
//    config.pheromoneMin = 1.0;
//    config.pheromoneMax = 10.0;
//    doReady(config);
//
//    //min 1 max 5
//    config.pheromoneMin = 1.0;
//    config.pheromoneMax = 5.0;
//    doReady(config);
//
//    //min 0.1 max 5
//    config.pheromoneMin = 0.1;
//    config.pheromoneMax = 5.0;
//    doReady(config);
//
//    //iterations 100
//    config.numIterations = 100;
//    doReady(config);
//
//    //iteraition 1000
//    config.numIterations = 1000;
//    doReady(config);
//
//    //iterations 2000
//    config.numIterations = 200;
//    doReady(config);





    return 0;
}
