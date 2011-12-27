#include <stdlib.h>
#include <SDL/SDL_image.h>
#include "icons.h"
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

char **get_icon_filenames(char *filename) {
    char **result = malloc(NUM_ICONS * sizeof(char*));
    FILE* fp = fopen(filename, "r");
    int i;
    for (i = 0; i < NUM_ICONS; i++) {
        result[i] = malloc(40);
        fgets(result[i], 40, fp);
        result[i][strlen(result[i]) - 1] = '\0';
    }
    return result;
} 

SDL_Surface **load_images(void) {
    char** filenames = get_icon_filenames("icons.txt");
    SDL_Surface** result = malloc(NUM_ICONS * sizeof(SDL_Surface*));
    int i;
    for (i = 0; i < NUM_ICONS; ++i) {
        result[i] = load_image(filenames[i]);
        free(filenames[i]);
    }
    free(filenames);
    return result;
}

void draw(SDL_Surface* src, SDL_Surface* dest, int x, int y) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src, NULL, dest, &offset);
}
