#ifndef __game_h
#define __game_h

#include<SDL/SDL.h>

typedef struct {
    int x;
    int y;
    int visible;
    SDL_Surface* icon;
} Tile;

Tile* init_game_grid(void);

#endif
