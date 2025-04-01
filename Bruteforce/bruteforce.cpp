#include "bruteforce.h"
#include <algorithm>
#include <limits>
#include <vector>
#include <iomanip>

void bruteForce(const std::vector<std::vector<int>>& distanceMatrix, int& minCost, std::vector<int>&bestPath, Config& config) {

    int n = distanceMatrix.size();
    minCost = std::numeric_limits<int>::max();
    bestPath.clear();

    std::vector<int> path;

    if (config.showProgress) {
        unsigned long long result = 1;
        unsigned long long count = 0;
        for (int i = 0; i < n; i++) {
            path.push_back(i); //Inicjalizacja ścieżki jako {0, 1, 2, ..., n-1}
            if (i == 0) {
                continue; //Ignorowanie pierwszej iteracji przy obliczaniu `result`
            }
            result *= i; //Obliczanie liczby permutacji dla ścieżki
        }

        do {
            int currentCost = 0;
            for (int i = 0; i < n - 1; i++) {
                currentCost += distanceMatrix[path[i]][path[i + 1]]; //Dodawanie kosztu kolejnych przejść

            }
            currentCost += distanceMatrix[path[n - 1]][path[0]]; //Dodanie kosztu powrotu do punktu startowego

            if (currentCost < minCost) {  //Sprawdzanie, czy nowy koszt jest lepszy
                minCost = currentCost;
                bestPath = path;
            }

            count++;
            double progress = (double) count / result * 100.0; //Obliczanie procentu ukończenia

            std::cout << "\rPostep: " << std::fixed << std::setprecision(2) << progress << "%";
            std::cout.flush();

        } while (std::next_permutation(path.begin(), path.end())); //Generowanie kolejnych permutacji
    } else {
        for (int i = 0; i < n; i++) { //Inicjalizacja ścieżki jako {0, 1, 2, ..., n-1}
            path.push_back(i);
        }

        do {
            int currentCost = 0;
            for (int i = 0; i < n - 1; i++) {
                currentCost += distanceMatrix[path[i]][path[i + 1]]; //Dodawanie kosztu kolejnych przejść

            }
            currentCost += distanceMatrix[path[n - 1]][path[0]]; //Dodanie kosztu powrotu do punktu startowego

            if (currentCost < minCost) { //Sprawdzanie, czy nowy koszt jest lepszy
                minCost = currentCost;
                bestPath = path;
            }

        } while (std::next_permutation(path.begin() + 1, path.end())); //Generowanie kolejnych permutacji

    }
}