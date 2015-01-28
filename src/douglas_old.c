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
// Prend en argument la matrice des points, la taille de cette matrice,
// et le seuil pour appliquer l'algorithme.
// Ne renvoi rien
//
void douglas(t_point **img_point, uint32_t nl, uint32_t nc){
	char name_v=1, name_e=1;
	t_graph* skel_graph;
	skel_graph=create_graph();
	skel_graph->vertices=add_vertex(*skel_graph,img_point,1,1,&name_v);
	skel_graph->vertices=add_vertex(*skel_graph,img_point,2,2,&name_v);
	skel_graph->edges=add_edge(*skel_graph,skel_graph->vertices->vertex,skel_graph->vertices->next->vertex,&name_e);
}

//
// set_graph
// Prend en argument la matrice des points, sa taille
// Retourne un graphe composé des points Bornes et Bifurcation.
//
/*t_graph set_graph(t_point **img_point, uint32_t nl, uint32_t nc){
	// Graphe retourné en fin de fonction
	//t_graph graph;
	uint32_t i,j;
	// Variable d'arrêt pour rechercher un élément de l'image
	int stop;

	/**********************************/
	/*    Initialisation du graphe    */
	/**********************************/
	//graph=create_graph();

	// Recherche d'un élément de l'image non traité
	/*for(i=0;i<nl && !stop;i++){
		for(j=0;j<nc && !stop;j++){
			if(img_point[i][j].type!=4 && !img_point[i][j].is_done){
			}
		}
	}

	/**********************************/
	/*      Remplissage du graphe     */
	/**********************************/
//}

//
// fill_graph
// Prend en argument la matrice des points, sa taille, les coordonnées
// du point d'entrée 