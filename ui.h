#ifndef _ui_h_included
#define _ui_h_included

#include <stdint.h>

typedef struct {
    uint8_t r, g, b;
} ui_color_t;

typedef enum {
    ui_event_quit,
    ui_event_click
} ui_event_type_t;

typedef struct {
    ui_event_type_t type;
    int x;
    int y;
} ui_click_event_t;

typedef union {
    ui_event_type_t type;
    ui_click_event_t click;
} ui_event_t;

typedef void* ui_icon_t;

int ui_init();
void ui_destroy();

ui_icon_t ui_load_icon(char* filename);
ui_icon_t* ui_load_icons(int how_many);
int ui_icons_equal(ui_icon_t i1, ui_icon_t i2);

void ui_draw_square(ui_color_t color, int x, int y, int side);
void ui_draw_icon(ui_icon_t icon, int x, int y);

void ui_render(void);

int ui_poll_event(ui_event_t* event);

#endif
