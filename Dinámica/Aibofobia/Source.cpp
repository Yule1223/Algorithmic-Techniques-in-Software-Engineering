
// Yule Zhang

// Comentario general sobre la soluciƒn,
// explicando cƒmo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include "Matriz.h"
using namespace std;

int patin_rec(string const& patitos, int i, int j, Matriz<int>& patin) {
    int& res = patin[i][j];
    if (res == -1) {
        if (i > j) res = 0;
        else if (i == j) res = 0;
        else if (patitos[i] == patitos[j])
            res = patin_rec(patitos, i + 1, j - 1, patin);
        else
            res = min(patin_rec(patitos, i + 1, j, patin), patin_rec(patitos, i, j - 1, patin)) + 1;
    }
    return res;
}

void reconstruir(string const& patitos, Matriz<int> const& patin, int i, int j, string& sol) {
    if (i > j) return;
    if (i == j) sol.push_back(patitos[i]); 
    else if (patitos[i] == patitos[j]) {
        sol.push_back(patitos[i]); 
        reconstruir(patitos, patin, i + 1, j - 1, sol); 
        sol.push_back(patitos[j]);
    }
    else if (patin[i][j] == patin[i + 1][j] + 1) {
        sol.push_back(patitos[i]);
        reconstruir(patitos, patin, i + 1, j, sol);
        sol.push_back(patitos[i]);
    }
    else {
        sol.push_back(patitos[j]);
        reconstruir(patitos, patin, i, j - 1, sol);
        sol.push_back(patitos[j]);
        
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciƒn, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    string patitos;
    cin >> patitos;
    if (!cin)
        return false;
    int n = patitos.length();
    Matriz<int> patindromo(n, n, -1);

    cout << patin_rec(patitos, 0, n - 1, patindromo) << ' ';
    //cout << patindromo;
    // escribir sol
    string sol;
    reconstruir(patitos, patindromo, 0, n - 1, sol); 
    cout << sol << '\n';

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
