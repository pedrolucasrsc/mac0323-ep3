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
  graph.quemComp(&elemComp);

  // Encontra índice de maior componente
  int imax = 0, max = 0;
  for (int i = 0; i < ncomp; i++)
	if (max < tamComp[i]) {
	  max = tamComp[i];
	  imax = i;
	}
  // calcula distâncias na maior componente
  int maxdist = 0, contadist6 = 0, media = 0, n = 0;
  std::string udistante, vdistante;
  for (int i = 0; i < tamComp[imax]; i++) {
    int iu = elemComp[imax].at(i);
    std::string u = graph.nomes[iu];
    //    std::cout << u << "\n";
    graph.distancias(u,&dist);
    for (int j = iu+1; j < V; j++) {
      if (maxdist < dist[j]) {
        maxdist = dist[j];
        vdistante = graph.nomes[j];
        udistante = u;
      }
      if (0 < dist[j]) {
        media += dist[j];
        n++;
        if (dist[j] <= 6)
          contadist6++;
      }
    }
  }
  media /= n;
  contadist6;
  
  std::cout << "O Grafo possuí:\n";
  std::cout << "\t" << V << " vértices\n";
  std::cout << "\t" << E << " arestas\n";
  std::cout << "\t" << ncomp << " componentes\n";
  std::cout << "A componente de " << udistante << " tem " << tamComp[imax] << " vértices, sobre a componente:\n";
  std::cout << "A média das distâncias entre dois vértices é de " << media << "\n";
  std::cout << "Há " << contadist6 << " conexões a uma distância de 6 graus ou menos\n";
  std::cout << udistante << "----" << vdistante << " tem a maior distância de " << maxdist << " na componente!!\n";
  
}
