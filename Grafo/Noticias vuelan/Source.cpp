
// Yule Zhang

// Comentario general sobre la soluci€n,
// explicando c€mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"  // propios o los de las estructuras de datos de clase
using namespace std;

class Noticias {
private:
	vector<bool> visit;
	vector<int> res;//vector para guardar los datos de salida
	vector<int> datos;

	int comprobarAmigos(Grafo const& g, int v) {
		int tam = 1;
		visit[v] = true;
		datos.push_back(v);//para apuntar elementos del arbol conexo
		
		//recorremos sus adyacentes
		for (int w : g.ady(v)) {
			if (!visit[w]) {
				tam += comprobarAmigos(g, w);
			}
		}
		return tam;
	}

public:
	Noticias(Grafo const& g) : visit(g.V(), false), res(g.V(), 0), datos(0,0){
		for (int v = 0; v < g.V(); v++) {
			//si no esta marcado
			if (!visit[v]) {
				int nAmigos = comprobarAmigos(g, v);
				for (int i = 0; i < datos.size(); i++) {
					res[datos[i]] = nAmigos;
				}
				datos.resize(0);
			}
		}
	}

	void print() {
		cout << res[0];
		for (int i = 1; i < res.size(); i++) {
			cout << " " << res[i];
		}
		cout << '\n';
	}

};

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci€n, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	//Grafo g(cin);
	int N, M;
	cin >> N >> M;
	if (!cin)  // fin de la entrada
		return false;
	Grafo g(N);

	for (int i = 0; i < M; i++) {
		int num;
		cin >> num;
		//si en el grupo solo hay una persona o nadie no hacemos nada
		if (num == 1) {
			int n;
			cin >> n;
		}
		if (num != 0 && num != 1) {
			vector<int>datos;
			for (int j = 0; j < num; j++) {
				int m;
				cin >> m;
				datos.push_back(m);
			}
			for (int x = 0; x < num - 1; x++) {
				g.ponArista(datos[x] - 1, datos[x + 1] - 1);
			}
		}
	}

	Noticias noticia(g);
	noticia.print();

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
