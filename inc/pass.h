#ifndef __PASS_H__
#define __PASS_H__
void alloc_matrix(uint8_t ***pA, uint32_t nl, uint32_t nc);
void disp_matrix(uint8_t ***pX, uint32_t nl, uint32_t nc);
void first_pass(uint8_t ***bin, uint8_t ***dist, uint32_t nl, uint32_t nc);
void last_pass(uint8_t ***bin, uint8_t *** dist, uint32_t nl, uint32_t nc);
#endif
