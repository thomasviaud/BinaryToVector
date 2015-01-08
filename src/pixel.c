///////////////////////////////////////////////////////////
// pixel.c                                                //
// Contient les fonctions relatives à la gestion des     //
// pixel                                               //
///////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#define N1 4
#define N2 8
#include "../inc/pixel.h"
#include "../inc/list.h"
char set_type(uint8_t ***dist, uint32_t l, uint32_t c){
	if((*dist)[l][c]>0){
		return 1;
	}else{
		return 0;
	}
}

char set_border(uint8_t ***dist, uint32_t l, uint32_t c){
	if((*dist)[l][c]==1){
		return 1;
	}else if((*dist)[l][c]>1){
		return 2;
	}else{
		return 0;
	}
}

char set_mult(uint8_t ***dist, uint32_t l, uint32_t c){

// Déclarations
	int i;
	// Compteur de comparaison entre les modèles et les tableaux des voisins
	int cpt1=0, cpt1_bis=0;
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

	// Création du tableau contenant les voisins du pixel (*dist)[l][c] dans 
	// l'ordre horaire
	for(i=0;i<2*N1;i+=2){
		dist_border1[i/2]=(*dist)[l+coord_cas1[i]][c+coord_cas1[i+1]];
	}

	// Vérification des labels Fond et Interne
	for(i=0;i<N1/2;i++){
		// Voisins de type 0 - 2
		if(dist_border1[i]==0 && dist_border1[i+2]>1){
			cpt1++;
		}
		// Voisins de type 2 - 0
		else if(dist_border1[i+2]==0 && dist_border1[i]>1){
			cpt1_bis++;
		}
	}
	
	//
	// Cas où les pixels NO, NE, SE et SO sont contour et les pixels N,E,S,O dans le fond
	//
	for(i=0;i<2*N2;i+=2){
		dist_border2[i/2]=(*dist)[l+coord_cas2[i]][c+coord_cas2[i+1]];
	}
	// Comparaison entre dist_border2 et la chaîne model
	for(i=0;i<N2+1;i++){
		if(dist_border2[i]==model[i]){
			cpt2++;
		}
	}
	if(cpt2==8 || (cpt1+cpt1_bis)<2){
		return 1;
	}
	return 0;
}
//
// print_pixel
// Prend en argument un pixel
// et l'affiche dans la console
//
void print_pixel(t_pixel pix){
//	int i,j;
			if(pix.fond==1){
				(void)printf("F--");
				return;
			}else{
				(void)printf("O");
			}

			if(pix.obj.border==1){
				(void)printf("C");
			}else{
				(void)printf("I");
			}

			if(pix.obj.mult==0){
				(void)printf("-");
			}else{
				(void)printf("M");
			}
			(void)printf("\n");
	
}
