#ifndef __DOUGLAS_H__
#define __DOUGLAS_H__

// Librairies
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../inc/pixel.h"
#include "../inc/point.h"
#include "../inc/tree.h"

// Macros
#define N 8

// Prototypes
plarbre 	douglas 		(t_point** img_point, uint32_t nl, uint32_t nc);
void 		parcours_img	(pnoeud tree, t_point** point, uint32_t l, uint32_t c);

#endif