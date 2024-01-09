#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void op(int Nx, int valor, int tr, int right, int br, int bl, int left, int tl){
	int i, j, elem, rb;
	double x, y;
	char name[100];
	sprintf(name, "dat/triang-rede%d-act%d.dat", Nx, valor);
	FILE *file= fopen(name, "w");

	for(j= 0; j<Nx; j++){
		for(i= 0; i<Nx; i++){
			x= i+0.5*(j%2);
			y= j*(sqrt(3/2));
			elem= j*Nx+i;
			
			rb= 0;
			if(elem == valor){
				rb=1;}
			if(elem == tr){
				rb= 2;}
			if(elem == right){
				rb= 2;}
			if(elem == br){
				rb= 2;}
			if(elem == bl){
				rb= 2;}
			if(elem == left){
				rb= 2;}
			if(elem == tl){
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
		
		int tr, right, br, bl, left, tl;
		int valor= atoi(argv[2]);
  	int Nx= atoi(argv[1]);
		int i= valor%Nx;
		int j= (valor-i)/Nx;

//	EQUAÇÃO:				j				*Nx + 		i
//	C.C. top:		(j-1+Nx)%Nx)*Nx + 		i
//	C.C. right:			j				*Nx + (i+1)%Nx

		tr= 		((j-1+Nx)%Nx)*Nx	+((i+(j%2))%Nx); 				//top-right
		right= 	j*Nx							+((i+1)%Nx); 						//right
		br= 		((j+1)%Nx)*Nx			+((i+(j%2))%Nx);				//bot-right
		bl= 		((j+1)%Nx)*Nx			+((i-1+Nx+(j%2))%Nx);		//bot-left
		left= 	j*Nx							+((i-1+Nx)%Nx);					//left
		tl= 		((j-1+Nx)%Nx)*Nx	+((i-1+Nx+(j%2))%Nx);		//top-left

		op(Nx, valor, tr, right, br, bl, left, tl);
    return 0;
}

