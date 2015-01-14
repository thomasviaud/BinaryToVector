#ifndef __POINT_H__
#define __POINT_H__
typedef char t_point; 	// 0 : Point 	1 : Borne 	2 : Noeud 	3 : Bifurcation 

void alloc_point_matrix(t_point ***pA, uint32_t nl, uint32_t nc);
void set_point_matrix(t_point ** img_point_matrix, t_pixel ** img_label_matrix, uint32_t nl, uint32_t nc);
char set_point(t_pixel ** img_label_matrix, uint32_t l, uint32_t c);
char set_tl_point(t_pixel ** img_label_matrix, uint32_t nl, uint32_t nc);
char set_tr_point(t_pixel ** img_label_matrix, uint32_t nl, uint32_t nc);
char set_bl_point(t_pixel ** img_label_matrix, uint32_t nl, uint32_t nc);
char set_br_point(t_pixel ** img_label_matrix, uint32_t nl, uint32_t nc);
char set_lineu_point(t_pixel ** img_label_matrix, uint32_t c, uint32_t nl);
char set_lineb_point(t_pixel ** img_label_matrix, uint32_t c, uint32_t nl);
char set_coll_point(t_pixel ** img_label_matrix, uint32_t l, uint32_t nc);
char set_colr_point(t_pixel ** img_label_matrix, uint32_t l, uint32_t nc);
void print_point(t_point ** point, uint32_t l, uint32_t c);
void disp_point_matrix(t_point ** point, uint32_t nl, uint32_t nc);
#endif