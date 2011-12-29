#ifndef __icons_h
#define __icons_h

#include<SDL/SDL.h>
#include "game.h"

SDL_Surface** load_images();
void draw(Tile* t, SDL_Surface* dest);
void draw_cover(Tile* t, SDL_Surface* dest);

#endif
