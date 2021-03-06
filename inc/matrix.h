#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "pixel.h"
#include "point.h"
void alloc_matrix(uint8_t ***pA, uint32_t nl, uint32_t nc);
void alloc_label_matrix(t_pixel ***pA, uint32_t nl, uint32_t nc);
void alloc_point_matrix(t_point ***pA, uint32_t nl, uint32_t nc);
void disp_matrix(uint8_t **pX, uint32_t nl, uint32_t nc);
void dup_matrix(uint8_t ** A, uint8_t **A_copy, uint32_t nl, uint32_t nc);
void dup_matrix_wborders(uint8_t ** A, uint8_t **A_copy, uint32_t nl, uint32_t nc);
#endif