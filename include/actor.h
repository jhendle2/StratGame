#pragma once

#include <tile.h>

#define ACTOR_ALIGNMENT_GOOD true
#define ACTOR_ALIGNMENT_BAD false

#define ACTOR_HP_COMMON 10

enum Actor_Direction{
    Direction_Up,
    Direction_Down,
    Direction_Left,
    Direction_Right,
};

class Actor : Tile{
    private:

    public:
        bool allignment=ACTOR_ALIGNMENT_GOOD;
        int row, col;
        int hp=ACTOR_HP_COMMON, hp_max=ACTOR_HP_COMMON;

        enum Actor_Direction facing = Direction_Down;

        Actor(const char* name, const char* sprite_sheet_path, int row, int col);
        Actor(const char* name, const char* sprite_sheet_path, int row, int col, int hp, bool alignment);
        
        void move(int r, int c);
        void step();
        void turn_left();
        void turn_right();
};