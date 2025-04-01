#ifndef PEA_NN_NN_H
#define PEA_NN_NN_H


#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>


void nearestNeighborTSP(const std::vector<std::vector<int>>& distanceMatrix, int& minCost, std::vector<int>& bestPath, int optimalValue, int maxRunTimeMinutes, int thresholdValue);


void multiplePaths(std::vector<int> path, std::vector<bool> visited, std::chrono::duration<double> elapsed,const std::vector<std::vector<int>>& distanceMatrix, int& minCost, std::vector<int>& bestPath,
                   int currentCost, int currentNode, int minDistance, int nextNode, int startPoint, int endPoint, int startingCity);

#endif //PEA_NN_NN_H
