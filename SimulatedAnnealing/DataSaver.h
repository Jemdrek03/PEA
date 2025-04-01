#ifndef SIMULATEDANNEALING_DATASAVER_H
#define SIMULATEDANNEALING_DATASAVER_H

#include <string>
#include <vector>
#include "ConfigFile.h"

void saveResults(const std::string& filename, const Config& config, int minCost, const std::vector<int>& bestPath, double duration_ns, int option, int temp, int iter, float endTemp);

void saveEarly(const std::string& filename, int minCost, double duration_ns);

void saveNew(const std::string& filename);

#endif //SIMULATEDANNEALING_DATASAVER_H
