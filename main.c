#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<SDL/SDL.h>

#include "constants.h"
#include "icons.h"

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

int randint(int low, int high) {
    return rand() % (high - low) + low;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    SDL_Init(SDL_INIT_EVERYTHING);
    atexit(SDL_Quit);
    SDL_SetVideoMode(SCREEN_SIZE, SCREEN_SIZE, SCREEN_BPP, SDL_SWSURFACE);
    char **filenames = get_icon_filenames("icons.txt");
    SDL_Surface **icons = load_images(filenames, NUM_ICONS);

    SDL_Surface* grid[NUM_ICONS*2];
    int i;
    for (i = 0; i < NUM_ICONS; ++i)
        grid[i] = grid[i+NUM_ICONS] = icons[i];
    for (i = NUM_ICONS * 2 - 1; i > 0; --i) {
        int j = randint(0, i);
        SDL_Surface* temp = grid[j];
        grid[j] = grid[i];
        grid[i] = temp;
    }
    
    SDL_Surface *screen = SDL_GetVideoSurface();
    Uint32 WHITE = SDL_MapRGB(screen->format, 255, 255, 255);

    int done = 0;
    while (!done) {
        SDL_FillRect(screen, NULL, WHITE);
        int row, col;
        for (row = 0; row < ICONS_PER_LINE; ++row)
            for (col = 0; col < ICONS_PER_LINE; ++col)
                draw(grid[row * ICONS_PER_LINE + col], 
                     screen, 
                     col * ICON_SIZE,
                     row * ICON_SIZE);
        SDL_Flip(screen);
    }
}
