#ifndef __game_h
#define __game_h

#include<SDL/SDL.h>

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
    SDL_Surface* icon;
} tile_t;

typedef struct {
    tile_t* tiles;
    unsigned int size;
} grid_t;

grid_t* init_game_grid(difficulty_t level);
int get_clicked_tile(int x, int y);
void draw_grid(grid_t* grid, SDL_Surface* screen);

#endif
