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
	if((*dist)[l][c]>=1){
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
	int i;
	int cpt=0, cpt_bis=0;
	char model[N2]={1,0,1,0,1,0,1,0};
	char dist_border1[2*N1];
	char dist_border2[N2];
	int coord_cas1[2*N1]={-1,0,0,1,1,0,0,-1};
	int coord_cas2[2*N2]={-1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1};
	//
	// Cas où les couples de pixels N,S et O,E sont deux à deux psa Fond et Interne
	//
	for(i=0;i<2*N1;i+=2){
		dist_border1[i/2]=(*dist)[l+coord_cas1[i]][c+coord_cas1[i+1]];
	}

	// Vérification des labels Fond et Interne
	for(i=0;i<(N1/2)+1;i++){
		if(dist_border1[i%N1]==0 && dist_border1[(i+2)%N1]>=2){
			cpt++;
		}
		if(dist_border1[i%N1]>=2 && dist_border1[(i+2)%N1]==0){
			cpt_bis++;
		}
	}
	if(cpt!=2){
		return 1;
	}
	if(cpt_bis!=2){
		return 1;
	}
	
	//
	// Cas où les pixels NO, NE, SE et SO sont contour et les pixels N,E,S,O dans le fond
	//
	for(i=0;i<2*N2;i+=2){
		dist_border2[i/2]=(*dist)[l+coord_cas2[i]][c+coord_cas2[i+1]];
	}
	// Comparaison entre dist_border2 et la chaîne model
	cpt=0;
	for(i=0;i<N2+1;i++){
		if(dist_border2[i]==model[i]){
			cpt++;
		}
	}
	if(cpt==8){
		return 1;
	}
	return 0;

/*

	// Cas où les pixels NO, NE, SE et SO sont contour et les pixels N,E,S,O dans le fond

	for(i=0;i<2*N1;i+=2){
		dist_border1[i/2]=(*dist)[l+coord_cas1[i]][c+coord_cas1[i+1]];
	}
	// Comparaison de dist_border à model
	for(i=0;i<N1+1;i++){
		if(dist_border1[i%N1]==0 && (*dist)[(i+1)%N1]>=2){
		cpt=cpt++;
		}
	}
	if(cpt=!4){
		return 1;
	}

	// Cas où les pixels NO, NE, SE et SO sont contour et les pixels N,E,S,O dans le fond
	char model_cas2[N2]={1,0,1,0,1,0,1,0};
	char dist_border2[N2];

	for(i=0;i<2*N2;i+=2){
		dist_border2[i/2]=(*dist)[l+coord_cas2[i]][c+coord_cas2[i+1]];
	}

	// Comparaison de dist_border à model
	cpt=0;
	for(i=0;i<N2+1;i++){
		if(dist_border2[i]==model_cas2[i]){
		cpt++;
		}
	}
	if(cpt==8){
		return 1;
	}
    return 0;*/
}
//
// print_pixel
// Prend en argument un pixel
// et l'affiche dans la console
//
void print_pixel(t_pixel pix, uint32_t l, uint32_t c){
	int i,j;
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			if(img_label_matrix[i][j].fond==1){
				(void)printf("F--");
				return;
			}else{
				(void)printf("O");
			}

			if(img_label_matrix[i][j].obj.border==1){
				(void)printf("C");
			}else{
				(void)printf("I");
			}

			if(img_label_matrix[i][j].obj.mult==0){
				(void)printf("-");
			}else{
				(void)printf("M");
			}
		}
		(void)printf("\n");
	}
}
