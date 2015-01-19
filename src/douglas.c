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

t_parbre set_tree(t_point **img_point, uint32_t nl, uint32_t nc){
	t_parbre new;
	int i=0,j=0;
	// Sens permet d'orienter le parcours de l'image en rappelant l'orientation
	// du précédent point. Si sens = 8, parcours_img parcourira tous les voisins.
	int sens=8;
	int i_bif=0, j_bif=0;
	// Récupère les coordonnées d'une bifurcation
	for(i=i_bif;i<nl;i++){
		for(j=j_bif;j<nc;j++){
			if(img_point[i][j]==3) parcours_img(img_point,nl,nc,i,j,sens);
		}
	}
	return new;
}

void parcours_img(t_point **img_point, uint32_t nl, uint32_t nc, uint32_t l, uint32_t c, int sens){
	int i;
	char voisins[N];
	// Coordonnées des pixels voisins au point img_point[l][c]
	int coord[2*N]={-1,-1, -1,0, -1,1, 0,1, 1,1, 1,0, 1,-1, 0,-1};
	/* ********************** */
	/*     Borne
	*/
	if(img_point[l][c]==1){
		//add_son;
		return;
	}

	/* ********************** */
	/*     Noeud
	*/
	if(img_point[l][c]==2){
		// Initialisation de voisins
		for(i=0;i<N;i++) voisins[i]=0;

		// Remplissage du tableau de voisins en connexité 8
		for(i=0;i<2*N;i+=2){
			if(img_point[l+coord[i]][c+coord[i+1]]!=4) voisins[i/2]=1;	
		}	
		// Suppression des pixels en connexité 8 qui sont voisins de ceux en connexité 4
		for(i=1;i<N;i+=2){
			if(voisins[i]==1){
				voisins[(i-1)%N]=0;
				voisins[(i+1)%N]=0;
			}
		}
		// Suppression du voisin sur lequel on était à l'étape précédente
		voisins[sens]=0;
		// Recherche du voisin
		i=0;
		while(voisins[i]!=1) i++;

		// Orientation du sens pour le prochain appel
		sens=(i+4)%N;
		
		//add_son;
		parcours_img(img_point,nl,nc,l+coord[2*i],c+coord[2*i+1],sens); 
	}

	/* ********************** */
	/*     Bifurcation
	*/
	if(img_point[l][c]==3){
		// Initialisation de voisins
		for(i=0;i<N;i++) voisins[i]=0;

		// Remplissage du tableau de voisins en connexité 8
		for(i=0;i<2*N;i+=2){
			if(img_point[l+coord[i]][c+coord[i+1]]!=4) voisins[i/2]=1;	
		}	
		// Suppression des pixels en connexité 8 qui sont voisins de ceux en connexité 4
		for(i=1;i<N;i+=2){
			if(voisins[i]==1){
				voisins[(i-1)%N]=0;
				voisins[(i+1)%N]=0;
			}
		}
		// Suppression du voisin sur lequel on était à l'étape précédente si ce n'est pas 
		// la première entrée dans la fonction récursive
		if (sens!=8) voisins[sens]=0;

		// Appel récursif de la fonction pour chaque voisin du pixel en [l][c]
		for(i=0;i<N;i++){
			if(voisins[i]==1){
				// Orientation du sens pour le prochain appel
				sens=(i+4)%N;
				parcours_img(img_point,nl,nc,l+coord[2*i],c+coord[2*i+1],sens);
			} 
		}
	}
	/* ********************** */
	/*     Point
	*/
	if(img_point[l][c]==0){
		// Suppression du voisin sur lequel on était à l'étape précédente
		voisins[sens]=0;
		// Recherche du voisin
		i=0;
		while(voisins[i]!=1) i++;

		// Orientation du sens pour le prochain appel
		sens=(i+4)%N;
		parcours_img(img_point,nl,nc,l+coord[2*i],c+coord[2*i+1],sens);
	}
	return;
}
