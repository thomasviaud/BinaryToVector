#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/bmp_reader.h"
#include "../inc/pass.h"
#include "../inc/pixel.h"
#include "../inc/matrix.h"
#include "../inc/list.h"
#include "../inc/skel.h"
#include "../inc/point.h"
#include "../inc/tree.h"
#include "../inc/douglas.h"
#define NAMESIZE 255

int main(){
	int mode;

	// Saisie du mode et du nom de l'image
	do{
	system("clear");
	printf("=====================================================\n");
	printf("|                VECTORISATION D'IMAGE              |\n");
	printf("|        Projet Algorithmique et Programmation      |\n");
	printf("|        HOAREAU Jordan           VIAUD Thomas      |\n");
	printf("|                   IRM 3A 2014/2015                |\n");
	printf("=====================================================\n");
	puts("---------Menu---------\n");
	puts("|                    |\n");
	puts("| 1- Pas à pas       |\n");
	puts("| 2- Démonstration   |\n");
	puts("|                    |\n");
	puts("----------------------\n");
	scanf("%d",&mode);
	}while(mode < 1 && mode >2);

	puts("\n\nEntrez le nom de l'image souhaitée stockée dans le dossier img sous le format .bmp : ");
	char *nom_img;
	nom_img=(char*)malloc(NAMESIZE*sizeof(char));
	scanf("%s",nom_img);
	char path[]="./img/";
	char format[]=".bmp";
	strcat(path,nom_img);
	strcat(path,format);

	FILE * fBMP = fopen(path,"rb+");
	if (fBMP != NULL)
	{
		puts("File opened.\n");

		BmpWorker_fileHeader * fileHeader = (BmpWorker_fileHeader *) malloc(
			sizeof(BmpWorker_fileHeader));

		BmpWorker_infoHeader * bmpHeader = (BmpWorker_infoHeader *) malloc(
			sizeof(BmpWorker_infoHeader));

		if (BmpWorker_FileHeader_read(fBMP, fileHeader) == SUCCESS)
		{
			// BmpWorker_FileHeader_display(fileHeader);

			if (BmpWorker_InfoHeader_read(fBMP, bmpHeader) == SUCCESS)
			{
				uint32_t width = bmpHeader->img_width;
				uint32_t height = bmpHeader->img_height;

				uint8_t * pData = (uint8_t *) malloc(bmpHeader->bmp_bytesz
				* sizeof(uint8_t));

				//BmpWorker_InfoHeader_display(bmpHeader);
				if (BmpWorker_RawData_read(fBMP, fileHeader, bmpHeader, pData) == SUCCESS)
				{
					//Uncomment for testing following functions
					//BmpWorker_RawData_display(bmpHeader, pData);
					//BmpWorker_RawData_white2black(bmpHeader, pData);
					//BmpWorker_RawData_display(bmpHeader, pData);
					//BmpWorker_saveOnDisk("../img/test.bmp", fileHeader, bmpHeader, pData);



					pData = BmpWorker_RawData_removeEndlinePaddingBytes(pData, bmpHeader); // ALIGNEMENT SUR 32 BITS
					pData = BmpWorker_RawData_invertLines(pData, height, width // INVERSE LES LIGNES, PERMET DE LIRE L'IMAGE DANS LE BON SENS
					  * bmpHeader->bitspp / 8);

					// Déclaration matrice img_bin
					uint8_t **img_bin;
					alloc_matrix(&img_bin,height,width);

					// Remplissage matrice img_bin
					if (BmpWorker_img_bin(img_bin, bmpHeader, pData) == 0) 
                    {
                        fprintf(stderr, "Votre image n'est pas binaire !\n");
                        return ERROR_INVALID_DATA;
                    }

					// Affichage matrice img_bin
					printf("===================================\n");
					printf("===== TRANSFORMEE EN DISTANCE =====\n");
					printf("===================================\n");
					puts("===== MATRICE BINAIRE =====");
					disp_matrix(img_bin,height,width);

					// Déclaration img_bin_borders et duplication
					uint8_t **img_bin_borders;
					alloc_matrix(&img_bin_borders,height+2,width+2);
					dup_matrix_wborders(img_bin,img_bin_borders,height,width);

					// Déclaration img_dist et duplication
					uint8_t **img_dist;
					alloc_matrix(&img_dist,height+2,width+2);
					dup_matrix(img_bin_borders,img_dist,height+2,width+2);

					puts("===== MATRICE BINAIRE COPIEE =====");
					disp_matrix(img_bin_borders,height+2,width+2);
					/*********************************/
					/*    TRANSFORMEE EN DISTANCE    */
					/*********************************/
					// Première passe
					first_pass(img_bin_borders, img_dist, height, width);
					puts("===== MATRICE PASSE 1 =====");
					disp_matrix(img_dist,height+2,width+2);

					// Seconde passe
					last_pass(img_bin_borders, img_dist, height, width);
					puts("===== MATRICE PASSE 2 =====");
					disp_matrix(img_dist,height+2,width+2);
					if(mode==1) getchar();
					/*********************************/

					/*********************************/
					/*        SQUELETTISATION        */
					/*********************************/
					printf("===================================\n");
					printf("========= SQUELETTISATION =========\n");
					printf("===================================\n");
					// Déclaration et allocation en mémoire de img_label_matrix
					t_pixel **img_label_matrix;
					alloc_label_matrix(&img_label_matrix,height+2,width+2);

					// Déclaration et initialisation de img_label_list
					t_plist img_label_list;
					img_label_list=create_void();

					// Squelettisation
					puts("===== CREATION DU SQUELETTE ====="); 
					skelet(img_dist, img_label_matrix, &img_label_list, height+2,width+2);

					/*********************************/

					/*********************************/
					/*        DOUGLAS-PEUCKER        */
					/*********************************/					
					// Déclaration et allocation en mémoire de img_point_matrix
					t_point ** img_point_matrix;
					alloc_point_matrix(&img_point_matrix,height+2,width+2);
					// Douglas-Peucker
					puts("===== MATRICE POINT =====");
					printf("Po = Point\nBo = Borne\nNo = Noeud\nBi = Bifurcation\n");
					set_point_matrix(img_point_matrix,img_label_matrix,height+2,width+2);
					plarbre img_tree_list;
					img_tree_list=init_ltree();
					img_tree_list=douglas(img_point_matrix,height+2,width+2);
					print_larbre(img_tree_list);
					/*
					// Test arbres
					plarbre larbre;
					larbre=init_ltree();
					// Création arbre 1
					pnoeud img_tree, img_tree2, son1, son2, son21,son3,son4;
					img_tree=set_node(img_point_matrix,0,0);
					son1=set_node(img_point_matrix,3,2);
					son2=set_node(img_point_matrix,6,6);
					son21=set_node(img_point_matrix,3,6);
					son1->leaf=1;
					son21->leaf=1;
					printf("Premier noeud : %d\n",img_tree->point.type);
					set_son(img_tree,son1,1);
					set_son(img_tree,son2,2);
					set_son(img_tree->son2,son21,1);
					printf("Fils 1 : %d \n",img_tree->son1->point.type);
					printf("Fils 2 : %d\n",img_tree->son2->point.type);
					print_tree(img_tree);
					// Ajout arbre 1 dans liste
					printf("\n");
					larbre=add_tree(larbre,img_tree);

					// Création arbre 2
					img_tree2=set_node(img_point_matrix,0,0);
					son3=set_node(img_point_matrix,6,6);
					son4=set_node(img_point_matrix,3,6);
					son4->leaf=1;
					printf("h");
					printf("Premier noeud : %d\n",img_tree2->point.type);
					set_son(img_tree2,son3,1);
					set_son(img_tree2->son1,son4,1);
					printf("Fils 1 : %d \n",img_tree2->son1->point.type);
					printf("Fils 11 : %d\n",img_tree2->son1->son1->point.type);
					print_tree(img_tree2);
					// Ajout dans liste
					larbre=add_tree(larbre,img_tree2);
					printf("\n");
					print_larbre(larbre);*/

					
					
				}
				else
				{
					fprintf(stderr, "Can't read bitmap data\n");
				}
				free(pData);
		  }
		  else
		  {
			fprintf(stderr, "Can't read info header\n");
		  }
		}
		else
		{
		  fprintf(stderr, "Can't read file header.\n");
		}

		if (fclose(fBMP) != 0)
		{
		  fprintf(stderr, "Cannot close BMP file.\n");
		  return ERROR_CLOSING_FILE;
		}
	}
	else
	{
		fprintf(stderr, "Can't open the BMP file.\n");
	}

	puts("\nQuit.");
	return EXIT_SUCCESS;
}

