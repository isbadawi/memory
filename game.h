#ifndef __game_h
#define __game_h

#include<SDL/SDL.h>

typedef struct {
    int x;
    int y;
    int covered;
    int removed;
    SDL_Surface* icon;
} Tile;

Tile* init_game_grid(void);
int get_tile_clicked(int x, int y);

#endif
