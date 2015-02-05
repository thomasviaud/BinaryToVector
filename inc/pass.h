#ifndef __PASS_H__
#define __PASS_H__
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "pixel.h"
#include "matrix.h"
void first_pass(uint8_t **bin, uint8_t **dist, uint32_t nl, uint32_t nc);
void last_pass(uint8_t **bin, uint8_t **dist, uint32_t nl, uint32_t nc);
#endif
