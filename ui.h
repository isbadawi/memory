#ifndef _ui_h_included
#define _ui_h_included

#include <stdint.h>

typedef struct {
    uint8_t r, g, b;
} ui_color;

typedef enum {
    ui_event_quit,
    ui_event_click
} ui_event_type;

typedef struct {
    ui_event_type type;
    int x;
    int y;
} ui_click_event;

typedef union {
    ui_event_type type;
    ui_click_event click;
} ui_event;

typedef void* ui_icon;

int ui_init();
void ui_destroy();

ui_icon ui_load_icon(char* filename);
ui_icon* ui_load_icons(int how_many);
int ui_icons_equal(ui_icon i1, ui_icon i2);

void ui_draw_square(ui_color color, int x, int y, int side);
void ui_draw_icon(ui_icon icon, int x, int y);

void ui_render(void);

int ui_poll_event(ui_event* event);

#endif
