#pragma once

#include <SDL.h>
#include <tile.h>
#include <board.h>

#define ACTOR_ALIGNMENT_GOOD true
#define ACTOR_ALIGNMENT_BAD false

#define ACTOR_UPDATE_COUNTER 10 //250

#define ACTOR_HP_COMMON 10

enum Actor_Direction{
    Direction_Up,
    Direction_Down,
    Direction_Left,
    Direction_Right,
};

class Actor : public Tile{
    private:

    public:
        bool allignment=ACTOR_ALIGNMENT_GOOD;
        int row, col;
        int hp=ACTOR_HP_COMMON, hp_max=ACTOR_HP_COMMON;
        int id=0;

        enum Actor_Direction facing = Direction_Down;

        Actor(const char* name, const char* sprite_sheet_path, int id, int row, int col);
        Actor(const char* name, const char* sprite_sheet_path, int id, int row, int col, int hp, bool alignment);
        ~Actor();
        
        void move(int r, int c, int board_rows, int board_cols);
        void step(int board_rows, int board_cols);
        void turn_left();
        void turn_right();
        void face(enum Actor_Direction direction);

        void ai(Board* ground, Board* overlay);

        void draw(SDL_Renderer* renderer, int screen_x, int screen_y);
};