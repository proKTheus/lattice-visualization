#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void op(int Nx, int valor, int v1, int v2, int v3, int v4, int dact, int dpasp, int dpasi){
	int i, j, elem, rb, desl, desl2, col;
	double x, y;
	char name[100];
	sprintf(name, "dat/kagome-rede%d-act%d.dat", Nx, valor);
	FILE *file= fopen(name, "w");

	for(j= 0; j<Nx; j++){
//	desl: deslocamento em X quando j= 3, 7, 11...
		desl=0;
		if(j%4==3){
			desl= 1;			
		}
//	desl2: Cte para que o calculo do elemento não se perca
		desl2= Nx*(j-j%2)/4;	
		
//	separação linhas pares e impares
		if(j%2==0){
			col= Nx;
		}else{
			col= Nx/2;	
		}
		
		for(i= 0; i<col; i++){ 
			if(j%2==0){				
				x= i;				
			}else{	
				x= 2*i+0.5+desl;
			}
							
			y= j*(sqrt(3));
			elem= j*Nx+i-desl2;
			
			rb= 0;
			if(elem == valor){
				rb=1;}
			if(elem == v1 || elem == v2 || elem == v3 || elem == v4){
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
		int v1, v2, v3, v4, dact, dpasi, dpasp;

				//v1  	= top-right			(para linhas impares)
				//v2	 	= top-left			(para linhas impares)
				//v3  	= bottom-right	(para linhas impares)
				//v4  	= bottom-left		(para linhas impares)
				//v1		= left					(para linhas pares)
				//v2		=	right					(para linhas pares)
				//v4		=	top						(para linhas pares)
				//v3		=	bottom				(para linhas pares)
				
				//dact	=	deslocamento ind. ativo
				//dpasp	= deslocamento ind. passivo para linha par
				//dpasi = deslocamento ind. passivo para linha impar
				
				//Esses 3 deslocamentos são necessários pois essa rede varia a
				//quantidade de colunas. Isso faz com que a equação j*Nx+i só 
				//funcione se subtraidas a uma dessas constantes, que valem:
				//0 			para as linhas 0 e 1
				//Nx*1/2	para as linhas 2 e 3
				//Nx*3/2	para as linhas 4 e 5
				//Nx*5/2	para as linhas 6 e 7

		int valor= atoi(argv[2]);
  	int Nx= atoi(argv[1]);
		int j= (int)((valor+Nx/2)/(Nx*3/2))+(int)(valor/(Nx*3/2));
		dact= (Nx/2)*(int)(valor/(Nx*3/2));
		int i= valor-j*Nx+dact;
	
		//"Condições de contorno" para deslocamento em linha par
		if(j==0){
			dpasp= Nx*Nx/4-Nx/2;			//deslocamento igual da ultima linha
		}else{
			dpasp= dact-Nx/2;
		}
		//"Condições de contorno" para deslocamento em linha impar
		if(j==Nx-1){
			dpasi= 0;					//deslocamento igual da primeira linha
		}else{
			dpasi= dact+Nx/2;
		}
		
		//Calculo vizinhança com C.C
		if(j%2==1){				//linha impar, que contém Nx/2 elementos
			v1= ((j-1+Nx)%Nx)*Nx 	+ ((2*i+1	+2*(dact%Nx)/Nx)%Nx)		- dact;		//top-right
			v2=	((j-1+Nx)%Nx)*Nx 	+ ((2*i		+2*(dact%Nx)/Nx+Nx)%Nx)	- dact;		//top-left
			v3= ((j+1)%Nx)*Nx 		+ ((2*i+1	+2*(dact%Nx)/Nx)%Nx)		- dpasi;	//bot-right
			v4= ((j+1)%Nx)*Nx 		+ ((2*i		+2*(dact%Nx)/Nx+Nx)%Nx)	- dpasi;	//bot-left
		}else{					//linha par
			v1= j*Nx							+ (i-1+Nx)%Nx	- dact;												//left
			v2= j*Nx							+ (i+1)%Nx 		- dact;												//right
			if(dact%Nx==0){  //quando linha j= 0, 4, 8, 12...
				v3= ((j-1+Nx)%Nx)*Nx	+(i/2-(1-i%2)+Nx/2)%(Nx/2) 	- dpasp;  		//bot
				v4= ((j+1)%Nx)*Nx			+((i-i%2)/2)%Nx 						- dact;				//top
			}else{					//quando linha j= 2, 6, 10, 14...
				v3= ((j-1+Nx)%Nx)*Nx	+(i-i%2)/2 										- dpasp;		//bot
				v4= ((j+1)%Nx)*Nx			+((i-1-(1-i%2))/2+Nx/2)%(Nx/2) - dact;		//top
			}
		}

		op(Nx, valor, v1, v2, v3, v4, dact, dpasi, dpasp);
    return 0;
}
