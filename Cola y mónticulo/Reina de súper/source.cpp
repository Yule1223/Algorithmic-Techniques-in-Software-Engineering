
// Yule Zhang

// Comentario general sobre la soluci®Æn,
// explicando c®Æmo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

struct datos {
    int id;//id de la caja
    int tiempo;
};

bool operator>(datos const& a, datos const& b) {
    return a.tiempo>b.tiempo || (a.tiempo == b.tiempo && a.id > b.id);
}

//El coste de la funcion es O(Nlog(N) + Clog(N)) = Nlog(N)
bool resuelveCaso() {

    int N;//numero de cajas abiertas
    int C;//numero de clientes esperando
    cin >> N >> C;
    if (N == 0 && C == 0)
        return false;

    priority_queue<datos, vector<datos>, greater<datos>> cola;
    //PriorityQueue<datos>cola;
    
    for (int i = 0; i < N; i++) {
        cola.push({ i + 1, 0 });//O(log(N))
    }//coste del for O(Nlog(N))

    for (int i = 0; i < C; i++) {
        int tiempo;
        cin >> tiempo;
        auto e = cola.top();//O(1)
        cola.pop();//O(log(N))
        e.tiempo += tiempo;
        cola.push(e);//O(log(N))
    }//coste del bucle for O(Clog(N))
    /*
    for (int i = 0; i < N; i++) {
        cout << cola.top().id << " " << cola.top().tiempo << endl;
        cola.pop();
    }*/
    
    auto m = cola.top();
    cout << m.id << '\n';
    
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
