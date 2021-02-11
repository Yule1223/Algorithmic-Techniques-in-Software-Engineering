
// Yule Zhang

// Comentario general sobre la soluci€n,
// explicando c€mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Matriz.h"
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci€n, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int N;
    cin >> N;
    if (!cin)//fin de entrada
        return false;

    //Matriz para guardar los datos de la entrada
    Matriz<int>datos(N + 1, N + 1, 0);

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> datos[i][j];
    
    //Matriz para calcular el valor máximo para cada casilla
    Matriz<int>m(N + 1, N + 2, 0);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (m[i - 1][j] == 0) //si es la primera fila
                m[i][j] = datos[i][j];
            else {//si no es la primera fila
                //sacamos el máximo entre las casillas diagonales y la casilla encima
                int maxi = max(m[i - 1][j - 1], m[i - 1][j + 1]);//Max de las dos diagonales
                maxi = max(maxi, m[i - 1][j]); //Max entre el de las diagonales y la casilla de encima
                m[i][j] = maxi + datos[i][j];
            }
        }
    }
    /*
    vector<int> juego(N);
    
    // primera fila, caso básico, igual al tablero
    for (int j = 0; j < N; ++j) {
        juego[j] = tablero[0][j];
    }
    
    // resto
    for (int i = 1; i < N; ++i) {
        int ant = juego[0];
        for (int j = 0; j < N; ++j) {
            int act = juego[j];
            if (j == 0) { // solo 2 vecinos
                juego[j] = max(juego[j], juego[j+1]);
            } else if (j == N-1){
                juego[j] = max(juego[j], ant);
            } else { // hay 3 vecinos
                juego[j] = max(max(juego[j], juego[j+1]), ant);
            }
             // más lo que hay donde estamos
            juego[j] += tablero[i][j];
            ant = act;
        }
    }*/

    //calculamos el máximo de la última fila
    int col = 1;
    // cálculo de los objetos
    for (int j = 1; j <= N; j++) {
        if (m[N][j] > m[N][col]) {//hacemos un mayor no mayor igual para guardar el primero máximo que encontramos
            col = j;
        }
    }
    cout << m[N][col] << " " << col << "\n";
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
