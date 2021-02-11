
// Yule Zhang

// Comentario general sobre la soluci…n,
// explicando c…mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <deque>
#include <climits>
#include "GrafoValorado.h"
#include "IndexPQ.h"
using namespace std;
//el coste del problema es O(A*logV) ya que para cada arista se hacen operaciones de IndexPQ que tienen el coste log(V)

class Dijkstra {
private:
    const int INF = INT_MAX;
    int origen;
    vector<int> dist;
    IndexPQ<int> pq;
    vector<int> aux;//vector para guardar el numero de camino minimo iguales para cada vertice

    void visit(Arista<int> a, int v) {
        int w = a.otro(v);
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            aux[w] = aux[v];
            pq.update(w, dist[w]);
        }
        else if (dist[w] == dist[v] + a.valor()) {
            aux[w] += aux[v];
        }
    }
public:
    Dijkstra(GrafoValorado<int> const& g, int orig) : origen(orig), dist(g.V(), INF), pq(g.V()), aux(g.V(), 0) {
        dist[origen] = 0;
        pq.push(origen, 0);
        aux[0] = 1;
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v))
                visit(a, v);
        }
    }
    bool hayCamino(int v) const {
        return dist[v] != INF;
    }

    int distancia(int v) const {
        return dist[v];
    }

    int caminoMinimo(int v) const {
        /*
        for (int i = 0; i < aux.size(); i++)
            cout << aux[i] << " ";
        cout << endl;
        */
        return aux[v];
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
// configuraci…n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
  
    GrafoValorado<int> g(cin, 1);
    if (!cin)    // fin de la entrada
        return false;

    Dijkstra d(g, 0);

    cout << d.caminoMinimo(g.V() - 1) << '\n';

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
