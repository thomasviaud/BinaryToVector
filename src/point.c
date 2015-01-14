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
	// Coin haut-gauche
	img_point_matrix[0][0]=set_tl_point(img_label_matrix,nl,nc);
	img_point_matrix[0][nc-1]=set_tr_point(img_label_matrix,nl,nc);
	img_point_matrix[nc-1][0]=set_bl_point(img_label_matrix,nl,nc);
	img_point_matrix[nc-1][nl-1]=set_br_point(img_label_matrix,nl,nc);
	// Premières lignes
	for(i=1;i<nc-1;i++){
		img_point_matrix[0][i]=set_lineu_point(img_label_matrix,i,nl);
		img_point_matrix[nl-1][i]=set_lineb_point(img_label_matrix,i,nl);
	}
	// Premières colonnes
	for(i=1;i<nl-1;i++){
		img_point_matrix[i][0]=set_coll_point(img_label_matrix,i,nc);
		img_point_matrix[i][nc-1]=set_colr_point(img_label_matrix,i,nc);		
	}
	// Partie interne de la matrice
	for(i=1;i<nl-1;i++){
		for(j=1;j<nc-1;j++){
			img_point_matrix[i][j]=set_point(img_label_matrix,i,j);
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

char set_tl_point(t_pixel ** img_label_matrix, uint32_t nl, uint32_t nc){	
	int cpt=0;
	int i;
	int coord[2*N_coin]={0,1, 1,1, 1,0};
	int voisins[N_coin]={0,0,0};
	if(img_label_matrix[0][0].obj.squel!=2) return 4;
	for(i=0;i<2*N_coin;i+=2){
		if(img_label_matrix[0+coord[i]][0+coord[i+1]].obj.squel==2) voisins[i/2]=1;
	}
	for(i=0;i<N_coin;i+=2){
		if(voisins[i]==1) voisins[1]=0;
	}
	for(i=0;i<N_bord;i++) if(voisins[i]==1) cpt++;
	return cpt;
}

char set_tr_point(t_pixel ** img_label_matrix, uint32_t nl, uint32_t nc){		
	int cpt=0;
	int i;
	int coord[2*N_coin]={0,nc-2, 1,nc-2, 1,nc-1};
	int voisins[N_coin]={0,0,0};
	if(img_label_matrix[0][nc-1].obj.squel!=2) return 4;
	for(i=0;i<2*N_coin;i+=2){
		if(img_label_matrix[0+coord[i]][nc-1+coord[i+1]].obj.squel==2) voisins[i/2]=1;
	}
	for(i=0;i<N_coin;i++){
		if(voisins[i]==1) voisins[1]=0;
	}
	for(i=0;i<N_bord;i++) if(voisins[i]==1) cpt++;
	return cpt;
}

char set_bl_point(t_pixel ** img_label_matrix, uint32_t nl, uint32_t nc){	
	int cpt=0;
	int i;
	int coord[2*N_coin]={nl-2,0, nl-2,1, nl-1,1};
	int voisins[N_coin]={0,0,0};
	if(img_label_matrix[nl-1][0].obj.squel!=2) return 4;
	for(i=0;i<2*N_coin;i+=2){
		if(img_label_matrix[nl-1+coord[i]][0+coord[i+1]].obj.squel==2) voisins[i/2]=1;
	}
	for(i=0;i<N_coin;i++){
		if(voisins[i]==1) voisins[1]=0;
	}
	for(i=0;i<N_bord;i++) if(voisins[i]==1) cpt++;
	return cpt;
}

char set_br_point(t_pixel ** img_label_matrix, uint32_t nl, uint32_t nc){	
	int cpt=0;
	int i;
	int coord[2*N_coin]={nl-1,nc-2, nl-2,nc-1, nl-2,nc-2};
	int voisins[N_coin]={0,0,0};
	if(img_label_matrix[nl-1][nc-1].obj.squel!=2) return 4;
	for(i=0;i<2*N_coin;i+=2){
		if(img_label_matrix[nl-1+coord[i]][nc-1+coord[i+1]].obj.squel==2) voisins[i/2]=1;
	}
	for(i=0;i<N_coin;i++){
		if(voisins[i]==1) voisins[1]=0;
	}
	for(i=0;i<N_bord;i++) if(voisins[i]==1) cpt++;
	return cpt;
}

char set_lineu_point(t_pixel ** img_label_matrix, uint32_t c, uint32_t nl){
	int cpt=0;
	int i;
	int coord[2*N_bord]={c-1,0, c-1,1, c,1, c,2, c+1,0};	
	int voisins_t[N_bord]={0,0,0,0,0};
	if(img_label_matrix[0][c].obj.squel!=2) return 4;
	for(i=0;i<2*N_bord;i+=2){
		if(img_label_matrix[coord[i]][c+coord[i+1]].obj.squel==2) voisins_t[i/2]=1;
		
	}
	if(voisins_t[0]==1) voisins_t[1]=0;
	if(voisins_t[2]==1){
		voisins_t[1]=0;
		voisins_t[3]=0;
	}
	if(voisins_t[4]==1) voisins_t[3]=0;
	for(i=0;i<N_bord;i++) if(voisins_t[i]==1) cpt++;
	return cpt;
}
char set_lineb_point(t_pixel ** img_label_matrix, uint32_t c, uint32_t nl){
	int cpt=0;
	int i;
	int coord[2*N_bord]={c-1,0, c-1,1, c,1, c,2, c+1,0};
	int voisins_b[N_bord]={0,0,0,0,0};	
	if(img_label_matrix[nl-1][c].obj.squel!=2) return 4;	
	for(i=0;i<2*N_bord;i+=2){
		if(img_label_matrix[nl-1+coord[i]][c+coord[i+1]].obj.squel==2) voisins_b[i/2]=1;
	}	
	if(voisins_b[0]==1) voisins_b[1]=0;
	if(voisins_b[2]==1){
		voisins_b[1]=0;
		voisins_b[3]=0;
	}
	if(voisins_b[4]==1) voisins_b[3]=0;
	for(i=0;i<N_bord;i++) if(voisins_b[i]==1) cpt++;
	return cpt;
}

char set_coll_point(t_pixel ** img_label_matrix, uint32_t l, uint32_t nc){
	int cpt=0;
	int i;
	int coord[2*N_bord]={0,l-1, 1,l-1, 1,l, 2,l, 0,l+1};	
	int voisins_l[N_bord]={0,0,0,0,0};
	if(img_label_matrix[l][0].obj.squel!=2) return 4;
	for(i=0;i<2*N_bord;i+=2){
		if(img_label_matrix[l+coord[i]][coord[i+1]].obj.squel==2) voisins_l[i/2]=1;
		
	}
	if(voisins_l[0]==1) voisins_l[1]=0;
	if(voisins_l[2]==1){
		voisins_l[1]=0;
		voisins_l[3]=0;
	}
	if(voisins_l[4]==1) voisins_l[3]=0;
	for(i=0;i<N_bord;i++) if(voisins_l[i]==1) cpt++;
	return cpt;
}
char set_colr_point(t_pixel ** img_label_matrix, uint32_t l, uint32_t nc){
	int cpt=0;
	int i;
	int coord[2*N_bord]={0,l-1, 1,l-1, 1,l, 2,l, 0,l+1};	
	int voisins_r[N_bord]={0,0,0,0,0};	
	if(img_label_matrix[l][nc-1].obj.squel!=2) return 4;	
	for(i=0;i<2*N_bord;i+=2){
		if(img_label_matrix[l+coord[i]][nc-1+coord[i+1]].obj.squel==2) voisins_r[i/2]=1;
	}	
	if(voisins_r[0]==1) voisins_r[1]=0;
	if(voisins_r[2]==1){
		voisins_r[1]=0;
		voisins_r[3]=0;
	}
	if(voisins_r[4]==1) voisins_r[3]=0;
	for(i=0;i<N_bord;i++) if(voisins_r[i]==1) cpt++;
	return cpt;
}
void print_point(t_point ** point, uint32_t l, uint32_t c){
	if(point[l][c]==1) (void)printf("Bo  ");
	else if(point[l][c]==2) (void)printf("No  ");
	else if(point[l][c]==3) (void)printf("Bi  ");
	else if(point[l][c]==0) (void)printf("Po  ");
	else if(point[l][c]==4)(void)printf("    ");
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