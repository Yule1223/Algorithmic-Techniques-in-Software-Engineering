
// Yule Zhang

// Comentario general sobre la soluciƒn,
// explicando cƒmo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
#include "Matriz.h"
using namespace std;
const int INF = 1000000000;

void Floyd(Matriz<int> const& G, Matriz<int>& C, Matriz<int>& A) {
    int V = G.numfils(); // número de vértices de G
    // inicialización
    C = G;
    A = Matriz<int>(V, V, -1);
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j && G[i][j] != INF)
                A[i][j] = i;
        }
    }

    // actualizaciones de la matriz
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                auto temp = C[i][k] + C[k][j];
                if (temp < C[i][j]) { // es mejor pasar por k
                    C[i][j] = temp;
                    //A[i][j] = k;
                    A[i][j] = A[k][j];
                }
            }
        }
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciƒn, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int P, R;
    cin >> P >> R;
    if (!cin)
        return false;

    Matriz<int> relaciones(P + 1, P + 1, INF);
    //una persona no puede tener relaciones con si mismo
    for (int i = 0; i <= P; i++)
        relaciones[i][i] = 0;

    unordered_map<string, int> mapaP;
    string a, b;
    int cont = 1;

    for (int i = 0; i < R; i++) {
        cin >> a >> b;
        //comprobamos si la persona ya existia
        if (mapaP[a] == 0) {
            mapaP[a] = cont;
            cont++;
        }
        if (mapaP[b] == 0) {
            mapaP[b] = cont;
            cont++;
        }

        //guardamos la relacion para las dos personas en la matriz
        relaciones[mapaP[a]][mapaP[b]] = 1;
        relaciones[mapaP[b]][mapaP[a]] = 1;
    }
    Matriz<int> C(0, 0); Matriz<int> A(0, 0);
    Floyd(relaciones, C, A);

    // escribir sol
    int maxi = 0;

    for (int i = 1; i <= P; i++) {
        for (int j = 1; j <= P; j++) {
            maxi = max(maxi, C[i][j]);
        }
    }

    if (maxi == INF) 
        cout << "DESCONECTADA" << '\n';
    else 
        cout << maxi << '\n';

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
