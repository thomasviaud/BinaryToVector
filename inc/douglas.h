#ifndef __DOUGLAS_H__
#define __DOUGLAS_H__
t_graph*	douglas 	(t_point **img_point, uint32_t nl, uint32_t nc);
void parcours_img(t_graph* graph, t_point** img_point, uint32_t nl, uint32_t nc, int l, int c, char n_vertex, char n_edge, char* first);
#endif