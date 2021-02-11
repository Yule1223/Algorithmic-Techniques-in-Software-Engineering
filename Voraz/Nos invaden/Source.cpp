
// Yule Zhang

// Comentario general sobre la soluci€n,
// explicando c€mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
//coste de la funcion O(NlogN), siendo N el numero de ciudades

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci€n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    priority_queue<int, vector<int>, greater<int>> enemigos;
    priority_queue<int, vector<int>, greater<int>> efectivos;

    int n;
    for (int i = 0; i < N; i++) {
        cin >> n;
        enemigos.push(n);
    }

    for (int j = 0; j < N; j++) {
        cin >> n;
        efectivos.push(n);
    }

    int num = 0;

    while (!enemigos.empty() && !efectivos.empty()) {
        if (efectivos.top() >= enemigos.top()) {//ganamos
            num++;
            enemigos.pop();
        }
        efectivos.pop();
    }

    // escribir sol
    cout << num << '\n';

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
