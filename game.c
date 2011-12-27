#include<stdio.h>
#include<stdlib.h>
#include "game.h"
#include "constants.h"
#include "icons.h"

int randint(int low, int high) {
    return rand() % (high - low) + low;
} 

Tile* init_game_grid(void) {
    SDL_Surface **icons = load_images();

    Tile* grid = malloc(2*NUM_ICONS*sizeof(Tile));
    int i;
    for (i = 0; i < NUM_ICONS; ++i)
        grid[i].icon = grid[i+NUM_ICONS].icon = icons[i];

    int row, col;
    for (row = 0; row < ICONS_PER_LINE; ++row)
        for (col = 0; col < ICONS_PER_LINE; ++col) {
            int index = row*ICONS_PER_LINE + col;
            grid[index].visible = 1;
            grid[index].x = row * ICON_SIZE;
            grid[index].y = col * ICON_SIZE;
        }

    for (i = NUM_ICONS * 2 - 1; i > 0; --i) {
        int j = randint(0, i);
        Tile temp = grid[j];
        grid[j] = grid[i];
        grid[i] = temp;
    }

    free(icons);
    return grid;
}
