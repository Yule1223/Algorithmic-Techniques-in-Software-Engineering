
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

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciƒn, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int L, N;
    cin >> L >> N;
    if (L == 0 || N == 0)
        return false;
    vector<int>cortes;

    cortes.push_back(0);
    //insertamos el origen
    cortes.push_back(0);
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        cortes.push_back(num);
    }
    //insertamos el destino
    cortes.push_back(L);

    int n = cortes.size() - 1;
    Matriz<int> esfuerzo(n + 1, n + 1, 0);

    for (int d = 1; d <= n - 1; ++d) {//recorre diagonales
        for (int i = 1; i <= n - d; ++i) {//recorre elementos de diagonal
            int j = i + d;
            int esfuerzoActual = INF;
            for (int k = i + 1; k <= j - 1; k++) {
                int temp = esfuerzo[i][k] + esfuerzo[k][j] + 2 * (cortes[j] - cortes[i]);
                if (temp < esfuerzoActual) {
                    esfuerzo[i][j] = temp;
                    esfuerzoActual = temp;
                }
            }
        }
    }
    //cout << esfuerzo;
    cout << esfuerzo[1][n] << "\n";

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
