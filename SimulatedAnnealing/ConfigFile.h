#ifndef SIMULATEDANNEALING_CONFIGFILE_H
#define SIMULATEDANNEALING_CONFIGFILE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


struct Config {
    std::string File; //plik z danymi
    bool showProgress;
    int numTries;
    int howBig;
    int Which;
    float Temperature;
    float endTemperature;
    float Decrease;
    int noImproveLimit;
    int readyResult;
    int decreaseType;
    int opt;
    float satisfaction;
    int maxNoImprove;
    int whichOpt;


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
            else if(key == "showProgress") iss >> showProgress;
            else if(key == "numTries") iss >> numTries;
            else if (key == "howBig") iss >> howBig;
            else if (key == "Which") iss >> Which;
            else if (key == "Temperature") iss >> Temperature;
            else if (key == "Decrease") iss >> Decrease;
            else if (key == "noImproveLimit") iss >> noImproveLimit;
            else if (key == "readyResult") iss >> readyResult;
            else if (key == "decreaseType") iss >> decreaseType;
            else if (key == "opt") iss >> opt;
            else if (key == "satisfaction") iss >> satisfaction;
            else if (key == "endTemperature") iss >> endTemperature;
            else if (key == "maxNoImprove") iss >> maxNoImprove;
            else if (key == "whichOpt") iss >> whichOpt;
        }
        file.close();
        return true;
    }


};


#endif //SIMULATEDANNEALING_CONFIGFILE_H
