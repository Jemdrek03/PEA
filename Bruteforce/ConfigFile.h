
#ifndef PEA_CONFIGFILE_H
#define PEA_CONFIGFILE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


struct Config {
    std::string File; //plik z danymi
    bool showProgress;
    int numTries;
    int howBig;


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
        }
        file.close();
        return true;
    }


};


#endif //PEA_CONFIGFILE_H
