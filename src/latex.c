///////////////////////////////////////////////////////////
// latex.c                                               //
// Contient les fonctions relatives à la création du pdf //
///////////////////////////////////////////////////////////

#include "../inc/latex.h"

//
// parcours_tree_print
// Prend en arguments un arbre ainsi qu'un fichier dans lequel il faut écrire.
//
void parcours_tree_print(pnoeud tree, FILE* file) {

	if(tree->son1 != NULL)
	{
		fprintf(file, "\\draw[black, line width=1mm] (%d,%d) -- (%d,%d);\n", tree->posx, tree->posy, tree->son1->posx, tree->son1->posy);
		parcours_tree_print(tree->son1, file);
	}
	if(tree->son2 != NULL)
	{
		fprintf(file, "\\draw[black, line width=1mm] (%d,%d) -- (%d,%d);\n", tree->posx, tree->posy, tree->son2->posx, tree->son2->posy);
		parcours_tree_print(tree->son2, file);
	}
	if(tree->son3 != NULL)
	{
		fprintf(file, "\\draw[black, line width=1mm] (%d,%d) -- (%d,%d);\n", tree->posx, tree->posy, tree->son3->posx, tree->son3->posy);
		parcours_tree_print(tree->son3, file);
	}
	return;
}

//
// print_latex
// Prend en arguments une liste d'arbres, un fichier dans lequel il faut écrire ainsi que la hauteur/largeur de l'image.
//
void print_latex(plarbre list, FILE* file, uint32_t height, uint32_t width) {
 
    file = fopen("./result.tex", "w");
 
    if (file != NULL)
    {
        fputs("\\documentclass{article}\n", file);
        fputs("\\usepackage{tikz}\n", file);    
        fputs("\\usepackage{caption}\n", file);
        fputs("\\begin{document}\n", file);
        fputs("\\begin{figure}\n", file);
        fputs("\\centering\n", file);
        // Calcul de l'échelle en fonction de la taille de l'image
        fprintf(file,"\\begin{tikzpicture}[scale=%f]\n", fmin((float)10/height,(float)10/width));
        //Rotation pour commencer en haut à gauche
        fputs("\\begin{scope}[rotate=-90]\n",file);
        // Grille de la taille de notre image
        fprintf(file,"\\draw[color=gray, style=dotted] (0,0) grid[xstep=1, ystep=1] (%d,%d);\n", height, width);

        while (list != NULL)
        {
        parcours_tree_print(list->tree, file);
        list=list->next;
        }
        fputs("\\end{scope}\n", file);
        fputs("\\end{tikzpicture}\n", file);
        fputs("\\caption{Image}\n", file);
        fputs("\\end{figure}\n", file);
        fputs("\\end{document}\n", file);

        fclose(file);
    }
    system("pdflatex ./result.tex");
    system("evince --presentation ./result.pdf >> /dev/null &");
    return;
}