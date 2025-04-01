#ifndef SIMULATEDANNEALING_SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_SIMULATEDANNEALING_H

#include "ConfigFile.h"
#include <random>
#include <algorithm>
#include "DataSaver.h"
#include <vector>
#include <cmath>

void solveTSP_SA(Config &config, const std::vector<std::vector<int>>& distanceMatrix, int minCost, std::vector<int>& bestPath);

void getNewSolution( std::vector<int>& currentPath, int whichOpt);

float getEnergy(const std::vector<std::vector<int>>& distanceMatrix, std::vector<int> currentPath);

#endif //SIMULATEDANNEALING_SIMULATEDANNEALING_H
