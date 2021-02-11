
// Yule Zhang

// Comentario general sobre la soluci®Æn,
// explicando c®Æmo se resuelve el problema

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <functional>
#include <queue>  // propios o los de las estructuras de datos de clase
using namespace std;

struct datos {
    int ini;//instante de comienzo
    int fin;//instante de finalizacion
    int periodo;
};

bool operator>(datos const& a, datos const& b) {
    return a.ini > b.ini;
}

//El coste de la funcion es O(Nlog(N) + Mlog(N)+ Klog(N)) = Nlog(N)
bool resuelveCaso() {
    int N;//numero de tareas unicas
    int M;//numero de tareas periodicas
    int T;//minutos
    cin >> N >> M >> T;
    if (!cin)
        return false;

    priority_queue<datos, vector<datos>, greater<datos>> cola;
    //PriorityQueue<datos>cola;

    for (int i = 0; i < N; i++) {
        int ini, fin;
        cin >> ini >> fin;
        cola.push({ ini, fin, 0});//O(log(N))
    }//coste del bucle for O(Nlog(N))

    for (int j = 0; j < M; j++) {
        int ini, fin, periodo;
        cin >> ini >> fin >> periodo;
        cola.push({ ini, fin, periodo });//O(log(N))
    }//coste del bucle for O(Mlog(N))

    bool enc = true;
    int tiempo = 0;
    while (tiempo < T && enc) {
        auto e = cola.top();//O(1)
        //tiempo = e.ini;
        cola.pop();//O(log(N))
        if (cola.empty()) break;
        auto f = cola.top();//O(1)
        tiempo = f.ini;
        //cout << e.ini << " "<< e.fin<< " " << f.ini<< " " << f.fin << endl;
        if (f.ini < T) {
            enc = (e.ini < f.ini && e.fin <= f.ini); 
            if (e.periodo != 0)
                cola.push({ e.ini + e.periodo, e.fin + e.periodo, e.periodo });//O(log(N))
        }
       
    }//el bucle while O(Klog(N))

    if (!enc)
        cout << "SI" << '\n';
    else
        cout << "NO" << '\n';

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
