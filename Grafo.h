#ifndef GRAFO_H
#define GRAFO_H

#include "Bag.h"
#include "Fila.h"
#include "arvore23.h"
#include <iostream>

class Grafo {
 private:
  int V = 0, E = 0;
  TsA23<std::string,int> dict;
  void cal_dist(int u, int **dist);
 public:
  Bag<int> *adj = new Bag<int>[0];
  Grafo() {};
  ~Grafo() {if (adj != nullptr) delete [] adj;};
  // métodos
  void le();
  int vertices() {return V;};
  int edges() {return E;};
  void limpa();
  void distancias(std::string u, int **dist);
  void componentes(int *ncomp,int **comp);
};

void Grafo::le() {
  // Lê grafo e retorna V
  std::cin >> V >> E;
  int contv = 0;
  adj = new Bag<int>[V];
  for (int i = 0; i < E; i++) {
	std::string u, v;
	std::cin >> u >> v;
    if (!dict.isIn(u))
	  dict.add(u,contv++);
	if (!dict.isIn(v))
	  dict.add(v,contv++);
	int iu = dict.value(u), iv = dict.value(v);
	adj[iu].add(iv);
	adj[iv].add(iu);
  }
  return;
}

void Grafo::limpa() {
  V = E = 0;
  adj = new Bag<int>[0];
  dict = TsA23<std::string,int>();
}

void Grafo::distancias(std::string u, int **distPointer) {
  if (!dict.isIn(u)) {
	int *dist;
	dist = new int[V];
	for (int i = 0; i < V; i++)
	  dist[i] = -1;
	*distPointer = dist;
	return;
  }
  return cal_dist(dict.value(u), distPointer);
}

void Grafo::cal_dist(int u, int **distPointer) {
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
  int cont = 0, *comp;
  comp = new int[V];
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

#endif
