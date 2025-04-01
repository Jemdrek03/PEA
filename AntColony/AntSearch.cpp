#include "AntSearch.h"

static std::mutex mtx;

static float calculatePathCost(const std::vector<std::vector<int>>& distanceMatrix, const std::vector<int>& path) {
    int totalCost = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        totalCost += distanceMatrix[path[i]][path[i + 1]];
    }
    totalCost += distanceMatrix[path.back()][path.front()];
    return totalCost;
}

// Funkcja lokalnej aktualizacji feromonów (DAS)
static void localUpdatePheromones(std::vector<std::vector<double>>& pheromones, int from, int to, const Config& config) {
    static std::mutex localMtx;
    std::lock_guard<std::mutex> lock(localMtx); // Synchronizacja dla wielowątkowości

    pheromones[from][to] = (1.0 - config.evaporationRate) * pheromones[from][to] + config.pheromoneMin;
    pheromones[to][from] = pheromones[from][to]; // Symetryczna aktualizacja
}

static void updatePheromones(std::vector<std::vector<double>>& pheromones, const std::vector<std::vector<int>>& distanceMatrix, const std::vector<Ant>& ants, const Config& config) {
    for (auto& row : pheromones) {
        for (auto& pheromone : row) {
            pheromone *= (1.0 - config.evaporationRate);
            pheromone = std::max(pheromone, static_cast<double>(config.pheromoneMin));
        }
    }

    for (const auto& ant : ants) {
        for (size_t i = 0; i < ant.path.size() - 1; ++i) {
            int from = ant.path[i];
            int to = ant.path[i + 1];
            pheromones[from][to] += 1.0 / ant.cost;
            pheromones[from][to] = std::min(pheromones[from][to], static_cast<double>(config.pheromoneMax));
        }
    }
}

static int selectNextCity(int currentCity, const std::vector<bool>& visited, const std::vector<std::vector<double>>& pheromones, const std::vector<std::vector<double>>& heuristic, const Config& config) {
    std::vector<double> probabilities(visited.size(), 0.0);
    double sum = 0.0;

    for (size_t i = 0; i < visited.size(); ++i) {
        if (!visited[i]) {
            probabilities[i] = std::pow(pheromones[currentCity][i], config.alpha) * std::pow(heuristic[currentCity][i], config.beta);
            sum += probabilities[i];
        }
    }

    std::discrete_distribution<int> dist(probabilities.begin(), probabilities.end());
    static std::mt19937 rng(std::random_device{}());

    return dist(rng);
}

static void constructAntPath(
        Ant& ant,
        const std::vector<std::vector<int>>& distanceMatrix,
        std::vector<std::vector<double>>& pheromones,
        const std::vector<std::vector<double>>& heuristic,
        const Config& config,
        int numCities
) {
    std::vector<bool> visited(numCities, false);
    ant.path.push_back(0); // Start z miasta 0
    visited[0] = true;

    for (int step = 1; step < numCities; ++step) {
        int currentCity = ant.path.back();
        int nextCity = selectNextCity(currentCity, visited, pheromones, heuristic, config);
        ant.path.push_back(nextCity);
        visited[nextCity] = true;

        // DAS - lokalna aktualizacja feromonów
        localUpdatePheromones(pheromones, currentCity, nextCity, config);
    }
    ant.path.push_back(0); // Powrót do miasta startowego
    ant.cost = calculatePathCost(distanceMatrix, ant.path);
}

void solveTSP_ACO(Config& config, const std::vector<std::vector<int>>& distanceMatrix, int& minCost, std::vector<int>& bestPath) {
    int numCities = distanceMatrix.size();
    std::vector<std::vector<double>> pheromones(numCities, std::vector<double>(numCities, config.pheromoneMax));
    std::vector<std::vector<double>> heuristic(numCities, std::vector<double>(numCities, 0.0));

    for (int i = 0; i < numCities; ++i) {
        for (int j = 0; j < numCities; ++j) {
            if (i != j) {
                heuristic[i][j] = 1.0 / distanceMatrix[i][j];
            }
        }
    }

    minCost = std::numeric_limits<int>::max();
    bestPath.clear();

    auto startTime = std::chrono::high_resolution_clock::now();
   // saveNew("Cost_over_time_AC.csv");

    for (int iter = 0; iter < config.numIterations; ++iter) {
        std::vector<Ant> ants(config.numAnts);

        // Wątki dla każdej mrówki
        std::vector<std::thread> threads;

        for (int antIdx = 0; antIdx < config.numAnts; ++antIdx) {
            threads.emplace_back(
                    [&ants, &distanceMatrix, &pheromones, &heuristic, &config, numCities, antIdx]() {
                        constructAntPath(ants[antIdx], distanceMatrix, pheromones, heuristic, config, numCities);
                    }
            );
        }

        // Dołączanie wątków
        for (auto& thread : threads) {
            thread.join();
        }

        // Aktualizacja najlepszego rozwiązania
        for (const auto& ant : ants) {
            std::lock_guard<std::mutex> lock(mtx);
            if (ant.cost < minCost) {
                minCost = ant.cost;
                bestPath = ant.path;
                auto partialTime = std::chrono::high_resolution_clock::now();
                double partialDuration = std::chrono::duration<double>(partialTime - startTime).count();
           //     saveEarly("Cost_over_time_AC.csv", minCost, partialDuration);
            }
        }

        // CAS - globalna aktualizacja feromonów
        updatePheromones(pheromones, distanceMatrix, ants, config);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double duration_ns = std::chrono::duration<double>(endTime - startTime).count();

    saveResults("ACO_ResultsDAS1.csv", config, minCost, bestPath, duration_ns);
}
