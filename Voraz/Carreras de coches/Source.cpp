
// Yule Zhang

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    int N, V;
    // leer los datos de la entrada
    cin >> N >> V;
    int n;
    vector<int> pilas;//vector para guardar las pilas
    for (int i = 0; i < N; i++) {
        cin >> n;
        pilas.push_back(n);
    }
    sort(pilas.begin(), pilas.end());//ordenamos el vector de menor a mayor

    int j = pilas.size() - 1;
    int numCoches = 0;//variable de salida

    for (int i = 0; i < j; i++) {
        if (pilas[i] + pilas[j] >= V) {//comparamos si la suma del menor y el mayor mayor igual que V
            numCoches++;
            j--;
        }
    }

    // escribir solución
    cout << numCoches << '\n';
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
