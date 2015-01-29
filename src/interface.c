///////////////////////////////////////////////////////////
// interface.c                                           //
// Fonctions d'interface                                 //
//                                                   	 //
///////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/interface.h"

int displayMenu(void)
{
    int mode=0;
    puts("\033[H\033[2J");
    puts("=====================================================");
	puts("|                VECTORISATION D'IMAGE              |");
	puts("|        Projet Algorithmique et Programmation      |");
	puts("|        HOAREAU Jordan           VIAUD Thomas      |");
	puts("|                   IRM 3A 2014/2015                |");
	puts("=====================================================");
    puts("======================= Menu ========================");
	puts("|                                                   |");
	puts("| 1- Choix de l'image                               |");
	puts("| 2- Démonstration 1                                |");
	puts("| 3- Démonstration 2                                |");
	puts("| 4- Démonstration 3                                |");
	puts("|                                                   |");
	puts("=====================================================");
	scanf("%d",&mode);
	return mode;
}