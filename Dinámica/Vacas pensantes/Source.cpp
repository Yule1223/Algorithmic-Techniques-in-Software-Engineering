
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

int dinamica(int N, vector<int>const& cubos) {
    Matriz<int> m(N + 1, N + 1, 0);

    //casos base
    for (int i = 1; i < N; i++) {
        m[i][i + 1] = max(cubos[i], cubos[i + 1]);
        m[i][i] = cubos[i];
    }
    m[N][N] = cubos[N];

    //cout << m;
    
    //construir la matriz
    for (int d = 2; d <= N - 1; ++d) // recorre diagonales
        for (int i = 1; i <= N - d; ++i) { // recorre elementos de diagonal 
            int j = i + d;
            int iz, dr;

            if (m[j - 1][j - 1] < m[i][i])
                dr = m[j][j] + m[i + 1][j - 1];
            else
                dr = m[j][j] + m[i][j - 2];

            if (m[j][j] < m[i + 1][i + 1])
                iz = m[i][i] + m[i + 2][j];
            else
                iz = m[i][i] + m[i + 1][j - 1];
         
            int actual = max(iz, dr);
            m[i][j] = actual;
        }

    //cout << m;

    return m[1][N];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciƒn, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    cin >> N;
    if (N == 0)
        return false;
    vector<int> cubos(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> cubos[i];
    }

    auto sol = dinamica(N, cubos);

    // escribir sol
    cout << sol << "\n";

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
