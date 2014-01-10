#include<stdio.h>
#include<stdlib.h>
#include "game.h"
#include "constants.h"
#include "ui.h"

int randint(int low, int high) {
    return rand() % (high - low) + low;
} 

grid_t* init_game_grid(difficulty_t level) {
    int row, col;
    grid_t* grid = malloc(sizeof(*grid));
    switch (level) {
        case EASY:
            grid->num_tiles = 16;
            grid->tiles_per_row = 4;
            break;
        case MEDIUM:
            grid->num_tiles = 36;
            grid->tiles_per_row = 6;
            break;
        case HARD:
            grid->num_tiles = 64;
            grid->tiles_per_row = 8;
            break;
    }
    grid->tiles = malloc(grid->num_tiles * sizeof(*(grid->tiles)));

    for (row = 0; row < grid->tiles_per_row; ++row)
        for (col = 0; col < grid->tiles_per_row; ++col) {
            int index = row * grid->tiles_per_row + col;
            grid->tiles[index].covered = 1;
            grid->tiles[index].removed = 0;
            grid->tiles[index].x = col * ICON_SIZE;
            grid->tiles[index].y = row * ICON_SIZE;
        }

    return grid;
}

void load_icons(grid_t* grid) {
    ui_icon* icons = ui_load_icons(grid->num_tiles / 2);
    int i;
    for (i = 0; i < grid->num_tiles / 2; ++i) {
        grid->tiles[i].icon = icons[i];
        grid->tiles[i + grid->num_tiles / 2].icon = icons[i];
    }
    for (i = grid->num_tiles - 1; i > 0; --i) {
        int j = randint(0, i);
        ui_icon temp = grid->tiles[j].icon;
        grid->tiles[j].icon = grid->tiles[i].icon;
        grid->tiles[i].icon = temp;
    } 
    free(icons);
}

tile_t* get_clicked_tile(grid_t* grid, int x, int y) {
    int row = y / ICON_SIZE;
    int col = x / ICON_SIZE;
    return &grid->tiles[row * grid->tiles_per_row + col];
}

int tiles_match(tile_t *t1, tile_t *t2) {
    return ui_icons_equal(t1->icon, t2->icon);
}
