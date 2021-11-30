#include <daycycle.h>

#include <iostream>
#include <SDL_image.h>

SDL_Surface* daycycle_sprites[10];

void init_daycycle(){
    daycycle_sprites[0] = IMG_Load("../img/daycycle/daylight0.png");
    daycycle_sprites[1] = IMG_Load("../img/daycycle/daylight1.png");
    daycycle_sprites[2] = IMG_Load("../img/daycycle/daylight2.png");
    daycycle_sprites[3] = IMG_Load("../img/daycycle/daylight3.png");
    daycycle_sprites[4] = IMG_Load("../img/daycycle/daylight4.png");
    daycycle_sprites[5] = IMG_Load("../img/daycycle/daylight5.png");
    daycycle_sprites[6] = IMG_Load("../img/daycycle/daylight6.png");
    daycycle_sprites[7] = IMG_Load("../img/daycycle/daylight7.png");
    daycycle_sprites[8] = IMG_Load("../img/daycycle/daylight8.png");
    daycycle_sprites[9] = IMG_Load("../img/daycycle/daylight9.png");
}

static int hour_to_sprite_index(int daylight_current_hour){
    switch(daylight_current_hour){
        default:
        case 0:
            return 9;
        case 1:
            return 8;
        case 2:
            return 7;
        case 3:
            return 6;
        case 4:
            return 5;
        case 5:
            return 4;
        case 6:
            return 3;
        case 7:
            return 2;
        case 8:
            return 1;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            return 0;
        case 14:
            return 1;
        case 15:
            return 2;
        case 16:
            return 3;
        case 17:
            return 4;
        case 18:
            return 5;
        case 19:
            return 6;
        case 20:
            return 7;
        case 21:
            return 8;
        case 22:
        case 23:
            return 9;
    }
}

Daycycle next_daycycle(Daycycle current_daycycle){
    Daycycle next_d = current_daycycle+1;
    if(next_d > 23) next_d = 0;
    std::cout<<"Time="<<next_d<<"\n";
    return next_d;
}

void draw_daycycle(SDL_Renderer* renderer, Daycycle current_daycycle, int screen_x, int screen_y){
    int sprite_index = hour_to_sprite_index(current_daycycle);
    SDL_Texture* current_texture = SDL_CreateTextureFromSurface(renderer, daycycle_sprites[sprite_index]);
    SDL_Rect dstrect = { 0, 0, screen_x, screen_y };
    SDL_RenderCopy(renderer, current_texture, NULL, &dstrect);
    SDL_DestroyTexture(current_texture);
}

bool tick_daycycle(){
    static int counter = 0;
    if(counter > DAYCYCLE_DELAY){
        counter = 0;
        return true;
    }
    counter++;
    return false;
}