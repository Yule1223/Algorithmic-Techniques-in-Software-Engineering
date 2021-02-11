
// Yule Zhang

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"  // propios o los de las estructuras de datos de clase
using namespace std;

class ColocarGuardias {
private:
	bool ok;
	vector<bool> visit;
	vector<bool> guardias;//true->hay guardia, false->no hay guardia
	int minim;

	void comprobarGuardias(Grafo const& g, int v, bool guardia, int& nTrue, int& nFalse) {
		visit[v] = true;
		//marcamos
		guardias[v] = guardia;
		
		//sumamos
		if (guardia)
			nTrue++;
		else
			nFalse++;
		//cambiamos el guardia
		if (guardia) guardia = false;
		else guardia = true;

		//recorremos sus adyacentes
		for (int w : g.ady(v)) {
			if (!visit[w]) {
				comprobarGuardias(g, w, guardia, nTrue, nFalse);
			}
			// si ya estaba marcado
			else {
				if (guardias[v] == guardias[w])
					ok = false;
			}
		}
	}
	
public:
	ColocarGuardias(Grafo const& g) : visit(g.V(), false), guardias(g.V(), false), ok(true), minim(0){
		bool guardia = false;
		
		for (int v = 0; v < g.V(); v++) {
			int nTrue = 0;
			int nFalse = 0;
			if (!visit[v]) {// si no esta marcado
				comprobarGuardias(g, v, guardia, nTrue, nFalse);
				minim += min(nTrue, nFalse);
			}
		}
	}

	bool esPosible() {
		return ok;
	}
	
	int minimo() {
		return minim;
	}
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
	Grafo g(cin);
    if (!cin)  // fin de la entrada
        return false;

	ColocarGuardias cGuardias(g);
    auto sol = cGuardias.esPosible();

	if (sol)
		cout << cGuardias.minimo() << '\n';
	else
		cout << "IMPOSIBLE" << '\n';

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
