#!/bin/bash

echo ---------TESTE--COMPONENTE--GIGANTE----------
for V in {256,512,1024,2048,4096,8192,16384}; do
	for P in {1-0.1/V,1+0.1/V}; do
		echo
		./arestasAleatorias.out $V $P | ./testeComponenteGig.out
	done
done
echo ---------------------------------------------
echo
echo ---------------TESTE--6--GRAUS---------------
