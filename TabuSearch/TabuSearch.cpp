#include <chrono>
#include <unordered_set>
#include <queue>
#include "TabuSearch.h"


float getEnergy(const std::vector<std::vector<int>>& distanceMatrix, std::vector<int> currentPath)
{
    int currentCost = 0;

    for (size_t i = 0; i < currentPath.size() - 1; ++i)
    {
        int from = currentPath[i];
        int to = currentPath[i + 1];
        currentCost += distanceMatrix[from][to];
    }
    currentCost += distanceMatrix[currentPath.back()][currentPath.front()];

    return currentCost;
}


void getNewSolution(std::vector<int>& currentPath, int whichOpt) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, currentPath.size() - 2);

    int size = currentPath.size();
    if (size < 4) return; // 3-opt wymaga co najmniej 4 miast


    switch (whichOpt) {
        case 2: {
            // Implementacja 2-opt
            int i = dist(rng);
            int j = dist(rng);

            // Zapewnij, że i < j i nie są zbyt blisko
            if (i > j) std::swap(i, j);
            if (j - i < 2) return;

            // Odwróć segment między i a j
            std::reverse(currentPath.begin() + i, currentPath.begin() + j + 1);
            return;
        }
        case 3: {
            // Wybierz trzy różne indeksy
            int i = dist(rng);
            int j = dist(rng);
            int k = dist(rng);

            // Zapewnij, że są w kolejności rosnącej
            if (j < i) std::swap(i, j);
            if (k < j) std::swap(j, k);
            if (j < i) std::swap(i, j);

            // Upewnij się, że są różne i wystarczająco odległe
            if (i == j || j == k || i == k || (k - i < 3)) return;

            // Wybierz jedną z ośmiu możliwych permutacji segmentów
            std::uniform_int_distribution<int> choiceDist(0, 7);
            int choice = choiceDist(rng);

            // Podziel ścieżkę na trzy segmenty: A (0..i), B (i+1..j), C (j+1..k), D (k+1..n-1)
            std::vector<int> newPath;
            switch (choice) {
                case 0: // Nic nie zmieniaj
                    break;
                case 1: // Odwróć B
                    std::reverse(currentPath.begin() + i + 1, currentPath.begin() + j + 1);
                    break;
                case 2: // Odwróć C
                    std::reverse(currentPath.begin() + j + 1, currentPath.begin() + k + 1);
                    break;
                case 3: // Odwróć B i C
                    std::reverse(currentPath.begin() + i + 1, currentPath.begin() + j + 1);
                    std::reverse(currentPath.begin() + j + 1, currentPath.begin() + k + 1);
                    break;
                case 4: // Przestaw segmenty w kolejności: A + C + B + D
                    newPath.insert(newPath.end(), currentPath.begin(), currentPath.begin() + i + 1);
                    newPath.insert(newPath.end(), currentPath.begin() + j + 1, currentPath.begin() + k + 1);
                    newPath.insert(newPath.end(), currentPath.begin() + i + 1, currentPath.begin() + j + 1);
                    newPath.insert(newPath.end(), currentPath.begin() + k + 1, currentPath.end());
                    currentPath = newPath;
                    return;
                case 5: // Przestaw segmenty w kolejności: A + C (odwrócone) + B + D
                    newPath.insert(newPath.end(), currentPath.begin(), currentPath.begin() + i + 1);
                    newPath.insert(newPath.end(), currentPath.begin() + j + 1, currentPath.begin() + k + 1);
                    std::reverse(newPath.end() - (k - j), newPath.end());
                    newPath.insert(newPath.end(), currentPath.begin() + i + 1, currentPath.begin() + j + 1);
                    newPath.insert(newPath.end(), currentPath.begin() + k + 1, currentPath.end());
                    currentPath = newPath;
                    return;
                case 6: // Przestaw segmenty w kolejności: A + B + C (odwrócone) + D
                    newPath.insert(newPath.end(), currentPath.begin(), currentPath.begin() + i + 1);
                    newPath.insert(newPath.end(), currentPath.begin() + i + 1, currentPath.begin() + j + 1);
                    newPath.insert(newPath.end(), currentPath.begin() + j + 1, currentPath.begin() + k + 1);
                    std::reverse(newPath.end() - (k - j), newPath.end());
                    newPath.insert(newPath.end(), currentPath.begin() + k + 1, currentPath.end());
                    currentPath = newPath;
                    return;
                case 7: // Przestaw segmenty w kolejności: A + B (odwrócone) + C + D
                    newPath.insert(newPath.end(), currentPath.begin(), currentPath.begin() + i + 1);
                    newPath.insert(newPath.end(), currentPath.begin() + i + 1, currentPath.begin() + j + 1);
                    std::reverse(newPath.end() - (j - i), newPath.end());
                    newPath.insert(newPath.end(), currentPath.begin() + j + 1, currentPath.begin() + k + 1);
                    newPath.insert(newPath.end(), currentPath.begin() + k + 1, currentPath.end());
                    currentPath = newPath;
                    return;
        }
        break;
    }
        default:
            return;
    }
}


