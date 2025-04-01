#include "testing.h"


void doReady(Config& config)
{


    std::vector<std::vector<int>> distanceMatrix;
    if (!DataRead(config.File, distanceMatrix)) {
        std::cerr << "Nie udało się załadować pliku danych.\n";
        return;
    }

    std::vector<int> bestPath;
    int mincost;

    for(int i = 0; i < config.numTries; i++) {
        solveTSP_ACO(config, distanceMatrix, mincost, bestPath);
    }

}
