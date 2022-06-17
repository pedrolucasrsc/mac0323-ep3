#include "Grafo.h"
#include <iostream>
#include "Bag.h"

int main() {
  // Recebe grafo e realiza impressões sobre 6 graus de separação

  Grafo graph;
  graph.le();
  int V = graph.vertices(), E = graph.edges();
  int ncomp, *tamComp, *comp, *dist;
  tamComp = new int[V];
  comp = new int[V];
  dist = new int[V];
  Bag<int> *elemComp;
  elemComp = new Bag<int>[V];
  graph.componentes(&ncomp,&tamComp);
  graph.qualComp(&comp);
  graph.quemComp(&elemComp);

  // Encontra índice de maior componente
  int imax = 0, max = 0;
  for (int i = 0; i < ncomp; i++)
	if (max < tamComp[i]) {
	  max = tamComp[i];
	  imax = i;
	}
  // calcula distâncias a partir de vértice que está na maior componente
  int iu = elemComp[imax].at(0);
  std::string u = graph.nomes[iu];
  graph.distancias(u,&dist);
  
  std::cout << "O Grafo possuí:\n";
  std::cout << "\t" << V << " vértices\n";
  std::cout << "\t" << E << " arestas\n";
  std::cout << "\t" << ncomp << " componentes\n";
  int maxdist = 0, contadist6 = 0;
  std::string vdist = u;
  for (int i = 0; i < V; i++) {
	if (maxdist < dist[i]) {
	  maxdist = dist[i];
	  vdist = graph.nomes[i];
	}
	if (0 < dist[i] && dist[i] <= 6)
	  contadist6++;
  }
  std::cout << "A componente de " << u << " tem " << tamComp[comp[iu]] << " vértices:\n";
  std::cout << u << " está conectada a " << contadist6 << " vértices numa distâncias menor que 6\n";
  std::cout << u << "----" << vdist << " tem a maior distância de " << maxdist << " na componente!!\n";
}
