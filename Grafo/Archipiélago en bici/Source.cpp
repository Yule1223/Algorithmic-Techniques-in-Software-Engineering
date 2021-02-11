
// Yule Zhang

// Comentario general sobre la soluciƒn,
// explicando cƒmo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <deque>
#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"
using namespace std;

class ARM {
private:
    vector<Arista<int>> res;
    int coste;

public:
    ARM(GrafoValorado<int> const& g) : coste(0) {
        PriorityQueue<Arista<int>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        
        while (!pq.empty()) {
            auto u = pq.top(); pq.pop();
            int v = u.uno();
            int w = u.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                res.push_back(u);
                coste += u.valor();
                if (res.size() == g.V() - 1) break;
            }
        }

        if (res.size() == g.V() - 1)
            cout << coste << '\n';
        else
            cout << "No hay puentes suficientes" << '\n';
    }
    
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciƒn, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    GrafoValorado<int>g(cin, 1);
    if (!cin)  // fin de la entrada
        return false;
    ARM a(g);

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
