#include "NN.h"
#include <stack>

int nearestNeighborTSP(const std::vector<std::vector<int>>& distanceMatrix, int& minCost, std::vector<int>& bestPath)
{
    int n = distanceMatrix.size();
    minCost = std::numeric_limits<int>::max();
    bestPath.clear();
    int start = 0;

    // Stos do przechowywania stanu w przeszukiwaniu
    struct State {
        int currentNode;
        int currentCost;
        std::vector<int> path;
        std::vector<bool> visited;
    };

    std::stack<State> stack;
    stack.push({start, 0, {start}, std::vector<bool>(n, false)});
    stack.top().visited[start] = true;

    while (!stack.empty()) {
        State state = stack.top();
        stack.pop();

        if (state.path.size() == n) { // Jeśli odwiedzono wszystkie wierzchołki
            int totalCost = state.currentCost + distanceMatrix[state.currentNode][start];
            if (totalCost < minCost) {
                minCost = totalCost;
                bestPath = state.path;
                bestPath.push_back(start); // Zamknięcie cyklu
            }
            continue;
        }

        // Szukanie kandydatów na kolejny wierzchołek
        std::vector<int> candidates;
        int minDistance = std::numeric_limits<int>::max();
        for (int j = 0; j < n; ++j) {
            if (!state.visited[j] && distanceMatrix[state.currentNode][j] <= minDistance) {
                if (distanceMatrix[state.currentNode][j] < minDistance) {
                    candidates.clear();
                    minDistance = distanceMatrix[state.currentNode][j];
                }
                candidates.push_back(j);
            }
        }
        // Dodawanie wszystkich kandydatów do stosu
        for (int candidate : candidates) {
            State newState = state;
            newState.currentNode = candidate;
            newState.currentCost += distanceMatrix[state.currentNode][candidate];
            newState.path.push_back(candidate);
            newState.visited[candidate] = true;
            stack.push(newState);


        }
    }
    return minCost;

}
