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
// #include <gamemenu.h>
#include <weather.h>
#include <daycycle.h>


#undef main

#define SCREEN_X 800
#define SCREEN_Y 600

Spritesheet sp = Spritesheet("sprites1.png", 8, 8);

enum Weather current_weather = Weather_Clear;
Daycycle current_daycycle = DAYCYCLE_NOON;
// Menu menu1 = Menu(5);
Board board1 = Board(1, 1);
Board overlay_board = Board(1, 1);

void Game_init(){
    srand(time(NULL));
    init_daycycle();
    init_Weather();
    load_Tiles();
}

void draw_boards(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // board1.draw(renderer, SCREEN_X, SCREEN_Y);
    board1.draw_slice(renderer, 0, 0, SCREEN_X, SCREEN_Y);
    overlay_board.draw_slice(renderer, 0, 0, SCREEN_X, SCREEN_Y);
    // menu1.draw(renderer, 540, 20);
    // SDL_RenderPresent(renderer);
    // draw_weather(renderer, current_weather, SCREEN_X, SCREEN_Y);
    // SDL_RenderPresent(renderer);
}

void draw(SDL_Renderer* renderer){
    bool update_weather = weather_timer();
    SDL_RenderClear(renderer);
    draw_boards(renderer);

    // std::cout<<update_weather<<"\n";
    bool update_daycycle = tick_daycycle();
    if(update_daycycle) current_daycycle = next_daycycle(current_daycycle);
    draw_daycycle(renderer, current_daycycle, SCREEN_X, SCREEN_Y);
    draw_weather(renderer, current_weather, SCREEN_X, SCREEN_Y, update_weather);
    SDL_RenderPresent(renderer);
    SDL_Delay(1);
}

int main(int argc, char** args){
    /* Initialization */
    Game_init();

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, SCREEN_X, SCREEN_Y, SDL_WINDOW_SHOWN);
    // SDL_Renderer *weather_renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event input;

    current_weather = Weather_Clear;

    /* World Generation */
    // std::cout << "Generating terrain...\n";
    board1 = generate_random_Board(DEFAULT_MAP_SIZE_X, DEFAULT_MAP_SIZE_Y);
    board1.show_cursor = false;
    overlay_board = Board(DEFAULT_MAP_SIZE_X, DEFAULT_MAP_SIZE_Y);
    add_vegetation_on_grass(DEFAULT_MAP_SIZE_X, DEFAULT_MAP_SIZE_Y, &board1, &overlay_board);
    overlay_board.show_cursor = true;
    // overlay_board.set_tile(5,5, Tiles_get_Tile("tree"));
    // overlay_board.set_tile(5, 5, Tiles_get_Tile("clay"));
    // board1.set_tile(2,2,Tiles_get_Tile("deepwater"));
    // board1.save("../maps/map1.txt");

    /* Keyboard Initialization */
    bool quit = false;
    char key_pressed = 0;

    int weather_counter = 0;

    /* Main Game Loop */
    while (!quit)
    {
        weather_counter++;
        if(weather_counter>5000){
            current_weather = randomize_Weather();
            weather_counter = 0;
        }
        while (SDL_PollEvent(&input) > 0)
        {
            if (input.type == SDL_QUIT) quit = true;

            else if (input.type == SDL_KEYDOWN)
            {
                key_pressed = (char)(input.key.keysym.sym);

                if(key_pressed=='a') overlay_board.move_cursor(Cursor_Left);
                else if(key_pressed=='d') overlay_board.move_cursor(Cursor_Right);
                else if(key_pressed=='w') overlay_board.move_cursor(Cursor_Up);
                else if(key_pressed=='s') overlay_board.move_cursor(Cursor_Down);

                // else if(key_pressed=='r'){
                //     board1 = generate_random_Board(DEFAULT_MAP_SIZE_X, DEFAULT_MAP_SIZE_Y);
                // }

                else if(key_pressed=='z') {board1.zoom_in(); overlay_board.zoom_in();}
                else if(key_pressed=='x') {board1.zoom_out(); overlay_board.zoom_out();}

                // else if(key_pressed=='q') board1.rotate_left();
                // else if(key_pressed=='e') board1.rotate_right();

                // else if(key_pressed=='i') {board1.move_slice(-1, 0); overlay_board.move_cursor(-1, 0);}
                // else if(key_pressed=='j') {board1.move_slice(0, -1); overlay_board.move_cursor(0, -1);}
                // else if(key_pressed=='l') {board1.move_slice(0, 1); overlay_board.move_cursor(0, 1);}
                // else if(key_pressed=='k') {board1.move_slice(1, 0); overlay_board.move_cursor(1, 0);}
                
                else if(key_pressed=='i') {board1.move_slice(-1, 0); overlay_board.move_slice(-1, 0);}
                else if(key_pressed=='j') {board1.move_slice(0, -1); overlay_board.move_slice(0, -1);}
                else if(key_pressed=='l') {board1.move_slice(0, 1); overlay_board.move_slice(0, 1);}
                else if(key_pressed=='k') {board1.move_slice(1, 0); overlay_board.move_slice(1, 0);}

                // /draw(renderer);
            }
            
            
            
        }
        draw(renderer);
        // SDL_RenderPresent(renderer);
        // draw_overlays(weather_renderer);
    }
    SDL_DestroyRenderer(renderer);
    // SDL_DestroyRenderer(weather_renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

/*int main(int argc, char **args)
{
    Game_init();
    // board1 = Board("../maps/map0.txt");
    board1 = generate_random_Board(128, 128);
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
                    board1 = generate_random_Board(32, 32);
                }

                else if(key_pressed=='z') board1.zoom_in();
                else if(key_pressed=='x') board1.zoom_out();

                else if(key_pressed=='q') board1.rotate_left();
                else if(key_pressed=='e') board1.rotate_right();

                else if(key_pressed=='i') board1.move_slice(-1, 0);
                else if(key_pressed=='j') board1.move_slice(0, -1);
                else if(key_pressed=='l') board1.move_slice(0, 1);
                else if(key_pressed=='k') board1.move_slice(1, 0);
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
}*/