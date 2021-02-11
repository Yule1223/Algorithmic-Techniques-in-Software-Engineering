
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
    int destino;
    vector<int> dist;
    IndexPQ<int> pq;
    vector<bool> visit;
    vector<int> ant;
    vector<int> anchura;
    vector<int> aux;//vector para guardar el numero de camino minimo iguales para cada vertice
   
    void comprobar(Arista<int> a, int v) {
        int w = a.otro(v);
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            aux[w] = aux[v] + 1;
            pq.update(w, dist[w]);
        }
        else if (dist[w] == dist[v] + a.valor()) {
            aux[w] = min(aux[w], aux[v] + 1);
        }
    }

    int bfs(GrafoValorado<int> const& g) {
        queue<int> q;
        anchura[origen] = 0; 
        visit[origen] = true; 
        q.push(origen);
        while (!q.empty() && !visit[destino]) {
            int v = q.front(); q.pop(); 
            for (auto w : g.ady(v)) {
                int m = w.otro(v);
                if (!visit[m]) {
                    ant[m] = v;
                    anchura[m] = anchura[v] + 1;
                    visit[m] = true; 
                    q.push(m);
                }
            }
        }
        return anchura[destino];
    }
public:
    Dijkstra(GrafoValorado<int> const& g, int orig, int desti) : origen(orig), destino(desti), dist(g.V(), INF), 
        pq(g.V()), aux(g.V(), 0), anchura(g.V(), 0), visit(g.V(), false), ant(g.V(), 0) {
        dist[origen] = 0;
        pq.push(origen, 0);
        aux[origen] = 0;
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v))
                comprobar(a, v);
        }

        int num = bfs(g);
        if (distancia(destino) != INT_MAX) {
            cout << distancia(destino) << " ";
          
            if (num < caminoMinimo(destino))
                cout << "NO";
            else
                cout << "SI";
            cout << '\n';
        }
        else
            cout << "SIN CAMINO" << '\n';
    }

    int numeroArista(int v) const {
        return anchura[v];
    }

    bool hayCamino(int v) const {
        return dist[v] != INF;
    }

    int distancia(int v) const {
        return dist[v];
    }

    int caminoMinimo(int v) const {
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

    int casos;
    cin >> casos;
    for (int i = 0; i < casos; i++) {
        int orig, desti;
        cin >> orig >> desti;
        Dijkstra d(g, orig-1, desti-1);
    }
    cout << "---" << '\n';
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
