#ifndef SIMULATEDANNEALING_DATAREADER_H
#define SIMULATEDANNEALING_DATAREADER_H

#include <string>
#include <vector>
#include <fstream>

bool DataRead(const std::string& filename, std::vector<std::vector<int>>& distanceMatrix);


#endif //SIMULATEDANNEALING_DATAREADER_H
