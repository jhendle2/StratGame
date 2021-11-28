#pragma once

#include <vector>
#include <SDL.h>

#define ENABLE_ALT_TEXTURES false

class Tile{
    private:
    
    public:
        Tile();
        char icon;
        char name[32];       
        char texture_path[100];
        int num_alt_textures;
        Tile(char icon, const char* texture_path);
        Tile(char icon, const char* name, const char* texture_path);
        Tile(char icon, const char* texture_path, int num_alt_textures);
        ~Tile();
        SDL_Surface *texture;
        std::vector<SDL_Surface*> textures;
        void copy(Tile t);
};