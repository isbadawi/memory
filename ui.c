#include "ui.h"
#include "game.h"
#include "constants.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

int ui_init(int screen_size) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
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

void ui_fill_screen(ui_color_t color) {
    SDL_Surface* screen = SDL_GetVideoSurface();
    Uint32 sdl_color = SDL_MapRGB(screen->format, color.r, color.g, color.b);
    SDL_FillRect(screen, NULL, sdl_color);
}

void ui_draw_square(ui_color_t color, int x, int y, int side) {
    SDL_Surface* screen = SDL_GetVideoSurface();
    Uint32 sdl_color = SDL_MapRGB(screen->format, color.r, color.g, color.b);
    SDL_Rect sdl_rect = {x, y, side, side};
    SDL_FillRect(screen, &sdl_rect, sdl_color);
}

void ui_draw_icon(ui_icon_t icon, int x, int y) {
    SDL_Surface* screen = SDL_GetVideoSurface();
    SDL_Rect offset = {x, y, 0, 0};
    SDL_BlitSurface((SDL_Surface*) icon, NULL, screen, &offset);
}

ui_icon_t ui_load_icon(char *filename) {
    SDL_Surface* temp = IMG_Load(filename);
    if (temp == NULL) {
        return NULL;
    }
    return (ui_icon_t) temp;
}

ui_icon_t *ui_load_icons(int how_many) {
    char buffer[40];
    FILE* fp = fopen("icons.txt", "r");
    ui_icon_t* result = malloc(how_many * sizeof(ui_icon_t));
    for (int i = 0; i < how_many; ++i) {
        fgets(buffer, 40, fp);
        buffer[strlen(buffer) - 1] = '\0';
        result[i] = ui_load_icon(buffer);
    }
    return result;
}

int ui_icons_equal(ui_icon_t i1, ui_icon_t i2) {
    return i1 == i2;
}

void ui_draw_tile(tile_t* t) {
    ui_draw_icon(t->icon, t->x, t->y);
}

void ui_draw_covered_tile(tile_t* t) {
    ui_color_t orange = {255, 165, 0};
    ui_color_t indian_red = {205, 92, 92};
    ui_draw_square(orange, t->x, t->y, ICON_SIZE);
    ui_draw_square(indian_red, t->x + 1, t->y + 1, ICON_SIZE);
}

void ui_draw_grid(grid_t* grid) {
    ui_color_t white = {255, 255, 255};
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

int ui_poll_event(ui_event_t* event) {
    SDL_Event sdl_event;
    if (!SDL_PollEvent(&sdl_event)) {
        return 0;
    }
    switch (sdl_event.type) {
    case SDL_QUIT:
        event->type = ui_event_quit;
        return 1;
    case SDL_MOUSEBUTTONDOWN:
        if (sdl_event.button.button == SDL_BUTTON_LEFT) {
            event->type = ui_event_click;
            event->click.x = sdl_event.button.x;
            event->click.y = sdl_event.button.y;
        }
        return 1;
    }
    return ui_poll_event(event);
}
