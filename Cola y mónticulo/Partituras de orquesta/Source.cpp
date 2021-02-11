
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
    int num_musico;//numero de musico
    int num_partitura;//numero de partitura
    int res;//resultado
    //bool ok;//si tiene al menos una partitura
};

bool operator<(registro const& a, registro const& b) {
    if ((a.num_partitura == 0 && b.num_partitura == 0) || (a.num_partitura != 0 && b.num_partitura != 0))
        return a.res < b.res;
    if (a.num_partitura == 0 && b.num_partitura != 0)
        return false;
    if (a.num_partitura != 0 && b.num_partitura == 0)
        return true;
    //return a.num < b.num;
}

//El coste de la funcion es O(Nlog(N) + klog(N)) = Nlog(N)
bool resuelveCaso() {
    int p;//numero de partituras
    int n;//numero instrumentos distintos
    cin >> p >> n;
    
    if (!cin)
        return false;

    //priority_queue<registro, vector<registro>, greater<registro>> cola;
    priority_queue<registro>cola;

    for (int i = 0; i < n; i++) {
        int num_musico;
        cin >> num_musico;
        cola.push({ num_musico, 0, num_musico });//O(log(N))
    }//el bucle for O(nlog(N))

    while (p--) {
        auto e = cola.top();//O(1)
        cola.pop();//O(log(N))
 
        if(e.num_partitura != 0) {
            e.num_partitura++;
            if (e.num_musico % e.num_partitura != 0)
                e.res = (e.num_musico / e.num_partitura + 1);
            else
                e.res = (e.num_musico / e.num_partitura);
        }
        else
            e.num_partitura++;
        //cout << e.res << '\n';
        cola.push(e);//O(log(N))
    }//el bucle while O(plog(N)) siendo p el numero de partituras

    //cout << "---" << endl;
    cout << cola.top().res << '\n';
    //cout << "---" << endl;

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
