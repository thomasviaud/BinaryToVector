#ifndef __DOUGLAS_H__
#define __DOUGLAS_H__
void douglas( t_point **img_point, uint32_t nl, uint32_t nc, int ep);
t_parbre set_graph(t_parbre test, t_point **img_point, uint32_t nl, uint32_t nc);
void parcours_img(t_parbre debut, t_parbre* tree,t_point **img_point, uint32_t nl, uint32_t nc, uint32_t l, uint32_t c, int *sens, int* num_fils);
#endif