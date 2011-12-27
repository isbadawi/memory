#include "icons.h"
#include <stdlib.h>
#include <SDL/SDL_image.h>

SDL_Surface *load_image(char *filename) {
    SDL_Surface* temp = NULL;
    SDL_Surface* result = NULL;
    temp = IMG_Load(filename);
    if (temp != NULL) {
        result = SDL_DisplayFormatAlpha(temp);
        SDL_FreeSurface(temp);
    }
    return result;
}

SDL_Surface **load_images(char** filenames, int num_images) {
    SDL_Surface** result = malloc(num_images * sizeof(SDL_Surface*));
    int i;
    for (i = 0; i < num_images; ++i)
        result[i] = load_image(filenames[i]);
    return result;
}

void draw(SDL_Surface* src, SDL_Surface* dest, int x, int y) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src, NULL, dest, &offset);
}
