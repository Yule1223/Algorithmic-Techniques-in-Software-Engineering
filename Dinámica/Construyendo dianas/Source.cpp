
// Yule Zhang

// Comentario general sobre la soluci€n,
// explicando c€mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Matriz.h"
using namespace std;
const int INF = 1000000000;
/*
//coste O(S*V)
bool esPosible(vector<int>const& v, int S, int V) {
    Matriz<bool> m(S + 1, V + 1, false);
    m[0][0] = true;

    for (int i = 1; i <= S; i++) {
        m[i][0] = true;
        for (int j = 1; j <= V; j++) {
            if (v[i - 1] > j) //NO lo queremos
                m[i][j] = m[i - 1][j];
            else //Si lo queremos
                m[i][j] = m[i - 1][j] || m[i - 1][j - v[i - 1]] || j % v[i - 1] == 0;
        }
    }
    //cout << m << '\n';
    return m[S][V];
}
*/
//coste O(S*V + S) = O(S*V)
void calcularMinimo(vector<int>const& v, int S, int V) {
    Matriz<int> m(S + 1, V + 1, INF);

    m[0][0] = 0;
    
    for (int i = 1; i <= S; i++) {
        m[i][0] = 0;
        for (int j = 1; j <= V; j++) {
            if (v[i - 1] > j)//No lo queremos 
                m[i][j] = m[i - 1][j];
            /*
            else { //Si lo queremos
                m[i][j] = min(m[i - 1][j], m[i - 1][j - v[i - 1]] + 1);
                if (j % v[i - 1] == 0) {
                    int num = j / v[i - 1];
                    m[i][j] = min(m[i][j], num);
                }
            }*/
            else
                m[i][j] = min(m[i - 1][j], m[i][j - v[i - 1]] + 1);
        }
    }
    if (m[S][V] == INF)
        cout << "Imposible" << '\n';
    else {
        cout << m[S][V] << ":";

        int valor = V;
        vector<int>sol;

        int z = S;
        while (z > 0 && valor > 0) {
            if (v[z - 1] <= valor && m[z][valor] == m[z][valor - v[z - 1]] + 1) {
                sol.push_back(v[z - 1]);
                valor -= v[z - 1];
            }
            else
                z--;
        }
        for (int i = 0; i < sol.size(); i++) {
            cout << " " << sol[i];
        }
        cout << '\n';
    }
    //cout << m << '\n';
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci€n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int V, S;
    cin >> V >> S;
    if (!cin)  // fin de la entrada
        return false;

    vector<int> v(S);
    for (int i = 0; i < S; i++) {
        cin >> v[i];
    }

    //bool posible = esPosible(v, S, V);
    /*
    if (posible) {
        calcularMinimo(v, S, V);
    }
    else
        cout << "Imposible" << '\n';
    */
    calcularMinimo(v, S, V);
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
