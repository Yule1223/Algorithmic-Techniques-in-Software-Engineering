
// Yule Zhang

// Comentario general sobre la soluci€n,
// explicando c€mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include "ConjuntosDisjuntos.h"
using namespace std;
using Mapa = vector<string>;

class Petroleros {
private:
    int F, C;//tamano de mapa
    vector<vector<bool>>visit;
    int maxim;//tamano de la mancha mas grande
    ConjuntosDisjuntos cd;

    bool correcta(int i, int j) const {
        return 0 <= i && i < F && 0 <= j && j < C;
    }

    const vector<pair<int, int>>dirs = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 }, { -1, -1 }, { -1, 1 }, { 1, -1 }, { 1, 1 } };

    //O(N+M*lg*N)
    int dfs(Mapa const& M, int i, int j) {
        visit[i][j] = true;
        int tam = 1;
        for (auto d : dirs) {
            int v = i * C + j;
            int ni = i + d.first, nj = j + d.second;
            if (correcta(ni, nj) && M[ni][nj] == '#' && !visit[ni][nj]) {
                int w = ni * C + nj;
                cd.unir(v, w);//unir los dos vertices
                tam += dfs(M, ni, nj);
            }
        }
        return tam;
    }
public:
    Petroleros(Mapa const& M) : F(M.size()), C(M[0].size()), visit(F, vector<bool>(C, false)), maxim(0), cd(F* C) {
        for (int i = 0; i < F; i++) {
            for (int j = 0; j < C; j++) {
                if (!visit[i][j] && M[i][j] == '#') {
                    int nuevotam = dfs(M, i, j);
                    maxim = max(maxim, nuevotam);
                }
            }
        }
    }

    void actualizar(Mapa const& M, int i, int j) {
        bool vacia = true;
        int v = i * C + j;
        for (auto d : dirs) {
            int ni = i + d.first, nj = j + d.second;
            if (correcta(ni, nj) && M[ni][nj] == '#') {
                int w = ni * C + nj;
                cd.unir(v, w);
                maxim = max(cd.cardinal(v), maxim);
                vacia = false;
            }
        }
        if (vacia) maxim = max(cd.cardinal(v), maxim);
    }

    int maximo() const {
        return maxim;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci€n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int F, C;
    cin >> F >> C;
    if (!cin)  // fin de la entrada
        return false;

    Mapa mapa(F);

    cin.get();
    for (int i = 0; i < F; i++) {
        getline(cin, mapa[i]);
    }
    /*
    for (string& linea : mapa) {
        cin >> linea;
    }
    */
    Petroleros p(mapa);
    cout << p.maximo();

    int N;
    cin >> N;
    
    for (int i = 0; i < N; i++) {
        int fila, col;
        cin >> fila >> col;
        mapa[fila - 1][col - 1] = '#';
        p.actualizar(mapa, fila - 1, col - 1);
        cout << " " << p.maximo();
    }
    // escribir sol
    cout << '\n';

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
