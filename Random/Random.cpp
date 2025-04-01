#include "Random.h"
#include <limits>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>

void randomTSP(const std::vector<std::vector<int>>& distanceMatrix, int numTrials, int& minCost, std::vector<int>& bestPath, bool showProgress, int optimalValue, int maxRunTimeMinutes, double thresholdValue) {
    int n = distanceMatrix.size();
    minCost = std::numeric_limits<int>::max();
    bestPath.clear();

    std::mt19937 rng(static_cast<unsigned>(time(nullptr))); // generator losowy z aktualnym czasem
    std::uniform_int_distribution<int> dist(0, n - 1);

    auto start = std::chrono::steady_clock::now(); // Start zegara
    const double threshold = thresholdValue * optimalValue;
    // std::cout<<threshold;

    for ( int trial = 0; trial < numTrials; ++trial) {

        // Sprawdzenie, czy minęło 30 minut lub znaleziono rozwiązanie w granicach 10%
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - start;
        if (elapsed.count() > maxRunTimeMinutes * 60) {
            std::cout << "\nMaksymalny czas działania osiągnięty (30 minut).\n";
            break;
        }
        if (minCost <= threshold) {
            //std::cout << "\nZnaleziono rozwiazanie w granicach 1% od optymalnej wartosci.\n";
            break;
        }



        std::vector<int> unvisited;
        for (int i = 0; i < n; ++i) unvisited.push_back(i); // Inicjalizacja listy nieodwiedzonych wierzcholkow

        std::vector<int> path;
        int currentNode = dist(rng);       // Wybierz losowy startowy wierzchołek
        path.push_back(currentNode);

        unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), currentNode), unvisited.end()); // Usuń startowy wierzchołek z listy nieodwiedzonych

        int currentCost = 0;
        while (!unvisited.empty()) {
            std::uniform_int_distribution<int> nextDist(0, unvisited.size() - 1);
            int nextIndex = nextDist(rng);    // Wybierz losowy indeks z listy nieodwiedzonych
            int nextNode = unvisited[nextIndex];

            currentCost += distanceMatrix[currentNode][nextNode]; // Aktualizuj koszt
            currentNode = nextNode;                               // Przejdź do następnego wierzcholka
            path.push_back(currentNode);                          // Dodaj do ścieżki

            unvisited.erase(unvisited.begin() + nextIndex);       // Usuń odwiedzone wierzcholki z listy
        }

        // Zamknij cykl, wracając do pierwszego wierzchołka
        currentCost += distanceMatrix[currentNode][path[0]];

        // Sprawdź, czy nowa ścieżka jest najlepsza
        if (currentCost < minCost) {
            minCost = currentCost;
            bestPath = path;
        }



        if(showProgress)
        {
            double progress = (double)(trial + 1.0) / numTrials * 100;
            std::cout << "\rPostep: " << std::fixed << std::setprecision(2) << progress <<"%";
            std::cout.flush();
        }
    }
}
