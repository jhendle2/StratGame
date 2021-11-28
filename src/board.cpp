#include <SDL.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <board.h>

#include <tt.h>

#include <utils.h>

Board::Board(int rows, int cols){
    this->rows = rows;
    this->cols = cols;
    this->r_cursor = 0;
    this->c_cursor = 0;
}

Board::Board(const char* filename){
    char** lines = (char**)malloc(sizeof(char*)*BOARD_MAX_ROWS);
    for(int r = 0; r<BOARD_MAX_ROWS; r++){
        lines[r] = (char*)malloc(sizeof(char)*BOARD_MAX_COLS);
    }

    int rows = 0, cols = 0;
    load_file_as_lines(filename, lines, &rows, &cols);
    for(int r = 0; r<rows; r++){
        for(int c = 0; c<cols; c++){
            if(lines[r][c]==0 || lines[r][c]=='\n') break;
            this->tiles[r][c] = Tiles_get_Tile(lines[r][c]);
            // std::cout << lines[r][c];
        }
        // std::cout << "\n";
    }
    this->rows = rows;
    this->cols = cols;
    this->r_cursor = 0;
    this->c_cursor = 0;
}

Board::~Board(){
    this->rows=0;
    this->cols=0;
}

int Board::get_rows(){
    return this->rows;
}

int Board::get_cols(){
    return this->cols;
}

void Board::set_tile(int r, int c, Tile t){
    this->tiles[r][c]=t;
}

void Board::fill_tile(int r1, int c1, int r2, int c2, Tile t){
    for(int ri = r1; ri<r2; ri++){
        for(int ci = c1; ci<c2; ci++){
            this->set_tile(ri,ci,t);
        }
    }
}

void Board::flood_tile(Tile t){
    this->fill_tile(0,0,this->rows,this->cols,t);
}

Tile Board::get_tile(int r, int c){
    return this->tiles[r][c];
}

void Board::check_cursor(){
    if(this->r_cursor < 0) this->r_cursor = 0;
    else if(this->r_cursor >= this->rows) this->r_cursor = this->rows-1;

    if(this->c_cursor < 0) this->c_cursor = 0;
    else if(this->c_cursor >= this->cols) this->c_cursor = this->cols-1;

    // std::cout << "(" << this->r_cursor << ", " << this->c_cursor << ")\n";
}

void Board::set_cursor(int r, int c){
    this->r_cursor=r;
    this->c_cursor=c;
    this->check_cursor();
}

void Board::move_cursor(enum Cursor_Direction direction){
    int last_row = this->r_cursor;
    bool last_row_odd = is_odd(last_row);
    // std::cout << "direction=" << direction << "\n";
    if(last_row_odd){
        switch(direction){
            case Cursor_Left:
                this->r_cursor--;
                // this->c_cursor--;
                break;
            case Cursor_Right:
                this->r_cursor++;
                this->c_cursor++;
                break;
            case Cursor_Up:
                this->r_cursor--;
                this->c_cursor++;
                break;
            case Cursor_Down:
                this->r_cursor++;
                // this->c_cursor--;
                break;
            default:
                break;
        }
    }
    else{
        switch(direction){
            case Cursor_Left:
                this->r_cursor--;
                this->c_cursor--;
                break;
            case Cursor_Right:
                this->r_cursor++;
                //this->c_cursor;
                break;
            case Cursor_Up:
                this->r_cursor--;
                // this->c_cursor++;
                break;
            case Cursor_Down:
                this->r_cursor++;
                this->c_cursor--;
                break;
            default:
                break;
        }
    }
    this->check_cursor();
}

void Board::draw(SDL_Renderer *renderer){
    for(int r = 0; r<this->rows; r++){
        for(int c = 0; c<this->cols; c++){
            int x = 0, y = 0;
            snap_grid2(r,c,32,&x,&y);
            if(this->show_cursor && (r == this->r_cursor && c == this->c_cursor) ){
                Tile cursor = Tiles_get_Tile("cursor");
                if(cursor.texture != NULL){
                    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, cursor.texture);
                    SDL_Rect dstrect = { x, y, 64, 64 };
                    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
                    SDL_DestroyTexture(texture); // Keeps the program from crashing :)
                }
            }
            else{
                Tile tile_to_draw = this->get_tile(r,c);
                if(tile_to_draw.num_alt_textures == 0){
                    if(tile_to_draw.texture != NULL){
                        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, tile_to_draw.texture);
                        SDL_Rect dstrect = { x, y, 64, 64 };
                        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
                        SDL_DestroyTexture(texture); // Keeps the program from crashing :)
                    }
                }
                else{
                    int rand_index = rand() % tile_to_draw.num_alt_textures;
                    // std::cout << "alts=" << tile_to_draw.num_alt_textures << "\n";
                    int current_index = 0;
                    std::vector<SDL_Surface*> textures = tile_to_draw.textures;
                    for(std::vector<SDL_Surface*>::iterator surface_iterator = textures.begin();
                    surface_iterator != textures.end();
                    surface_iterator++, current_index++ ){
                        if(current_index == rand_index) {
                            // std::cout << current_index << "\t";
                            SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, *surface_iterator);
                            SDL_Rect dstrect = { x, y, 64, 64 };
                            SDL_RenderCopy(renderer, texture, NULL, &dstrect);
                            SDL_DestroyTexture(texture); // Keeps the program from crashing :)
                            break;
                        }
                    }
                }
            }
        }
    }
}