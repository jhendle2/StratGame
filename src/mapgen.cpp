#include <mapgen.h>
// #include "../include/mapgen.h"
#include <iostream>
#include <stdlib.h>
#include <tt.h>

static void print_matrix(int rows, int cols, int** map){
    for(int r = 0; r<rows; r++){
        for(int c = 0; c<cols; c++){
            std::cout << map[r][c] << " ";
        }
        std::cout << "\n";
    }    
}

static void print_terrain(int rows, int cols, char** terrain_map){
    for(int r = 0; r<rows; r++){
        for(int c = 0; c<cols; c++){
            std::cout << terrain_map[r][c] << " ";
        }
        std::cout << "\n";
    }    
}

void generate_random_slopes(int rows, int cols, int** map){
    for(int r = 0; r<rows; r++){
        for(int c = 0; c<cols; c++){
            map[r][c] = rand() % (2*MAX_SLOPE_DIFFERENTIAL+1) - MAX_SLOPE_DIFFERENTIAL;
            // std::cout << map[r][c] << "\n";
        }
    }
}

void generate_elevations(int rows, int cols, int** map){
    int first_elevation_of_last_row = ELEVATION_MINIMUM;
    for(int r = 0; r<rows; r++){
        int last_elevation = first_elevation_of_last_row;
        for(int c = 0; c<cols; c++){
            if(c==0) last_elevation = first_elevation_of_last_row;
            last_elevation += map[r][c];
            if(ELEVATION_ADD_RANDOM_NOISE) last_elevation += rand() % 3 - 2;
            if(last_elevation < ELEVATION_MINIMUM) last_elevation = ELEVATION_MINIMUM;
            else if(last_elevation > ELEVATION_MAXIMUM) last_elevation = ELEVATION_MAXIMUM;
            map[r][c] = last_elevation;
        }
    }
}

void generate_terrain(int rows, int cols, int** map, char** terrain_map){
    for(int r = 0; r<rows; r++){
        for(int c = 0; c<cols; c++){
            int elevation = map[r][c];
            if(elevation < ELEVATION_SEALEVEL) terrain_map[r][c] = 'w';
            // else if(elevation > ELEVATION_MOUNTAINLEVEL) terrain_map[r][c] = 'i';
            else terrain_map[r][c] = 'g';
        }
    }
}

static void add_sand(int rows, int cols, Board* board){
    for(int r = 0; r<rows; r++){
        for(int c = 0; c<cols; c++){
            Tile self, left, right, up, down;
            self = board->get_tile(r,c);
            if(c > 0) left = board->get_tile(r,c-1);
            if(r > 0) up = board->get_tile(r-1,c);
            if(c < cols-1) right = board->get_tile(r,c+1);
            if(r < rows-1) down = board->get_tile(r+1,c);

            int water_neighbor_count = ( Tile_is_Water(left) + 
                                        Tile_is_Water(up)   +
                                        Tile_is_Water(right)+
                                        Tile_is_Water(down) );
            bool self_is_water = Tile_is_Water(self);
            // std::cout << "water neighbors = " << has_water_neighbor << " is water = " << self_is_water << "\n";
            if(!self_is_water && water_neighbor_count>0){
                board->set_tile(r,c,Tiles_get_Tile("sand"));
                // std::cout << "Placed Sand!\n";
            }

        }
    }
}

static void add_more_land(int rows, int cols, Board* board){
    for(int r = 0; r<rows; r++){
        for(int c = 0; c<cols; c++){
            Tile self, left, right, up, down;
            self = board->get_tile(r,c);
            if(c > 0) left = board->get_tile(r,c-1);
            if(r > 0) up = board->get_tile(r-1,c);
            if(c < cols-1) right = board->get_tile(r,c+1);
            if(r < rows-1) down = board->get_tile(r+1,c);

            int land_neighbor_count = ( !Tile_is_Water(left) + 
                                        !Tile_is_Water(up)   +
                                        !Tile_is_Water(right)+
                                        !Tile_is_Water(down) );
            bool self_is_water = Tile_is_Water(self);
            // std::cout << "water neighbors = " << has_water_neighbor << " is water = " << self_is_water << "\n";
            if(self_is_water && land_neighbor_count>2){
                board->set_tile(r,c,Tiles_get_Tile("grass"));
                // std::cout << "Placed Sand!\n";
            }

        }
    }
}

static void add_trees(int rows, int cols, Board* board){
    for(int r = 0; r<rows; r++){
        for(int c = 0; c<cols; c++){
            Tile self, left, right, up, down;
            self = board->get_tile(r,c);
            if(c > 0) left = board->get_tile(r,c-1);
            if(r > 0) up = board->get_tile(r-1,c);
            if(c < cols-1) right = board->get_tile(r,c+1);
            if(r < rows-1) down = board->get_tile(r+1,c);

            int veg_neighbor_count = ( Tile_is_Vegetation(left) + 
                                        Tile_is_Vegetation(up)   +
                                        Tile_is_Vegetation(right)+
                                        Tile_is_Vegetation(down) );
            bool self_is_grass = Tile_is_Grass(self);
            // std::cout << "water neighbors = " << has_water_neighbor << " is water = " << self_is_water << "\n";
            if(self_is_grass && veg_neighbor_count>2){
                board->set_tile(r,c,Tiles_get_Tile("tree"));
                // std::cout << "Placed Sand!\n";
            }

        }
    }   
}

static void add_terrain(int rows, int cols, Board* board){
    add_more_land(rows,cols,board);
    add_sand(rows,cols,board);
    add_trees(rows,cols,board);
}

Board generate_random_Board(int rows, int cols){
    int** map = (int**)malloc(sizeof(int*)*rows);
    for(int i = 0; i<rows; i++) map[i] = (int*)malloc(sizeof(int)*cols);
    generate_random_slopes(rows, cols, map);
    generate_elevations(rows, cols, map);
    
    // print_matrix(rows, cols, map);

    Board board = Board(rows, cols); 
    for(int r = 0; r<rows; r++){
        for(int c = 0; c<cols; c++){
            int elevation = map[r][c];
            if(elevation < ELEVATION_SEALEVEL) board.set_tile(r,c,Tiles_get_Tile("water"));
            // else if(elevation > ELEVATION_MOUNTAINLEVEL) terrain_map[r][c] = 'i';
            else board.set_tile(r,c,Tiles_get_Tile("grass"));
        }
    }

    add_terrain(rows, cols, &board);

    // Clean-up
    for(int i = 0; i<rows; i++) free(map[i]);
    free(map);
    
    return board;
}