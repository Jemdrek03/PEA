#ifndef ANTCOLONY_ANTSEARCH_H
#define ANTCOLONY_ANTSEARCH_H

#include <vector>
#include <string>
#include <chrono>
#include <vector>
#include <random>
#include <cmath>
#include <limits>
#include <algorithm>
#include <thread>
#include <mutex>
#include "ConfigFile.h"
#include "DataSaver.h"

struct Ant {
    std::vector<int> path;
    int cost;
};

// Funkcja do obliczania kosztu ścieżki
static float calculatePathCost(const std::vector<std::vector<int>>& distanceMatrix, const std::vector<int>& path);

// Funkcja do aktualizacji feromonów
static void updatePheromones(
        std::vector<std::vector<double>>& pheromones,
        const std::vector<std::vector<int>>& distanceMatrix,
        const std::vector<Ant>& ants,
        const Config& config
);

// Funkcja wybierająca kolejne miasto dla mrówki
static int selectNextCity(
        int currentCity,
        const std::vector<bool>& visited,
        const std::vector<std::vector<double>>& pheromones,
        const std::vector<std::vector<double>>& heuristic,
        const Config& config
);

static void constructAntPath();

// Główna funkcja rozwiązująca problem TSP za pomocą algorytmu mrówkowego (ACO)
void solveTSP_ACO(
        Config& config,
        const std::vector<std::vector<int>>& distanceMatrix,
        int& minCost,
        std::vector<int>& bestPath
);

#endif // ANTCOLONY_ANTSEARCH_H
