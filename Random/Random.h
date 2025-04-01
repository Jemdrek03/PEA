#ifndef PEA__RANDOM_RANDOM_H
#define PEA__RANDOM_RANDOM_H

#include <vector>
#include <random>
#include <algorithm>

void randomTSP(const std::vector<std::vector<int>>& distanceMatrix, int numTrials, int& minCost, std::vector<int>& bestPath, bool showProgress, int optimalValue, int maxRunTimeMinutes, double thresholdValue);

#endif //PEA__RANDOM_RANDOM_H
