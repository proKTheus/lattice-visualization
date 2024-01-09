#!/bin/bash
#
#vis.sh - Shell para visualizar diferentes redes pelo gnuplot
#
# Criado em     : 2023/11/08
# Atualizado		: 2023/11/08
# Autor		      : Matheus <matheuslucasgp@gmail.com>
#----------------------------------------
# Notas:
#
#----------------------------------------
# Exemplo:
# ./vis.sh 1 8  gera todos os ind. ativos de rede 8x8 triangular 
#----------------------------------------
# Histórico:
#
#----------------------------------------

#---CHAVES---
if [[ $1 -eq 1 ]]; then TRIAN=1; fi
if [[ $1 -eq 2 ]]; then HONEY=1; fi
if [[ $1 -eq 3 ]]; then KAGOM=1; fi
if [[ $1 -eq 4 ]]; then MOORE=1; fi
if [[ $1 -eq 5 ]]; then NEUMN=1; fi
if [[ $1 -eq 6 ]]; then 					
	TRIAN=1;
 	HONEY=1;
 	KAGOM=1;
	MOORE=1;
	NEUMN=1;
fi

#---VERIFICAÇÕES---
#quantidade de termos
if [[ $# -ne 2 || $(($2 % 2)) -ne 0 ]]; then 
	echo
	echo "Uso: $0 <Tipo rede> <Tamanho rede>"
	echo
	echo "Tipo = 1 : Rede Triangular"
	echo "Tipo = 2 : Rede Favo de mel"
	echo "Tipo = 3 : Rede Kagomé"
	echo "Tipo = 4 : Rede Moore"
	echo "Tipo = 5 : Rede Neumann"
	echo "Tipo = 6 : Todas as redes"
 	echo
	echo "OBS.: Tamanho Rede DEVE ser par."	
	exit 1
fi 

#---Rede Triangular---

if [[ $TRIAN -eq 1 ]]; then
	echo "Executando rede triangular $2 X $2..."
	make triang
	for (( i = 0; i < $(($2*$2)); i++ ))
	do				
		./rede-triang.out $2 $i
		cd plt/
		gnuplot -c rede-triang.plt $2 $i
		cd ..
	done
fi

#---Rede Honey---

if [[ $HONEY -eq 1 ]];
then
	echo "Executando rede honeycomb $2 X $2..."
	make honey
	for (( i = 0; i < $(($2*$2)); i++ ))
	do				
		./rede-honeycomb.out $2 $i
		cd plt/
		gnuplot -c rede-honey.plt $2 $i
		cd ..
	done
fi

#---Rede Kagomé---

if [[ $KAGOM -eq 1 ]];
then
	echo "Executando rede kagomé $2 X $2..."
	make kagome
	for (( i = 0; i < $((3*$2*$2/4)); i++ ))
	do				
		./rede-kagome.out $2 $i
		cd plt/
		gnuplot -c rede-kagome.plt $2 $i
		cd ..
	done
fi

#---Rede Moore---

if [[ $MOORE -eq 1 ]]; then
	echo "Executando rede Moore $2 X $2..."
	make moore
	for (( i = 0; i < $(($2*$2)); i++ ))
	do				
		./rede-moore.out $2 $i
		cd plt/
		gnuplot -c rede-moore.plt $2 $i
		cd ..
	done
fi

#---Rede Neumann---

if [[ $NEUMN -eq 1 ]]; then
	echo "Executando rede Neumann $2 X $2..."
	make neumann
	for (( i = 0; i < $(($2*$2)); i++ ))
	do				
		./rede-neumann.out $2 $i
		cd plt/
		gnuplot -c rede-neumann.plt $2 $i
		cd ..
	done
fi

