#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../inc/arbre.h"

t_noeud create_node(t_parbre *arbre, t_point pt, uint32_t l, uint32_t c){
	t_noeud new;
	new->point=pt;
	new->posx=l;
	new->posy=c;
	return new;
}
void set_bro(t_noeud fat, t_noeud bro){
	fat->bro=bro;
}
void set_son(t_noeud fat, t_noeud bro){
	fat->son=son;
}

void 