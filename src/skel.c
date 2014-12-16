///////////////////////////////////////////////////////////
// skel.c                                                //
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

t_plist skelet(uint8_t ***img_dist, uint32_t nl, uint32_t nc){
	uint32_t i,j;
	t_plist img_label;
	t_pixel pix;
	img_label=create_void();
	// Contour de la matrice img_dist
	for(i=0;i<nl;i++){
		// Première colonne gauche
		pix.posN=i;
		pix.posM=0;		
		pix.type=set_type(img_dist, i, 0);
		pix.border=set_border(img_dist,i,0);		
		if(pix.type==1 && img_dist[i][1]==0){
			pix.mult=0;
		}
		if(pix.type==1){
			img_label=add_list(pix,img_label);
		}		

		// Première colonne droite		
		pix.posN=i;
		pix.posM=nc-1;		
		pix.type=set_type(img_dist, i, nc-1);
		pix.border=set_border(img_dist,i,nc-1);		
		if(pix.type==1 && img_dist[i][nc-2]==0){
			pix.mult=0;
		}
		if(pix.type==1){
			img_label=add_list(pix,img_label);
		}	
	}	
	for(j=1;j<nc-1;j++){
		// Première ligne haute
		pix.posN=0;
		pix.posM=j;		
		pix.type=set_type(img_dist, 0, j);
		pix.border=set_border(img_dist,0, j);		
		if(pix.type==1 && img_dist[1][j]==0){
			pix.mult=0;
		}
		if(pix.type==1){
			img_label=add_list(pix,img_label);
		}		

		// Première ligne basse
		pix.posN=nl-1;
		pix.posM=j;		
		pix.type=set_type(img_dist, nl-1, j);
		pix.border=set_border(img_dist, nl-1, j);		
		if(pix.type==1 && img_dist[1][j]==0){
			pix.mult=0;
		}
		if(pix.type==1){
			img_label=add_list(pix,img_label);
		}	
	}
	// Matrice privée des bords
	for(i=1;i<nl-1;i++){
		for(j=1;j<nc-1;j++){			
			pix.posN=i;
			pix.posM=j;		
			pix.type=set_type(img_dist, i, j);
			pix.border=set_border(img_dist, i, j);
			pix.mult=set_mult(img_dist,i,j);
			if(pix.type==1){
			img_label=add_list(pix,img_label);
			}
		}
	}
	return img_label;
}