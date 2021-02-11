
// Yule Zhang

// Comentario general sobre la soluci¨®n,
// explicando c¨®mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <set>
#include "TreeSet_AVL.h"  // propios o los de las estructuras de datos de clase
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci¨®n, y escribiendo la respuesta
bool resuelveCaso() {
    int nNodos;
    cin >> nNodos;//numero de nodos
    if (nNodos == 0)
        return false;
    
    Set<int>arbol;
    int num;
    for (int i = 0; i < nNodos; i++) {
        cin >> num;
        arbol.insert(num);
    }
    int M;
    cin >> M;
    int aux;
    for (int i = 0; i < M; i++) {
        cin >> aux;
        
        if (aux > arbol.size() || aux <= 0) //si no existe la posicion consultada
            cout << "??" << endl;
        else {
            auto sol = arbol.kesimo(aux);
            cout << sol << endl;
        }
        
    }
    cout << "---" << endl;
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
