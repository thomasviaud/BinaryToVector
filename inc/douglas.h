#ifndef __DOUGLAS_H__
#define __DOUGLAS_H__

// Librairies
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "pixel.h"
#include "point.h"
#include "tree.h"

// Macros
#define N 8

// Prototypes
plarbre 	douglas 		(t_point** img_point, uint32_t nl, uint32_t nc, int ep);
plarbre 	build_ltree		(t_point** img_point, uint32_t nl, uint32_t nc);
void 		find_node		(pnoeud node, t_point** point, uint32_t l, uint32_t c, int num, int ep);
void 		edit_tree		(pnoeud tree, t_point** point, int ep);
pnoeud		ins_node		(pnoeud father, pnoeud son, t_point** point, uint32_t l, uint32_t c, int n_fils);
void 		parcours_img	(pnoeud tree, t_point** point, uint32_t l, uint32_t c);
float 		calc_dist		(pnoeud node1, pnoeud node2, uint32_t li, uint32_t co);

#endif