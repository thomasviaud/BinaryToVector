#include "../inc/latex.h"



void parcours_tree_print(pnoeud tree, FILE* file) {

	if(tree->son1 != NULL)
	{
		fprintf(file, "\\draw[black, line width=5mm] (%d,%d) -- (%d,%d);\n", tree->posx, tree->posy, tree->son1->posx, tree->son1->posy);
		parcours_tree_print(tree->son1, file);
	}
	if(tree->son2 != NULL)
	{
		fprintf(file, "\\draw[black, line width=5mm] (%d,%d) -- (%d,%d);\n", tree->posx, tree->posy, tree->son2->posx, tree->son2->posy);
		parcours_tree_print(tree->son2, file);
	}
	if(tree->son3 != NULL)
	{
		fprintf(file, "\\draw[black, line width=5mm] (%d,%d) -- (%d,%d);\n", tree->posx, tree->posy, tree->son3->posx, tree->son3->posy);
		parcours_tree_print(tree->son3, file);
	}
	if(tree->son4 != NULL)
	{
		fprintf(file, "\\draw[black, line width=5mm] (%d,%d) -- (%d,%d);\n", tree->posx, tree->posy, tree->son4->posx, tree->son4->posy);
		parcours_tree_print(tree->son4, file);
	}
	return;
}

void print_latex(plarbre list, FILE* file, uint32_t height, uint32_t width) {
 
    file = fopen("./bin/result.tex", "w");
 
    if (file != NULL)
    {
        fputs("\\documentclass{article}\n", file);
        fputs("\\usepackage{tikz}\n", file);    
        fputs("\\usepackage{caption}\n", file);
        fputs("\\begin{document}\n", file);
        fputs("\\begin{figure}\n", file);
        fputs("\\centering\n", file);
        fprintf(file,"\\begin{tikzpicture}[scale=%f]\n", fmin((float)10/height,(float)10/width));
        fputs("\\begin{scope}[rotate=-90]\n",file);
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
    system("pdflatex ./bin/result.tex");
    system("evince --fullscreen result.pdf &");
    return;
}