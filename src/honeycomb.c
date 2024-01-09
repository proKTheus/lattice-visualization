#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void op(int Nx, int valor, int cim, int bai, int hor){
	int i, j, elem, rb, desl;
	double x, y;
	char name[100];
	sprintf(name, "dat/honey-rede%d-act%d.dat", Nx, valor);
	FILE *file= fopen(name, "w");

	for(j= 0; j<Nx; j++){
		if(j%2==0){
			desl= 1;			
		}else{
			desl= 0;
		}
		for(i= 0; i<Nx; i++){
			x= i+desl;
			y= j*(sqrt(3));
			elem= j*Nx+i;
			
			if(i%2!=j%2){
				desl+= 2;			
			}
			
			rb= 0;
			if(elem == valor){
				rb=1;}
			if(elem == cim){
				rb= 2;}
			if(elem == bai){
				rb= 2;}
			if(elem == hor){
				rb= 2;}

			fprintf(file, "%e %e %d %d %d %d\n", x, y, rb, elem, j, i);
		}
	}
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <tam rede><ind actv>\n", argv[0]);
        return 1;
    }

		int cim, bai, hor;
		int valor= atoi(argv[2]);
  	int Nx= atoi(argv[1]);
		int i= valor%Nx;
		int j= (valor-i)/Nx;

//	EQUAÇÃO:				j				*Nx + 		i
//	C.C. top:		(j-1+Nx)%Nx)*Nx + 		i
//	C.C. right:			j				*Nx + (i+1)%Nx

// 	Calculo da vizinhança com C.C.

		cim=	((j-1+Nx)%Nx)*Nx	+i;														//cima
		bai=	((j+1)%Nx)*Nx			+i;														//baixo
		if(i%2==j%2){
			hor= j*Nx + (i+1)%Nx;												//horiz-dir	
		}else{
			hor= j*Nx + (i-1+Nx)%Nx;										//horiz-esq
		}
		op (Nx, valor, cim, bai, hor);		
		return 0;
}

