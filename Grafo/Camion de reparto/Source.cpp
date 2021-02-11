
// Yule Zhang

// Comentario general sobre la soluciÄn,
// explicando cÄmo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <deque>
#include "GrafoValorado.h"
using namespace std;

class Reparto {
private:
    bool ok;//es posible repartir
    vector<bool> visit;

    void dfs(GrafoValorado<int> const& g, int v, int fin, int width) {
        visit[v] = true;
        for (auto a : g.ady(v)) {
            if (a.valor() >= width) {
                int w = a.otro(v);
                if (w == fin) {//si llegamos a fin
                    ok = true;
                    return;
                }
                if (!visit[w]) {
                    dfs(g, w, fin, width);
                }
            }
        }
    }

public:
    Reparto(GrafoValorado<int> const& g, int ini, int fin, int width) : visit(g.V(), false), ok(false) {
        dfs(g, ini, fin, width);
    }

    void printResultado() const{
        if (ok) cout << "SI ";
        else cout << "NO";
        cout << '\n';
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciÄn, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    GrafoValorado<int>g(cin, 1);
    if (!cin)  // fin de la entrada
        return false;
    int K;
    cin >> K;
    for (int i = 0; i < K; i++) {
        int ini, fin, width;
        cin >> ini >> fin >> width;
        Reparto r(g, ini-1, fin-1, width);
        r.printResultado();
    }
    
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
