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
#include "pass.h"

int main(){
    uint8_t **img_dist,**img_bin;
    uint32_t nl=4,nc=4;
    alloc_matrix(&img_dist,nl,nc);
    alloc_matrix(&img_bin,nl,nc);

    img_bin[0][0]=0;
    img_bin[0][1]=1;
    img_bin[0][2]=1;
    img_bin[0][3]=1;
    img_bin[1][0]=1;
    img_bin[1][1]=1;
    img_bin[1][2]=1;
    img_bin[1][3]=1;
    img_bin[2][0]=1;
    img_bin[2][1]=1;
    img_bin[2][2]=1;
    img_bin[2][3]=0;
    img_bin[3][0]=1;
    img_bin[3][1]=1;
    img_bin[3][2]=1;
    img_bin[3][3]=1;

    printf("Matrice img_bin : \n");
    disp_matrix(&img_bin,nl,nc);
    first_pass(&img_bin, &img_dist,nl,nc);

    printf("Passe avant : \n");
    disp_matrix(&img_dist,nl,nc);
    last_pass(&img_bin, &img_dist,nl,nc);

    printf("Passe arriere et matrice img_dist: \n");
    disp_matrix(&img_dist,nl,nc);
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
