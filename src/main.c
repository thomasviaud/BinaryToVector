/** 
 *
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de Polytech Marseille. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

/**
 * @author VIAUD Thomas <thomas.viaud@etu.univ-amu.fr>
 * @author HOAREAU Jordan <jordan.hoareau@etu.univ-amu.fr>
 *
 * @version 1.0.0 / 02-02-2015
 * @todo Implementer Douglas-Peucker
 * @bug 
 */


/**
 * @file main.c
 * @brief Vectorisation d'images binaires
 *
 * Lis une image bmp binaire, en extrait un squelette et 
 * rend un pdf vectoriel de cette image vectorisée.
 */

#include "../inc/main.h"


#define NAMESIZE 255

int main(){

	char *nom_img;
	system("clear");
	puts("=====================================================");
	puts("|                VECTORISATION D'IMAGE              |");
	puts("|        Projet Algorithmique et Programmation      |");
	puts("|        HOAREAU Jordan           VIAUD Thomas      |");
	puts("|                   IRM 3A 2014/2015                |");
	puts("=====================================================");

	char path[30];

	switch(displayMenu())
	{
	case 1:

		printf("Image au format .bmp : ");
		nom_img=(char*)malloc(NAMESIZE*sizeof(char));
		scanf("%s",nom_img);
		strcpy(path,"./img/");
		char format[]=".bmp";
		strcat(path,nom_img);
		strcat(path,format);
		break;

	case 2 :
		strcpy(path,"./img/full.bmp");
		break;

	case 3 :
		strcpy(path,"./img/random.bmp");
		break;

	case 4 :
		strcpy(path,"./img/face.bmp");
		break;
	case 5:
		strcpy(path,"./img/coin.bmp");
		break;
	default :
		return 0;
	}

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

                    // Mode step by step
                    int step= 0;
					printf("Step by step ? (Oui : 1) ");
					scanf("%d",&step);

					// Affichage matrice img_bin
					puts("=====================================================");
					puts("|               TRANSFORMEE EN DISTANCE             |");
					puts("=====================================================");
					if(step==1) getchar();
					if(step==1) getchar();
					puts("================== MATRICE BINAIRE ==================\n");
					if(step==1) getchar();
					disp_matrix(img_bin,height,width);
					if(step==1) getchar();
					// Déclaration img_bin_borders et duplication
					uint8_t **img_bin_borders;
					alloc_matrix(&img_bin_borders,height+2,width+2);
					dup_matrix_wborders(img_bin,img_bin_borders,height,width);

					// Déclaration img_dist et duplication
					uint8_t **img_dist;
					alloc_matrix(&img_dist,height+2,width+2);
					dup_matrix(img_bin_borders,img_dist,height+2,width+2);


					puts("============= MATRICE BINAIRE COPIEE ==============\n");
					if(step==1) getchar();
					disp_matrix(img_bin_borders,height+2,width+2);
					if(step==1) getchar();

					// PREMIERE PASSE
					first_pass(img_bin_borders, img_dist, height, width);

					puts("================= MATRICE PASSE 1 =================\n");
					if(step==1) getchar();
					disp_matrix(img_dist,height+2,width+2);
					if(step==1) getchar();

					// SECONDE PASSE
					last_pass(img_bin_borders, img_dist, height, width);

					puts("================= MATRICE PASSE 2 =================\n");
					if(step==1) getchar();
					disp_matrix(img_dist,height+2,width+2);
					if(step==1) getchar();


					puts("=====================================================");
					puts("|                   SQUELETTISATION                  |");
					puts("=====================================================");
					// Déclaration et allocation en mémoire de img_label_matrix
					t_pixel **img_label_matrix;
					alloc_label_matrix(&img_label_matrix,height+2,width+2);

					// Déclaration et initialisation de img_label_list
					t_plist img_label_list;
					img_label_list=create_void();

					// Squelettisation
					puts("================ CREATION DU SQUELETTE ==============\n"); 
					if(step==1) getchar();
					skelet(img_dist, img_label_matrix, &img_label_list, height+2,width+2, step);


					puts("=====================================================");
					puts("|                   DOUGLAS-PEUCKER                  |");
					puts("=====================================================");			
					// Déclaration et allocation en mémoire de img_point_matrix
					t_point ** img_point_matrix;
					alloc_point_matrix(&img_point_matrix,height+2,width+2);
					// Douglas-Peucker
					puts("==================== MATRICE POINT ==================\n");
					printf("Po = Point\nBo = Borne\nNo = Noeud\nBi = Bifurcation\n");
					set_point_matrix(img_point_matrix,img_label_matrix,height+2,width+2);

					float seuil;
					printf("Entrez le seuil epsilon : ");
					scanf("%f",&seuil);

					plarbre img_tree_list;
					img_tree_list=init_ltree();
					img_tree_list=douglas(img_point_matrix,height+2,width+2,seuil);
					printf("Arbre final : \n");
					print_larbre(img_tree_list);


					FILE* file = NULL;
					print_latex(img_tree_list, file, height, width);
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

