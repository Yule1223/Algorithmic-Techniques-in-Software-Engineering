
// Yule Zhang

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Grafo.h"
using namespace std;

class ArbolLibre {
private:
	vector<bool>visit;
	bool ok;

	void dfs(Grafo const& g, int v) {
		visit[v] = true;
		for (int w : g.ady(v)) {
			if (!visit[w]) {
				dfs(g, w);
			}
		}
	}
public:
	ArbolLibre(Grafo const& g) : visit(g.V(), false), ok(false) {
		int veces = 0;//para saber si un arbol es conexo
		for (int v = 0; v < g.V(); v++) {
			if (!visit[v]) {
				veces++;//si veces igual que 1, el arbol es conexo
				dfs(g, v);
			}
		}
		//cout << maxim << " " << g.V()<< endl;
		//cout << veces << endl;
		if (g.A() == g.V() - 1 && veces == 1)
			ok = true;
	}

	bool esArbolLibre() const {
		return ok;
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	
	Grafo grafo(cin);
	if (!cin)
		return false;
	/*
	int V;//numero de vertices
	int	A;//numero de aristas
	cin >> V >> A;
	if (!cin)
		return false;

	int v, w;//los extremos de aristas
	Grafo grafo(V);

	for (int i = 0; i < A; i++) {
		cin >> v >> w;
		grafo.ponArista(v, w);//O(1)
	}
	*/
	ArbolLibre arbol(grafo);
	bool sol = arbol.esArbolLibre();

	if (sol)
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