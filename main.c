/*
 * main.c
 *
 *  Created on: 2011-07-10
 *      Author: Thomas Bores
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp_reader.h"
int
main(void)
{
  puts("BmpWorker started.\n");

    FILE * fBMP = fopen("./img/test_32x20.bmp",
        "rb+");

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

        // BmpWorker_InfoHeader_display(bmpHeader);
        if (BmpWorker_RawData_read(fBMP, fileHeader, bmpHeader, pData)
            == SUCCESS)
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
          allocmatrix_bin(&img_bin,height,width);

          // Remplissage matrice img_bin
          BmpWorker_img_bin(img_bin, bmpHeader, pData);


          //Affichage matrice img_bin

          int i = 0;
          int j = 0;
          for (i = 0 ; i<height ; i++) {
            for(j = 0 ; j<width ; j++){
              fprintf(stdout, "%d ", img_bin[i][j]);
            }
            fprintf(stdout, "\n");
          }
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
