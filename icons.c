#include <stdlib.h>
#include <SDL/SDL_image.h>
#include "icons.h"
#include "game.h"
#include "constants.h"

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

char **get_icon_filenames(char *filename, int how_many) {
    char **result = malloc(how_many * sizeof(char*));
    FILE* fp = fopen(filename, "r");
    int i;
    for (i = 0; i < how_many; i++) {
        result[i] = malloc(40);
        fgets(result[i], 40, fp);
        result[i][strlen(result[i]) - 1] = '\0';
    }
    return result;
} 

SDL_Surface **load_images(int how_many) {
    char** filenames = get_icon_filenames("icons.txt", how_many);
    SDL_Surface** result = malloc(how_many * sizeof(SDL_Surface*));
    int i;
    for (i = 0; i < how_many; ++i) {
        result[i] = load_image(filenames[i]);
        free(filenames[i]);
    }
    free(filenames);
    return result;
}

void draw(tile_t* t, SDL_Surface* dest) {
    SDL_Rect offset;
    offset.x = t->x;
    offset.y = t->y;
    SDL_BlitSurface(t->icon, NULL, dest, &offset);
}

void draw_cover(tile_t* t, SDL_Surface* dest) {
    Uint32 orange = SDL_MapRGB(dest->format, 255, 165, 0);
    Uint32 indian_red = SDL_MapRGB(dest->format, 205, 92, 92);
    SDL_Rect offset;
    offset.x = t->x;
    offset.y = t->y;
    offset.w = offset.h = ICON_SIZE;
    SDL_FillRect(dest, &offset, orange);
    offset.x += 1;
    offset.y += 1;
    offset.w = offset.h = ICON_SIZE - 2;
    SDL_FillRect(dest, &offset, indian_red);
}
