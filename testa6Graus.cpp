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
    for (int j = iu+1; j < tamComp[imax]; j++) {
      int iv = elemComp[imax].at(j);
      if (maxdist < dist[iv]) {
        maxdist = dist[iv];
        vdistante = graph.nomes[iv];
        udistante = u;
      }
      if (0 < dist[iv]) {
        media += dist[iv];
        n++;
        if (dist[iv] <= 6)
          contadist6++;
      }
    }
  }
  media /= n;
  double porcentagem = (double)contadist6/n;
  contadist6;
  
  std::cout << "O Grafo possuí:\n";
  std::cout << "\t" << V << " vértices\n";
  std::cout << "\t" << E << " arestas\n";
  std::cout << "\t" << ncomp << " componentes\n";
  std::cout << "A componente de " << udistante << " tem " << tamComp[imax] << " vértices, sobre a componente:\n";
  std::cout << "A média das distâncias entre dois vértices é de " << media << "\n";
  std::cout << porcentagem*100 << "% das conexões a uma distância de 6 graus ou menos\n";
  std::cout << udistante << "----" << vdistante << " tem a maior distância de " << maxdist << " na componente!!\n";
  
}
