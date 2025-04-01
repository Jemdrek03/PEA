#include "DFS.h"
#include <limits>
#include <algorithm>
#include <stack>
#include <chrono>
#include "DataSaver.h"


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




// Funkcja rozwiązująca problem TSP za pomocą iteracyjnego DFS i metody podziału i ograniczeń
void solveTSP_DFS(const Config& config, const std::vector<std::vector<int>>& distanceMatrix) {
    auto start = std::chrono::high_resolution_clock::now();
    int n = distanceMatrix.size();
    int minCost = std::numeric_limits<int>::max();
    std::vector<int> bestPath;

    // Tworzymy początkowy węzeł
    Node root;
    root.level = 0;
    root.cost = 0;
    root.vertex = 0;
    root.path.push_back(0); // Startujemy z miasta 0

    // Stos do przechowywania węzłów do przetworzenia
    std::stack<Node> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Node node = nodeStack.top();
        nodeStack.pop();

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

                // Obliczamy dolne ograniczenie i przechodzimy do następnego miasta, jeśli jest obiecujące
                int bound = calculateBound(distanceMatrix, child, n);
                if (bound < minCost) {
                    nodeStack.push(child);
                }
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ns = std::chrono::duration_cast<std::chrono::milliseconds >(end - start).count();

    // Zapisujemy najlepszą ścieżkę i koszt
    saveResults("Results_DFS.csv", config, minCost, bestPath, duration_ns);
}