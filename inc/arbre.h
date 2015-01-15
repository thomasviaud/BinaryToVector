#ifndef __ARBRE_H__
#define __ARBRE_H__
typedef struct mm{
	t_point point;
	char posx;
	char posy;
	struct mm *son1;
	struct mm *son2;
	struct mm *son3;
	struct mm *son4;
	}t_noeud, *t_parbre;
#endif