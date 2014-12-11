///////////////////////////////////////////////////////////
// pixel.c                                                //
// Contient les fonctions relatives à la gestion des     //
// pixel                                               //
///////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "pixel.h"
#define N 8
#include "../list/list.h"

int main(){
    return EXIT_SUCCESS;
}
void alloc_matrix(uint8_t ***pA, uint32_t nl, uint32_t nc)
{
	int i ;
	*pA = (uint8_t **)malloc(nl * sizeof(uint8_t *)) ;
	for (i=0; i<nc; i++)
	{
		(*pA)[i] = (uint8_t *)malloc(nc * sizeof(uint8_t)) ;
	}
}

void disp_matrix(uint8_t ***pX, uint32_t nl, uint32_t nc)
{
	int i,j;
	for (i=0;i<nc;i++)
	{
		for(j=0; j<nl;j++)
		{
			printf("%d  ",(*pX)[i][j]);
		}
		printf("\n");
	}
}

char set_type(int l, int c, uint8_t ***dist){
	if((*dist)[l][c]>=1){
		return 1;
	}else{
		return 0;
	}
}

char set_border(int l, int c, uint8_t ***dist){
	if((*dist)[l][c]==1){
		return 1;
	}else if((*dist)[l][c]>1){
		return 2;
	}else{
		return 0;
	}
}

char set_mult(int l, int c, uint8_t ***dist){
	int i;
	int cpt=0;
	// Cas où les couples de pixels N,S et O,E sont deux à deux de même type (fond ou image)
	if((*dist)[l+1][c]==(*dist)[l-1][c]&&(*dist)[l][c+1]==(*dist)[l][c-1]){
		return 1;
	}
	// Cas où les pixels NO, NE, SE et SO sont contour et les pixels N,E,S,O dans le fond
	char model[N]={1,0,1,0,1,0,1,0};
	char dist_border[N];
	int coord[2*N]={-1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1};
	for(i=0;i<2*N;i+=2){
		dist_border[i/2]=(*dist)[l+coord[i]][c+coord[i+1]];
	}

	// Comparaison de dist_border à model
	i=0;
	while(dist_border[i]==model[i] && i<N){
		cpt++;
	}
	if(cpt==8){
		return 1;
	}
    return 0;
}

