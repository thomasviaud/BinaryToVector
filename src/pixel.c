///////////////////////////////////////////////////////////
// pixel.c                                               //
// Contient les fonctions relatives à la gestion des     //
// pixel                                               	 //
///////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#define N1 4
#define N2 8
#include "../inc/pixel.h"
#include "../inc/matrix.h"
#include "../inc/list.h"

//
// set_border
// Prend en argument une matrice, ainsi que la paire de coordonnées d'une case
// de celle-ci
// Retourne 2 si le pixel est dans le contour, 3 s'il est interne. 
//
char set_border(uint8_t **dist, uint32_t l, uint32_t c){
	if(dist[l][c]==1){
		return 2;
	}else{
		return 3;
	}
}
//
// set_mult
// Prend en argument une matrice, ainsi que la paire de coordonnées d'une case
// de celle-ci
// Retourne 2 si le pixel est un pixel multiple, 1 sinon.
//
char set_mult(uint8_t **dist, uint32_t l, uint32_t c){

// Déclarations
	int i;
	// Compteur de comparaison entre les modèles et les tableaux des voisins
	int cpt1=0;
	int cpt2=0;
	// Modèle du type des pixels dans le cas 2
	char model[N2]={1,0,1,0,1,0,1,0};
	// Tableau des voisins à utiliser pour vérifier la multiplicité
	char dist_border1[2*N1];
	char dist_border2[N2];
	// Tableau contenant les paires de coordonnées à utiliser pour vérifier la
	// multiplicité
	int coord_cas1[2*N1]={-1,0,0,1,1,0,0,-1};
	int coord_cas2[2*N2]={-1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1};
/* ***************** */

// Opérations
	//
	// Cas où les couples de pixels N,S et O,E sont deux à deux pas "Fond 
	// et Interne"
	//

	// Création du tableau contenant les voisins du pixel dist[l][c] dans 
	// l'ordre horaire
	for(i=0;i<2*N1;i+=2){
		dist_border1[i/2]=dist[l+coord_cas1[i]][c+coord_cas1[i+1]];
	}

	// Vérification des labels Fond et Interne
	for(i=0;i<N1/2;i++){
		// Voisins de type 0 - 1
		if(dist_border1[i]==0 && dist_border1[i+2]==1) cpt1++;
		// Voisins de type 1 - 0
		else if(dist_border1[i+2]==0 && dist_border1[i]==1) cpt1++;
		// Voisins de type 2+ - 1
		else if(dist_border1[i+2]==1 && dist_border1[i]>1) cpt1++;
		// Voisins de type 1 - 2+
		else if(dist_border1[i]==1 && dist_border1[i+2]>1) cpt1++;		
		// Voisins de type x - x
		else if(dist_border1[i]==dist_border1[i+2]) cpt1++;
	}
	
	//
	// Cas où les pixels NO, NE, SE et SO sont contour et les pixels N,E,S,O dans le fond
	//
	for(i=0;i<2*N2;i+=2){
		dist_border2[i/2]=dist[l+coord_cas2[i]][c+coord_cas2[i+1]];
	}
	// Comparaison entre dist_border2 et la chaîne model
	for(i=0;i<N2+1;i++){
		if(dist_border2[i]==model[i]){
			cpt2++;
		}
	}
	if(cpt2==8 || cpt1==2){
		return 2;
	}else{
	return 1;
	}
}
//
// set_squel
// Prend en argument une matrice, ainsi que la paire de coordonnées d'une case
// de celle-ci
// Retourne 2 si le pixel est un pixel du squelette, 1 sinon.
//
char set_squel(t_pixel **pix, uint32_t l, uint32_t c){
	if(pix[l][c].obj.mult==2) return 2;
	return 1;
}
//
// print_pixel
// Prend en argument un pixel dans un tableau de pixel
// et l'affiche dans la console sous le format TYPE CONTOUR MULTIPLE
//
void print_pixel(t_pixel **pix, uint32_t l, uint32_t c){
			if(pix[l][c].obj.border==1){
				(void)printf("    ");
				return;
			}else{
				(void)printf("O");
			}
			if(pix[l][c].obj.border==2){
				(void)printf("C");
				if(pix[l][c].obj.mult==2){
				(void)printf("M ");
				}else{				
				(void)printf("- ");
				}
			}else if(pix[l][c].obj.border==3){
				(void)printf("I  ");
			}
			
}

//
// print_pixel_list
// Prend en argument un pixel
// et l'affiche dans la console sous le format TYPE CONTOUR MULTIPLE
//
void print_pixel_list(t_pixel pix){
	if(pix.obj.border==1){
		(void)printf("    ");
		return;
	}else{
		(void)printf("O");
	}
	if(pix.obj.border==2){
		(void)printf("C");
		if(pix.obj.mult==2){
		(void)printf("M");
		}else if(pix.obj.mult==1){				
		(void)printf("-");
		}
	}else if(pix.obj.border==3){
		(void)printf("I-");
	}
}
//
// disp_matrix_label
// Prend en argument un ne matrice de pixel et sa taille
// et l'affiche dans la console 
//
void disp_matrix_label(t_pixel **img_label_matrix, uint32_t nl, uint32_t nc){
	int i,j;
	for(i=1;i<nl-1;i++){
		for(j=1;j<nc-1;j++){
			print_pixel(img_label_matrix,i,j);
		}							
		(void)printf("\n\n");
	}
}

void disp_skel(t_pixel **img_label_matrix, uint32_t nl, uint32_t nc){
	int i,j;
	for(i=0;i<nl;i++){
		for(j=0;j<nc;j++){
			print_pixel_skel(img_label_matrix,i,j);
		}							
		(void)printf("\n\n");
	}
}
void print_pixel_skel(t_pixel **pix, uint32_t l, uint32_t c){		
	if(pix[l][c].obj.squel==2) (void)printf("S   ");
	else printf("    ");
}