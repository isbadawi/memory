#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>

#include "constants.h"
#include "game.h"
#include "icons.h"

tile_t* previous_tile;
int wait;

Uint32 remove_tiles(Uint32 interval, void *state) {
    tile_t** s = (tile_t**)state;
    s[0]->removed = 1;
    s[1]->removed = 1;
    wait = 0;
    previous_tile = NULL;
    return 0;
}

Uint32 resume_play(Uint32 interval, void *state) {
    tile_t** s = (tile_t**)state;
    s[0]->covered = 1;
    s[1]->covered = 1;
    wait = 0;
    previous_tile = NULL;
    return 0;
}

void print_usage_and_exit(void) {
    puts("usage: memory [easy|medium|hard]");
    exit(0);
}

int main(int argc, char *argv[])
{
    if (argc > 2)
        print_usage_and_exit();
    difficulty_t level = MEDIUM;
    if (argc == 2) {
        if (!strcmp(argv[1], "easy"))
            level = EASY;
        else if (!strcmp(argv[1], "medium"))
            level = MEDIUM;
        else if (!strcmp(argv[1], "hard"))
            level = HARD;
        else 
            print_usage_and_exit();
    }

    srand(time(0));
    SDL_Init(SDL_INIT_EVERYTHING);
    atexit(SDL_Quit);
    SDL_SetVideoMode(SCREEN_SIZE, SCREEN_SIZE, SCREEN_BPP, SDL_SWSURFACE);
    SDL_WM_SetCaption("Memory game", "Memory game");
    SDL_WM_SetIcon(load_image("icons/32/Chip 100_32x32-32.png"), NULL);

    grid_t* grid = init_game_grid(level);

    SDL_Surface *screen = SDL_GetVideoSurface();

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
                    tile_t *clicked_tile = &grid->tiles[get_clicked_tile(x, y)];
                    if (clicked_tile->removed)
                        break;
                    if (previous_tile == NULL) {
                        previous_tile = clicked_tile;
                        clicked_tile->covered = 0;
                    } else if (previous_tile != clicked_tile) {
                        clicked_tile->covered = 0;
                        wait = 1;
                        tile_t* s[2] = {previous_tile, clicked_tile};
                        if (tiles_match(previous_tile, clicked_tile))
                            SDL_AddTimer(1000, remove_tiles, s);
                        else
                            SDL_AddTimer(1000, resume_play, s);
                    } 
                }
                break;
            }
        }
        draw_grid(grid, screen);
        SDL_Flip(screen);
    }
}
