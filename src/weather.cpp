#include <weather.h>
#include <SDL_image.h>
#include <iostream>

SDL_Surface* rain_sprites[8];

void init_Weather(){
    rain_sprites[0] = IMG_Load("../img/weather/rain0.png");
    rain_sprites[1] = IMG_Load("../img/weather/rain1.png");
    rain_sprites[2] = IMG_Load("../img/weather/rain2.png");
    rain_sprites[3] = IMG_Load("../img/weather/rain3.png");
    rain_sprites[4] = IMG_Load("../img/weather/rain4.png");
    rain_sprites[5] = IMG_Load("../img/weather/rain5.png");
    rain_sprites[6] = IMG_Load("../img/weather/rain6.png");
    rain_sprites[7] = IMG_Load("../img/weather/rain7.png");
}

static void draw_weather_on_screen(SDL_Renderer* renderer, SDL_Texture* texture, int screen_x, int screen_y){
    SDL_Rect dstrect = { 0, 0, screen_x, screen_y };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
}

void draw_weather(SDL_Renderer* renderer, enum Weather weather, int screen_x, int screen_y, bool next_state){
    if(weather == Weather_Clear) return;
    
    static int cycle = 0;
    // std::cout << counter << "\n";
    SDL_Texture* current_texture;

    switch(weather){
    case Weather_Rain:
        if(cycle > 7) cycle = 0;
        current_texture = SDL_CreateTextureFromSurface(renderer, rain_sprites[cycle]);
        draw_weather_on_screen(renderer, current_texture, screen_x, screen_y);
        break;
    default:
        break;
    }
   if(next_state) cycle++;
    // SDL_RenderPresent(renderer);
}

enum Weather randomize_Weather(){
    int weather_id = rand() % 10;
    if(weather_id == 0){
        return Weather_Rain;
    }
    return Weather_Clear;
}

#define WEATHER_TIMER_TIME 10
bool weather_timer(){
    static int counter = 0;
    // std::cout<<"ct="<<counter<<"\n";
    counter++;
    if(counter > WEATHER_TIMER_TIME){
        counter = 0;
        return true;
    }
    return false;
}