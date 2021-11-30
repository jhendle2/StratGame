#include <iostream> //for rand() method
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <time.h>

#include <board.h>
#include <player.h>
#include <spritesheet.h>
#include <tt.h>

#include <exception>      // std::set_terminate

#include <mapgen.h>
// #include <gamemenu.h>
#include <weather.h>
#include <daycycle.h>
// #include <actor.h>
// #include <vector>

// #include <item.h>
// #include <inventory.h>

#undef main

#define SCREEN_X 800
#define SCREEN_Y 600

Spritesheet sp = Spritesheet("sprites1.png", 8, 8);

enum Weather current_weather = Weather_Clear;
Daycycle current_daycycle = DAYCYCLE_NOON;
// Menu menu1 = Menu(5);
Board board1 = Board(1, 1);
Board overlay_board = Board(1, 1);
// Inventory GameInventory = Inventory();

void Game_init(){
    srand(time(NULL));
    init_daycycle();
    init_Weather();
    load_Tiles();
}

void update_actors(){

}

void draw_boards(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // SCROLL MAP MODE
    board1.draw_slice(renderer, 0, 0, SCREEN_X, SCREEN_Y);
    overlay_board.draw_slice(renderer, 0, 0, SCREEN_X, SCREEN_Y);

    // FULL MAP MODE
    // board1.draw(renderer, SCREEN_X, SCREEN_Y);
    // overlay_board.draw(renderer, SCREEN_X, SCREEN_Y);
}

void draw(SDL_Renderer* renderer){
    static int actor_counter = 0;

    SDL_RenderClear(renderer);

    // if(actor_counter == ACTOR_UPDATE_COUNTER){
    //     actor_counter = 0;
    //     update_actors();
    // }

    bool update_weather = weather_timer();
    draw_boards(renderer);

    bool update_daycycle = tick_daycycle();
    if(update_daycycle) current_daycycle = next_daycycle(current_daycycle);
    draw_daycycle(renderer, current_daycycle, SCREEN_X, SCREEN_Y);
    draw_weather(renderer, current_weather, SCREEN_X, SCREEN_Y, update_weather);
    SDL_RenderPresent(renderer);
    
    actor_counter++;
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
    // Test1
    board1 = generate_random_Board(DEFAULT_MAP_SIZE_X,DEFAULT_MAP_SIZE_Y);
    // Test 2
    // board1 = Board(DEFAULT_MAP_SIZE_X, DEFAULT_MAP_SIZE_Y); // generate_random_Board(DEFAULT_MAP_SIZE_X, DEFAULT_MAP_SIZE_Y);
    // board1.flood_tile(Tiles_get_Tile("grass"));

    board1.show_cursor = false;
    overlay_board = Board(DEFAULT_MAP_SIZE_X, DEFAULT_MAP_SIZE_Y);
    add_vegetation_on_grass(DEFAULT_MAP_SIZE_X, DEFAULT_MAP_SIZE_Y, &board1, &overlay_board);
    overlay_board.show_cursor = true;

    // Item item0 = Item("item0","this is a zeroth item!");
    // Item item1 = Item("item1","this is a first item!");
    // Item item2 = Item("item2","this is a second item!");
    
    // GameInventory.add(item0);
    // GameInventory.add(item1);
    // GameInventory.add(item1);
    // GameInventory.add(item1);
    // GameInventory.add(item0);
    // GameInventory.add(item0);
    // GameInventory.add(item0);
    // GameInventory.add(item2);
    // GameInventory.add(item2);
    // GameInventory.add(item2);
    // GameInventory.add(item2);

    // GameInventory.print_all();

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

                else if(key_pressed=='h') {
 
                }
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