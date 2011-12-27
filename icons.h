#ifndef __icons_h
#define __icons_h

#include<SDL/SDL.h>

SDL_Surface** load_images();
void draw(SDL_Surface* dest, SDL_Surface* src, int x, int y);

#endif
