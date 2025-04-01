#include "DataSaver.h"

void saveResults(const std::string& filename, const Config& config, int minCost, const std::vector<int>& bestPath, double duration_ns)
{
    std::ofstream file(filename, std::ios::app); //Otwarcie pliku z opcja dodawania danych
    file << "Plik: " << config.File<< " ";
    file << "Liczba wierzcholkow: " << bestPath.size() -1 <<"";
    file << "Minimalny koszt: " << minCost << "";
    file << "Czas: " << duration_ns << " ";
    file << "Najlepsza sciezka: ";
    for( int o : bestPath) file << o << " ";
    file << "\n";
    file.close();
}
