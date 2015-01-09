#ifndef __SKEL_H__
#define __SKEL_H__
void alloc_label_matrix(t_pixel ***pA, uint32_t nl, uint32_t nc);
void skelet(uint8_t **img_dist, t_pixel **img_label_matrix, t_plist* img_label_list, uint32_t nl, uint32_t nc);
#endif