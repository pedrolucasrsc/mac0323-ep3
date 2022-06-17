#!/bin/bash

mkdir -p ./grafos
for V in {256,512,1024,2048,4096,8192,16384}; do
	./arestasAleatorias.out $V $(bc -l <<< "(1-0.1)/$V") > ./grafos/$(echo $V)"minusE.txt"
	./arestasAleatorias.out $V $(bc -l <<< "(1+0.1)/$V") > ./grafos/$(echo $V)"plusE.txt"	
done
./arestasAleatorias.out 100000 $(bc -l <<< "50/100000") > ./grafos/redeSocial.i
./arestasAleatorias.out 60 $(bc -l <<< "3/60") > ./grafos/salaDeAula.i

