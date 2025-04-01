#include "DataSaver.h"

void saveResults(const std::string& filename, const Config& config, int minCost, const std::vector<int>& bestPath, double duration_ns, int option, int temp, int iter, float endTemp)
{
    std::ofstream file(filename, std::ios::app); //Otwarcie pliku z opcja dodawania danych
    file << "Plik: " << config.File<< " ";
    file << "Liczba wierzcholkow: " << bestPath.size() - 1  <<" ";
    file << "Optymalna sciezka: " << config.opt<<" ";
    file << "Minimalny koszt: " << minCost << " ";
    file << "Blad w %: "<<(100.0*(float(minCost) - float(config.opt))) / float(config.opt)<<" ";
    file << "Roznica bledu: "<<minCost - config.opt<<" ";
    file << "Czas: " << duration_ns << " ";
    file << "Czemu zatrzymano: "<<option<<" ";
    file << "Temperatura: "<<temp<<" ";
    file << "Temperatura końcowa: " <<endTemp <<" ";
    file << "Ilosc iteracji na temperature: "<<iter<<" ";
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