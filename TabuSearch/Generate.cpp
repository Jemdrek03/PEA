#include "Generate.h"

void generateM(int liczbaWierzcholkow) {
    // Inicjalizacja generatora liczb losowych
    srand(time(0));

    // Tworzenie pliku do zapisu (nadpisanie pliku, jeśli istnieje)
    std::ofstream plik("data.txt", std::ios::trunc); // Otwieramy plik w trybie nadpisania

    // Sprawdzenie, czy plik otworzył się poprawnie
    if (!plik) {
        std::cerr << "Nie udało się otworzyć pliku!" << std::endl;
        return;
    }

    // Zapisanie liczby wierzchołków do pliku
    plik << liczbaWierzcholkow << std::endl;

    // Tworzenie macierzy odległości
    std::vector<std::vector<int>> macierz(liczbaWierzcholkow, std::vector<int>(liczbaWierzcholkow));

    // Wypełnianie macierzy losowymi wartościami z przedziału <1, 100>
    for (int i = 0; i < liczbaWierzcholkow; i++) {
        for (int j = 0; j < liczbaWierzcholkow; j++) {
            if (i == j) {
                macierz[i][j] = 0;  // Odległość od wierzchołka do samego siebie to 0
            } else {
                macierz[i][j] = rand() % 100 + 1;  // Losowa wartość z przedziału <1, 100>
            }
        }
    }

    // Zapisanie macierzy do pliku
    for (int i = 0; i < liczbaWierzcholkow; i++) {
        for (int j = 0; j < liczbaWierzcholkow; j++) {
            plik << macierz[i][j] << " ";
        }
        plik << std::endl;
    }

    // Zamknięcie pliku
    plik.close();
}




void generateS(int liczbaWierzcholkow){
    // Inicjalizacja generatora liczb losowych
    srand(time(0));

    // Tworzenie pliku do zapisu (nadpisanie pliku, jeśli istnieje)
    std::ofstream plik("data.txt", std::ios::trunc); // Otwieramy plik w trybie nadpisania

    // Sprawdzenie, czy plik otworzył się poprawnie
    if (!plik) {
        std::cerr << "Nie udało się otworzyć pliku!" << std::endl;
        return;
    }

    // Zapisanie liczby wierzchołków do pliku
    plik << liczbaWierzcholkow << std::endl;

    // Tworzenie macierzy odległości
    std::vector<std::vector<int>> macierz(liczbaWierzcholkow, std::vector<int>(liczbaWierzcholkow));

    // Wypełnianie macierzy losowymi wartościami z przedziału <1, 100>
    for (int i = 0; i < liczbaWierzcholkow; i++) {
        for (int j = i + 1; j < liczbaWierzcholkow; j++) {  // Generujemy tylko dla górnej połowy macierzy
            // Generujemy losową odległość w przedziale <1, 100>
            int odleglosc = rand() % 100 + 1;

            // Przypisujemy odległość symetrycznie
            macierz[i][j] = odleglosc;
            macierz[j][i] = odleglosc;
        }
    }

    // Ustalamy odległość wierzchołka od samego siebie na 0
    for (int i = 0; i < liczbaWierzcholkow; i++) {
        macierz[i][i] = 0;
    }

    // Zapisanie macierzy do pliku
    for (int i = 0; i < liczbaWierzcholkow; i++) {
        for (int j = 0; j < liczbaWierzcholkow; j++) {
            plik << macierz[i][j] << " ";
        }
        plik << std::endl;
    }

    // Zamknięcie pliku
    plik.close();
}
