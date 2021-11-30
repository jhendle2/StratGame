#pragma once

#include <SDL.h>

enum Weather{
    Weather_Clear,
    Weather_Rain,
};

void init_Weather();
void draw_weather(SDL_Renderer* renderer, enum Weather weather, int screen_x, int screen_y, bool next_state);
enum Weather randomize_Weather();

bool weather_timer();