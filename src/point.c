#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../inc/pixel.h"
#include "../inc/point.h"
#define N 8
#define N_coin 3
#define N_bord 5
void alloc_point_matrix(t_point ***pA, uint32_t nl, uint32_t nc){
	int i;
    *pA = (t_point **)malloc(nl * sizeof(t_point *)) ;
    for (i=0; i<nl; i++)
    {
        (*pA)[i] = (t_point *)malloc(nc * sizeof(t_point)) ;
    }

}

void set_point_matrix(t_point ** img_point_matrix, t_pixel ** img_label_matrix, uint32_t nl, uint32_t nc){
	uint32_t i,j;
	// Initialisation 
	// Partie interne de la matrice
	for(i=0;i<nl;i++){
		for(j=0;j<nc;j++){
			img_point_matrix[i][j].type=set_point(img_label_matrix,i,j);
			img_point_matrix[i][j].is_done=0;
		}
	}
	disp_point_matrix(img_point_matrix,nl,nc);
}

char set_point(t_pixel ** img_label_matrix, uint32_t l, uint32_t c){

	int i;
	int cpt=0;
	// Le tableau voisins contiendra 1 pour tous les voisins du pixel img_label_matrix[l][c] en partant
	// du voisin NO dans le sens des aiguilles d'une montre
	int voisins[N];
	// Si le pixel n'appartient pas au squelette
	if(img_label_matrix[l][c].obj.squel!=2) return 4;
	// Initialisation de voisins
	for(i=0;i<N;i++) voisins[i]=0;
	// Coordonnées des pixels voisins au pixel img_label_matrix[l][c]
	int coord[2*N]={-1,-1, -1,0, -1,1, 0,1, 1,1, 1,0, 1,-1, 0,-1};

	// Remplissage du tableau de voisins en connexité 8
	for(i=0;i<2*N;i+=2){
		if(img_label_matrix[l+coord[i]][c+coord[i+1]].obj.squel==2) voisins[i/2]=1;	
	}	
	// Suppression des pixels en connexité 8 qui sont voisins de ceux en connexité 4
	for(i=1;i<N;i+=2){
		if(voisins[i]==1){
			voisins[(i-1)%N]=0;
			voisins[(i+1)%N]=0;
		}
	}
	// Comptage du nombre de voisins
	for(i=0;i<N;i++) if(voisins[i]==1) cpt++;
	// Attribution du label	
			// Bifurcation	
	if(cpt>2) return 3;
	else if(cpt==2){
		// Récupération du premier voisin
		i=0;
		while(voisins[i]==0) i++;
		// Vérification de l'état du voisin en face et retour en fonction de sa valeur
			// Point
		if(voisins[(i+4)%N]==1) return 0;
			// Noeud
		else return 2;
	}
			// Borne
	else if(cpt==1) return 1;
			// Point seul
	return 0;
}
void print_point(t_point ** point, uint32_t l, uint32_t c){
	if(point[l][c].type==1) (void)printf("Bo  ");
	else if(point[l][c].type==2) (void)printf("No  ");
	else if(point[l][c].type==3) (void)printf("Bi  ");
	else if(point[l][c].type==0) (void)printf("Po  ");
	else if(point[l][c].type==4) (void)printf("--  ");
}

void disp_point_matrix(t_point ** point, uint32_t nl, uint32_t nc){
	int i,j;
	for(i=0;i<nl;i++){
		for(j=0;j<nc;j++){
			print_point(point,i,j);
		}
		(void)printf("\n\n");
	}
}