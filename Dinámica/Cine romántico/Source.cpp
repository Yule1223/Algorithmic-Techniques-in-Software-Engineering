
// Yule Zhang

// Comentario general sobre la soluci€n,
// explicando c€mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
#include "Matriz.h"
using namespace std;
const int INF = 1000000000;

struct tHora {
    int HH;
    int MM;
};

struct tPelicula {
    tHora ini;
    tHora fin;
    int duration;
};

bool operator==(tHora const& a, tHora const& b) {
    return a.HH == b.HH && a.MM == b.MM;
}

bool operator<(tHora const& a, tHora const& b) {
    return (a.HH < b.HH) || (a.HH == b.HH && a.MM < b.MM);
}

bool operator<(tPelicula const& a, tPelicula const& b) {
    return a.ini < b.ini || (a.ini == b.ini && a.fin < b.fin);
}

int justificar(vector<tPelicula>& cine) {
    int n = cine.size() -1;
    vector<int> v(n + 1, 0);
    v[n] = cine[n].duration;

    for(int i = n; i >= 1; i--){
        for (int j = i; j < n; j++) {

            if (cine[i].fin < cine[j + 1].ini) // Me quedo con ambas peliculas
                v[i] = max(v[i], cine[i].duration + v[j + 1]);
            else
                v[i] = max(v[i], max(cine[i].duration, v[j + 1]));

        }
    }
    /*
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    */
    return v[1];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci€n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    cin >> N;
    if (N == 0)  // fin de la entrada
        return false;

    vector<tPelicula> cine(N + 1);

    int hora, min, duration;
    char c;

    for (int i = 1; i <= N; i++) {
        cin >> hora >> c >> min >> duration;
        tHora ini = { hora, min };
        tHora fin = { hora, min };
        fin.MM = ini.MM + duration + 9;//9 minutos para palomitas
        while (fin.MM >= 60) {
            fin.MM -= 60;
            fin.HH++;
        }
        cine[i] = { ini, fin, duration };
    }
 
    sort(cine.begin(), cine.end());
    /*for (int i = 0; i < cine.size(); i++) {
        cout << cine[i].duration << endl;;
    }
    cout << cine.size();*/
    
    auto sol = justificar(cine);

    // escribir sol
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
