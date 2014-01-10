#ifndef __game_h
#define __game_h

#include "ui.h"

typedef enum {
    EASY,
    MEDIUM,
    HARD
} difficulty_t;

typedef struct {
    int x;
    int y;
    int covered;
    int removed;
    ui_icon icon;
} tile_t;

typedef struct {
    tile_t* tiles;
    unsigned int num_tiles;
    unsigned int tiles_per_row;
} grid_t;

grid_t* init_game_grid(difficulty_t level);
tile_t* get_clicked_tile(grid_t* grid, int x, int y);
void load_icons(grid_t* grid);
int tiles_match(tile_t* t1, tile_t* t2);
 
/* These are declared here to avoid circular includes. */
void ui_draw_tile(tile_t* t);
void ui_draw_covered_tile(tile_t* t);
void ui_draw_grid(grid_t* grid);

#endif
