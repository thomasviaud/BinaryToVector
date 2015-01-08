#ifndef __PIXEL_H__
#define __PIXEL_H__
typedef struct{
    	char border;   	// 0 : interne  1 : contour
    	char mult;      // 0 : !mult    1 : mult

	}objet;

typedef union{
	char fond;
	objet obj;
}t_pixel;

char set_type(uint8_t **dist, uint32_t l, uint32_t c);
char set_border(uint8_t **dist, uint32_t l, uint32_t c);
char set_mult(uint8_t **dist, uint32_t l, uint32_t c);
void print_pixel(t_pixel **pix, uint32_t l, uint32_t c);
#endif