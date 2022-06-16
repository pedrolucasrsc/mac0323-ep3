#include "Grafo.h"
#include <iostream>

int main() {
  /* Lê um grafo e realiza impressões sobre suas componentes */
  
  Grafo graph;
  graph.le();
  int V = graph.vertices(), E = graph.edges();
  int ncomp, *tamComp;
  tamComp = new int[V];
  graph.componentes(&ncomp,&tamComp);

  std::cout << "O Grafo possuí:\n";
  std::cout << "\t" << V << " vértices\n";
  std::cout << "\t" << E << " arestas\n";
  std::cout << "\t" << ncomp << " componentes\n";
  int max = 0;
  for (int i = 0; i < ncomp; i++)
	if (max < tamComp[i])
	  max = tamComp[i];
  std::cout << "Sua maior componente tem " << max << " vértices!!\n";
  
}
