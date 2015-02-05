#ifndef __LATEX_H__
#define __LATEX_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "tree.h"

void 	parcours_tree_print		(pnoeud tree, FILE* file);
void 	print_latex				(plarbre list, FILE* file, uint32_t height, uint32_t width,char*name);

#endif
