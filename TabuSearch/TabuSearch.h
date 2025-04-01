#ifndef TABUSEARCH_TABUSEARCH_H
#define TABUSEARCH_TABUSEARCH_H

#include "ConfigFile.h"
#include <random>
#include <algorithm>
#include "DataSaver.h"
#include <vector>
#include <cmath>

void getNewSolution(int which, std::vector<int>& currentPath);

float getEnergy(const std::vector<std::vector<int>>& distanceMatrix, std::vector<int> currentPath);

void solveTSP_TS(const Config& config, const std::vector<std::vector<int>>& distanceMatrix, int minCost, std::vector<int>& bestPath, int whichOpt);

#endif //TABUSEARCH_TABUSEARCH_H
