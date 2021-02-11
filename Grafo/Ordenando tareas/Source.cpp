
// Yule Zhang

// Comentario general sobre la soluci€n,
// explicando c€mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <deque>
#include "Digrafo.h"
using namespace std;

class CicloDirigido {
private:
    vector<bool> visit;
    vector<int> ant;
    vector<bool> apilado;//si esta el vertice v en la pila
    deque<int> _ciclo;
    deque<int> res;//vector de resultado
    bool hayciclo;

    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;

        for (int w : g.ady(v)) {
            if (hayciclo)//acabamos si hay un ciclo
                return;
            if (!visit[w]) {//nuevo vertice
                ant[w] = v;
                dfs(g, w);
            }
            else if (apilado[w]) {//detectamos que hay ciclo
                hayciclo = true;
                /* no hace falta en este ejercicio
                for (int x = v; x != w; x = ant[v]) {
                    _ciclo.push_front(x);
                }
                _ciclo.push_front(w);
                _ciclo.push_front(v);
                */
            }
        }
        res.push_front(v + 1);
        apilado[v] = false;
    }
public:
    CicloDirigido(Digrafo const& g) : visit(g.V(), false), ant(g.V()), apilado(g.V(), false), hayciclo(false) {
        for (int v = 0; v < g.V(); v++) {
            if (!visit[v])
                dfs(g, v);
        }
        /*
        for (int i = 0; i < ant.size(); i++) {
            cout << ant[i]<< " ";
        }
        cout << endl;
        */
    }

    deque<int> getCamino() const {
        return res;
    }

    bool hayCiclo() const {
        return hayciclo;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci€n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    Digrafo g(cin, 1);
    if (!cin)  // fin de la entrada
        return false;

    CicloDirigido ciclo(g);
    
    if (ciclo.hayCiclo())
        cout << "Imposible" << '\n';
    else {
        deque<int> v = ciclo.getCamino();
        for (int i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
        }
        cout << '\n';
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
