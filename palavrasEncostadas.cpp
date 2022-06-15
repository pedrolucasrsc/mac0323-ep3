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

  Ts23<std::string,std::vector<std::string>> dict;
  int V, E = 0, word;

  std::cin >> V;
  for (int v = 0; v < V; v++) {
    std::cin >> word;
    for (int i = 0; i < word.length(); i++) {
      std::string bucket;
      bucket = word.substr(0,i) + "_" + word.substr(i+1,word.length()-i-1);
      if (dict.isIn(bucket))
	dict.value(bucket).push_back(word);
      else {
	std::vector<std::string> wv;
	wv.push_back(word);
	dict.add(bucket,wv);
      }
    }
  }

  Fila<std::string> vAdj;
  for 
  
}
