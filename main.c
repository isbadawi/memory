#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<SDL/SDL.h>

#include "constants.h"
#include "game.h"

Tile* previous_tile;
int wait;

Uint32 remove_tiles(Uint32 interval, void *state) {
    Tile** s = (Tile**)state;
    s[0]->removed = 1;
    s[1]->removed = 1;
    wait = 0;
    previous_tile = NULL;
    return 0;
}

Uint32 resume_play(Uint32 interval, void *state) {
    Tile** s = (Tile**)state;
    s[0]->covered = 1;
    s[1]->covered = 1;
    wait = 0;
    previous_tile = NULL;
    return 0;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    SDL_Init(SDL_INIT_EVERYTHING);
    atexit(SDL_Quit);
    SDL_SetVideoMode(SCREEN_SIZE, SCREEN_SIZE, SCREEN_BPP, SDL_SWSURFACE);
    SDL_WM_SetCaption("Memory game", NULL);

    Tile* grid = init_game_grid();

    SDL_Surface *screen = SDL_GetVideoSurface();
    Uint32 WHITE = SDL_MapRGB(screen->format, 255, 255, 255);

    int done = 0;
    wait = 0;
    SDL_Event event;
    previous_tile = NULL;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                done = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (wait)
                        break;
                    int x = event.button.x;
                    int y = event.button.y;
                    Tile *clicked_tile = &grid[get_clicked_tile(x, y)];
                    if (clicked_tile->removed)
                        break;
                    if (previous_tile == NULL) {
                        previous_tile = clicked_tile;
                        clicked_tile->covered = 0;
                    } else if (previous_tile != clicked_tile) {
                        clicked_tile->covered = 0;
                        wait = 1;
                        Tile* s[2] = {previous_tile, clicked_tile};
                        if (tiles_match(previous_tile, clicked_tile))
                            SDL_AddTimer(1000, remove_tiles, s);
                        else
                            SDL_AddTimer(1000, resume_play, s);
                    } 
                }
                break;
            }
        }
        SDL_FillRect(screen, NULL, WHITE);
        int i;
        for (i = 0; i < NUM_ICONS * 2; ++i) {
            if (grid[i].removed)
                continue;
            if (grid[i].covered) 
                draw_cover(grid + i, screen);
            else
                draw(grid + i, screen);
        }
        SDL_Flip(screen);
    }
}
