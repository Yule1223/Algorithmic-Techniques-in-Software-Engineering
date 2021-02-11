
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

class ColaMedianas {
private:
    priority_queue<int> cola1;//cola para guardar los elementos menor que la mediana y la mediana
    priority_queue<int, vector<int>, greater<int>> cola2;//cola para guardar los elementos mayor que la mediana

public:
    //O(log(N))
    void insertar(int x) {
        if (vacia()) {
            cola1.push(x);
        }
        else {
            if (x > mediana())
                cola2.push(x);
            else
                cola1.push(x);
            //equilibrar las dos colas
            if (cola2.size() > cola1.size()) {
                int y = cola2.top();
                cola2.pop();
                cola1.push(y);
                //cout << "top2 " << cola2.top() << endl;
            }
            if (cola1.size() > cola2.size() + 1) {
                int z = cola1.top();
                cola1.pop();
                cola2.push(z);
                //cout << "top1 " << cola1.top() << endl;
            }
        }
    }
    //O(1)
    bool vacia() const {
        return cola1.empty();
    }
    //O(1)
    int mediana() const {
        return cola1.top();
    }
    //O(log(N))
    void quitarMediana(){
        cola1.pop();
        if (cola2.size() > cola1.size()) {
            cola1.push(cola2.top());
            cola2.pop();
        }
    }
};


//El coste de la funcion es O(Nlog(N) + Mlog(N)+ Klog(N)) = Nlog(N)
bool resuelveCaso() {
    int numAcciones;
    cin >> numAcciones;
    if (!cin)
        return false;
    
    int num;
    ColaMedianas cola;
    for (int i = 0; i < numAcciones; i++) {
        cin >> num;
        if (num == 0) {
            if (cola.vacia())
                cout << "ECSA ";
            else {
                cout << cola.mediana() << " ";
                cola.quitarMediana();
            }
        }
        else
            cola.insertar(num);
    }
    cout << '\n';
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
