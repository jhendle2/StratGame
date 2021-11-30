#pragma once

// #include <SDL.h>

#define MENU_MAX_INDEX 10

class Menu{
    private:
        int menu_index;
        int menu_len;
        
        // SDL_Surface *texture;

    public:
        Menu();
        Menu(int menu_len);
        ~Menu();

        void set_index(int i);
        void up_index();
        void down_index();

        // void draw(SDL_Renderer *renderer, int x, int y);
};