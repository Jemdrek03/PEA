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
    std::cout<<nearestNeighborTSP(distanceMatrix,mincost,bestPath);

    for(int i = 0; i < config.numTries; i++) {
        solveTSP_SA(config, distanceMatrix, mincost, bestPath);
    }

}




void doRandom(Config& config)
{

    std::vector<std::vector<int>> distanceMatrix;
    if (!DataRead(config.File, distanceMatrix)) {
        std::cerr << "Nie udało się załadować pliku danych.\n";
        return;
    }

    // Wylosuj losową ścieżkę
    std::vector<int> allVertices;
    for (int i = 1; i < config.howBig; ++i) {
        allVertices.push_back(i);
    }

    // Losowe tasowanie wierzchołków (pomijając 0)
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allVertices.begin(), allVertices.end(), g);

    std::vector<int> bestPath;
    int mincost;
    // Utwórz pełną ścieżkę z 0 na początku i końcu
    bestPath.clear();
    bestPath.push_back(0); // Początek
    bestPath.insert(bestPath.end(), allVertices.begin(), allVertices.end());
    bestPath.push_back(0); // Koniec

    for(int i = 0; i < config.numTries; i++) {
        solveTSP_SA(config, distanceMatrix, mincost, bestPath);
    }
}