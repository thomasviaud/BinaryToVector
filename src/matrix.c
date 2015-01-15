#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../inc/pixel.h"
#include "../inc/matrix.h"

void alloc_matrix(uint8_t ***pA, uint32_t nl, uint32_t nc){
	int i ;
	*pA = (uint8_t **)malloc(nl * sizeof(uint8_t *)) ;
	for (i=0;i<nl;i++)
	{
		(*pA)[i] = (uint8_t *)malloc(nc * sizeof(uint8_t)) ;
	}
}

void alloc_label_matrix(t_pixel ***pA, uint32_t nl, uint32_t nc){
    int i;
    *pA = (t_pixel **)malloc(nl * sizeof(t_pixel *)) ;
    for (i=0;i<nl;i++)
    {
        (*pA)[i] = (t_pixel *)malloc(nc * sizeof(t_pixel)) ;
    }
}

void disp_matrix(uint8_t **pX, uint32_t nl, uint32_t nc){
	int i,j;
	for (i=0;i<nl;i++)
	{
		for(j=0;j<nc;j++)
		{
			if(pX[i][j])printf("%d ",pX[i][j]);
            else(printf("0 "));
		}
		printf("\n");
	}
	printf("\n");
}
void dup_matrix(uint8_t ** A, uint8_t **A_copy, uint32_t nl, uint32_t nc){
	int i;
	for(i=0;i<nl;i++) memcpy(&(A_copy[i][0]), &(A[i][0]), nl * sizeof(uint8_t));
}
void dup_matrix_wborders(uint8_t ** A, uint8_t **A_copy, uint32_t nl, uint32_t nc){
	int i;
	// Initialisation de la matrice A_copy
	// Colonnes
	for(i=0;i<nl+2;i++){
		A_copy[i][0]=0;
		A_copy[i][nc+1]=0;
	}
	// Lignes
	for(i=1;i<nc+1;i++){
		A_copy[0][i]=0;
		A_copy[nl+1][i]=0;
	}
	// Partie interne de la matrice
	for(i=0;i<nl;i++) memcpy(&(A_copy[i+1][1]), &(A[i][0]), (nl+2) * sizeof(uint8_t));
}