#include "../inc/douglas.h"
//
// douglas
// Prend en argument la matrice des points, sa taille
// et la précision demandée
// Retourne la liste des arbres contenant les squelettes
//
plarbre douglas(t_point** img_point, uint32_t nl, uint32_t nc, int ep){
	plarbre list,save;
	list=build_ltree(img_point,nl,nc);
	save=list;
	while(save!=NULL){
		edit_tree(save->tree,img_point,ep);
		save=next_tree(save);
	}
	return list;
}

//
// build_ltree
// Prend en argument la matrice des points, sa taille
// Retourne une liste d'arbres 
//
plarbre build_ltree(t_point** img_point, uint32_t nl, uint32_t nc){
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
// find_node
// Prend en argument un pointeur de noeud, la matrice des points, deux coordonnées
// Parcourt la matrice des points du noeud à son fils, et ajoute 
// au besoin un élément de type Noeud dans l'arbre
// Ne retourne rien
//
void find_node(pnoeud node, t_point** point, uint32_t l, uint32_t c, int num, int ep){
	int i,cpt=1;
	float dist;
	// Mise à jour du statut du pixel pour douglas
	point[l][c].is_done_d=1;
	// Le tableau voisins contiendra 1 pour tous les voisins du pixel point[l][c] en partant
	// du voisin NO dans le sens des aiguilles d'une montre
	int voisins[N];
		// Initialisation de voisins
		for(i=0;i<N;i++) voisins[i]=0;
	// Coordonnées des pixels voisins au pixel point[l][c]
	int coord[2*N]={-1,-1, -1,0, -1,1, 0,1, 1,1, 1,0, 1,-1, 0,-1};
	// Remplissage du tableau de voisins en connexité 8
	for(i=0;i<2*N;i+=2){
		if(point[l+coord[i]][c+coord[i+1]].type!=4 && point[l+coord[i]][c+coord[i+1]].is_done_d==0){

			voisins[i/2]=1;
			cpt++;
		}
	}
	cpt=0;
	for(i=0;i<N;i++) if(voisins[i]==1) cpt++;	
	if(cpt==0) return;
	// Suppression des pixels en connexité 8 qui sont voisins de ceux en connexité 4
	for(i=1;i<N;i+=2){
		if(voisins[i]==1){
			voisins[(i-1)%N]=0;
			voisins[(i+1)%N]=0;
		}
	}
	// Premier passage dans la fonction récursive : Borne ou Bifurcation
	if(l==node->posx && c==node->posy){
		// Type Borne : on avance
		if(node->point.type==1){
			i=0;
			while(voisins[i]==0) i++;
			
			find_node(node,point,l+coord[2*i],c+coord[2*i+1],num,ep);
		// Type Bifurcation : on avance sur le fils considéré
		}else{
			cpt=1;
			i=0;
			while(voisins[i]==0){
				i++;
				if(voisins[i]==1){
					cpt++;
					if(cpt==num) break;
				}
			}
			
			find_node(node,point,l+coord[2*i],c+coord[2*i+1],num,ep);
		}
	// Type point : on avance
	}else if(point[l][c].type==0){
			i=0;
			while(voisins[i]==0) i++;
			
			find_node(node,point,l+coord[2*i],c+coord[2*i+1],num,ep);		
	// Type Borne/Bifurcation : on s'arrête, on a atteint le noeud fils
	}else if(point[l][c].type==1 || point[l][c].type==3){ 
			return;
	// Type Noeud : on compare sa distance par rapport au noeud Père et fils,
	//				on l'ajoute si cette distance dépasse le seuil
	//				et on avance
	}else if(point[l][c].type==2){
		if(num==1){
			dist=calc_dist(node,node->son1,l,c);
			if(dist>ep) node=ins_node(node,node->son1,point,l,c,num);
			printf("Distance=%f\n",dist);
		}
		else if(num==2){
			dist=calc_dist(node,node->son2,l,c);
			if(dist>ep) node=ins_node(node,node->son2,point,l,c,num);
			printf("Distance=%f\n",dist);
		}
		else if(num==3){
			dist=calc_dist(node,node->son3,l,c);
			if(dist>ep) node=ins_node(node,node->son3,point,l,c,num);
			printf("Distance=%f\n",dist);
		}
		i=0;
		while(voisins[i]==0) i++;	
		
		find_node(node,point,l+coord[2*i],c+coord[2*i+1],num,ep);

	}
	return;
}

//
// edit_tree
// Prend en argument un pointeur d'arbre, la matrice des points, des coordonnées et
// un seuil
// Retourne l'arbre complété par les points de type Noeud qui sont à une distance supérieure
// au seuil de l'arbre. 
//
void edit_tree(pnoeud tree, t_point** point, int ep){
	int x=tree->posx;
	int y=tree->posy;
	int num;

	// Si le pointeur est sur un Noeud : on va au prochain noeud de l'arbre
	if(tree->point.type==2) edit_tree(tree->son1,point,ep);

	// Parcours de l'arbre en profondeur
	if(tree->son1!=NULL){
		num=1;
		find_node(tree,point,x,y,num,ep);
		edit_tree(tree->son1,point,ep);		
	}
	if(tree->son2!=NULL){
		num=2;
		find_node(tree,point,x,y,num,ep);
		edit_tree(tree->son2,point,ep);
	}
	if(tree->son3!=NULL){
		num=3;
		find_node(tree,point,x,y,num,ep);
		edit_tree(tree->son3,point,ep);
	}
	return;
}

//
// ins_node
// Prend en argument deux pointeurs d'arbre, la matrice des points, des coordonnées 
// Ajoute les points de type noeud à l'arbre si leur distance au graphe
// est supérieure au seuil
// Retourne l'arbre complété
//
pnoeud ins_node(pnoeud father, pnoeud son, t_point** point, uint32_t l, uint32_t c, int n_fils){
	pnoeud new;
	new=set_node(point,l,c);
	new->son1=son;
	if(n_fils==1)	father->son1=new;
	if(n_fils==2)	father->son2=new;
	if(n_fils==3)	father->son3=new;
	return new;
}


//
//
// parcours_img 
// Fonction récursive qui prend en argument la matrice des points 
// et des coordonnées 
// Retourne un noeud d'arbre
//
void parcours_img(pnoeud tree, t_point** point, uint32_t l, uint32_t c){
	// Mise à jour du statut du point courant
	point[l][c].is_done=1;
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
		tree->feuille=1;
		return;
	} 


	// Ajout du pixel courant s'il est du bon type (1 ou 3) dans l'arbre	
	if((point[l][c].type)%2==1){	
		if(point[l][c].type==3){
			tree->posx=l;
			tree->posy=c;
			tree->point=point[l][c];
		}
		if(point[l][c].type==1) tree->borne=1;
		// Appel récursif pour chaque voisin non lu
		for(i=0;i<2*N;i+=2){
			if(voisins[i/2]==1){
				n_node=set_node(point,l,c);
				parcours_img(n_node,point,l+coord[i],c+coord[i+1]);
				// Lien entre n_node et tree
				set_son(tree,n_node,n);
				n++;
			}
		}
	// Le pixel est de type Point ou Noeud : on avance quand même
	}else{
		// Appel récursif pour chaque voisin non lu
		for(i=0;i<2*N;i+=2){
			if(voisins[i/2]==1){
				parcours_img(tree,point,l+coord[i],c+coord[i+1]);
				break;

			}
		}

	}
	return;
}

float calc_dist(pnoeud node1, pnoeud node2, uint32_t li, uint32_t co){

	float a,b,orth;
	// Calcul des coefficients de l'équation de la droite

	// Résolution du système d'équations 
	// | y = ax + b
	// | y' = ax' + b
	// On obtient en substituant b par y' - ax' 
	// a = y-y'/x-x'
	// b = y'- ax'
	if(node2->posx!=node1->posx) a=((float)node2->posy - node1->posy)/(node2->posx - node1->posx);
	else a=0;
	b=(float)node2->posy - a*node2->posx;

	// Calcul de la distance du point à la droite d'équation ax + by + c = 0
	orth=fabs(a*li - co + b)/sqrt(1+a*a);
	return orth;
}