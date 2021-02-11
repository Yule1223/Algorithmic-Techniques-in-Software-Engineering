
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

class Sumidero {
private:
    bool haySumidero;
    vector<int> res;

public:
    Sumidero(Digrafo const& g) : haySumidero(false) {
        for (int i = 0; i < g.V(); i++) {
            if (g.getNEntradas(i) == g.V() - 1 && g.ady(i).size() == 0) {
                haySumidero = true;
                res.push_back(i);
            }
        }

        if (haySumidero) {
            cout << "SI ";
            for (int i = 0; i < res.size(); i++) {
                cout << res[i] << " ";
            }
        }
        else
            cout << "NO";
        cout << '\n';
    }

};

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci€n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    Digrafo g(cin);
    if (!cin)  // fin de la entrada
        return false;

    Sumidero s(g);

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
