#ifndef __POINT_H__
#define __POINT_H__
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "pixel.h"
typedef struct{
	char type; 		// 0 : Point 	1 : Borne 	2 : Noeud 	3 : Bifurcation	4 : Fond
	char is_done; 	// 0 : !done 	1 : done
	char is_done_d;	// 0 : !done 	1 : done
}t_point;

void set_point_matrix(t_point ** img_point_matrix, t_pixel ** img_label_matrix, uint32_t nl, uint32_t nc);
char set_point(t_pixel ** img_label_matrix, uint32_t l, uint32_t c);
void print_point(t_point ** point, uint32_t l, uint32_t c);
void disp_point_matrix(t_point ** point, uint32_t nl, uint32_t nc);
#endif