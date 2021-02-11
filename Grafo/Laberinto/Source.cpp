
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

class Laberinto {
private:
    const int INF = INT_MAX;
    int origen;
    vector<int> dist;
    vector<AristaDirigida<int>> ult;
    IndexPQ<int> pq;
    int t;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            ult[w] = a;
            pq.update(w, dist[w]);
        }
    }

    void calcular() const {
        int cont = 0;
        for (int i = 0; i < dist.size(); i++) {
            if (i != origen && dist[i] <= t)
                cont++;
        }
        cout << cont << '\n';
    }
public:
    Laberinto(DigrafoValorado<int> const& g, int orig, int T) : origen(orig), dist(g.V(), INF), ult(g.V()), pq(g.V()), t(T) {
        DigrafoValorado<int> gi = g.inverso();
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : gi.ady(v))
                relajar(a);
        }
        calcular();
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
// configuraci…n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, S, T, P;
    cin >> N >> S >> T >> P;
    if (!cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> g(N);

    for (int i = 0; i < P; i++) {
        int v, w, c;
        cin >> v >> w >> c;
        g.ponArista({ v - 1, w - 1, c });
    }

    Laberinto d(g, S-1, T);

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
