#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../inc/pixel.h"
#include "../inc/point.h"
#include "../inc/graph.h"
#include "../inc/douglas.h"
#define N 8
//
// douglas
// Prend en argument la matrice des points, sa taille
// et la précision demandée
// Retourne un graphe simplifié du squelette
//
t_graph* douglas(t_point **img_point, uint32_t nl, uint32_t nc){
	// Création du graphe que la fonction va retourner
	t_graph* graph;
	graph=create_graph();

	int i,j;
	char name_v=1, name_e=1;
	
	// Variable indiquant si c'est la première entrée dans la fonction
	// récursive
	char first=1;
	// Parcours de l'image et ajout des éléments dans le graphe
	for(i=0;i<nl;i++){
		for(j=0;j<nc;j++){
			if(img_point[i][j].is_done==0 && img_point[i][j].type!=4){
				parcours_img(graph,img_point,nl,nc,i,j,name_v,name_e,&first);
			}
		}
	}
	/*graph->vertices=add_vertex(img_point,i,j,graph->vertices,graph,name_v);
	printf("Adresse du maillon ajouté : 0x%x\n",(int)graph->vertices->next);*/
	return graph;
}
//
// parcours_img 
// Fonction récursive qui prend en argument un graphe, 
//la matrice des points, sa taille et des coordonnées
// Ne retourne rien
//
void parcours_img(t_graph* graph, t_point** img_point, uint32_t nl, uint32_t nc, int l, int c, char n_vertex, char n_edge, char* first){
	printf("Etape : [%d][%d]\n",l,c);
	int nb_voisins=0, nb_lus=0;
	int i;
	/***********************************/
	/*      Recherche des voisins      */
	/***********************************/
	// Mise à jour de l'état du pixel en [l][c]
	img_point[l][c].is_done=1;
	// Le tableau voisins contiendra 1 pour tous les voisins du pixel img_label_matrix[l][c] en partant
	// du voisin NO dans le sens des aiguilles d'une montre
	int voisins[N];
		// Initialisation de voisin à 0 pour les tests
		for(i=0;i<N;i++) voisins[i]=0;
	/**************************************/

	// Coordonnées des pixels voisins au point img_point[l][c]
	int coord[2*N]={-1,-1, -1,0, -1,1, 0,1, 1,1, 1,0, 1,-1, 0,-1};

	// Remplissage du tableau de voisins en connexité 8
	for(i=0;i<2*N;i+=2){
		if(img_point[l+coord[i]][c+coord[i+1]].type!=4 && img_point[l+coord[i]][c+coord[i+1]].is_done==0) voisins[i/2]=1;	
	}	

	// Suppression des pixels en connexité 8 qui sont voisins de ceux en connexité 4
	for(i=1;i<N;i+=2){
		if(voisins[i]==1){
			voisins[(i-1)%N]=0;
			voisins[(i+1)%N]=0;
		}
	}
	printf("Voisins : (");
	for(i=0;i<N;i++) printf("%d",voisins[i]);
		printf(")\n");
	// Comptage du nombre de voisins et des voisins lus
	for(i=0;i<N;i++){
		if(voisins[i]==1) nb_voisins++;
		if(img_point[l+coord[i]][c+coord[i+1]].is_done==1) nb_lus++;
	}
	printf("%d voisins dont %d lus\n",nb_voisins,nb_lus);
	/***********************************/

	/***********************************/
	/*   Traitement du point courant   */
	/***********************************/

	// Cas d'arrêt : tous les voisins ont été lus
	if(nb_voisins==nb_lus) return;

	// Cas Borne : appel vers le prochain voisin
	// Ajout de la borne dans les sommets du graphe
	if(nb_voisins==1 && (*first)==1){
		printf("Premier point\n");
		// Mise à jour du compteur de passage
		(*first)=0;
		// Recherche du voisin
		i=0;
		while(voisins[i]==0) i++;
		printf("i = %d\n",i);
		printf("Voisin en [%d][%d]\n=================================\n",l+coord[i],c+coord[i+1]);
		// Appel récursif vers le prochain voisin
		parcours_img(graph,img_point,nl,nc,l+coord[2*i],c+coord[2*i+1],n_vertex,n_edge,first);
	}else if(nb_voisins==1 && (*first)==0){		
		// Recherche du voisin
		i=0;
		while(voisins[i]==0) i++;
		printf("Borne trouvée : ajout dans le graphe\n");
		// Appel récursif vers le prochain voisin
		parcours_img(graph,img_point,nl,nc,l+coord[2*i],c+coord[2*i+1],n_vertex,n_edge,first);
		
	}else if(nb_voisins>=3 && (*first)==1){
		printf("Bifurcation 1\n");
	// Mise à jour du compteur de passage
		(*first)=0;
		// Recherche du voisin
		for(i=0;i<N;i++){
			if(voisins[i]==1){
			printf("Appel récursif en [%d][%d]\n",l+coord[i],c+coord[i+1]);
			// Appel récursif vers le prochain voisin
			parcours_img(graph,img_point,nl,nc,l+coord[2*i],c+coord[2*i+1],n_vertex,n_edge,first);
			}
		}
	}else if(nb_voisins>=2 && first==0){
		printf("Bifurcation\n");
		// Recherche du voisin
		for(i=0;i<N;i++){
			if(voisins[i]==1){
			printf("Appel récursif en [%d][%d]\n",l+coord[i],c+coord[i+1]);
			// Appel récursif vers le prochain voisin
			parcours_img(graph,img_point,nl,nc,l+coord[2*i],c+coord[2*i+1],n_vertex,n_edge,first);
			}
		}
	}
}