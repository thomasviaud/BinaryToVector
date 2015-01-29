#ifndef __GRAPH_H__
#define __GRAPH_H__
/*******************************/
/*    STRUCTURE DE GRAPHE      */
/*******************************/

/*********************/
/*      SOMMETS      */
/*********************/

// Type sommet
typedef struct{
	char name;
	t_point point;
	int posx;
	int posy;
}t_vertex;

// Type liste de sommets
typedef struct vm{
	t_vertex* val;
	struct vm* next;
}t_lvertex;

/*********************/
/*       EDGES       */
/*********************/

// Type edge
typedef struct{
	char name;
	t_vertex* src;
	t_vertex* dest;
}t_edge;

// Type liste d'edges
typedef struct em{
	t_edge* val;
	struct em* next;
}t_ledge;

/*********************/
/* STRUCTURE FINALE  */
/*********************/

// Type graphe : liste de vertex + liste d'edge
typedef struct{
	t_lvertex* 		vertices;
	t_ledge*		edges;
}t_graph;

t_graph* 	create_graph	();
t_lvertex* 	create_lvertex	();
t_ledge* 	create_ledge	();
t_vertex* 	create_vertex 	();
t_edge* 	create_edge 	();
t_lvertex* 	add_vertex		(t_point **point, uint32_t l, uint32_t c, t_lvertex* lvertex, char vname);
t_vertex* 	set_vertex		(t_point **point, uint32_t l, uint32_t c, char vname);
t_ledge* 	add_edge		(t_vertex* src, t_vertex* dest, t_ledge* ledge, char ename);
t_edge* 	set_edge		(t_vertex* src, t_vertex* dest, char ename);
void 		print_ledge		(t_ledge* ledge);
void 		print_edge 		(t_edge* edge);
void 		print_lvertex 	(t_lvertex* lvertex);
void 		print_vertex 	(t_vertex* vertex);
#endif