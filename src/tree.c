#include "../inc/tree.h"

pnoeud set_node(t_point** img_point, int l, int c){
	pnoeud new;
	new=(pnoeud)malloc(sizeof(noeud));
	new->point=img_point[l][c];
	new->posx=l;
	new->posy=c;
	new->son1=NULL;
	new->son2=NULL;
	new->son3=NULL;
	new->son4=NULL;
	return new;
}

void set_son(pnoeud node, pnoeud son, int nson){
	if(nson==1) node->son1=son;
	if(nson==2) node->son2=son;
	if(nson==3) node->son3=son;
	if(nson==4) node->son4=son;	
	return;
}

pnoeud next_node(pnoeud node, int nson){
	
	if(nson==1) return node->son1;
	if(nson==2) return node->son2;
	if(nson==3) return node->son3;
	if(nson==4) return node->son4;
	return node;
}

void print_tree(pnoeud node){
	//printf(" %d ",node->point.type);
	printf("%d",node->point.type);
	printf("(");
	if(node->son1!=NULL) print_tree(next_node(node,1));
	printf(" ");
	if(node->son2!=NULL) print_tree(next_node(node,2));
	if(node->son3!=NULL) print_tree(next_node(node,3));
	printf(" ");
	if(node->son4!=NULL) print_tree(next_node(node,4));
	printf(")");
	return;
}

plarbre init_ltree(){
	return (plarbre)NULL;
}

plarbre add_tree(plarbre larbre, pnoeud noeud){
	plarbre new;
	new=(plarbre)malloc(sizeof(larbre));
	new->tree=noeud;
	new->next=larbre;
	return new;
}

plarbre next_tree(plarbre larbre){
	return larbre->next;
}

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