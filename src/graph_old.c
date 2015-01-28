#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../inc/pixel.h"
#include "../inc/point.h"
#include "../inc/douglas.h"
#include "../inc/graph.h"

t_graph* create_graph(){
	t_graph* graph;
	// Allocation de l'espace nécessaire au stockage de 
	// les adresses des listes Vertices et Edges
	graph=(t_graph*)malloc(sizeof(t_vertex*)+sizeof(t_edge*));

	// Initialisation des listes Vertices et Edges
	graph->vertices=(t_pvlist*)malloc(sizeof(t_mvertex));
	graph->edges=(t_pelist*)malloc(sizeof(t_medges));

	(graph->vertices)->next=NULL;
	(graph->edges)->next=NULL;
	return graph;
}

t_pvlist add_vertex(t_graph graph, t_point** img_point, uint32_t l, uint32_t c, char *name){
	// Déclarations du nouveau maillon edge
	// et de l'edge
	t_pvlist new;
	t_vertex new_v;

	// Création du nouveau vertex
	new_v=(t_vertex*)malloc(sizeof(t_vertex*));
	new_v->name=name;
	new_v.type=img_point[l][c].type;
	new_v.posx=l;
	new_v.posy=c;

	// Ajout du vertex créé à la liste
	new=(t_pvlist*)malloc(sizeof(t_mvertex));
	new->vertex=new_v;
	new->next=graph->vertices;
	return new;
}

t_pelist add_edge(t_graph graph, t_vertex vertex1, t_vertex vertex2, char *name){
	// Déclarations du nouveau maillon edge
	// et de l'edge
	t_pelist new;
	t_edge* new_e;

	// Création du nouvel edge
	new_e=(t_edge*)malloc(sizeof(t_edge*));
	new_e->name=name;
	new_e->src=vertex1;
	new_e->dest=vertex2;

	// Ajout du vertex créé à la liste
	new=(t_pelist*)malloc(sizeof(t_medge));
	new->edge=new_e;
	new->next=graph->vertices;
	return new;
}