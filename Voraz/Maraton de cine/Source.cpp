
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
using namespace std;

struct tHora {
    int HH;
    int MM;
};

struct tPelicula {
    tHora ini;
    tHora fin;
};

bool operator==(tHora const& a, tHora const& b) {
    return a.HH == b.HH && a.MM == b.MM;
}

bool operator>(tHora const& a, tHora const& b) {
    return (a.HH > b.HH) || (a.HH == b.HH && a.MM > b.MM);
}

bool operator>(tPelicula const& a, tPelicula const& b) {
    return a.fin > b.fin || (a.fin == b.fin && a.ini > b.ini);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci€n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    cin >> N;
    if (N == 0)  // fin de la entrada
        return false;

    priority_queue<tPelicula, vector<tPelicula>, greater<tPelicula>> cine;

    int hora, min, duration;
    char c;

    for (int i = 0; i < N; i++) {
        cin >> hora >> c >> min >> duration;
        tHora ini = { hora, min };
        tHora fin = { hora, min };
        fin.MM = ini.MM + duration;
        while (fin.MM >= 60) {
            fin.MM -= 60;
            fin.HH++;
        }
        cine.push({ ini, fin });
    }
    /*
    while (!cine.empty()) {
        auto n = cine.top();
        cout << n.ini.HH << " " << n.ini.MM << " " << n.fin.HH << " " << n.fin.MM << endl;
        cine.pop();
    }
    */
    
    int numPeli = 1;
    tPelicula primera = cine.top();
    cine.pop();
    
    while (!cine.empty()) {
        tHora final = primera.fin;
        tHora inicial = primera.ini;
        //calcular hora final
        final.MM += 9;
        if (final.MM >= 60) {
            final.MM -= 60;
            final.HH++;
        }
        //--------------------

        if (cine.top().ini > final) {
            numPeli++;
            primera = cine.top();
        }
        cine.pop();
    }

    // escribir sol
    cout << numPeli << '\n';
    
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
