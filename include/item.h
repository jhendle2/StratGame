#pragma once

#include <SDL.h>

class Item{
    private:

    public:
        char icon='?';
        char name[32];
        char description[256];

        // SDL_Surface* texture;

        Item();
        Item(const char* name, const char* description);
        Item(char icon, const char* name, const char* description);

        void print();
};