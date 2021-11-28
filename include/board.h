#ifndef BOARD_H
#define BOARD_H

#include <tile.h>

#define BOARD_MAX_ROWS 32
#define BOARD_MAX_COLS 16

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
        int r_cursor, c_cursor;
        Tile tiles[BOARD_MAX_ROWS][BOARD_MAX_COLS];
        void check_cursor();

    public:
        bool show_cursor = true;

        Board(int rows, int cols);
        Board(const char* filename);
        ~Board();
        
        int get_rows();
        int get_cols();

        void set_tile(int r, int c, Tile t);
        void fill_tile(int r1, int c1, int r2, int c2, Tile t);
        void flood_tile(Tile t);
        Tile get_tile(int r, int c);
        void set_cursor(int r, int c);
        void move_cursor(enum Cursor_Direction direction);

        void draw(SDL_Renderer *renderer);
};


#endif // BOARD_H