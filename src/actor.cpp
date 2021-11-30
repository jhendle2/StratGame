#include <actor.h>

Actor::Actor(const char* name, const char* sprite_sheet_path, int row, int col) :
Tile('*',name,sprite_sheet_path){
    this->row = row;
    this->col = col;
}

Actor::Actor(const char* name, const char* sprite_sheet_path, int row, int col, int hp, bool alignment) :
Tile('*',name,sprite_sheet_path){
    this->row = row;
    this->col = col;

    this->hp = hp;
    this->hp_max = hp;
    this->allignment = allignment;
}

void Actor::move(int r, int c){
    
}

void Actor::step(){

}

void Actor::turn_left(){
    switch(facing){
        case Direction_Left:
            facing = Direction_Down;
            break;
        case Direction_Up:
            facing = Direction_Left;
            break;
        case Direction_Right:
            facing = Direction_Up;
            break;
        default:
        case Direction_Down:
            facing = Direction_Right;
            break;
            
    }
}

void Actor::turn_right(){
    turn_left();
    turn_left();
    turn_left();
}