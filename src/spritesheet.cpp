#include <SDL_image.h>
#include <iostream>
#include <spritesheet.h>

Spritesheet::Spritesheet(char const *path, int rows, int columns)
{
    char new_path[100];
    strcpy(new_path, "../img/");
    strcat(new_path, path);


    m_spritesheet_image = IMG_Load(new_path);

    this->sprite_size_x = m_spritesheet_image->w / columns;
    this->sprite_size_y = m_spritesheet_image->h / rows;

    this->sprite_scaling = 1;

    selected_sprite.w = sprite_size_x;
    selected_sprite.h = sprite_size_y;
}

Spritesheet::~Spritesheet()
{
    SDL_FreeSurface(m_spritesheet_image);
}

void Spritesheet::select_sprite(int x, int y)
{
    selected_sprite.x = x * selected_sprite.w;
    selected_sprite.y = y * selected_sprite.h;
}

void Spritesheet::draw_selected_sprite(SDL_Renderer *renderer, int x, int y)
{
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, this->m_spritesheet_image);
    // SDL_Rect srcrect = { 0, 0, this->sprite_size_x, this->sprite_size_y };
    // std::cout << "(" << x << ", " << y << ")\n";
    SDL_Rect dstrect = { x, y, this->sprite_size_x*this->sprite_scaling, this->sprite_size_y*this->sprite_scaling };
    SDL_RenderCopy(renderer, texture, &selected_sprite, &dstrect);
    // SDL_BlitSurface(m_spritesheet_image, &m_clip, window_surface, position);
}
