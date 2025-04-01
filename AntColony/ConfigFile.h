#ifndef ANTCOLONY_CONFIGFILE_H
#define ANTCOLONY_CONFIGFILE_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct Config {
    std::string File; //plik z danymi
    int numTries;
    int howBig;
    int noImproveLimit;
    int readyResult;
    int opt;
    float satisfaction;
    int numAnts;
    float evaporationRate;
    float alpha;
    float beta;
    float pheromoneMin;
    float pheromoneMax;
    int numIterations;



    bool loadConfig( const std::string& fileName)
    {
        std::ifstream file(fileName); //Otwieranie pliku konfiguracyjnego
        if(!file.is_open())
            return false;

        std::string line;
        while(std::getline(file,line))
        {
            std::istringstream iss(line); //przeksztalcenie linii na strumien
            std::string key;
            if(!(iss >> key)) continue; //Pobieranie "key" i pomijanie pustych linii

            //Przypisywanie odpowiednich wartosci do zmiennej
            if (key == "inputFile") iss >> File;
            else if(key == "numTries") iss >> numTries;
            else if (key == "howBig") iss >> howBig;
            else if (key == "noImproveLimit") iss >> noImproveLimit;
            else if (key == "readyResult") iss >> readyResult;
            else if (key == "opt") iss >> opt;
            else if (key == "satisfaction") iss >> satisfaction;
            else if (key == "numAnts") iss >> numAnts;
            else if (key == "evaporationRate") iss >> evaporationRate;
            else if (key == "alpha") iss >> alpha;
            else if (key == "beta") iss >> beta;
            else if (key == "pheromoneMin") iss >> pheromoneMin;
            else if (key == "pheromoneMax") iss >> pheromoneMax;
            else if (key == "numIterations") iss >> numIterations;


        }
        file.close();
        return true;
    }


};



#endif //ANTCOLONY_CONFIGFILE_H
