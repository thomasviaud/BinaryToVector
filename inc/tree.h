#ifndef __TREE_H__
#define __TREE_H__

// Librairies
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "pixel.h"
#include "point.h"

// Structures

// Structure d'arbre
// 
typedef struct mm{
	char borne;
	t_point point;
	char feuille;
	char posx;
	char posy;
	struct mm *son1;
	struct mm *son2;
	struct mm *son3;
	}noeud, *pnoeud;

typedef struct mlarbre{
	pnoeud tree;
	struct mlarbre* next;
}larbre, *plarbre;

// Prototypes
pnoeud 		set_node		(t_point** img_point, int l, int c);
void 		set_son			(pnoeud node, pnoeud son, int nson);
pnoeud 		next_node		(pnoeud node, int nson);
void 		print_tree		(pnoeud node);
plarbre 	init_ltree		();
plarbre 	add_tree		(plarbre larbre, pnoeud noeud);
plarbre 	next_tree		(plarbre larbre);
void 		print_larbre	(plarbre larbre);

#endif