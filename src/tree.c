///////////////////////////////////////////////////////////
// tree.c                                                //
// Contient les fonctions relatives à la gestion des     //
// arbres                                                //
///////////////////////////////////////////////////////////

#include "../inc/tree.h"


//
// set_node
// Créée un noeud à partir du point [l][c] de la matrice des points
//
pnoeud set_node(t_point** img_point, int l, int c){
	pnoeud new;
	new=(pnoeud)malloc(sizeof(noeud));
	new->point=img_point[l][c];
	new->posx=l;
	new->posy=c;
	new->son1=NULL;
	new->son2=NULL;
	new->son3=NULL;
	return new;
}

//
// set_son
// Attribue un fils numéro nson au noeud entré en paramètre
//
void set_son(pnoeud node, pnoeud son, int nson){
	if(nson==1) node->son1=son;
	if(nson==2) node->son2=son;
	if(nson==3) node->son3=son;
	return;
}

//
// next_node
// Pointe le noeud suivant de l'arbre
//
pnoeud next_node(pnoeud node, int nson){
	
	if(nson==1) return node->son1;
	if(nson==2) return node->son2;
	if(nson==3) return node->son3;
	return node;
}

//
// print_tree
// Affichage de l'arbre
//
void print_tree(pnoeud node){
	//printf(" %d ",node->point.type);
	printf("%d",node->point.type);
	printf("(");
	if(node->son1!=NULL) print_tree(next_node(node,1));
	printf(" ");
	if(node->son2!=NULL) print_tree(next_node(node,2));
	if(node->son3!=NULL) print_tree(next_node(node,3));
	printf(" ");
	printf(")");
	return;
}

//
// init_ltree
// Initialise la liste d'arbres à NULL
//
plarbre init_ltree(){
	return (plarbre)NULL;
}

//
// add_tree
// Ajoute un arbre à la liste larbre
//
plarbre add_tree(plarbre larbre, pnoeud noeud){
	plarbre new;
	new=(plarbre)malloc(sizeof(larbre));
	new->tree=noeud;
	new->next=larbre;
	return new;
}

//
// next_tree
//
//
plarbre next_tree(plarbre larbre){
	return larbre->next;
}

//
// print_larbre
//
//
void print_larbre(plarbre larbre){
	plarbre save;
	save=larbre;
	while(save!=NULL){
		print_tree(save->tree);
		printf("\n");
		save=next_tree(save);
	}
	return;
}