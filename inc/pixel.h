#ifndef __PIXEL_H__
#define __PIXEL_H__
typedef struct{
    char type;      // 0 : fond     1 : objet
    char border;   	// 0 : fond     1 : contour     2 : interne
    char mult;      // 0 : !mult    1 : mult
    int posN;
    int posM;
}t_pixel;
char set_type(uint8_t ***dist, uint32_t l, uint32_t c);
char set_border(uint8_t ***dist, uint32_t l, uint32_t c);
char set_mult(uint8_t ***dist, uint32_t l, uint32_t c);
void print_pixel(t_pixel pix);
#endif