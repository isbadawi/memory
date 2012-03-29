#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "game.h"
#include "constants.h"
#include "icons.h"

int randint(int low, int high) {
    return rand() % (high - low) + low;
} 

grid_t* init_game_grid(difficulty_t level) {
    int i;
    int row, col;
    SDL_Surface **icons = load_images();
    grid_t* grid = malloc(sizeof(*grid));
    grid->tiles = malloc(2*NUM_ICONS*sizeof(*(grid->tiles)));
    grid->num_tiles = 2*NUM_ICONS;
    grid->tiles_per_row = sqrt(grid->num_tiles);
    for (i = 0; i < NUM_ICONS; ++i)
        grid->tiles[i].icon = grid->tiles[i+NUM_ICONS].icon = icons[i];
    for (i = NUM_ICONS * 2 - 1; i > 0; --i) {
        int j = randint(0, i);
        tile_t temp = grid->tiles[j];
        grid->tiles[j] = grid->tiles[i];
        grid->tiles[i] = temp;
    }
    for (row = 0; row < grid->tiles_per_row; ++row)
        for (col = 0; col < grid->tiles_per_row; ++col) {
            int index = row * grid->tiles_per_row + col;
            grid->tiles[index].covered = 1;
            grid->tiles[index].removed = 0;
            grid->tiles[index].x = col * ICON_SIZE;
            grid->tiles[index].y = row * ICON_SIZE;
        }

    free(icons);
    return grid;
}

tile_t* get_clicked_tile(grid_t* grid, int x, int y) {
    int row = y / ICON_SIZE;
    int col = x / ICON_SIZE;
    return &grid->tiles[row * grid->tiles_per_row + col];
}

int tiles_match(tile_t *t1, tile_t *t2) {
    return t1->icon == t2->icon;
}

void draw_grid(grid_t* grid, SDL_Surface* screen) {
    Uint32 WHITE = SDL_MapRGB(screen->format, 255, 255, 255);
    int i;
    SDL_FillRect(screen, NULL, WHITE);
    for (i = 0; i < grid->num_tiles; ++i) {
        if (grid->tiles[i].removed)
            continue;
        if (grid->tiles[i].covered) 
            draw_cover(grid->tiles + i, screen);
        else
            draw(grid->tiles + i, screen);
    }  
}
