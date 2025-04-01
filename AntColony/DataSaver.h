#ifndef ANTCOLONY_DATASAVER_H
#define ANTCOLONY_DATASAVER_H

#include <string>
#include <vector>
#include "ConfigFile.h"

void saveResults(const std::string& filename, const Config& config, int minCost, const std::vector<int>& bestPath, double duration_ns);

void saveEarly(const std::string& filename, int minCost, double duration_ns);

void saveNew(const std::string& filename);
#endif //ANTCOLONY_DATASAVER_H
