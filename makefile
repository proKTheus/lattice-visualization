COMPILER = gcc
FLAGS = -Wall -O3 -mtune=native

LIB = -lgsl -lgslcblas -lm

triang:
	@${COMPILER} ${FLAGS} src/triang.c 		${LIB} -o rede-triang.out

honey:
	@${COMPILER} ${FLAGS} src/honeycomb.c ${LIB} -o rede-honeycomb.out

kagome:
	@${COMPILER} ${FLAGS} src/kagome.c 		${LIB} -o rede-kagome.out

moore:
	@${COMPILER} ${FLAGS} src/moore.c 		${LIB} -o rede-moore.out

neumann:
	@${COMPILER} ${FLAGS} src/neumann.c 	${LIB} -o rede-neumann.out

clean:
	@rm *.out
	@rm plt/*.png
	@rm dat/*.dat
