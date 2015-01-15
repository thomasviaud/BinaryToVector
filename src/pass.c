///////////////////////////////////////////////////////////
// pass.c                                                //
// Contient les fonctions relatives aux deux passes pour //
// retourner une matrice contenant les distances au fond //
// pour chaque pixel                                     //
///////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "../inc/pixel.h"
#include "../inc/matrix.h"
#include "../inc/pass.h"

//
// first_pass
// Prend en argument une matrice A, une matrice B et leur
// dimension, indique dans chaque pixel de la matrice B leur distance
// au fond de l'image en passant de haut en bas et de gauche à droite
//
void first_pass(uint8_t **bin, uint8_t **dist, uint32_t nl, uint32_t nc){
    int i,j;
    for(i=1;i<nl+1;i++){
        for(j=1;j<nc+1;j++){
            if(bin[i][j]==1){
                    dist[i][j]=(int)fmin(dist[i-1][j],dist[i][j-1])+1;
            }
            else{
                dist[i][j]=0;
            }
        }
    }
}
//
// last_pass
// Prend en argument une matrice A, une matrice B et leur
// dimension, indique dans chaque pixel de la matrice B leur distance
// au fond de l'image en passant de bas en haut et de droite à gauche
//
void last_pass(uint8_t **bin, uint8_t **dist, uint32_t nl, uint32_t nc){
    int i,j;
    for(i=nl+1;i>0;i--){
        for(j=nc+1;j>0;j--){
            if(bin[i][j]==1){
                    dist[i][j]=(uint8_t)fmin(dist[i][j],fmin(dist[i][j+1]+1,dist[i+1][j]+1));
            }
            else{
                dist[i][j]=0;
            }
        }
    }
}
