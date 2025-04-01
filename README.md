# Efektywne Rozwiązywanie Problemu Komiwojażera (TSP)

Projekt zrealizowany w ramach przedmiotu **Projektowanie Efektywnych Algorytmów** na Politechnice Wrocławskiej.

## Autor

- **Jędrzej Radłowski**

---

## 📌 Opis problemu

Problem komiwojażera (TSP – *Travelling Salesman Problem*) polega na znalezieniu najkrótszej możliwej trasy odwiedzającej wszystkie miasta dokładnie jeden raz i powracającej do miasta początkowego. Jest to problem **NP-trudny** z dziedziny optymalizacji na grafach ważonych, a jego złożoność rośnie wykładniczo wraz z liczbą miast.

---

## 🎯 Cel projektu

Analiza i porównanie różnych metod rozwiązywania problemu TSP – zarówno dokładnych, heurystycznych, jak i metaheurystycznych – pod kątem:

- czasu wykonania,
- jakości rozwiązania,
- skalowalności,
- stabilności działania.

---

## 🧠 Zastosowane metody

### 🔹 Etap 1 – Metody klasyczne i heurystyczne

- **Brute-force (przegląd zupełny)**
- **Nearest Neighbour (najbliższy sąsiad)**
- **Random Search (losowa)**
- **Branch and Bound (B&B):**
  - BFS – przeszukiwanie wszerz
  - DFS – przeszukiwanie w głąb
  - LC – wybór węzła o najniższym koszcie

### 🔹 Etap 2 – Metaheurystyki

- **Tabu Search**
- **Simulated Annealing (symulowane wyżarzanie)**
- **Ant Colony Optimization (ACO, algorytm kolonii mrówek)**

---

## 🧪 Zbiór danych

### Etap 1

- Generowane instancje grafów (symetryczne i asymetryczne) o liczbie wierzchołków: `3–25`

### Etap 2

- Instancje z **TSPLIB**:
  - `ftv47.atsp` (48 miast)
  - `ftv170.atsp` (171 miast)
  - `rbg403.atsp` (403 miasta)

---

## ⚙️ Sprzęt i środowisko

- Apple M3 (8 rdzeni, 4×3.2GHz + 4×2.0GHz)
- 16 GB zunifikowanej pamięci RAM
- macOS, kompilator C++

---

## 📊 Wyniki i wnioski

### 🔹 Etap 1

- Brute-force sprawdza się tylko do ~10 miast
- Najbliższy sąsiad działa bardzo szybko, ale generuje suboptymalne rozwiązania
- DFS w metodzie B&B okazał się najefektywniejszy – zarówno pod względem czasu jak i pamięci

### 🔹 Etap 2

- **Tabu Search**: słabe wyniki, często nie poprawiał wyniku startowego
- **Simulated Annealing**: stabilna wydajność, różne wyniki w zależności od strategii chłodzenia
- **ACO**: najlepsze wyniki jakościowe, dobrze się skaluje (szczególnie dla średnich instancji)

---


## 🔬 Hipotezy badawcze

1. Heurystyki mogą działać niestabilnie
2. DFS działa szybciej niż BFS
3. Metaheurystyki są skuteczniejsze dla większych instancji
4. Parametry (np. w ACO) mają istotny wpływ na jakość wyników



