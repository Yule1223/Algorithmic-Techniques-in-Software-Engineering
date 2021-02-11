
// Yule Zhang

// Comentario general sobre la soluci€n,
// explicando c€mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;
//coste de la funcion O(NlogN), siendo N el numero de ciudades

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci€n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    cin >> N;
    if (N == 0)  // fin de la entrada
        return false;

    priority_queue<int, vector<int>, greater<int>> alturas;
    priority_queue<int, vector<int>, greater<int>> longitudes;

    int n;
    for (int i = 0; i < N; i++) {
        cin >> n;
        alturas.push(n);
    }

    for (int j = 0; j < N; j++) {
        cin >> n;
        longitudes.push(n);
    }

    int suma = 0;

    while (!alturas.empty() && !longitudes.empty()) {
        suma += abs(alturas.top() - longitudes.top());
        alturas.pop(); longitudes.pop();
    }

    // escribir sol
    cout << suma << '\n';

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
