#include <chrono>
#include "SimulatedAnnealing.h"

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






// Algorytm symulowanego wyżarzania dla TSP
void solveTSP_SA(Config &config, const std::vector<std::vector<int>>& distanceMatrix, int minCost, std::vector<int>& bestPath) {
    auto startTime = std::chrono::high_resolution_clock::now();

    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    int option = 0;

    // Inicjalizacja
    std::vector<int> currentPath = bestPath;
    std::vector<int> nextPath = currentPath;
    float bestEnergy = getEnergy(distanceMatrix, bestPath);
    float currentEnergy = bestEnergy;
    float decreaseRate = config.Decrease;

    int iterations = config.noImproveLimit;
    int epoch = 0; // Licznik epok
    const int maxNoImprove = 2000;          // Limit iteracji bez poprawy
    int noImproveCount = 0;                // Licznik iteracji bez poprawy

    // Obliczenie granicy akceptowalnego rozwiązania
    float satisfactionThreshold = config.opt * (1.0f + config.satisfaction / 100.0f);


    // Wyznaczenie temperatury początkowej metodą Hao Chena
    float deltaE = 0.0f; // Średnia różnica energii między losowymi rozwiązaniami
    int sampleSize = 10000; // Liczba próbek do estymacji
    for (int i = 0; i < sampleSize; ++i) {
        std::vector<int> samplePath = currentPath;
        getNewSolution(samplePath, config.whichOpt);
        float sampleEnergy = getEnergy(distanceMatrix, samplePath);
        deltaE += std::abs(sampleEnergy - currentEnergy);
    }
    deltaE /= sampleSize; // Średnia różnica energii

    float temperature = deltaE / std::log(1.0 / 0.99); // T0 obliczone na podstawie wzoru Thompson i Bilbro
    config.Temperature = temperature;

    saveNew("Cost_over_time.csv");


    while (temperature > config.endTemperature) {
        for(int iteration = 0; iteration < iterations; iteration++ ) {

            // Generowanie nowego rozwiązania
            nextPath = currentPath;
            getNewSolution( nextPath, config.whichOpt);

            // Obliczenie kosztu dla nowego rozwiązania
            float nextEnergy = getEnergy(distanceMatrix, nextPath);
            float deltaEnergy = nextEnergy - currentEnergy;

            // Warunek akceptacji nowego rozwiązania
            if (deltaEnergy < 0 || std::exp(-deltaEnergy / temperature) > probDist(rng)) {
                currentPath = nextPath;
                currentEnergy = nextEnergy;

                // Aktualizacja najlepszego rozwiązania
                if (currentEnergy < bestEnergy) {
                    bestEnergy = currentEnergy;
                    bestPath = currentPath;
                    noImproveCount = 0; // Zresetowanie licznika iteracji bez poprawy
                    auto partialTime = std::chrono::high_resolution_clock::now();
                    double partialDuration = std::chrono::duration<double>(partialTime - startTime).count();
                    saveEarly("Cost_over_time.csv", bestEnergy, partialDuration);
                }
                else
                {
                    noImproveCount++;
                }
            }
            else
            {
                noImproveCount++;
            }
            if (noImproveCount > config.maxNoImprove) {
                option = 3;
                break;
            }

            // Sprawdzenie, czy rozwiązanie mieści się w zakresie akceptowalnym
            if (bestEnergy <= satisfactionThreshold) {
                option = 2; // Oznaczenie zakończenia przez osiągnięcie akceptowalnego rozwiązania
                break;
            }

        }

        if(option != 0)
        {
            break;
        }


        if (bestEnergy <= satisfactionThreshold) {
            break; // Wyjście z pętli głównej
        }
        auto possibleEndTime = std::chrono::high_resolution_clock::now();
        double durationEnd = std::chrono::duration<double>(possibleEndTime - startTime).count();
        if( durationEnd > 150)
        {
            option = 1;
            break;
        }
        // Schładzanie temperatury
        if(config.decreaseType == 0)
        {
            temperature *= decreaseRate;
        }
        else
        {
            // Logarytmiczny schemat chłodzenia
            temperature = config.Temperature / (std::log(1 + epoch));
        }

        epoch++; // Zwiększenie licznika epok
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double>(endTime - startTime).count();

    // Zapis wyników
    saveResults("Results_SA.csv", config, bestEnergy, bestPath, duration, option, config.Temperature, iterations, temperature);
}


