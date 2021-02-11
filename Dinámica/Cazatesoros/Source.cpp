
// Yule Zhang

// Comentario general sobre la soluciÄn,
// explicando cÄmo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include "Matriz.h"
using namespace std;
const int INF = 1000000000;

struct tesoro {
    int tiempo;
    int oro;
};

void cogerCofres(vector<tesoro>const& v, int N, int T) {
    Matriz<int> m(N + 1, T + 1, 0);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= T; j++) {
            if (v[i - 1].tiempo > j)
                m[i][j] = m[i - 1][j];
            else
                m[i][j] = max(m[i - 1][j], m[i - 1][j - v[i - 1].tiempo] + v[i - 1].oro);
        }
    }
    cout << m[N][T] << '\n';

    list<tesoro>sol;
    int resto = T;

    for (int x = N; x >= 1; x--) {
        if (m[x][resto] != m[x - 1][resto]) {
            sol.push_back(v[x - 1]);
            resto -= v[x - 1].tiempo;
        }
    }
   
    cout << sol.size() << '\n';

    while (!sol.empty()) {
        tesoro t = sol.back();
        cout << t.tiempo / 3 << " " << t.oro << '\n';
        sol.pop_back();
    }
    cout << "---" << '\n';
    //cout << m << endl;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciÄn, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int T, N;
    cin >> T >> N;
    if (!cin)  // fin de la entrada
        return false;

    vector<tesoro> v(N);
    for (int i = 0; i < N; i++) {
        int profundidad;
        cin >> profundidad >> v[i].oro;
        v[i].tiempo = 3 * profundidad;//2p de ascenso y p de descenso
    }

    cogerCofres(v, N, T);
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
