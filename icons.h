#ifndef __icons_h
#define __icons_h

#include<SDL/SDL.h>
#include "game.h"

SDL_Surface* load_image(char* filename);
SDL_Surface** load_images(int how_many);
void draw(tile_t* t, SDL_Surface* dest);
void draw_cover(tile_t* t, SDL_Surface* dest);

#endif
