
// Yule Zhang

// Comentario general sobre la soluciƒn,
// explicando cƒmo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <deque>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <climits>
using namespace std;

class Dijkstra {
private:
    const int INF = INT_MAX;
    int origen;
    vector<int> dist; 
    vector<AristaDirigida<int>> ult;
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); 
            ult[w] = a;
            pq.update(w, dist[w]);
        }
    }
public:
    Dijkstra(DigrafoValorado<int> const& g, int orig) : origen(orig), dist(g.V(), INF), ult(g.V()), pq(g.V()) {
        dist[origen] = 0; 
        pq.push(origen, 0); 
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop(); 
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const { 
        return dist[v] != INF; 
    } 

    int distancia(int v) const { 
        return dist[v]; 
    }

    /*
    Camino<Valor> camino(int v) const {
        Camino<Valor> cam;
        // recuperamos el camino retrocediendo AristaDirigida<Valor> a;
        for (a = ult[v]; a.desde() != origen; a = ult[a.desde()])
            cam.push_front(a); cam.push_front(a); return cam;
    }*/
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciƒn, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int V;
    cin >> V;
    if (V == 0)  // fin de la entrada
        return false;

    DigrafoValorado<int>g(cin, V);
    
    Dijkstra d(g, 0);

    if (d.hayCamino(g.V() - 1))
        cout << d.distancia(g.V() - 1) << '\n';
    else
        cout << "IMPOSIBLE" << '\n';

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
