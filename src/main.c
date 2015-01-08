/*
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/bmp_reader.h"
#include "../inc/pass.h"
#include "../inc/pixel.h"
#include "../inc/list.h"
#include "../inc/skel.h"

int
main(void)
{
	puts("BmpReader started.\n");

	FILE * fBMP = fopen("./img/test_30x20.bmp","rb+");
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
					puts("===== MATRICE BINAIRE =====");
					disp_matrix(&img_bin,height,width);

					// Déclaration img_dist + Duplication img_bin
					uint8_t **img_dist;
					alloc_matrix(&img_dist,height,width);
					int i=0;
					for(i = 0; i < height; ++ i) memcpy(&(img_dist[i][0]), &(img_bin[i][0]), height * sizeof(uint8_t));

					// Première passe
					first_pass(&img_bin, &img_dist, height, width);
					puts("===== MATRICE PASSE 1 =====");
					disp_matrix(&img_dist,height,width);

					// Seconde passe
					last_pass(&img_bin, &img_dist, height, width);
					puts("===== MATRICE PASSE 2 =====");
					disp_matrix(&img_dist,height,width);

					// Déclaration img_label
					t_pixel **img_label_matrix;
					alloc_label_matrix(&img_label_matrix,height,width);
					// Squelettisation
					puts("===== SQUELETTE ====="); 
					skelet(&img_dist, &img_label_matrix,height,width);
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

