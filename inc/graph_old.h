#ifndef __GRAPH_H__
#define __GRAPH_H__
/*********************************/
/*     STRUCTURE DE GRAPHE       */
/*********************************/

/***************************/
//  Sommets
/***************************/
// Structure de sommet
typedef struct{
	char* name;
	t_point type;
	int posx;
	int posy;
}t_vertex;

// Liste des sommets
typedef struct vmaillon{
    t_vertex vertex;
    struct vmaillon *next;
}t_mvertex, *t_pvlist;

/***************************/
//  Arcs
/***************************/
// Structure d'arc
typedef struct{
	char* name;
	t_vertex* src;
	t_vertex* dest;
}t_edge;
// Liste des arcs
typedef struct emaillon{
    t_edge edge;
    struct emaillon *next;
}t_medge, *t_pelist;

/***************************/
//  Graphe
/***************************/
// Structure de graphe
typedef struct{
	t_pvlist vertices;
	t_pelist edges;
}t_graph;


t_graph*	create_graph	();
t_pvlist 	add_vertex		(t_graph graph, t_point** img_point, uint32_t l, uint32_t c, char *name);
t_pelist	add_edge		(t_graph graph, t_vertex vertex1, t_vertex vertex2, char *name);
#endif