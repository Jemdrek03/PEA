#include "ConfigFile.h"
#include "DataReader.h"
#include "NN.h"
#include "DataSaver.h"
#include "Generate.h"
#include <iostream>
#include <chrono>
#include <vector>

int main()
{
    Config config;
    if(!config.loadConfig("config.txt")){
        std::cout<<"Nie udalo sie zaladowac pliku konfiguracyjnego"<<std::endl;
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
        nearestNeighborTSP(distanceMatrix,minCost,bestPath,  config.optimalValue,  config.maxRunTimeMinutes,  config.thresholdValue);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(end - start);
        saveResults("Results_NN.csv", config, minCost, bestPath, duration.count());
    }


    return 0;
}