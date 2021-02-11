
// Yule Zhang

// Comentario general sobre la soluci¨®n,
// explicando c¨®mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <functional>
#include <queue>  // propios o los de las estructuras de datos de clase
using namespace std;

struct registro {
    int momento;//cuando le toca
    int id;//identificador
    int periodo;//tiempo entre consultas
};

bool operator<(registro const& a, registro const& b) {
    return a.momento < b.momento || (a.momento == b.momento && a.id < b.id);
}

bool operator>(registro const& a, registro const& b) {
    return b < a;
}

//El coste de la funcion es O(Nlog(N) + klog(N)) = Nlog(N)
bool resuelveCaso() {

    int N;//numero d usuarios registrados
    cin >> N;

    if (N == 0)
        return false;

    priority_queue<registro, vector<registro>, greater<registro>> cola;
    //PriorityQueue<registro>cola;

    for (int i = 0; i < N; i++) {
        int id_usu, periodo;
        cin >> id_usu >> periodo;
        cola.push({ periodo, id_usu, periodo });//O(log(N))
    }//el bucle for O(Nlog(N))

    int envios;
    cin >> envios;

    while (envios--) {
        auto e = cola.top();//O(1)
        cola.pop();//O(log(N))
        cout << e.id <<'\n';
        e.momento += e.periodo;
        cola.push(e);//O(log(N))
    }//el bucle while O(klog(N)) siendo k el numero de envios

    cout << "---" << '\n';

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
