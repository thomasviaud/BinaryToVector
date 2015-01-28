#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../inc/pixel.h"
#include "../inc/point.h"
#include "../inc/graph.h"
//
// create_graph
// Ne prend rien en argument
// Retourne un pointeur vers un graphe dont les éléments sont initialisés 
// et prêts à être utilisés
//
t_graph* create_graph(){
	// Initialisation du graphe
	// et de ses composantes
	t_graph* graph;
	t_lvertex* lvertex;
	t_ledge* ledge;
	t_vertex* vertex;
	t_edge* edge;

	// Allocation en mémoire des champs
	// Graphe 
	graph=(t_graph*)malloc(sizeof(t_graph));
	printf("Graph : 0x%x\n",(int)graph);
	// Composantes du graphe : listes de sommets et liste d'arcs
	lvertex=create_lvertex();
	ledge=create_ledge();
	graph->vertices=lvertex;
	printf("Champ vertices : 0x%x\n",(int)graph->vertices);
	graph->edges=ledge;
	printf("Champ edges : 0x%x\n",(int)graph->edges);
	// Composantes des listes : sommets et arcs
	vertex=create_vertex();
	edge=create_edge();
	graph->vertices->val=vertex;	
	printf("Adresse liste vertex : 0x%x\n",(int)graph->vertices->val);
	graph->edges->val=edge;
	printf("Adresse liste edge : 0x%x\n---------------------------------\n",(int)graph->edges->val);
	return graph;
}

//
// create_lvertex
// Ne prend aucun argument
// Retourne une liste de sommets initialisée et allouée
//
t_lvertex* create_lvertex(){
	t_lvertex* l_vertex;
	l_vertex=(t_lvertex*)malloc(sizeof(t_lvertex));
	return l_vertex;
}

//
// create_ledge
// Ne prend aucun argument
// Retourne une liste d'arcs initialisée et allouée
//
t_ledge* create_ledge(){
	t_ledge* l_edge;
	l_edge=(t_ledge*)malloc(sizeof(t_ledge));
	return l_edge;
}

//
// create_vertex
// Ne prend aucun argument
// Retourne un sommet initialisée et alloué
//
t_vertex* create_vertex(){
	t_vertex* vertex;
	vertex=(t_vertex*)malloc(sizeof(t_vertex));
	return vertex;
}

//
// create_edge
// Ne prend aucun argument
// Retourne un arc initialisée et alloué
//
t_edge* create_edge(){
	t_edge* edge;
	edge=(t_edge*)malloc(sizeof(t_edge));
	return edge;
}

//
// add_vertex
// Prend en argument la matrice des points, des coordonnées,
// la liste des sommets, le graphe et le numéro correspondant au nom
// Retourne le pointeur vers la liste de sommets avec le nouveau sommet
//
t_lvertex* add_vertex(t_point **point, uint32_t l, uint32_t c, t_lvertex* lvertex, t_graph* graph, char vname){
	t_lvertex* new;
	new=create_lvertex();
	new->val=set_vertex(point,l,c,vname);
	new->next=lvertex;
	printf("Nouvelle adresse de la liste vertex : 0x%x\n",(int)new);
	return new;
}

// 
// set_vertex
// Prend en argument la matrice des points, deux coordonnées,
// et le nom du nouveau sommet
// Retourne le pointeur vers le nouveau sommet
//
t_vertex* set_vertex(t_point **point, uint32_t l, uint32_t c, char vname){
	t_vertex* new;
	new=create_vertex();
	new->point=point[l][c];
	new->name=vname;
	new->posx=l;
	new->posy=c;
	printf("Nouveau sommet : 0x%x\n",(int)new);
	return new;
}

//
// add_edge
// Prend en argument un sommet source et un sommet destination,
// une matrice point, deux coordonnées, la liste des arcs,
// le graph et le nom de l'arc
// Retourne le pointeur vers la liste d'arcs avec le nouvel arc
//
t_ledge* add_edge(t_vertex* src, t_vertex* dest, t_point **point, uint32_t l, uint32_t c, t_ledge* ledge, t_graph* graph, char ename){
	t_ledge* new;
	new=create_ledge();
	new->val=set_edge(src,dest,point,l,c,ename);
	new->next=ledge;
	printf("Nouvelle valeur dans la liste edge : 0x%x\n", (int)new);
	return new;
}

//
// set_edge
// Prend en argument les sommets sources et destinations,
// la matrice des points, deux coordonnées et le nom du nouvel arc
// Retourne le pointeur vers le nouvel arc
//
t_edge* set_edge(t_vertex* src, t_vertex* dest, t_point **point, uint32_t l, uint32_t c, char ename){
	t_edge* new;
	new=create_edge();
	new->src=src;
	new->dest=dest;
	new->name=ename;
	printf("Nouvel arc : 0x%x\nSource : 0x%x\nDestination : 0x%x\n", (int)new,(int)new->src, (int)new->dest);
	return new;
}

void print_ledge(t_ledge* ledge){
	if(ledge==NULL) return;
	print_edge(ledge->val);
	print_ledge(ledge->next);
	return;
}

void print_edge(t_edge* edge){
	printf("%d : du sommet %d au sommet %d\n", edge->name,edge->src->name, edge->dest->name);
}