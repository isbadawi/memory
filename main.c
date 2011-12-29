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
    SDL_Event event;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                done = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int x = event.button.x;
                    int y = event.button.y;
                    int index = get_tile_clicked(x, y);
                    if (!grid[index].removed && grid[index].covered)
                        grid[index].covered = 0;
                }
            }
        }
        SDL_FillRect(screen, NULL, WHITE);
        int i;
        for (i = 0; i < NUM_ICONS * 2; ++i) {
            if (grid[i].removed)
                continue;
            if (grid[i].covered) 
                draw_cover(&grid[i], screen);
            else
                draw(&grid[i], screen);
        }
        SDL_Flip(screen);
    }
}
