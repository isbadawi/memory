#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/* This include is necessary even though there are no
 * references to SDL in this file. This is because SDL
 * needs to perform some initialization, and it does this
 * by renaming the app's main function (#define main SDL_main)
 * and defining its own that eventually calls it.
 *
 * An alternative to including this would be to just change
 * the definition of main to SDL_main. I'd rather keep the magic
 * contained in the SDL header.  */
#include<SDL/SDL.h>

#include "constants.h"
#include "game.h"
#include "ui.h"

tile_t* previous_tile;
tile_t* clicked_tile;
int waiting;

void remove_tiles(void) {
    previous_tile->removed = 1;
    clicked_tile->removed = 1;
    waiting = 0;
    previous_tile = NULL;
}

void resume_play(void) {
    previous_tile->covered = 1;
    clicked_tile->covered = 1;
    waiting = 0;
    previous_tile = NULL;
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
        if (tiles_match(previous_tile, clicked_tile)) {
            ui_run_task_after(1 /* second */, remove_tiles);
        } else {
            ui_run_task_after(1 /* second */, resume_play);
        }
    } 
}

void print_usage_and_exit(void) {
    puts("usage: memory [easy|medium|hard]");
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        print_usage_and_exit();
    }
    difficulty_t level = MEDIUM;
    if (argc == 2) {
        if (!strcmp(argv[1], "easy")) {
            level = EASY;
        } else if (!strcmp(argv[1], "medium")) {
            level = MEDIUM;
        } else if (!strcmp(argv[1], "hard")) {
            level = HARD;
        } else {
            print_usage_and_exit();
        }
    }

    grid_t* grid = init_game_grid(level);
    ui_init(grid->tiles_per_row * ICON_SIZE);
    load_icons(grid);

    srand(time(0));

    int done = 0;
    waiting = 0;
    previous_tile = NULL;
    ui_event_t event;
    while (!done) {
        while (ui_poll_event(&event)) {
            switch (event.type) {
            case ui_event_quit:
                done = 1;
                break;
            case ui_event_click:
                if (waiting) {
                    break;
                }
                int x = event.click.x;
                int y = event.click.y;
                clicked_tile = get_clicked_tile(grid, x, y);
                on_tile_click();
                break;
            }
        }
        ui_draw_grid(grid);
        ui_render();
    }
    ui_destroy();
    return 0;
}
