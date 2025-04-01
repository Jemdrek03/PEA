#ifndef PEA_BFS_NN_H
#define PEA_BFS_NN_H

#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>


int nearestNeighborTSP(const std::vector<std::vector<int>>& distanceMatrix, int& minCost, std::vector<int>& bestPath);



#endif //PEA_BFS_NN_H
