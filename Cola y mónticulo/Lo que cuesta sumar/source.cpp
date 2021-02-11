
// Yule Zhang

// Comentario general sobre la soluci¨®n,
// explicando c¨®mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <functional>
#include <queue>
using namespace std;

struct datos {
    unsigned long long numero;
};

bool operator> (datos const& d1, datos const& d2) {
    return d1.numero > d2.numero;
}

//El coste de la funcion es O(2Nlog(N)) = Nlog(N)
bool resuelveCaso() {
    int N;//numero de sumandos
    cin >> N;
    if (N == 0)
        return false;

    priority_queue<datos, vector<datos>, greater<datos>> cola;
    //priority_queue<int>cola;
    
    for (int i = 0; i < N; i++) {//O(N*log(N)) siendo N el numero de sumandos
        unsigned long long num;
        cin >> num;
        cola.push({ num});//O(log(N))
    }
   
    unsigned long long aux = 0;//guardar el ultimo esfuerzo
    unsigned long long res = 0;//resultado
    //si solo hay un numero
    if (cola.size() == 1)
        cout << res << '\n';
    else {
        N--;
        while (N--) {//O(2*N/2log(N))=O(Nlog(N)) siendo N el numero de sumandos
            unsigned long long x = cola.top().numero;//O(1)
            cola.pop();//O(log(N))
            unsigned long long y = cola.top().numero;//O(1)
            cola.pop();//O(log(N))
            unsigned long long n = x + y;
            aux += n;

            res += n;
            
            if (cola.size() > 0) {
                cola.push({ n });//metemos el esfuerzo
            }
            
        }
        
        cout << res << '\n';
    }
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
