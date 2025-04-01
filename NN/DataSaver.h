#ifndef PEA_DATASAVER_H
#define PEA_DATASAVER_H

#include <string>
#include <vector>
#include "ConfigFile.h"

void saveResults(const std::string& filename, const Config& config, int minCost, const std::vector<int>& bestPath, double duration_ns);

#endif //PEA_DATASAVER_H
