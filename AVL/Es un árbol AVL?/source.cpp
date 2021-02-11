
// Nombre y Apellidos
// Yule Zhang

// Comentario general sobre la soluci—n,
// explicando c—mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "bintree_eda.h"  // propios o los de las estructuras de datos de clase
using namespace std;

struct sol {
    bool ok;
    int min, max;
    int depth = 0;
};

//El coste de la funcion es
//T(n) = C0; si n = 0
//T(n) = T(n/2) + T(n/2) + C1 = T(n) + C1 si n > 1
//siendo n es el numero de nodos del arbol
sol esArbolBinarioAndAVL(bintree<int> const& arbol) {
    sol s;
    if (arbol.empty())
        s.ok = true;
    else {
        sol iz = esArbolBinarioAndAVL(arbol.left());//O(n/2)
        sol dr = esArbolBinarioAndAVL(arbol.right());//O(n/2)

        if (!arbol.left().empty()) {
            s.min = iz.min;
            iz.depth++;
        }
        else {
            s.min = arbol.root();
            iz.depth = 0;
        }

        if (!arbol.right().empty()) {
            s.max = dr.max;
            dr.depth++;
        }
        else {
            s.max = arbol.root();
            dr.depth = 0;
        }

        bool ordenado = (arbol.left().empty() || iz.max < arbol.root()) && (arbol.right().empty() || dr.min > arbol.root());
        
        s.ok = (iz.ok && dr.ok && ordenado && abs(dr.depth - iz.depth) <= 1);
        s.depth = max(iz.depth, dr.depth);
        
    }
    
    return s;
}

bool esBinarioAndAVL(bintree<int>const& arbol) {
    return esArbolBinarioAndAVL(arbol).ok;
}

void resuelveCaso() {

    // leer los datos de la entrada
    bintree<int>arbol = leerArbol(-1);
    auto esAVL = esBinarioAndAVL(arbol);
    
    // escribir soluci—n
    if (esAVL)
        cout << "SI" << endl;
    else
        cout << "NO" << endl;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
