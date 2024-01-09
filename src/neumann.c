#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void op(int Nx, int valor, int right, int left, int top, int bot){
	int i, j, elem, rb;
	double x, y;
	char name[100];
	sprintf(name, "dat/neumann-rede%d-act%d.dat", Nx, valor);
	FILE *file= fopen(name, "w");

	for(j= 0; j<Nx; j++){
		for(i= 0; i<Nx; i++){
			x= i;
			y= j;
			elem= j*Nx+i;
			
			rb= 0;
			if(elem == valor){
				rb=1;}
//			if(elem == tr){
//				rb= 2;}
			if(elem == right){
				rb= 2;}
//			if(elem == br){
//				rb= 2;}
//			if(elem == bl){
//				rb= 2;}
			if(elem == left){
				rb= 2;}
//			if(elem == tl){
//				rb= 2;}
			if(elem == top){
				rb= 2;}
			if(elem == bot){
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
		
		int right, left, top, bot;
		int valor= atoi(argv[2]);
  	int Nx= atoi(argv[1]);
		int i= valor%Nx;
		int j= (valor-i)/Nx;

//	EQUAÇÃO:				j				*Nx + 		i
//	C.C. top:		(j-1+Nx)%Nx)*Nx + 		i
//	C.C. right:			j				*Nx + (i+1)%Nx

		top=		((j-1+Nx)%Nx)*Nx	+			i;								//top
//		tr= 		((j-1+Nx)%Nx)*Nx	+((i+1)%Nx); 						//top-right
		right= 	j*Nx							+((i+1)%Nx); 						//right
//		br= 		((j+1)%Nx)*Nx			+((i+1)%Nx);						//bot-right
		bot=		((j+1)%Nx)*Nx			+			i;								//bottom
//		bl= 		((j+1)%Nx)*Nx			+((i-1+Nx)%Nx);					//bot-left
		left= 	j*Nx							+((i-1+Nx)%Nx);					//left
//		tl= 		((j-1+Nx)%Nx)*Nx	+((i-1+Nx)%Nx);					//top-left

		op(Nx, valor, right, left, top, bot);
    return 0;
}

