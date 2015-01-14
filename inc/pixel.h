#ifndef __PIXEL_H__
#define __PIXEL_H__

// Structure Objet
// Partie décrivant le côté objet du pixel
typedef struct{
    	char border;   	// 2 : contour	3 : interne
    	char mult;      // 1 : !mult    2 : mult
    	char squel;		// 1 : !squel   2 : squel
	}objet;

// Union Pixel
// Contient deux champs fond et obj pour correspondre au cas
// où le pixel est dans le fond ou dans l'image
typedef union{
	char fond;
	objet obj;
}t_pixel;

void alloc_label_matrix(t_pixel ***pA, uint32_t nl, uint32_t nc);
char set_type(uint8_t **dist, uint32_t l, uint32_t c);
char set_border(uint8_t **dist, uint32_t l, uint32_t c);
char set_mult(uint8_t **dist, uint32_t l, uint32_t c);
void print_pixel(t_pixel **pix, uint32_t l, uint32_t c);
void print_pixel_list(t_pixel pix);
void disp_matrix_label(t_pixel **img_label_matrix, uint32_t nl, uint32_t nc);
void disp_skel(t_pixel **img_label_matrix, uint32_t nl, uint32_t nc);
void print_pixel_skel(t_pixel **pix, uint32_t l, uint32_t c);		
#endif