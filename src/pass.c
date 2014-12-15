///////////////////////////////////////////////////////////
// pass.c                                                //
// Contient les fonctions relatives aux deux passes pour //
// retourner une matrice contenant les distances au fond //
// pour chaque pixel                                     //
///////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "../inc/pass.h"


void alloc_matrix(uint8_t ***pA, uint32_t nl, uint32_t nc)
{
	int i ;
	*pA = (uint8_t **)malloc(nl * sizeof(uint8_t *)) ;
	for (i=0; i<nl; i++)
	{
		(*pA)[i] = (uint8_t *)malloc(nc * sizeof(uint8_t)) ;
	}
}

void disp_matrix(uint8_t ***pX, uint32_t nl, uint32_t nc)
{
	int i,j;
	for (i=0;i<nl;i++)
	{
		for(j=0; j<nc;j++)
		{
			printf("%d ",(*pX)[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
//
// first_pass
// Prend en argument une matrice A, une matrice B et leur
// dimension, indique dans chaque pixel de la matrice B leur distance
// au fond de l'image en passant de haut en bas et de gauche à droite
//
void first_pass(uint8_t ***bin, uint8_t ***dist, uint32_t nl, uint32_t nc){
    int i,j;

    for(i=0;i<nl;i++){
        if((*bin)[i][0]==1){
            (*dist)[i][0]=1;
        }
        else{
            (*dist)[i][0]=0;
        }
    }

    for(j=0;j<nc;j++){
        if((*bin)[0][j]==1){
            (*dist)[0][j]=1;
        }
        else{
            (*dist)[0][j]=0;
        }
    }

    for(i=1;i<nl;i++){
        for(j=1;j<nc;j++){
            if((*bin)[i][j]==1){
                    (*dist)[i][j]=(int)fmin((*dist)[i-1][j],(*dist)[i][j-1])+1;
            }
            else{
                (*dist)[i][j]=0;
            }
        }
    }
}
//
// last_pass
// Prend en argument une matrice A, une matrice B et leur
// dimension, indique dans chaque pixel de la matrice B leur distance
// au fond de l'image en passant de bas en haut et de droite à gauche
//
void last_pass(uint8_t ***bin, uint8_t ***dist, uint32_t nl, uint32_t nc){
    int i,j;

    for(i=0;i<nl;i++){
        if((*bin)[i][nc-1]==1){
            (*dist)[i][nc-1]=1;
        }
        else{
            (*dist)[i][nc-1]=0;
        }
    }

    for(j=0;j<nc;j++){
        if((*bin)[nl-1][j]==1){
            (*dist)[nl-1][j]=1;
        }
        else{
            (*dist)[nl-1][j]=0;
        }
    }

    for(i=1;i<nl-1;i++){
        for(j=1;j<nc-1;j++){
            if((*bin)[i][j]==1){
                    (*dist)[i][j]=(int)fmin(fmin((*dist)[i+1][j]+1,(*dist)[i][j+1]+1),(*dist)[i][j]);
            }
            else{
                (*dist)[i][j]=0;
            }
        }
    }
}