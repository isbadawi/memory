#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<SDL/SDL.h>

#include "constants.h"
#include "game.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    SDL_Init(SDL_INIT_EVERYTHING);
    atexit(SDL_Quit);
    SDL_SetVideoMode(SCREEN_SIZE, SCREEN_SIZE, SCREEN_BPP, SDL_SWSURFACE);

    Tile* grid = init_game_grid();

    SDL_Surface *screen = SDL_GetVideoSurface();
    Uint32 WHITE = SDL_MapRGB(screen->format, 255, 255, 255);

    int done = 0;
    SDL_Event e;
    while (!done) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    done = 1;
            }
        }
        SDL_FillRect(screen, NULL, WHITE);
        int i;
        for (i = 0; i < NUM_ICONS * 2; ++i)
            if (grid[i].visible)
                draw(grid[i].icon, screen, grid[i].x, grid[i].y);
        SDL_Flip(screen);
    }
}
