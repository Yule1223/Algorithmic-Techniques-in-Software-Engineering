
// Yule Zhang

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
//coste de la funcion O(N), siendo N el numero de agujeeros, ya que recorremos cada elemento del vector 1 vez

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(vector<int>const& agujeros, int L) {
    int num = 1;
    int tapado = agujeros[0] + L;
    for (int i = 1; i < agujeros.size(); i++) {
        if (agujeros[i] > tapado) {
            num++;
            tapado = agujeros[i] + L;
        }
    }

    return num;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, L;
    cin >> N >> L;
    if (!std::cin)  // fin de la entrada
        return false;
    vector<int>agujeros;
    int n;
    for (int i = 0; i < N; i++) {
        cin >> n;
        agujeros.push_back(n);
    }

    int sol = resolver(agujeros, L);

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
