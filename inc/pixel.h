#ifndef __PIXEL_H__
#define __PIXEL_H__
typedef struct{
    char type;      // 0 : fond     1 : objet
    char border;   	// 0 : fond     1 : contour     2 : interne
    char mult;      // 0 : !mult    1 : mult
    int posN;
    int posM;
}t_pixel;
void alloc_matrix(uint8_t ***pA, uint32_t nl, uint32_t nc);
void disp_matrix(uint8_t ***pX, uint32_t nl, uint32_t nc);
char set_type(int l, int c, uint8_t ***dist);
char set_border(int l, int c, uint8_t ***dist);
char set_mult(int l, int c, uint8_t ***dist);
#endif