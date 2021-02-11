
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

void reconstruir(string const& X, string const& Y, Matriz<int> const& m, int i, int j, string& sol) {
    if (i <= 0 || j <= 0)
        return;
    else if (X[i - 1] == Y[j - 1]) {
        reconstruir(X, Y, m, i - 1, j - 1, sol);
        sol.push_back(Y[j - 1]);
    }
    else if (m[i][j] == m[i - 1][j])
        reconstruir(X, Y, m, i - 1, j, sol);
    else
        reconstruir(X, Y, m, i, j - 1, sol);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciƒn, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    string x, y;
    cin >> x >> y;
    if (!cin)
        return false;

    Matriz<int> tabla(x.length() + 1, y.length() + 1, 0);
    
    for (int i = 1; i <= x.length(); i++) {
        for (int j = 1; j <= y.length(); j++) {
            if (x[i - 1] != y[j - 1]) 
                tabla[i][j] = max(tabla[i - 1][j], tabla[i][j - 1]);
            else 
                tabla[i][j] = tabla[i - 1][j - 1] + 1;
        }
    }
    //cout << tabla << endl;

    // escribir sol
    string sol;
    reconstruir(x, y, tabla, x.length(), y.length(), sol);
    cout << sol << '\n';
    //cout << tabla[x.length()][y.length()] << "\n";

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
