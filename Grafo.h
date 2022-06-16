#ifndef GRAFO_H
#define GRAFO_H

#include "Bag.h"
#include "Fila.h"
#include "arvore23.h"
#include <iostream>

class Grafo {
 private:
  int V = 0, E = 0;
  void cal_dist(int u, int **dist);
 public:
  TsA23<std::string,int> dict;
  std::string *nomes = new std::string[0];
  Bag<int> *adj = new Bag<int>[0];
  Grafo() {};
  ~Grafo() {if (adj != nullptr) delete [] adj; if (nomes != nullptr) delete [] nomes;};
  // métodos
  void le();
  int vertices() {return V;};
  int edges() {return E;};
  void limpa();
  void distancias(std::string u, int **dist);
  void componentes(int *ncomp,int **comp);
  void qualComp(int **comp);
  void quemComp(Bag<int> **comp);
};

void Grafo::le() {
  // Lê grafo e retorna V
  std::cin >> V >> E;
  int contv = 0;
  adj = new Bag<int>[V];
  nomes = new std::string[V];
  for (int i = 0; i < E; i++) {
	std::string u, v;
	std::cin >> u >> v;
    if (!dict.isIn(u)) {
	  dict.add(u,contv);
	  nomes[contv++] = u;
	}
	if (!dict.isIn(v)) {
	  dict.add(v,contv);
	  nomes[contv++] = v;
	}
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
  // Vértice desconhecido
  if (!dict.isIn(u)) {
	// Vértice fora do Grafo
	if (dict.size() == V) {
	  int *dist;
	  dist = new int[V];
	  for (int i = 0; i < V; i++)
		dist[i] = -1;
      *distPointer = dist;
	  return;
	}
	// Assume que conhecemos esse vértice sem adjacências agora
	else {
	  dict.add(u,dict.size());
	}
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

void Grafo::qualComp(int **compPointer) {
  /* Recebe ponteiro para guardar no vetor comp[] qual componente está vertice i em comp[i] */
  int cont = 0, *comp;
  comp = new int[V];
  for (int i = 0; i < V; i++) {
	comp[i] = -1;
  }

  // percorre todos vértices não visitados
  for (int v = 0; v < V; v++)
	if (comp[v] == -1) {
	  // nova componente
	  comp[v] = cont++;
	  // bfs em v
	  Fila<int> fila;
	  fila.enqueue(v);
	  while(!fila.isEmpty()) {
		int u = fila.dequeue();
		for (int i = 0; i < adj[u].size(); i++) {
		  int v = adj[u].at(i);
		  if (comp[v] == -1) {
			comp[v] = comp[u];
			fila.enqueue(v);
		  }
		}
	  }
	}
  *compPointer = comp;
  return;
}

void Grafo::quemComp(Bag<int> **compPointer) {
  int cont = 0;
  bool visitado[V];
  Bag<int> *comp;
  comp = new Bag<int>[V];
  for (int i = 0; i < V; i++) {
	visitado[i] = false;
  }

  // percorre todos vértices não visitados
  for (int v = 0; v < V; v++)
	if (!visitado[v]) {
	  visitado[v] = true;
	  // nova componente
	  comp[cont].add(v);
	  // bfs em v
	  Fila<int> fila;
	  fila.enqueue(v);
	  while(!fila.isEmpty()) {
		int u = fila.dequeue();
		for (int i = 0; i < adj[u].size(); i++) {
		  int v = adj[u].at(i);
		  if (!visitado[v]) {
			visitado[v] = true;
			comp[cont].add(v);
			fila.enqueue(v);
		  }
		}
	  }
	  cont++;
	}
  *compPointer = comp;
  return;  
}

#endif
