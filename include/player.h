#pragma once

#include <SDL.h>

class Player{
    private:


    public:
        float x, y;
        float vx, vy;
        float vmax;
        float friction;

        Player();
        ~Player();

        void set_v(int vx, int vy);
        void change_v(int h, int v);

        void update(int screen_x, int screen_y);
        void draw(SDL_Renderer* renderer);
};