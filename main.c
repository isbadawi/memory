#include<stdio.h>
#include<stdlib.h>
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

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    printf("%d\n", SCREEN_SIZE);
    SDL_SetVideoMode(SCREEN_SIZE, SCREEN_SIZE, SCREEN_BPP, SDL_SWSURFACE);
    SDL_Surface *screen = SDL_GetVideoSurface();
    char **filenames = get_icon_filenames("icons.txt");
    SDL_Surface **icons = load_images(filenames, NUM_ICONS);
    Uint32 WHITE = SDL_MapRGB(screen->format, 255, 255, 255);
    SDL_FillRect(screen, NULL, WHITE);
    SDL_BlitSurface(icons[0], NULL, screen, NULL);
    SDL_Flip(screen);
    SDL_Delay(2000);
    SDL_Quit();
}
