
// Yule Zhang

// Comentario general sobre la soluciƒn,
// explicando cƒmo se resuelve el problema

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;
//coste es O(N + NlogN + N) = O(NlogN) por la ordenacion del vector

struct tAlienigena {
    int ini;
    int fin;
};

//ordenar por ini
bool operator< (tAlienigena const& a, tAlienigena const& b) {
    return a.ini < b.ini || (a.ini == b.ini && a.fin > b.fin);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciƒn, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int C, F, N;
    cin >> C >> F >> N;
    if (C == 0 && F == 0 && N == 0)// fin de la entrada
        return false;

    //priority_queue<tAlienigena, vector<tAlienigena>, greater<tAlienigena>> cola;
    vector<tAlienigena> alienigenas;

    int n, m;
    for (int i = 0; i < N; i++) {
        cin >> n >> m;
        /*
        //si n >= F o m <= C no hace falta que entre en la cola
        if (n < F && m > C) {
            if (n < C)
                n = C;
            if (m > F)
                m = F;
            alienigenas.push_back({ n, m });
        }*/
        alienigenas.push_back({ n, m });
    }

    sort(alienigenas.begin(), alienigenas.end(), less<tAlienigena>());

    bool posible = true;
    int i = 0;

    int num = 0;//contador iniciado a 0
    int cubierto = C;

    while (posible && cubierto < F) {
        int maxi = -1;
        while (i < N && alienigenas[i].ini <= cubierto) {
            maxi = max(maxi, alienigenas[i].fin);
            i++;
        }
        if (maxi == -1)
            posible = false;
        num++;
        cubierto = maxi;
    }

    // escribir sol
    if (posible)
        cout << num << '\n';
    else
        cout << "Imposible" << '\n';

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
