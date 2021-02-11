
// Yule Zhang

// Comentario general sobre la soluciÄn,
// explicando cÄmo se resuelve el problema

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#include <functional>
using namespace std;

struct tActividad {
    int ini;
    int fin;
};

bool operator> (tActividad const& a, tActividad const& b) {
    return a.ini > b.ini;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciÄn, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    cin >> N;
    if (N == 0)  // fin de la entrada
        return false;

    priority_queue<tActividad, vector<tActividad>, greater<tActividad>> cola;


    int n, m;
    for (int i = 0; i < N; i++) {
        cin >> n >> m;
        cola.push({ n, m });
    }

    int num = 0;
    tActividad a = cola.top();
    cola.pop();
    priority_queue<int, vector<int>, greater<int>> amigos;//cola para guardar el ini y fin de cada amigo


    while (!cola.empty()) {
        if (cola.top().ini < a.fin) {//necesitamos amigos
            //comprobamos si hay amigos disponibles
            if (amigos.empty()) {//no hay ningun amigo
                num++;
                amigos.push(cola.top().fin);
            }
            else if (amigos.top() <= cola.top().ini) {//el amigo que ya asignamos puede ir
                amigos.pop();
                amigos.push(cola.top().fin);
            }
            else {//necesitamos un amigo nuevo
                num++;
                amigos.push(cola.top().fin);
            }
                
        }
        else {//puedo ir yo
            a = cola.top();
        }
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
