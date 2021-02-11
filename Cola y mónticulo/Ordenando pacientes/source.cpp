
// Yule Zhang

// Comentario general sobre la soluci®Æn,
// explicando c®Æmo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

struct datos {
    string nombre;//nombre del paciente
    int gravedad;//gravedad
    int tiempo;//tiempo llevado esperando
};

bool operator>(datos const& a, datos const& b) {
    return b.gravedad > a.gravedad || (b.gravedad == a.gravedad && b.tiempo < a.tiempo);
}

//El coste de la funcion es O(Nlog(N) + klog(N)) = Nlog(N)
bool resuelveCaso() {

    int N;//numero de eventos
    cin >> N;
    if (N == 0)
        return false;

    priority_queue<datos, vector<datos>, greater<datos>> cola;
    //PriorityQueue<datos>cola;

    for (int i = 0; i < N; i++) {
        char c;
        cin >> c;
        if (c == 'I') {
            string nombre;
            int gravedad;
            cin >> nombre >> gravedad;
            cola.push({ nombre, gravedad, i });//O(log(N))
        }
        else if (c == 'A') {
            auto e = cola.top();
            cout << e.nombre << '\n';
            cola.pop();//O(log(N))
        }
    }//coste del bucle for O(Nlog(N))

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
