#ifndef DFS_H
#define DFS_H

#include <vector>
#include "ConfigFile.h"

// Struktura reprezentująca węzeł drzewa w algorytmie DFS
struct Node {
    int level; // Poziom w drzewie (liczba odwiedzonych miast)
    int cost; // Bieżący koszt
    int vertex; // Obecny wierzchołek
    std::vector<int> path; // Dotychczasowa ścieżka
};

// Deklaracja funkcji pomocniczej do obliczania dolnego ograniczenia kosztu
int calculateBound(const std::vector<std::vector<int>>& distanceMatrix, const Node& node, int n);


// Deklaracja funkcji głównej do rozwiązywania problemu TSP za pomocą DFS
void solveTSP_DFS(const Config& config, const std::vector<std::vector<int>>& distanceMatrix);

#endif // DFS_H