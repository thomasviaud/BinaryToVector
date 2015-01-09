#ifndef __PIXEL_H__
#define __PIXEL_H__
typedef struct{
    	char border;   	// 2 : contour	3 : interne
    	char mult;      // 0 : !mult    1 : mult
    	char squel;		// 0 : !squel   1 : squel
	}objet;

typedef union{
	char fond;
	objet obj;
}t_pixel;

char set_type(uint8_t **dist, uint32_t l, uint32_t c);
char set_border(uint8_t **dist, uint32_t l, uint32_t c);
char set_mult(uint8_t **dist, uint32_t l, uint32_t c);
void print_pixel(t_pixel **pix, uint32_t l, uint32_t c);
void print_pixel_list(t_pixel pix);
#endif