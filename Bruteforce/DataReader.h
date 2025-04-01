//
// Created by gagat on 16.10.2024.
//

#ifndef PEA_DATAREADER_H
#define PEA_DATAREADER_H

#include <string>
#include <vector>
#include <fstream>

bool DataRead(const std::string& filename, std::vector<std::vector<int>>& distanceMatrix);

#endif //PEA_DATAREADER_H
