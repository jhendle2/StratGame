#ifndef BOARD_H
#define BOARD_H

#include <tile.h>

#define BOARD_MAX_ROWS 128
#define BOARD_MAX_COLS 128

enum Cursor_Direction {
    Cursor_None,
    Cursor_Left,
    Cursor_Right,
    Cursor_Up,
    Cursor_Down
};

class Board{
    private:
        int rows, cols;
        int row_shift=0;
        int r_cursor, c_cursor;
        Tile tiles[BOARD_MAX_ROWS][BOARD_MAX_COLS];
        void check_cursor();
        int zoom_x=4, zoom_y=4;
        int slice_r=0, slice_c = 0, slice_size=16;

    public:
        bool show_cursor = true;

        Board(int rows, int cols);
        Board(const char* filename);
        ~Board();
        void save(const char* filename);
        
        int get_rows();
        int get_cols();

        void set_tile(int r, int c, Tile t);
        void fill_tile(int r1, int c1, int r2, int c2, Tile t);
        void flood_tile(Tile t);
        Tile get_tile(int r, int c);
        void set_cursor(int r, int c);
        void move_cursor(int r, int c);
        void move_cursor(enum Cursor_Direction direction);

        void move_slice(int r, int c);

        void zoom_in();
        void zoom_out();
        void rotate_left();
        void rotate_right();

        void draw(SDL_Renderer *renderer, int screen_size_x, int screen_size_y);
        void draw_slice(SDL_Renderer* renderer, int r1, int c1, int r2, int c2, int screen_size_x, int screen_size_y);
        void draw_slice(SDL_Renderer* renderer, int r1, int c1, int slice_size, int screen_size_x, int screen_size_y);
        void draw_slice(SDL_Renderer* renderer, int screen_size_x, int screen_size_y);
        void draw_slice(SDL_Renderer* renderer, int x1, int y1, int screen_size_x, int screen_size_y);
        void draw_slice_fast(SDL_Renderer* renderer, int x1, int y1, int r1, int c1, int r2, int c2, int screen_size_x, int screen_size_y);
        void draw_slice_fast(SDL_Renderer* renderer, int r1, int c1, int r2, int c2, int screen_size_x, int screen_size_y);
};


#endif // BOARD_H