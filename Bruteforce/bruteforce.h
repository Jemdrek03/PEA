

#ifndef PEA_BRUTEFORCE_H
#define PEA_BRUTEFORCE_H

#include <vector>
#include "ConfigFile.h"

void bruteForce(const std::vector<std::vector<int>>& distanceMatrix, int& minCost, std::vector<int>& bestPath, Config& config);

#endif //PEA_BRUTEFORCE_H
