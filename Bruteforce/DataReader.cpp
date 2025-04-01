//
// Created by gagat on 16.10.2024.
//


#include "DataReader.h"

bool DataRead(const std::string& filename, std::vector<std::vector<int>>& distanceMatrix)
{
    std::ifstream file(filename); //Otwieranie pliku z danymi

    if(!file.is_open()) return false;


    int n;
    file >> n; //Wczytanie rozmiaru macierzy
    distanceMatrix.resize(n, std::vector<int>(n)); //Zmiana rozmiaru macierzy

    //Wczutywanie danych do macierzy
    for(int i = 0; i < n; i++)
    {
        for( int j = 0; j < n; j++)
        {
            file >> distanceMatrix[i][j];

        }
    }

    file.close();
    return true;
}