#include "ui.h"
#include "game.h"
#include "constants.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

int ui_init(int screen_size) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return -1;
    }
    if (SDL_SetVideoMode(screen_size, screen_size, SCREEN_BPP, SDL_SWSURFACE) == NULL) {
        return -1;
    }
    SDL_WM_SetCaption("Memory game", "Memory game");
    return 0;
}

void ui_destroy(void) {
    SDL_Quit();
}

void ui_fill_screen(ui_color color) {
    SDL_Surface* screen = SDL_GetVideoSurface();
    Uint32 sdl_color = SDL_MapRGB(screen->format, color.r, color.g, color.b);
    SDL_FillRect(screen, NULL, sdl_color);
}

void ui_draw_square(ui_color color, int x, int y, int side) {
    SDL_Surface* screen = SDL_GetVideoSurface();
    Uint32 sdl_color = SDL_MapRGB(screen->format, color.r, color.g, color.b);
    SDL_Rect sdl_rect = {x, y, side, side};
    SDL_FillRect(screen, &sdl_rect, sdl_color);
}

void ui_draw_icon(ui_icon icon, int x, int y) {
    SDL_Surface* screen = SDL_GetVideoSurface();
    SDL_Rect offset = {x, y, 0, 0};
    SDL_BlitSurface((SDL_Surface*) icon, NULL, screen, &offset);
}

ui_icon ui_load_icon(char *filename) {
    SDL_Surface* temp = IMG_Load(filename);
    if (temp == NULL) {
        return NULL;
    }
    return (ui_icon) temp;
}

ui_icon *ui_load_icons(int how_many) {
    char buffer[40];
    FILE* fp = fopen("icons.txt", "r");
    ui_icon* result = malloc(how_many * sizeof(ui_icon));
    for (int i = 0; i < how_many; ++i) {
        fgets(buffer, 40, fp);
        buffer[strlen(buffer) - 1] = '\0';
        result[i] = ui_load_icon(buffer);
    }
    return result;
}

int ui_icons_equal(ui_icon i1, ui_icon i2) {
    return i1 == i2;
}

void ui_draw_tile(tile_t* t) {
    ui_draw_icon(t->icon, t->x, t->y);
}

void ui_draw_covered_tile(tile_t* t) {
    ui_color orange = {255, 165, 0};
    ui_color indian_red = {205, 92, 92};
    ui_draw_square(orange, t->x, t->y, ICON_SIZE);
    ui_draw_square(indian_red, t->x + 1, t->y + 1, ICON_SIZE);
}

void ui_draw_grid(grid_t* grid) {
    ui_color white = {255, 255, 255};
    ui_fill_screen(white);
    for (int i = 0; i < grid->num_tiles; ++i) {
        if (grid->tiles[i].removed) {
            continue;
        }
        if (grid->tiles[i].covered) {
            ui_draw_covered_tile(grid->tiles + i);
        } else {
            ui_draw_tile(grid->tiles + i);
        }
    }
}

void ui_render(void) {
    SDL_Flip(SDL_GetVideoSurface());
}
