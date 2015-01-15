#ifndef __SKEL_H__
#define __SKEL_H__
void skelet(uint8_t **img_dist, t_pixel **img_label_matrix, t_plist* img_label_list, uint32_t nl, uint32_t nc);
void build_img_label(uint8_t **img_dist, t_pixel **img_label_matrix, uint32_t nl, uint32_t nc);
void build_img_list(t_pixel **img_label_matrix, t_plist *img_label_list, uint32_t nl, uint32_t nc);
int skelet_condition(int cpt_border,int cpt_mult,t_plist list_copy, t_plist* img_label_list);
void delete_current_border(uint8_t** img_dist,uint32_t nl,uint32_t nc);
#endif