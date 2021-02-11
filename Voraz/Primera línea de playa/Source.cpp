
// Yule Zhang

// Comentario general sobre la soluciÄn,
// explicando cÄmo se resuelve el problema

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;

struct tEdificio {
    int iz;
    int dr;
};

bool operator> (tEdificio const& a, tEdificio const& b) {
    return a.dr > b.dr;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciÄn, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    cin >> N;
    if (N == 0)  // fin de la entrada
        return false;

    priority_queue<tEdificio, vector<tEdificio>, greater<tEdificio>> cola;

    int n, m;
    for (int i = 0; i < N; i++) {
        cin >> n >> m;
        cola.push({ n, m});
    }

    int num = 1;
    tEdificio edi = cola.top();
    cola.pop();
    while (!cola.empty()) {
        if (cola.top().iz >= edi.dr) {
            num++;
            edi = cola.top();
            cola.pop();
        }
        else
            cola.pop();
    }

    // escribir sol
    cout << num << '\n';

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
