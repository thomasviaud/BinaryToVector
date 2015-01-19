#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../inc/pixel.h"
#include "../inc/point.h"
#include "../inc/arbre.h"

t_noeud create_node(t_parbre *arbre, t_point pt, uint32_t l, uint32_t c){
	t_noeud new;
	new.point=pt;
	new.posx=l;
	new.posy=c;
	return new;
}
