#include "ConfigFile.h"
#include "Random.h"
#include <iostream>
#include <vector>
#include <chrono>
#include "DataReader.h"
#include "DataSaver.h"
#include "Generate.h"

int main() {

    Config config;
    if (!config.loadConfig("config.txt")) {
        std::cout << "Nie udało się załadować pliku konfiguracyjnego" << std::endl;
        return 0;
    }

    for(int i = 0; i < config.numTries; i++)
    {
        generateM(config.howBig);
        std::vector<std::vector<int>> distanceMatrix;
        if(!DataRead(config.File, distanceMatrix))
        {
            std::cout<<"Nie udało się załadować pliku z danymi" <<std::endl;
            return 0;
        }
        int minCost;
        std::vector<int> bestPath;
        auto start = std::chrono::high_resolution_clock::now();
        randomTSP(distanceMatrix, config.numTrials, minCost, bestPath, config.showProgress, config.optimalValue, config.maxRunTimeMinutes, config.thresholdValue);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(end - start);
        saveResults("Results_Random.csv", config, minCost, bestPath, duration.count());
    }


    return 0;
}