#include "Bag.h"
#include "Fila.h"
#include <iostream>

class Grafo {
 private:
 public:
  int V = 0, E = 0;
  Bag<int> *adj = nullptr;
  Grafo() {};
  ~Grafo() {if (adj != nullptr) delete [] adj;};
  // métodos
  void le();
  void limpa();
  void distancias(int u, int **dist);
  void componentes(int *ncomp,int **comp);
};

void Grafo::le() {
  std::cin >> V >> E;
  adj = new Bag<int>[V];
  for (int i = 0; i < E; i++) {
	int u,v;
	std::cin >> u >> v;
	adj[u].add(v);
	adj[v].add(u);
  }
}

void Grafo::limpa() {
  V = E = 0;
  adj = nullptr;
}

void Grafo::distancias(int u, int **distPointer) {
  /*
   *  recebe vértice e apontador para vetor das distâncias
   *  devolve o vetor de distâncias ao vértice u
   */
  int *dist;
  dist = new int[V];
  for (int i = 0; i < V; i++)
	dist[i] = -1;
  dist[u] = 0; // distância de u a si é 0
  Fila<int> fila(V);
  fila.enqueue(u); // bfs em u
  
  while(!fila.isEmpty()) {
	u = fila.dequeue();
	for (int i = 0; i < adj[u].size(); i++) {
	  int v = adj[u].at(i);
	  if (dist[v] == -1) { // vértice não visitado
		fila.enqueue(v);
		dist[v] = dist[u]+1; // tem distância de seu pai + 1
	  }
	}
  }
  *distPointer = dist;
  return;
}

void Grafo::componentes(int *ncomp,int **compPointer) {
  /*
   *  recebe ponteiro para #componentes e vetor comp[V]
   *  devolve o vetor com o tamanho de cada componente
   */
  int cont = 0, comp[V];
  bool visitado[V];
  for (int i = 0; i < V; i++) {
	visitado[i] = false;
	comp[i]     = 0;
  }
   
  for (int u = 0; u < V; u++)
	// visita todos vértices não visitados
	if (!visitado[u]) {
	  visitado[u] = true;
	  // nova componente com pelo menos um vértice
	  comp[cont]++;
	  // bfs em u
	  Fila<int> fila(V);
	  fila.enqueue(u); 

	  while(!fila.isEmpty()) {
		u = fila.dequeue();
		for (int i = 0; i < adj[u].size(); i++) {
		  int v = adj[u].at(i);
		  if (!visitado[v]) {
			visitado[v] = true;
			fila.enqueue(v);
			comp[cont]++; // incrementa o tamanho desta componente
		  }
		}
	  }
	  cont++;
	}

  *ncomp = cont;
  *compPointer = comp;
  return;
}
