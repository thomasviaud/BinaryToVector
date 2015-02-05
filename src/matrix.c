///////////////////////////////////////////////////////////
// matrix.c                                              //
// Contient les fonctions relatives aux 				 //
// manipulations de matrices 							 //
///////////////////////////////////////////////////////////

#include "../inc/matrix.h"

//
// alloc_matrix
// Alloue une matrice de uint8_t de taille nl*nc
//
void alloc_matrix(uint8_t ***pA, uint32_t nl, uint32_t nc){
	int i ;
	*pA = (uint8_t **)malloc(nl * sizeof(uint8_t *)) ;
	for (i=0;i<nl;i++)
	{
		(*pA)[i] = (uint8_t *)malloc(nc * sizeof(uint8_t)) ;
	}
}

//
// alloc_label_matrix
// Alloue une matrice de t_pixel de taille nl*nc
//
void alloc_label_matrix(t_pixel ***pA, uint32_t nl, uint32_t nc){
    int i;
    *pA = (t_pixel **)malloc(nl * sizeof(t_pixel *)) ;
    for (i=0;i<nl;i++)
    {
        (*pA)[i] = (t_pixel *)malloc(nc * sizeof(t_pixel)) ;
    }
}

//
// alloc_point_matrix
// Alloue une matrice de t_point de taille nl*nc
//
void alloc_point_matrix(t_point ***pA, uint32_t nl, uint32_t nc){
	int i;
    *pA = (t_point **)malloc(nl * sizeof(t_point *)) ;
    for (i=0; i<nl; i++)
    {
        (*pA)[i] = (t_point *)malloc(nc * sizeof(t_point)) ;
    }
}

//
// disp_matrix
// Affiche une matrice de uint8_t de taille nl*nc
//
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

//
// dup_matrix
// Duplique une matrice A dans une matrice A_copy passée en paramètre de taille nl*nc
//
void dup_matrix(uint8_t ** A, uint8_t **A_copy, uint32_t nl, uint32_t nc){
	int i;
	for(i=0;i<nl;i++) memcpy(&(A_copy[i][0]), &(A[i][0]), nl * sizeof(uint8_t));
}

//
// dup_matrix_wborders
// Duplique une matrice A dans une matrice A_copy passée en paramètre de taille nl+1*nc+1 entourée d'une ligne de 0
//
void dup_matrix_wborders(uint8_t ** A, uint8_t **A_copy, uint32_t nl, uint32_t nc){
	int i,j;
	// Initialisation de la matrice A_copy
	// Colonnes
	for(i=0;i<nl+2;i++){
		A_copy[i][0]=0;
		A_copy[i][nc+1]=0;
	}
	// Lignes
	for(i=1;i<nc+2;i++){
		A_copy[0][i]=0;
		A_copy[nl+1][i]=0;
	}
	// Partie interne de la matrice
	for(i=1;i<nl+1;i++){
		for(j=1;j<nc+1;j++){
			A_copy[i][j]=A[i-1][j-1];
		}
	}
}
