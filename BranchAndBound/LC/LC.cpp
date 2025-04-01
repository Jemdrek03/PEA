
#include <limits>
#include <algorithm>
#include <stack>
#include <chrono>
#include "DataSaver.h"
#include "LC.h"

// Obliczanie dolnego ograniczenia
int calculateBound(const std::vector<std::vector<int>>& distanceMatrix, const Node& node, int n) {
    int bound = node.cost;
    bool visited[n];
    std::fill(visited, visited + n, false);

    // Oznaczamy miasta z dotychczasowej ścieżki jako odwiedzone
    for (int city : node.path) {
        visited[city] = true;
    }

    // Obliczamy dolne ograniczenie na podstawie najniższych kosztów krawędzi
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int minEdge = std::numeric_limits<int>::max();
            for (int j = 0; j < n; j++) {
                if (i != j && !visited[j]) {
                    minEdge = std::min(minEdge, distanceMatrix[i][j]);
                }
            }
            bound += minEdge;
        }
    }

    return bound;
}

// Funkcja rozwiązująca problem TSP za pomocą Branch and Bound
void solveTSP_LowestCost(const Config& config, const std::vector<std::vector<int>>& distanceMatrix) {
    auto start = std::chrono::high_resolution_clock::now();
    int n = distanceMatrix.size();
    int minCost = std::numeric_limits<int>::max();
    std::vector<int> bestPath;
    // Priorytetowa kolejka do przechowywania węzłów według najniższego kosztu
    std::priority_queue<Node> pq;
    // Tworzymy początkowy węzeł
    Node root;
    root.level = 0;
    root.cost = 0;
    root.vertex = 0;
    root.path.push_back(0); // Startujemy z miasta 0

    pq.push(root);
    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();
        // Jeśli dotarliśmy do ostatniego poziomu i możemy wrócić do miasta startowego
        if (node.level == n - 1) {
            int finalCost = node.cost + distanceMatrix[node.vertex][0];
            if (finalCost < minCost) {
                minCost = finalCost;
                bestPath = node.path;
                bestPath.push_back(0); // Zamykamy cykl, wracając do początkowego miasta
            }
            continue;
        }
        // Rozwijamy węzeł o wszystkie możliwe kolejne miasta
        for (int i = 0; i < n; i++) {
            // Sprawdzamy, czy miasto i nie jest jeszcze odwiedzone
            if (std::find(node.path.begin(), node.path.end(), i) == node.path.end()) {
                Node child;
                child.level = node.level + 1;
                child.cost = node.cost + distanceMatrix[node.vertex][i];
                child.vertex = i;
                child.path = node.path;
                child.path.push_back(i);
                // Obliczamy dolne ograniczenie i dodajemy węzeł do kolejki, jeśli jest obiecujący
                int bound = calculateBound(distanceMatrix, child, n);
                if (bound < minCost) {
                    pq.push(child);
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli >(end - start);
    // Zapisujemy najlepszą ścieżkę i koszt
    saveResults("Results_LC1.csv", config, minCost, bestPath, duration.count());
}
