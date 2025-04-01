#include "DataSaver.h"

void saveResults(const std::string& filename, const Config& config, int minCost, const std::vector<int>& bestPath, double duration_ns)
{
    std::ofstream file(filename, std::ios::app); //Otwarcie pliku z opcja dodawania danych
    file << "Plik: " << config.File<< " ";
    file << "Liczba_wierzcholkow: " << bestPath.size() - 1  <<" ";
    file << "Optymalna_sciezka: " << config.opt<<" ";
    file << "Minimalny_koszt: " << minCost << " ";
    file << "Blad_w_%: "<<(100.0*(float(minCost) - float(config.opt))) / float(config.opt)<<" ";
    file << "Roznica_bledu: "<<minCost - config.opt<<" ";
    file << "Czas: " << duration_ns << " ";
    file << "Parametry:Ants,EvapRate,apha,beta,min,max,Ite: "<<config.numAnts<<" "<<config.evaporationRate<<" "<<config.alpha<<" "<<config.beta<<" "<<config.pheromoneMin<<" "<<config.pheromoneMax<<" "<<config.numIterations<<" ";
    file << "Najlepsza sciezka: ";
    for( int o : bestPath) file << o << " ";
    file << "\n";
    file.close();
}


void saveEarly(const std::string& filename, int minCost, double duration_ns)
{
    std::ofstream file(filename, std::ios::app);
    file << "Czas: " <<duration_ns;
    file << " Minimalny koszt: " << minCost << " ";
    file << "\n";
    file.close();
}

void saveNew(const std::string& filename)
{
    std::ofstream file(filename, std::ios::app);
    file <<"Nowe rozwiazanie: ";
    file << "\n";
    file.close();
}