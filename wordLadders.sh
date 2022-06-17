#!/bin/bash

mkdir -p ./grafos
mkdir -p ./listaDePalavras
for lista in $(ls "./listaDePalavras"); do
	./palavrasEncostadas.out < ./listaDePalavras/$lista > grafos/$lista
done
	
