#include "BFS.h"
#include <queue>
#include <algorithm>
#include <limits>
#include <chrono>
#include "DataSaver.h"

// Funkcja obliczająca dolne ograniczenie kosztu dla danego węzła
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

// Funkcja rozwiązująca problem TSP za pomocą BFS i metody podziału i ograniczeń
void solveTSP_BFS(const Config& config, const std::vector<std::vector<int>>& distanceMatrix, int min) {
    auto start = std::chrono::high_resolution_clock::now();
    int n = distanceMatrix.size();
    int minCost = min;
    std::vector<int> bestPath;

    // Kolejka BFS
    std::queue<Node> q;

    // Tworzymy początkowy węzeł
    Node root;
    root.level = 0;
    root.cost = 0;
    root.vertex = 0;
    root.path.push_back(0); // Startujemy z miasta 0
    q.push(root);

    while (!q.empty()) {
        auto now1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now1 - start;
        if (elapsed.count() > 5 * 60) {
            break; // Przerwanie po 5 minutach
        }

        Node node = q.front();
        q.pop();

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
                    q.push(child);
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    // Zapisujemy najlepszą ścieżkę i koszt
    saveResults("Results_BFS.csv", config, minCost, bestPath, duration.count());
}
