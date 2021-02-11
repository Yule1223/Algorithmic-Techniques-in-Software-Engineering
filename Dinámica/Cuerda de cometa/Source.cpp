
// Yule Zhang

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Matriz.h"
using namespace std;
const int INF = 1000000000;

struct tCordel {
    int longitud;
    int coste;
};

//coste O(N*L)
bool esPosible(vector<tCordel>const& v, int N, int L) {
    Matriz<bool> m(N + 1, L + 1, false);
    m[0][0] = true;

    for (int i = 1; i <= N; i++) {
        m[i][0] = true;
        for (int j = 1; j <= L; j++) {
            if (v[i - 1].longitud > j) //NO lo queremos
                m[i][j] = m[i - 1][j];
            else //Si lo queremos, si la casilla encima de el es uno o se puede sumar por los anteriores
                m[i][j] = m[i - 1][j] || m[i - 1][j - v[i - 1].longitud];
        }
    }
    //cout << m << '\n';
    return m[N][L];
}

//coste O(N*L)
long long calcularFormas(vector<tCordel>const& v, int N, int L) {
    Matriz<long long> m(N + 1, L + 1, 0);

    m[0][0] = 1;

    for (int i = 1; i <= N; i++) {v
        m[i][0] = 1;
        for (int j = 1; j <= L; j++) {
            if (v[i - 1].longitud > j)//No lo queremos 
                m[i][j] = m[i - 1][j];
            else //Si lo queremos
                m[i][j] = m[i - 1][j] + m[i - 1][j - v[i - 1].longitud];
        }
    }
    //cout << m << '\n';
    return m[N][L];
}

//coste O(N*L)
int calcularMinimo(vector<tCordel>const& v, int N, int L) {
    Matriz<int> m(N + 1, L + 1, INF);

    m[0][0] = 0;

    for (int i = 1; i <= N; i++) {
        m[i][0] = 0;
        for (int j = 1; j <= L; j++) {
            if (v[i - 1].longitud > j)//No lo queremos 
                m[i][j] = m[i - 1][j];
            else //Si lo queremos
                m[i][j] = min(m[i - 1][j], m[i - 1][j - v[i - 1].longitud] + 1);
        }
    }
    //cout << m << '\n';
    return m[N][L];
}

//coste O(N*L)
int calcularMinCoste(vector<tCordel>const& v, int N, int L) {
    Matriz<int> m(N + 1, L + 1, INF);

    m[0][0] = 0;

    for (int i = 1; i <= N; i++) {
        m[i][0] = 0;
        for (int j = 1; j <= L; j++) {
            if (v[i - 1].longitud > j)//No lo queremos 
                m[i][j] = m[i - 1][j];
            else //Si lo queremos
                m[i][j] = min(m[i - 1][j], m[i - 1][j - v[i - 1].longitud] + v[i - 1].coste);
        }
    }
    //cout << m << '\n';
    return m[N][L];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, L;
    cin >> N >> L;
    if (!cin)  // fin de la entrada
        return false;

    vector<tCordel> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i].longitud >> v[i].coste;
    }
    
    bool posible = esPosible(v, N, L);
    
    if (posible) {
        long long formas = calcularFormas(v, N, L);
        int minimo = calcularMinimo(v, N, L);
        int minCoste = calcularMinCoste(v, N, L);
        cout << "SI " << formas << " " << minimo << " " << minCoste << "\n";
    }
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
