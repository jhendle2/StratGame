#include <iostream> //for rand() method
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <time.h>

#include <board.h>
#include <player.h>
#include <spritesheet.h>
#include <tt.h>

#include <mapgen.h>
#include <gamemenu.h>


#undef main

#define SCREEN_X 800
#define SCREEN_Y 600

Spritesheet sp = Spritesheet("sprites1.png", 8, 8);

Menu menu1 = Menu(5);
Board board1 = Board(24, 12);

void Game_init(){
    srand(time(NULL));
    load_Tiles();
}

void draw(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    board1.draw(renderer);
    menu1.draw(renderer, 540, 20);
    SDL_RenderPresent(renderer);

    SDL_Delay(1);
}

int main(int argc, char **args)
{
    Game_init();
    // board1 = Board("../maps/map0.txt");
    board1 = generate_random_Board(24, 8);
    // board1.show_cursor = false;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, SCREEN_X, SCREEN_Y, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    //Struct for handling events
    SDL_Event input;

    //Boolean to find out whether the game is stopped or not
    //Of course, it will be false at start
    bool quit = false;

    //For selecting renderer's draw color
    int r = 0, g = 255, b = 0;

    char key_pressed = 0;

    // Tile grass_tile = Tile("grass");
    // std::cout<<grass_tile.texture_path;

    // board1.flood_tile(grass_tile);

    // Board board2 = Board("../maps/map0.txt");

    int cursor_r = 4, cursor_c = 4;
    while (!quit) //Same as while(quit == false)
    {
        //---Event polling method---
        //It runs until the number of events to be polled gets to zero
        while (SDL_PollEvent(&input) > 0)
        {
            // char key_pressed = 0;

            //If the user did something which should
            //result in quitting of the game then...
            if (input.type == SDL_QUIT)
            {
                //...go out of the while loop
                quit = true;
            }
            //If the user pressed any key then...
            else if (input.type == SDL_KEYDOWN)
            {
                key_pressed = (char)(input.key.keysym.sym);

                if(key_pressed=='a') board1.move_cursor(Cursor_Left);
                else if(key_pressed=='d') board1.move_cursor(Cursor_Right);
                else if(key_pressed=='w') board1.move_cursor(Cursor_Up);
                else if(key_pressed=='s') board1.move_cursor(Cursor_Down);

                else if(key_pressed=='r'){
                    board1 = generate_random_Board(32, 12);
                }
            }

            draw(renderer);
        }

        // SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        // SDL_RenderClear(renderer);
        // SDL_RenderPresent(renderer);

        // SDL_RenderCopy(renderer, texture, NULL, NULL);
        // SDL_RenderPresent(renderer);

        // player.update(SCREEN_X, SCREEN_Y);
        
        
        
        // std::cout << "(" << player.x << ", " << player.y << ") " << player.vx << ", " << player.vy << "\n";

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}