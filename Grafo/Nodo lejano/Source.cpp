
// Yule Zhang

// Comentario general sobre la soluci€n,
// explicando c€mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Grafo.h"  // propios o los de las estructuras de datos de clase
using namespace std;

class Redes {
private:
	vector<bool> visit;
	vector<int> ant;
	vector<int> dist;
	int s;
	int ttl;
	int nNodosVisitados;

	void bfs(Grafo const& g) {
		queue<int> q;
		dist[s] = 0; visit[s] = true;
		q.push(s);
		bool ok = true;
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int w : g.ady(v)) {
				if (!visit[w] && (dist[v] + 1 <= ttl)) {
					ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
					nNodosVisitados++;
					q.push(w);
				}
			}
		}
	}
public:
	Redes(Grafo const& g, int nodoIni, int TTL) : visit(g.V(), false), ant(g.V()), dist(g.V()), s(nodoIni), ttl(TTL), nNodosVisitados(0) {
		bfs(g);
		/*
		for (int i = 0; i < visit.size(); i++) {
			cout << visit[i] << " ";
		}
		cout << endl;
		*/
		cout << g.V() - nNodosVisitados - 1 << '\n';
	}

};

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci€n, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	Grafo g(cin);
	if (!cin)  // fin de la entrada
		return false;

	int nConsulta;
	cin >> nConsulta;
	for (int i = 0; i < nConsulta; i++) {
		int nodoIni, TTL;
		cin >> nodoIni >> TTL;
		Redes redes(g, nodoIni-1, TTL);
		
	}
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
