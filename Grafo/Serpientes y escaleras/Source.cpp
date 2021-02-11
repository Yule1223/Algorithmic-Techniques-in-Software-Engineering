
// Yule Zhang

// Comentario general sobre la soluci€n,
// explicando c€mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <queue>
using namespace std;

int bfs(vector<int> const& casillas, int N, int K) {
    vector<int> pasos(N*N, 0);//vector para guardar numero de pasos de cada casilla
    queue<int> cola;
    int ini = 0;//primera casilla
    int fin = N * N - 1;//ultima casilla
    cola.push(ini);
    
    while (!cola.empty()) {
        int v = cola.front(); cola.pop();
       
        for (int i = 1; i <= K; i++) {
            int casillaAct = v + i;
            if (casillaAct < fin) {
                if(casillaAct != casillas[casillaAct]) {//hay escalera o serpiente, w seguramente es menor que fin
                    if (pasos[casillas[casillaAct]] == 0) {
                        int w = casillas[casillaAct];
                        pasos[w] = pasos[v] + 1;
                        cola.push(w);
                    }
                }
                else{//es casilla vacia
                    if (pasos[casillaAct] == 0) {
                        pasos[casillaAct] = pasos[v] + 1;
                        cola.push(casillaAct);
                    }
                }
            }
            else return pasos[v] + 1;
        }
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci€n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, K, S, E;
    cin >> N >> K >> S >> E;

    // fin de la entrada
    if (N == 0 && K == 0 && S == 0 && E == 0)
        return false;

    vector<int>casillas(N*N);//vector de casillas

    for (int i = 0; i < casillas.size(); i++) {
        casillas[i] = i;
    }

    for (int i = 0; i < S; i++) {
        int v, w;
        cin >> v >> w;
        casillas[v - 1] = w - 1;
    }

    for (int j = 0; j < E; j++) {
        int x, y;
        cin >> x >> y;
        casillas[x - 1] = y - 1;
    }

    cout << bfs(casillas, N, K) << "\n";

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
