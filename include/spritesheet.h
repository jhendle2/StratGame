#pragma once

#include <SDL2/SDL.h>
// #include "utilities.hpp"

class Spritesheet
{
public:
    Spritesheet(char const *path, int rows, int columns);
    ~Spritesheet();

    void select_sprite(int x, int y);
    void draw_selected_sprite(SDL_Renderer *window_surface, int x, int y);

    int sprite_scaling;
    int sprite_size_x, sprite_size_y;

private:
    SDL_Rect     selected_sprite;
    SDL_Surface *m_spritesheet_image;
};
