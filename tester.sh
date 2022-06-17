#!/bin/bash

mkdir -p ./grafos6Graus

echo ---------TESTE--COMPONENTE--GIGANTE----------
let CONTADOR=1
for V in {256,512,1024,2048,4096,8192,16384}; do
	echo
	echo TESTE $CONTADOR:
	echo "    "V = $V
	echo "    "p = "(1-e)/V"
	./arestasAleatorias.out $V $(bc -l <<< "(1-0.1)/$V") | ./testaComponenteGig.out
	let CONTADOR=CONTADOR+1
	
	echo
	echo TESTE $CONTADOR
	echo "    "V = $V
	echo "    "p = "(1+e)/V"
	./arestasAleatorias.out $V $(bc -l <<< "(1+0.1)/$V") | ./testaComponenteGig.out
	let CONTADOR=CONTADOR+1
done
echo
echo ---------------------------------------------
echo
echo ---------------TESTE--6--GRAUS---------------
let CONTADOR=1
for grafo in $(ls grafos6Graus/); do
	echo
	echo TESTE $CONTADOR:
	echo "    "grafo: $grafo
	./testa6Graus.out < ./grafos6Graus/$grafo
	let CONTADOR=CONTADOR+1
done
echo
echo ---------------------------------------------

