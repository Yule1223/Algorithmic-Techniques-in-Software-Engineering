
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

struct bombilla {
    int potencia;
    int coste;
};

bool operator< (bombilla const& a, bombilla const& b) {
    return a.potencia < b.potencia || (a.potencia == b.potencia && a.coste < b.coste);
}

void calcularMinimo(vector<bombilla>const& v, int N, int PMax, int PMin) {
    Matriz<bombilla> m(N + 1, PMax + 1, { INF, INF });

    m[0][0] = { 0, 0 };

    for (int i = 1; i <= N; i++) {
        m[i][0] = { 0,0 };
        for (int j = 1; j <= PMax; j++) {
            if (v[i - 1].potencia > j)
                m[i][j] = m[i - 1][j];
            else {
                m[i][j].potencia = min(m[i - 1][j].potencia, m[i][j - v[i - 1].potencia].potencia + v[i - 1].potencia);
                m[i][j].coste = min(m[i - 1][j].coste, m[i][j - v[i - 1].potencia].coste + v[i - 1].coste);
            }
        }
    }
    int miniP = INF;
    int miniC = INF;
    for (int i = PMin; i <= PMax; i++) {
        if (m[N][i].coste < miniC) {
            miniC = m[N][i].coste;
            miniP = m[N][i].potencia;
        }
        else if (m[N][i].coste == miniC) {
            miniP = min(miniP, m[N][i].potencia);
        }
    }
    if (miniP == INF && miniC == INF)
        cout << "IMPOSIBLE" << '\n';
    else
        cout << miniC << " " << miniP << '\n';
    
    /*
    for (int i = 0; i < m.numfils(); i++) {
        for (int j = 0; j < m.numcols(); j++) {
            cout << m[i][j].coste << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < m.numfils(); i++) {
        for (int j = 0; j < m.numcols(); j++) {
            cout << m[i][j].potencia << " ";
        }
        cout << endl;
    }
    */
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci€n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, PMax, PMin;
    cin >> N >> PMax >> PMin;
    if (!cin)  // fin de la entrada
        return false;

    vector<bombilla> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i].potencia;
    }

    for (int i = 0; i < N; i++) {
        cin >> v[i].coste;
    }

    sort(v.begin(), v.end(), less<bombilla>());
    
    calcularMinimo(v, N, PMax, PMin);
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
