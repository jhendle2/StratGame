#include <actor.h>
#include <tt.h>
#include <iostream>
#include <utils.h>

Actor::Actor(const char* name, const char* sprite_sheet_path, int id, int row, int col) :
Tile('*',name,sprite_sheet_path){
    this->row = row;
    this->col = col;
    this->id = id;
}

Actor::Actor(const char* name, const char* sprite_sheet_path, int id, int row, int col, int hp, bool alignment) :
Tile('*',name,sprite_sheet_path){
    this->row = row;
    this->col = col;
    this->id = id;

    this->hp = hp;
    this->hp_max = hp;
    this->allignment = allignment;
}

Actor::~Actor(){

}

void Actor::move(int r, int c, int board_rows, int board_cols){
    std::cout << "r=" << r <<" c=" << c <<"\n";
    this->row+=r;
    this->col+=c;

    if(this->row < 0) this->row = 0;
    else if(this->row > board_rows-1) this->row = board_rows-1;

    if(this->col < 0) this->col = 0;
    else if(this->col > board_cols-1) this->col = board_cols-1;

    std::cout << name << "[" << id << "]" << "(" << row << ", " << col << ")\n";   
}

void Actor::step(int board_rows, int board_cols){
    switch(facing){
        case Direction_Left:
            move(0, -1, board_rows, board_cols);
            break;
        case Direction_Up:
            move(-1, 0, board_rows, board_cols);
            break;
        case Direction_Right:
            move(0, 1, board_rows, board_cols);
            break;
        default:
        case Direction_Down:
            move(1, 0, board_rows, board_cols);
            break;
    }    
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

void Actor::face(enum Actor_Direction direction){
    facing = direction;
}

void Actor::ai(Board* ground, Board* overlay){
    int board_rows = ground->get_rows(), board_cols = ground->get_cols();
    Tile left, right, up, down;
    Tile beneath, left_g, right_g, up_g, down_g;
    beneath = ground->get_tile(this->row,this->col);
    if(!Tile_Type_is(beneath, Tile_Type_Ground)){
        // this->row = rand() % overlay->get_rows();
        // this->col = rand() % overlay->get_cols();
        return;
    }

    overlay->get_neighbors(this->row, this->col, &left, &right, &up, &down);
    ground->get_neighbors(this->row, this->col, &left_g, &right_g, &up_g, &down_g);

    // bool can_move_left = Tile_is_Air(left) && Tile_Type_is(left_g, Tile_Type_Ground);
    // bool can_move_right = Tile_is_Air(right) && Tile_Type_is(right_g, Tile_Type_Ground);
    // bool can_move_up = Tile_is_Air(up) && Tile_Type_is(up_g, Tile_Type_Ground);
    // bool can_move_down = Tile_is_Air(down) && Tile_Type_is(down_g, Tile_Type_Ground);

    bool can_move_left = Tile_Type_is(left_g, Tile_Type_Ground);
    bool can_move_right = Tile_Type_is(right_g, Tile_Type_Ground);
    bool can_move_up = Tile_Type_is(up_g, Tile_Type_Ground);
    bool can_move_down = Tile_Type_is(down_g, Tile_Type_Ground);

    // if(can_move_left+can_move_right+can_move_down+can_move_right==0) return;


    int random_direction = rand() % 4;
    switch(random_direction){
        default:
        case 0:
            if(can_move_left){
                face(Direction_Left);
                step(board_rows, board_cols);
            }
            break;
        case 1:
            if(can_move_right){
                face(Direction_Right);
                step(board_rows, board_cols);
            }
            break;
        case 2:
            if(can_move_up){
                face(Direction_Up);
                step(board_rows, board_cols);
            }
            break;
        case 3:
            if(can_move_down){
                face(Direction_Down);
                step(board_rows, board_cols);
            }
            break;
    }
}

void Actor::draw(SDL_Renderer* renderer, int screen_x, int screen_y){
    if(this->texture != NULL){
        // std::cout << "HERE\n";
        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, this->texture);
        std::cout<<"I WILL BE PUT AT " << this->row << ", " << this->col << "\n";
        int x = 0, y = 0;
        // snap_grid_with_zoom(this->row,this->col,this->size_x,&x,&y);
        x = this->row;
        y = this->col;
        SDL_Rect dstrect = { x, y, size_x, size_y };
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_DestroyTexture(texture);
    }
}