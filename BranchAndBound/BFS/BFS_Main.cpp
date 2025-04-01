#include "ConfigFile.h"
#include "BFS.h"
#include <iostream>
#include <vector>
#include "DataReader.h"
#include "DataSaver.h"
#include "Generate.h"
#include "NN.h"

int main() {

    Config config;
    if (!config.loadConfig("config.txt")) {
        std::cout << "Nie udało się załadować pliku konfiguracyjnego" << std::endl;
        return 0;
    }



    for( int i = 0; i < config.numTries; i++)
    {
        generateM(config.howBig);
        // Wczytanie macierzy odległości
        std::vector<std::vector<int>> distanceMatrix;
        if (!DataRead(config.File, distanceMatrix)) {
            std::cerr << "Nie udało się załadować pliku danych.\n";
            return 1;
        }
        int mincos;
        std::vector<int> bestPath;
        solveTSP_BFS(config, distanceMatrix, nearestNeighborTSP(distanceMatrix,mincos,bestPath));
    }








    return 0;

}
