#include "../inc/douglas.h"
//
// douglas
// Prend en argument la matrice des points, sa taille
// et la précision demandée
// Retourne une liste d'arbres 
//
plarbre douglas(t_point** img_point, uint32_t nl, uint32_t nc){
	// Liste d'arbres retournée par la fonction
	plarbre list;
	list=init_ltree();
	// Variable contenant l'arbre qui va être ajouté pour chaque élément de l'image
	pnoeud tree=NULL;

	int i,j;
	for(i=0;i<nl;i++){
		for(j=0;j<nc;j++){
			if(img_point[i][j].is_done==0 && img_point[i][j].type!=4){
				tree=set_node(img_point,i,j);
				parcours_img(tree,img_point,i,j);
				list=add_tree(list,tree);
			}
		}
	}
	return list;
}
//
// parcours_img 
// Fonction récursive qui prend en argument la matrice des points, sa taille 
// et des coordonnées
// Retourne un noeud d'arbre
//
void parcours_img(pnoeud tree, t_point** point, uint32_t l, uint32_t c){
	printf("Position [%d][%d]\n",l,c);
	// Variable qui contient l'arbre retourné par la fonction
	pnoeud n_node;

	int cpt=0;
	int n=1;
	int i;

	// Le tableau voisins contiendra 1 pour tous les voisins du pixel point[l][c] en partant
	// du voisin NO dans le sens des aiguilles d'une montre
	int voisins[N];
		// Initialisation de voisins
		for(i=0;i<N;i++) voisins[i]=0;
	// Coordonnées des pixels voisins au pixel point[l][c]
	int coord[2*N]={-1,-1, -1,0, -1,1, 0,1, 1,1, 1,0, 1,-1, 0,-1};
	// Remplissage du tableau de voisins en connexité 8
	for(i=0;i<2*N;i+=2){
		if(point[l+coord[i]][c+coord[i+1]].type!=4 && point[l+coord[i]][c+coord[i+1]].is_done==0){
			
			voisins[i/2]=1;
			cpt++;
		}
	}	
	// Suppression des pixels en connexité 8 qui sont voisins de ceux en connexité 4
	for(i=1;i<N;i+=2){
		if(voisins[i]==1){
			voisins[(i-1)%N]=0;
			voisins[(i+1)%N]=0;
		}
	}

	// Condition d'arrêt : le pixel n'a pas de voisins non lus ni de l'image
	if(!cpt){
		tree->point=point[l][c];
		tree->posx=l;
		tree->posy=c;
		return;
	} 

	// Mise à jour du statut du point courant
	point[l][c].is_done=1;
	// Ajout du pixel courant s'il est du bon type (1 ou 3) dans l'arbre	
	if((point[l][c].type)%2==1){
	printf("Type Borne/Bifurcation\n");		
		if(point[l][c].type==3){
			tree->posx=l;
			tree->posy=c;
			tree->point=point[l][c];
		}
		if(point[l][c].type==1) tree->borne=1;
		// Appel récursif pour chaque voisin non lu
		for(i=0;i<2*N;i+=2){
			if(voisins[i/2]==1){
				printf("Prochain voisin : [%d][%d]\n",coord[i]+l,coord[i+1]+c);
				n_node=set_node(point,l,c);
				parcours_img(n_node,point,l+coord[i],c+coord[i+1]);
				// Lien entre n_node et tree
				printf("\n");
				set_son(tree,n_node,n);
				n++;
			}
		}
	// Le pixel est de type Point ou Noeud : on avance quand même
	}else{
		printf("Type Point/Noeud\n");
		// Appel récursif pour chaque voisin non lu
		for(i=0;i<2*N;i+=2){
			if(voisins[i/2]==1){
				parcours_img(tree,point,l+coord[i],c+coord[i+1]);
			}
		}

	}
	return;
}