///////////////////////////////////////////////////////////
// skel->c                                                //
// Contient les fonctions relatives à la squelettisation //
///////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "../inc/pixel.h"
#include "../inc/list.h"
#include "../inc/skel.h"
//
// skelet
// Prend en argument la matrice de transformée en distance ainsi que sa taille
// Renvoi le pointeur vers le premier élément de la liste img_label

void skelet(uint8_t ***img_dist, t_pixel ***img_label_matrix, uint32_t nl, uint32_t nc){
	uint32_t i,j;
	// Contour de la matrice img_label
	for(i=0;i<nl;i++){
		// Première colonne gauche
		if(img_dist[i][0]==0){
			img_label_matrix[i][0]->fond=1;
		}else{
			img_label_matrix[i][0]->obj.border=set_border(img_dist,i,0);		
			img_label_matrix[i][0]->obj.mult=set_mult(img_dist,i,0);
		}
		// Première colonne droite
		if(img_dist[i][nc-1]==0){
			img_label_matrix[i][nc-1]->fond=1;
		}else{		
			img_label_matrix[i][nc-1]->obj.border=set_border(img_dist,i,nc-1);		
			img_label_matrix[i][nc-1]->obj.mult=set_mult(img_dist,i,nc-1);
		}

	}
	for(j=1;j<nc-1;j++){
		// Première ligne haute
		if(img_dist[0][j]==0){
			img_label_matrix[0][j]->fond=1;
		}else{	
			img_label_matrix[0][j]->obj.border=set_border(img_dist,0,j);		
			img_label_matrix[0][j]->obj.mult=set_mult(img_dist,0,j);
		}
		// Première ligne basse	
		if(img_dist[nl-1][j]==0){
			img_label_matrix[nl-1][j]->fond=1;
		}else{
			img_label_matrix[nl-1][j]->obj.border=set_border(img_dist,nl-1,j);		
			img_label_matrix[nl-1][j]->obj.mult=set_mult(img_dist,nc-1,j);
		}
	}
	// Partie interne de la matrice
	for(i=1;i<nl-1;i++){
		for(j=1;j<nc-1;j++){
		if(img_dist[i][j]==0){
			img_label_matrix[i][j]->fond=1;
		}else{
			img_label_matrix[i][j]->obj.border=set_border(img_dist,i,j);		
			img_label_matrix[i][j]->obj.mult=set_mult(img_dist,i,j);
			}
		}
	}

	// Affichage 
	//for(i=0;i<nl;i++){
		//for(j=0;j<nc;j++){
			//print_pixel(*img_label_matrix[0][0]);
		//}
	//}
}