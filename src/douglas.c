#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../inc/pixel.h"
#include "../inc/point.h"
#include "../inc/arbre.h"
#include "../inc/douglas.h"
#define N 8

void douglas(t_point **img_point, uint32_t nl, uint32_t nc, int ep){
}

t_parbre set_graph(t_parbre arbre, t_point **img_point, uint32_t nl, uint32_t nc){
	t_parbre debut;
	uint32_t i=0,j=0;
	// Numéro du fils à ajouter initial
	int num=1;
	// Initialisation de l'arbre à un noeud bifurcation
	arbre=(t_parbre)malloc(sizeof(t_noeud));
	debut = arbre;
	arbre->val=3;
	arbre->father=NULL;
	// Sens permet d'orienter le parcours de l'image en rappelant l'orientation
	// du précédent point. Si sens = 8, parcours_img parcourira tous les voisins.
	int sens=8;
	//uint32_t i_bif=0, j_bif=0;
	// Récupère les coordonnées d'une bifurcation
	for(i=0;i<nl;i++){
		for(j=0;j<nc;j++){
			if(img_point[i][j].type==3 && img_point[i][j].is_done!=1) parcours_img(debut,&arbre,img_point,nl,nc,i,j,&sens,&num);
		}
	}
	return debut;
}

