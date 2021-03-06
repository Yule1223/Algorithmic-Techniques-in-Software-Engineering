
// Yule Zhang

// Comentario general sobre la soluci�n,
// explicando c�mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Grafo.h"  // propios o los de las estructuras de datos de clase
using namespace std;
using Mapa = vector<string>;

class Manchas {
private:
    int F, C;//tamano de mapa
    vector<vector<bool>>visit;
    int num;//numero de manchas
    int maxim;//tamano de la mancha mas grande

    bool correcta(int i, int j) const{
        return 0 <= i && i < F && 0 <= j && j < C;
    }

    const vector<pair<int, int>>dirs = { { 1, 0 }, { 0,1 }, { -1,0 }, { 0,-1 } };

    //O(F*C)
    int dfs(Mapa const& M, int i, int j) {
        visit[i][j] = true;
        int tam = 1;
        for (auto d : dirs) {
            int ni = i + d.first, nj = j + d.second;
            if (correcta(ni, nj) && M[ni][nj] == '#' && !visit[ni][nj]) {
                tam += dfs(M, ni, nj);
            }
        }
        return tam;
    }
public:
    Manchas(Mapa const& M) : F(M.size()), C(M[0].size()), visit(F, vector<bool>(C, false)), num(0), maxim(0) {
        for (int i = 0; i < F; i++) {
            for (int j = 0; j < C; j++) {
                if (!visit[i][j] && M[i][j] == '#') {
                    num++;
                    int nuevotam = dfs(M, i, j);
                    maxim = max(maxim, nuevotam);
                }
            }
        }
    }

    int numero() const{
        return num;
    }

    int maximo() const {
        return maxim;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci�n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int F, C;
    cin >> F >> C;

    if (!cin)  // fin de la entrada
        return false;

    Mapa mapa(F);
    for (string& linea : mapa) {
        cin >> linea;
    }

    Manchas manchas(mapa);

    // escribir sol
    cout << manchas.numero() << ' ' << manchas.maximo() << '\n';

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
