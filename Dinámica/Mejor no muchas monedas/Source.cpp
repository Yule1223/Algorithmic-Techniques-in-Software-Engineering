
// Yule Zhang

// Comentario general sobre la soluciƒn,
// explicando cƒmo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include "Matriz.h"
using namespace std;
const int INF = 1000000000;

struct tMoneda {
    int valor;
    int cantidad;
};

int dinamica(int N, int precio, vector<tMoneda>const& monedas) {
    Matriz<int> m(N + 1, precio + 1, INF);

    //casos base
    for (int i = 0; i <= N; i++)
        m[i][0] = 0;

    //construir la matriz
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= precio; j++) {
            int actual = INF;
            //calculamos el número de monedas que necesitamos, será el mínimo entre las que tenemos disponibles y las del precio que nos hace falta/valor de la moneda
            int cantidad = min(monedas[i].cantidad, j / monedas[i].valor);

            //recorremos hasta la cantidad de monedas para quedarnos con el mínimo de monedas
            for (int t = 0; t <= cantidad; t++) {
                actual = min(actual, m[i - 1][j - (t * monedas[i].valor)] + t);
            }

            m[i][j] = actual;
        }
    }
    return m[N][precio];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciƒn, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, precio;
    cin >> N;
    if (!cin)
        return false;
    vector<tMoneda> monedas(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> monedas[i].valor;
    }

    for (int i = 1; i <= N; i++) {
        cin >> monedas[i].cantidad;
    }

    cin >> precio;

    auto sol = dinamica(N, precio, monedas);
    
    // escribir sol
    if (sol == INF)
        cout << "NO" << '\n';
    else
        cout << "SI " << sol << "\n";

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
