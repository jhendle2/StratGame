#pragma once

#include <vector>
#include <SDL.h>

#define ENABLE_ALT_TEXTURES false

enum Tile_Type{
    Tile_Type_None,
    Tile_Type_Air,
    Tile_Type_Actor,
    Tile_Type_Vegetation,
    Tile_Type_Ground,
    Tile_Type_Fluid
};

class Tile{
    private:
    
    public:
        Tile();
        char icon;
        char name[32];       
        char texture_path[100];
        int num_alt_textures;
        enum Tile_Type type=Tile_Type_None;

        Tile(char icon, const char* texture_path);
        Tile(char icon, const char* name, const char* texture_path);
        Tile(char icon, const char* name, const char* texture_path, enum Tile_Type type);
        Tile(char icon, const char* texture_path, int num_alt_textures);
        ~Tile();

        SDL_Surface *texture;
        std::vector<SDL_Surface*> textures;
        void copy(Tile t);
};