#ifndef __SKEL_H__
#define __SKEL_H__
void alloc_label_matrix(t_pixel ***pA, uint32_t nl, uint32_t nc);
void skelet(uint8_t ***img_dist, t_pixel ***img_label_matrix, uint32_t nl, uint32_t nc);
#endif