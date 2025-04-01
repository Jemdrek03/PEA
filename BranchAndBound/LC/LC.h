#ifndef LC_H
#define LC_H

#include <vector>
#include <limits>
#include <queue>
#include <algorithm>
#include "ConfigFile.h"

// Struktura reprezentująca węzeł drzewa przeszukiwań
struct Node {
    int level; // Poziom w drzewie (liczba odwiedzonych miast)
    int cost; // Bieżący koszt
    int vertex; // Obecny wierzchołek
    std::vector<int> path; // Dotychczasowa ścieżka

    // Operator porównania dla priorytetowej kolejki, aby wybrać węzeł o najniższym koszcie
    bool operator<(const Node& other) const {
        return cost > other.cost; // Najpierw węzły o najniższym koszcie
    }

};



// Funkcja rozwiązująca problem TSP za pomocą metody Branch and Bound
void solveTSP_LowestCost(const Config& config, const std::vector<std::vector<int>>& distanceMatrix);

#endif // LC_H
