#ifndef __LIST_H__
#define __LIST_H__
typedef struct list{
    t_pixel v_pixel;
    struct list *next;
} t_list, *t_plist;

t_plist create_void (void);
int is_void (t_plist list);
t_plist add_list (t_pixel pix, t_plist list);
t_pixel head_list(t_plist list);
t_plist end_list(t_plist list);
void print_list (t_plist list);
#endif