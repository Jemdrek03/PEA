#include <iostream>
#include "ConfigFile.h"
#include "DataReader.h"
#include "LC.h"
#include "Generate.h"

int main() {
    // Wczytanie konfiguracji
    Config config;
    if (!config.loadConfig("config.txt")) {
        std::cerr << "Nie udało się załadować pliku konfiguracyjnego.\n";
        return 1;
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
        solveTSP_LowestCost(config, distanceMatrix);
    }




    return 0;
}
