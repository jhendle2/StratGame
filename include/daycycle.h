#pragma once

#include <SDL.h>

#define DAYCYCLE_DELAY 5000

#define DAYCYCLE_MIDNIGHT 0
#define DAYCYCLE_DAWN 6
#define DAYCYCLE_NOON 12
#define DAYCYCLE_DUSK 18

typedef int Daycycle;

void init_daycycle();
Daycycle next_daycycle(Daycycle current_daycycle);
void draw_daycycle(SDL_Renderer* renderer, Daycycle current_daycycle, int screen_x, int screen_y);
bool tick_daycycle();