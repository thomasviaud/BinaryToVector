///////////////////////////////////////////////////////////
// list.c                                                //
// Contient les fonctions relatives à la gestion des     //
// listes                                                //
///////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "../inc/pixel.h"
#include "../inc/list.h"

//
// create_void
// Ne prend aucun argument 
// Retourne un pointeur de liste NULL 
//
t_plist create_void(){
	return (t_plist)NULL;
}

//
// is_void
// Prend en argument un pointeur de liste
// Retourne 1 si la liste est vide, 0 sinon
//
int is_void(t_plist list){
	return list==create_void();
}

//
// add_list
// Prend en argument un pixel et ajoute cette valeur en tête de liste.
// Retourne le pointeur vers ce pixel
//
t_plist add_list (t_pixel pix, t_plist list){
	t_plist new;
	new =(t_plist)malloc(sizeof(t_maillon));
	new->v_pixel=pix;
	new->next=list;
	return new;
}

//
// head_list
// Prend en argument le pointeur sur la liste
// Retourne la valeur de la tête de liste
//
t_pixel head_list(t_plist list){
	assert(!is_void(list));
	return(list->v_pixel);
}

//
// end_list
// Prend en argument le pointeur sur la liste
// Retourne le pointeur suivant dans la liste
//
t_plist end_list(t_plist list){
	assert(!is_void(list));
	return(list->next);
}
//
// print_list
// Prend en argument le pointeur de début de liste 
// Retourne la liste affichée en console
//
void print_list(t_plist list){
	int cpt=0;
	while(list!=NULL){
		print_pixel_list(head_list(list));
		printf("\t");
		list=end_list(list);        
		cpt++;
		// Retour à la ligne
		if(cpt==10){
			printf("\n");
			cpt=0;
			}
		}
}