void solveTSP_TS(const Config& config, const std::vector<std::vector<int>>& distanceMatrix, int minCost, std::vector<int>& bestPath, int whichOpt) {
    auto startTime = std::chrono::high_resolution_clock::now();
    saveNew("Cost_over_time_AC.csv");

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, bestPath.size() - 1);

    const int maxTabuSize = config.tabuListSize;
    const int maxIterations = config.maxIterations;

    int option = 0;

    // Lista tabu używająca std::vector
    std::vector<std::vector<int>> tabuList;
    std::queue<std::vector<int>> tabuQueue;

    // Inicjalizacja
    std::vector<int> currentPath = bestPath;
    std::vector<int> bestCandidate = bestPath;
    float bestEnergy = getEnergy(distanceMatrix, bestPath);
    float currentEnergy = bestEnergy;

    int iteration = 0;
    int noImprovementCount = 0; // Licznik iteracji bez poprawy

    // Obliczenie granicy akceptowalnego rozwiązania
    float satisfactionThreshold = config.opt * (1.0f + config.satisfaction / 100.0f);

    while (noImprovementCount < maxIterations) {
        std::vector<int> neighborPath = currentPath;

        // Generowanie nowego sąsiada (lokalna zmiana rozwiązania)
        getNewSolution(neighborPath, whichOpt);

        // Obliczenie kosztu nowego sąsiada
        float neighborEnergy = getEnergy(distanceMatrix, neighborPath);

        // Sprawdzenie, czy rozwiązanie nie znajduje się w tablicy tabu
        bool isTabu = false;
        for (const auto& path : tabuList) {
            if (path == neighborPath) {
                isTabu = true;
                break;
            }
        }

        // Jeśli sąsiad nie jest w tablicy tabu lub jest lepszy niż obecne rozwiązanie
        if (!isTabu || neighborEnergy < bestEnergy) {
            currentPath = neighborPath;
            currentEnergy = neighborEnergy;

            // Aktualizacja najlepszego rozwiązania
            if (currentEnergy < bestEnergy) {
                bestEnergy = currentEnergy;
                bestPath = currentPath;
                auto partialTime = std::chrono::high_resolution_clock::now();
                double partialDuration = std::chrono::duration<double>(partialTime - startTime).count();
                saveEarly("Cost_over_time_AC.csv", minCost, partialDuration);
                noImprovementCount = 0; // Resetowanie licznika iteracji bez poprawy
            }
            else
            {
                noImprovementCount++; // Brak poprawy, zwiększamy licznik
            }

            // Dodanie do listy tabu
            tabuList.push_back(currentPath);
            tabuQueue.push(currentPath);

            // Usunięcie nadmiarowych elementów z listy tabu
            if (tabuList.size() > maxTabuSize) {
                tabuList.erase(tabuList.begin());  // Usuwamy najstarszy element
                tabuQueue.pop();  // Usuwamy najstarszy element z kolejki
            }
        }
        else
        {
            noImprovementCount++;
        }

        // Sprawdzenie limitu czasu
        auto possibleEndTime = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double>(possibleEndTime - startTime).count();
        if (duration > 5 * 60) {
            option = 1;
            break;
        }

        iteration++;

        // Sprawdzenie, czy rozwiązanie mieści się w zakresie akceptowalnym
        if (bestEnergy <= satisfactionThreshold) {
            option = 2; // Oznaczenie zakończenia przez osiągnięcie akceptowalnego rozwiązania
            break;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double totalDuration = std::chrono::duration<double>(endTime - startTime).count();

    // Zapis wyników
    saveResults("Results_TS_last.csv", config, bestEnergy, bestPath, totalDuration, option, iteration);
}
