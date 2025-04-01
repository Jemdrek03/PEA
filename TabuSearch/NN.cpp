#include "NN.h"
#include <stack>
#include <limits>

double nearestNeighborTSP(const std::vector<std::vector<int>>& distanceMatrix, int minCost, std::vector<int>& bestPath)
{
    int n = distanceMatrix.size();
    minCost = std::numeric_limits<int>::max();
    bestPath.clear();

    for (int start = 0; start < n; ++start) { // Dla każdego wierzchołka
        std::vector<int> currentPath;
        std::vector<bool> visited(n, false);
        int currentCost = 0;
        int currentNode = start;

        currentPath.push_back(currentNode);
        visited[currentNode] = true;

        for (int i = 1; i < n; ++i) { // Znajdowanie najbliższego sąsiada
            int nearestNeighbor = -1;
            int minDistance = std::numeric_limits<int>::max();

            for (int j = 0; j < n; ++j) {
                if (!visited[j] && distanceMatrix[currentNode][j] < minDistance) {
                    nearestNeighbor = j;
                    minDistance = distanceMatrix[currentNode][j];
                }
            }

            currentCost += minDistance;
            currentNode = nearestNeighbor;
            visited[currentNode] = true;
            currentPath.push_back(currentNode);
        }

        // Dodanie kosztu powrotu do wierzchołka startowego
        currentCost += distanceMatrix[currentNode][start];
        currentPath.push_back(start);

        if (currentCost < minCost) {
            minCost = currentCost;
            bestPath = currentPath;
        }
    }
    double mC = double(minCost);
    return mC;

}
