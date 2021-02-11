
// Yule Zhang

// Comentario general sobre la soluci…n,
// explicando c…mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <deque>
#include <climits>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
using namespace std;
//el coste del problema es O(A*logV) ya que para cada arista se hacen operaciones de IndexPQ que tienen el coste log(V)

class Paquetes {
private:
    const int INF = INT_MAX;
    int origen;
    vector<int> dist;
    IndexPQ<int> pq;
    bool posible;
    int coste;

    void visit(AristaDirigida<int> a, int v) {
        int w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }

public:
    Paquetes (DigrafoValorado<int> const& g, int orig) : origen(orig), dist(g.V(), INF), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        
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

    bool esPosible(int v) const {
        return hayCamino(v);
    }

    int getCoste(int v) const {
        return distancia(v);
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

    DigrafoValorado<int> g(cin, 1);
    if (!cin)    // fin de la entrada
        return false;

    int O;//O es el origen tb el final
    int P;//numero de paquetes a repartir
    cin >> O >> P;

    DigrafoValorado<int> inversaG = g.inverso();
    Paquetes d(g, O - 1);
    Paquetes inversa(inversaG, O - 1);

    bool posible = true;
    int suma = 0;
    for (int i = 0; i < P; i++) {
        int n;
        cin >> n;
        if(posible)
            posible = d.esPosible(n - 1) && inversa.esPosible(n - 1);
        suma = suma + d.getCoste(n - 1) + inversa.getCoste(n - 1);
    }

    if (!posible)
        cout << "Imposible" << "\n";
    else {
        cout << suma << "\n";
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
