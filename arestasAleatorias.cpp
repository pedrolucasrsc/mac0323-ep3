#include <iostream>
#include <time.h>
#include "Grafo.h"
#include "Fila.h"
#include <cstdlib>

void comp_gig(int V, double p) {

  int E = 0;
  Fila<int> fila;
  // Percorre todas as possíveis adjacências
  for (int i = 0; i < V; i++)
	for (int j = i+1; j < V; j++) {
	  double chance = (double) std::rand()/RAND_MAX;
	  // Guarda adjacência em fila para imprimir primeiro E
	  if (chance < p) {
		fila.enqueue(i);
		fila.enqueue(j);
		E++;
	  }
	}

  // Saída de Grafo
  std::cout << V << " " << E << "\n";
  while (!fila.isEmpty()) {
	int u = fila.dequeue(), v = fila.dequeue();
	std::cout << u << " " << v << "\n";
  }
  
  return;
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
	std::cout << "componenteGigange.cpp precisa de 2 argumentos\n";
	std::cout << "./compGig V p\n";
	return 1;
  }
  
  int V = std::atoi(argv[1]);
  double p = std::atof(argv[2]);
  std::srand((unsigned)time(NULL));

  comp_gig(V,p);

  return 0;
}
