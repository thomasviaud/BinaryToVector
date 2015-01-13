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
// Prend en argument la matrice de transformée en distance,
// la matrice contenant les labels et leurs tailles.
// Ne renvoi rien
//
void skelet(uint8_t **img_dist, t_pixel **img_label_matrix, t_plist *img_label_list, uint32_t nl, uint32_t nc){
	uint32_t i,j;
	t_plist list_copy;
	int cpt_mult;
	int cpt_border;

	do{
		(*img_label_list)=NULL;		
		cpt_mult=0;
		cpt_border=0;
		// Construction de la matric img_label
			// Contour de la matrice img_label
			for(i=0;i<nl;i++){
				// Première colonne gauche
				if(img_dist[i][0]==0){
					img_label_matrix[i][0].fond=1;
				}else{
					img_label_matrix[i][0].obj.border=set_border(img_dist,i,0);		
					img_label_matrix[i][0].obj.mult=2;
				}
				if(img_dist[i][nc-1]==0){
					img_label_matrix[i][nc-1].fond=1;
				}else{		
					img_label_matrix[i][nc-1].obj.border=set_border(img_dist,i,nc-1);		
					img_label_matrix[i][nc-1].obj.mult=2;
				}

			}
			for(j=1;j<nc-1;j++){
				// Première ligne haute
				if(img_dist[0][j]==0){
					img_label_matrix[0][j].fond=1;
				}else{	
					img_label_matrix[0][j].obj.border=set_border(img_dist,0,j);		
					img_label_matrix[0][j].obj.mult=2;
				}
				// Première ligne basse	
				if(img_dist[nl-1][j]==0){
					img_label_matrix[nl-1][j].fond=1;
				}else{
					img_label_matrix[nl-1][j].obj.border=set_border(img_dist,nl-1,j);		
					img_label_matrix[nl-1][j].obj.mult=2;
				}
			}
			/* *********************** */

			// Partie interne de la matrice
			for(i=1;i<nl-1;i++){
				for(j=1;j<nc-1;j++){
				if(img_dist[i][j]==0){
					img_label_matrix[i][j].fond=1;
				}else{
					img_label_matrix[i][j].obj.border=set_border(img_dist,i,j);		
					img_label_matrix[i][j].obj.mult=set_mult(img_dist,i,j);
					}
				}
			}
			/*  *********************** */

			// Affichage de la matrice img_label
			for(i=0;i<nl;i++){
				for(j=0;j<nc;j++){
					print_pixel(img_label_matrix,i,j);
				}							
				(void)printf("\n\n");
			}
		/*  ************************************ */

		// Construction de la liste chaînée img_label
			for(i=0;i<nl;i++){
				for(j=0;j<nc;j++){
					if(img_label_matrix[i][j].obj.border==2){
						(*img_label_list)=add_list(img_label_matrix[i][j], *img_label_list);
						printf("[%d][%d] ",i,j);
					}
					if(img_label_matrix[i][j].obj.mult==2) img_label_matrix[i][j].obj.squel=2;
				}					
			}

		// Vérification de la condition de d'arrêt de l'algorithme
			list_copy=(*img_label_list);
			while(list_copy!=NULL){
				if(list_copy->v_pixel.obj.mult==2) cpt_mult++;
				cpt_border++;
				list_copy=end_list(list_copy);	
			}
			printf("\n%d multiples à cette itération\n",cpt_mult);
			printf("%d pixels contours\n",cpt_border);

		// Décrémentation des valeurs de img_dist pour recommencer au contour
		// suivant
			for(i=0;i<nl;i++){
				for(j=0;j<nc;j++){
					if(img_dist[i][j]>0) img_dist[i][j]--;
				}
			}
	}while(cpt_border!=cpt_mult);
}

