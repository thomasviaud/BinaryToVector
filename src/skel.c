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
#include "../inc/matrix.h"
#include "../inc/list.h"
#include "../inc/skel.h"

//
// skelet
// Prend en argument la matrice de transformée en distance,
// la matrice contenant les labels, leurs tailles et la liste chaînée 
// contenant les labels.
// Ne renvoi rien
//
void skelet(uint8_t **img_dist, t_pixel **img_label_matrix, t_plist *img_label_list, uint32_t nl, uint32_t nc){
	t_plist list_copy;
	int cpt_mult, cpt_border;
	int mult_border;
	int etape=1;
	do{
		(*img_label_list)=NULL;
		list_copy=NULL;		
		cpt_mult=0;
		cpt_border=0;
		build_img_label(img_dist,img_label_matrix, nl, nc);
		printf("===== CONTOUR %d =====\n\n",etape);
		disp_matrix_label(img_label_matrix,nl,nc);
		build_img_list(img_label_matrix, img_label_list,nl,nc);
		mult_border=skelet_condition(cpt_border,cpt_mult,list_copy,img_label_list);
		delete_current_border(img_dist, nl, nc);
		etape++;
		disp_skel(img_label_matrix, nl, nc);
	}while(mult_border);
	printf("===== SQUELETTE =====\n");
	disp_skel(img_label_matrix, nl, nc);
}

//
// build_img_label
// Prend en argument la matrice de transformée en distance,
// la matrice contenant les labels et leurs tailles.
// Ne renvoi rien
//
void build_img_label(uint8_t **img_dist, t_pixel **img_label_matrix, uint32_t nl, uint32_t nc){
	int i,j;
	// Partie interne de la matrice
	for(i=0;i<nl;i++){
		for(j=0;j<nc;j++){
			if(img_dist[i][j]==0){
				img_label_matrix[i][j].fond=1;
			}else{
				img_label_matrix[i][j].obj.border=set_border(img_dist,i,j);		
				if(img_label_matrix[i][j].obj.border==2) img_label_matrix[i][j].obj.mult=set_mult(img_dist,i,j);
				else img_label_matrix[i][j].obj.mult=1;
				img_label_matrix[i][j].obj.squel=set_squel(img_label_matrix,i,j);
				}		
				
		}
	}
}
//
// build_img_list
// Prend en argument la matrice contenant les labels,
// sa taille et la liste chaînée contenant les labels.
// Ne renvoi rien
//
void build_img_list(t_pixel **img_label_matrix, t_plist *img_label_list, uint32_t nl, uint32_t nc){
	int i,j;	
	for(i=1;i<nl-1;i++){
		for(j=1;j<nc-1;j++){
			if(img_label_matrix[i][j].obj.border==2){
				(*img_label_list)=add_list(img_label_matrix[i][j], *img_label_list);
			}
		}					
	}
}

//
// skelet_condition
// Prend en argument deux compteurs,
// la liste chaînée contenant les labels et un pointeur sur cette liste
// Renvoie 0 si tous les pixels contours sont multiples, 1 sinon
//
int skelet_condition(int cpt_border,int cpt_mult,t_plist list_copy, t_plist* img_label_list){
	// Vérification de la condition de d'arrêt de l'algorithme
		list_copy=(*img_label_list);
		while(list_copy!=NULL){
			if(list_copy->v_pixel.obj.mult==2) cpt_mult++;
			cpt_border++;
			list_copy=end_list(list_copy);	
		}
		printf("%d mult et %d contours à cette itération\n",cpt_mult,cpt_border);
		if(cpt_border==cpt_mult) return 0;
		else return 1;
}
//
// delete_current_border
// Prend en argument la matrice de transformée en distance et,
// sa taille.
// Ne renvoie rien
//
void delete_current_border(uint8_t** img_dist,uint32_t nl,uint32_t nc){
	int i,j;
	// Décrémentation des valeurs de img_dist pour recommencer au contour
	// suivant
	for(i=1;i<nl-1;i++){
		for(j=1;j<nc-1;j++){
			if(img_dist[i][j]>0) img_dist[i][j]--;
		}
	}
}