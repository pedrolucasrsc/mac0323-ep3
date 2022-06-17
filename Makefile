all: testaComponenteGig.out testa6Graus.out palavrasEncostadas.out arestasAleatorias.out

testaComponenteGig.out: Grafo.h Bag.h testaComponenteGig.cpp
	g++ -w -o testaComponenteGig.out testaComponenteGig.cpp

testa6Graus.out: Grafo.h testa6Graus.cpp
	g++ -w -o testa6Graus.out testa6Graus.cpp

palavrasEncostadas.out: Fila.h arvore23.h palavrasEncostadas.cpp
	g++ -w -o palavrasEncostadas.out palavrasEncostadas.cpp

arestasAleatorias.out: Grafo.h Fila.h arestasAleatorias.cpp
	g++ -w -o arestasAleatorias.out arestasAleatorias.cpp
clean:
	rm *.o

