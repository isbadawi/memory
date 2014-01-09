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
tile_t* clicked_tile;
int waiting;

Uint32 remove_tiles(Uint32 interval, void *unused) {
    previous_tile->removed = 1;
    clicked_tile->removed = 1;
    waiting = 0;
    previous_tile = NULL;
    return 0;
}

Uint32 resume_play(Uint32 interval, void *unused) {
    previous_tile->covered = 1;
    clicked_tile->covered = 1;
    waiting = 0;
    previous_tile = NULL;
    return 0;
}

void on_tile_click(void) {
    if (clicked_tile->removed)
        return;
    if (previous_tile == NULL) {
        previous_tile = clicked_tile;
        clicked_tile->covered = 0;
    } else if (previous_tile != clicked_tile) {
        clicked_tile->covered = 0;
        waiting = 1;
        if (tiles_match(previous_tile, clicked_tile))
            SDL_AddTimer(1000, remove_tiles, NULL);
        else
            SDL_AddTimer(1000, resume_play, NULL);
    } 
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

    grid_t* grid = init_game_grid(level);
    int screen_size = grid->tiles_per_row * ICON_SIZE;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(screen_size, screen_size, SCREEN_BPP, SDL_SWSURFACE);
    load_icons(grid);

    srand(time(0));
    atexit(SDL_Quit);
    SDL_WM_SetCaption("Memory game", "Memory game");
    SDL_WM_SetIcon(load_image("icons/Chip 100_32x32-32.png"), NULL);
    SDL_Surface *screen = SDL_GetVideoSurface();

    int done = 0;
    waiting = 0;
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
                    if (waiting)
                        break;
                    int x = event.button.x;
                    int y = event.button.y;
                    clicked_tile = get_clicked_tile(grid, x, y);
                    on_tile_click();
                }
                break;
            }
        }
        draw_grid(grid, screen);
        SDL_Flip(screen);
    }
    return 0;
}
