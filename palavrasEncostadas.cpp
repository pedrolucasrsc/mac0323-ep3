#include <iostream>
#include <vector>
#include "arvore23.h"
#include "Fila.h"

int main() {

  /*

    Lerá entrada padrão no seguinte formato:

    N
    palavra1
    .
    .
    .
    palavraN

    e produzirá entrada padrão para grafo de acordo
    com as palavras que estarão encostadas:

   */

  TsA23<std::string,std::vector<std::string>> dict;
  int V, E = 0;

  std::cin >> V;
  for (int v = 0; v < V; v++) {
	std::string word;
    std::cin >> word;
    for (int i = 0; i < word.length(); i++) {
      std::string bucket;
      bucket = word.substr(0,i) + "_" + word.substr(i+1,word.length()-i-1);
      if (dict.isIn(bucket)) {
		std::vector<std::string> wv;
		wv = dict.value(bucket);
		wv.push_back(word);
  		dict.add(bucket,wv);
	  }
      else {
    	std::vector<std::string> wv;
    	wv.push_back(word);
	    dict.add(bucket,wv);
      }
    }
  }

  Fila<std::string> fila;
  for (int i = 0; i < dict.size(); i++) {
	std::string bucket = dict.select(i);
	std::vector<std::string> wv;
	wv = dict.value(bucket);
	for (int iw = 0; iw < wv.size(); iw++) {
	  for (int jw = iw+1; jw < wv.size(); jw++) {
		std::string u = wv[iw], v = wv[jw];
		//	std::cout << u << " " << v << "\n";
		fila.enqueue(u);
		fila.enqueue(v);
		E++;
	  }
	}
  }

  std::cout << V << " " << E << "\n";
  while (!fila.isEmpty()) {
	std::string u = fila.dequeue(), v = fila.dequeue();
   	std::cout << u << " " << v << "\n";
  }
  
}
