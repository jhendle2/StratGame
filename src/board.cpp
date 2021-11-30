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

    /* Cleanup */
    for(int r=  0; r<BOARD_MAX_ROWS; r++){
        free(lines[r]);
    }
    free(lines);

    this->rows = rows;
    this->cols = cols;
    this->r_cursor = 0;
    this->c_cursor = 0;
}

Board::~Board(){
    this->rows=0;
    this->cols=0;
}

void Board::save(const char* filename){
    char** lines = (char**)malloc(sizeof(char*)*BOARD_MAX_ROWS);
    for(int r = 0; r<BOARD_MAX_ROWS; r++){
        lines[r] = (char*)malloc(sizeof(char)*BOARD_MAX_COLS+1);
        for(int c = 0; c<BOARD_MAX_COLS+1; c++){
            lines[r][c] = 0;
        }
    }

    for(int r = 0; r<this->rows; r++){
        for(int c = 0; c<this->cols; c++){
            lines[r][c] = this->tiles[r][c].icon;
        }
    }

    save_file_as_lines(filename, lines, this->rows, this->cols);
    
    /* Cleanup */
    for(int r=  0; r<BOARD_MAX_ROWS; r++){
        free(lines[r]);
    }
    free(lines);
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

void Board::zoom_in(){
    this->zoom_x++;
    this->zoom_y++;
}
void Board::zoom_out(){
    this->zoom_x--;
    this->zoom_y--;
}

void Board::move_slice(int r, int c){
    this->slice_r+=r;
    this->slice_c+=c;

    if(this->slice_r < 0) this->slice_r = 0;
    else if(this->slice_r > this->rows-1) this->slice_r = this->rows-1;
    else this->row_shift += r;

    if(this->slice_c < 0) this->slice_c = 0;
    else if(this->slice_c > this->cols-1) this->slice_c = this->cols-1;

    move_cursor(r,c);
}

void Board::move_cursor(int r, int c){
    this->r_cursor+=r;
    this->c_cursor+=c;

    // this->slice_r+=r;
    // this->slice_c+=c;

    // if(this->slice_r < 0) this->slice_r = 0;
    // else if(this->slice_r > this->rows-1) this->slice_r = this->rows-1;
    // else this->row_shift += r;

    // if(this->slice_c < 0) this->slice_c = 0;
    // else if(this->slice_c > this->cols-1) this->slice_c = this->cols-1;

    // this->r_cursor+=r;
    // this->c_cursor+=c;

    this->check_cursor();
}

void Board::move_cursor(enum Cursor_Direction direction){
    int last_row = this->r_cursor;
    bool last_row_odd = is_odd(last_row + row_shift);
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

void Board::rotate_left(){
    this->rotate_right();
    this->rotate_right();
    this->rotate_right();
}

void Board::rotate_right(){
    if(BOARD_MAX_ROWS != BOARD_MAX_COLS) return;
    Tile temp[BOARD_MAX_ROWS][BOARD_MAX_COLS];

    for(int r = 0; r<BOARD_MAX_ROWS; r++){
        for(int c = 0; c<BOARD_MAX_COLS; c++){
            temp[r][c] = this->tiles[BOARD_MAX_ROWS-c-1][r];
        }
    }
    
    for(int r = 0; r<BOARD_MAX_ROWS; r++){
        for(int c = 0; c<BOARD_MAX_ROWS; c++){
            this->tiles[r][c] = temp[r][c];
        }
    }
}

static void draw_tiles(SDL_Renderer *renderer, Tile tiles[BOARD_MAX_ROWS][BOARD_MAX_COLS], int rows, int cols, int screen_size_x, int screen_size_y,
int zoom, bool show_cursor, int r_cursor, int c_cursor){
for(int r = 0; r<rows; r++){
        for(int c = 0; c<cols; c++){
            int x = 0, y = 0;
            snap_grid_with_zoom(r,c,zoom,&x,&y);
            if(x>(screen_size_x-16*zoom) || y>(screen_size_y-16*zoom)){
                // std::cout << "OUT OF BOUNDS";
                break;
            }

            if(show_cursor && (r == r_cursor && c == c_cursor) ){
                Tile cursor = Tiles_get_Tile("cursor");
                if(cursor.texture != NULL){
                    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, cursor.texture);
                    SDL_Rect dstrect = { x, y, 16*zoom, 16*zoom };
                    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
                    SDL_DestroyTexture(texture); // Keeps the program from crashing :)
                }
            }
            else{
                Tile tile_to_draw = tiles[r][c];
                if(tile_to_draw.num_alt_textures == 0){
                    if(tile_to_draw.texture != NULL){
                        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, tile_to_draw.texture);
                        SDL_Rect dstrect = { x, y, 16*zoom, 16*zoom };
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
                            SDL_Rect dstrect = { x, y, 16*zoom, 16*zoom };
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

void Board::draw(SDL_Renderer *renderer, int screen_size_x, int screen_size_y){
    draw_tiles(renderer, this->tiles, this->rows, this->cols, screen_size_x, screen_size_y,
    this->zoom_x, this->show_cursor, this->r_cursor, this->c_cursor);
}

void Board::draw_slice_fast(SDL_Renderer* renderer, int x1, int y1, int r1, int c1, int r2, int c2, int screen_size_x, int screen_size_y){
    if(r1 < 0) r1 =0;
    else if(r1 > rows-1) r1 = rows-1;

    if(c1 < 0) c1 =0;
    else if(c1 > cols-1) c1 = cols-1;

    if(r2 < 0) r2 =0;
    else if(r2 > rows) r2 = rows;

    if(c2 < 0) c2 =0;
    else if(c2 > cols) c2 = cols;

    for(int r = r1; r<r2; r++){
        for(int c = c1; c<c2; c++){
            int x = x1, y = y1;
            snap_grid_with_zoom(x1, y1, r-r1,c-c1,this->zoom_x,&x,&y);
            if(x>(screen_size_x-16*this->zoom_x) || y>(screen_size_y-16*this->zoom_y)){
                break;
            }

            if(show_cursor && (r == r_cursor && c == c_cursor) ){
                Tile cursor = Tiles_get_Tile("cursor");
                if(cursor.texture != NULL){
                    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, cursor.texture);
                    SDL_Rect dstrect = { x, y, 16*zoom_x, 16*zoom_y };
                    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
                    SDL_DestroyTexture(texture); // Keeps the program from crashing :)
                }
            }
            else{
                Tile tile_to_draw = tiles[r][c];
                
                if(strcmp(tile_to_draw.name,"air")==0) continue;
                if(tile_to_draw.num_alt_textures == 0){
                    if(tile_to_draw.texture != NULL){
                        // if(tile_to_draw.icon == TILE_AIR_ICON) return;
                        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, tile_to_draw.texture);
                        SDL_Rect dstrect = { x, y, 16*this->zoom_x, 16*this->zoom_y };
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
                            SDL_Rect dstrect = { x, y, 16*zoom_x, 16*zoom_y };
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

void Board::draw_slice_fast(SDL_Renderer* renderer, int r1, int c1, int r2, int c2, int screen_size_x, int screen_size_y){
    draw_slice_fast(renderer, 0, 0, r1, c1, r2, c2, screen_size_x, screen_size_y);
}

void Board::draw_slice(SDL_Renderer* renderer, int r1, int c1, int r2, int c2, int screen_size_x, int screen_size_y){
    /* Out of Bounds Checking */
    if(r1 < 0) r1 =0;
    else if(r1 > rows-1) r1 = rows-1;

    if(c1 < 0) c1 =0;
    else if(c1 > cols-1) c1 = cols-1;

    if(r2 < 0) r2 =0;
    else if(r2 > rows) r2 = rows;

    if(c2 < 0) c2 =0;
    else if(c2 > cols) c2 = cols;

    /* Generate Slice */
    Tile slice[BOARD_MAX_ROWS][BOARD_MAX_COLS];
    int sr = 0;
    int sc = 0;
    for(int r = r1; r<r2; r++){
        sc = 0;
        for(int c = c1; c<c2; c++){
            slice[sr][sc++] = tiles[r][c];
        }
        sr++;
    }

    draw_tiles(renderer, slice, sr, sc, screen_size_x, screen_size_y,
    this->zoom_x, this->show_cursor, this->r_cursor, this->c_cursor);
}

void Board::draw_slice(SDL_Renderer* renderer, int r1, int c1, int slice_size, int screen_size_x, int screen_size_y){
    this->draw_slice(renderer, r1, c1, r1+slice_size, c1+slice_size, screen_size_x, screen_size_y);
}

void Board::draw_slice(SDL_Renderer* renderer, int screen_size_x, int screen_size_y){
    this->draw_slice_fast(renderer, this->slice_r, this->slice_c, this->slice_r+2*this->slice_size, this->slice_c+this->slice_size, screen_size_x, screen_size_y);
}

void Board::draw_slice(SDL_Renderer* renderer, int x1, int y1, int screen_size_x, int screen_size_y){
    this->draw_slice_fast(renderer, x1, y1, this->slice_r, this->slice_c, this->slice_r+2*this->slice_size, this->slice_c+this->slice_size, screen_size_x, screen_size_y);
}