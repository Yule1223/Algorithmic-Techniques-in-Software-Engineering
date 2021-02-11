
// Yule Zhang

// Comentario general sobre la soluciƒn,
// explicando cƒmo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "Matriz.h"
using namespace std;

bool multiplica_matrices(const string s) {
    int n = s.length();
    Matriz<bool> A(n + 1, n + 1, false);
    Matriz<bool> B(n + 1, n + 1, false);
    Matriz<bool> C(n + 1, n + 1, false);
    //inicializar las tres matrices
    for (int i = 1; i <= n; i++) {
        A[i][i] = (s[i - 1] == 'a');
        B[i][i] = (s[i - 1] == 'b');
        C[i][i] = (s[i - 1] == 'c');
    }
    
    //actualizar las tres matrices
    for (int d = 1; d <= n - 1; ++d) // recorre diagonales
        for (int i = 1; i <= n - d; ++i) { // recorre elementos de diagonal 
            int j = i + d;
            
            for (int k = i; k <= j - 1 && !A[i][j]; k++) {
                A[i][j] = (A[i][k] && C[k + 1][j]) || (B[i][k] && C[k + 1][j]) || (C[i][k] && A[k + 1][j]);
            }
            for (int k = i; k <= j - 1 && !B[i][j]; k++) {
                B[i][j] = (A[i][k] && A[k + 1][j]) || (A[i][k] && B[k + 1][j]) || (B[i][k] && B[k + 1][j]);
            }
            for (int k = i; k <= j - 1 && !C[i][j]; k++) {
                C[i][j] = (B[i][k] && A[k + 1][j]) || (C[i][k] && B[k + 1][j]) || (C[i][k] && C[k + 1][j]);
            }
        }
    //cout << A;
    return A[1][n];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciƒn, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    string s;
    getline(cin, s);
    if (!cin)
        return false;
    
    auto sol = multiplica_matrices(s);

    // escribir sol
    if (sol)
        cout << "SI" << '\n';
    else
        cout << "NO" << '\n';
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
