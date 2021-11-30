#include <mapgen.h>
// #include "../include/mapgen.h"
#include <iostream>
#include <stdlib.h>
#include <tt.h>
#include <utils.h>

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
    int first_elevation_of_last_row = ELEVATION_STARTING;
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

/*void generate_terrain(int rows, int cols, int** map, char** terrain_map){
    for(int r = 0; r<rows; r++){
        Calculate_Percentage(r,c);
        for(int c = 0; c<cols; c++){
            int elevation = map[r][c];
            if(elevation < ELEVATION_SEALEVEL) terrain_map[r][c] = 'W';
            else if(elevation == ELEVATION_SEALEVEL) terrain_map[r][c] = 'w';
            // else if(elevation > ELEVATION_MOUNTAINLEVEL) terrain_map[r][c] = 'i';
            else terrain_map[r][c] = 'g';
        }
    }
}*/

static void add_sand(int rows, int cols, Board* board){
    for(int r = 0; r<rows; r++){
        Calculate_Percentage(r,c);
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
        Calculate_Percentage(r,c);
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
        Calculate_Percentage(r,c);
        for(int c = 0; c<cols; c++){
            int chance = rand()%MAPGEN_VEGETATION_TYPES == 0;
            if(!chance) continue;
            
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

static void less_sand(int rows, int cols, Board* board){
    for(int r = 0; r<rows; r++){
        Calculate_Percentage(r,c);
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
            bool self_is_not_water = !Tile_is_Water(self);
            // std::cout << "water neighbors = " << has_water_neighbor << " is water = " << self_is_water << "\n";
            if(self_is_not_water && water_neighbor_count>1){
                board->set_tile(r,c,Tiles_get_Tile("water"));
                // std::cout << "Placed Sand!\n";
            }

        }
    }      
}

static void add_terrain(int rows, int cols, Board* board){
    std::cout << "Generating terrain...\n";

    std::cout << "Adding more land...\n";
    add_more_land(rows,cols,board);

    std::cout << "Adding sand land...\n";
    add_sand(rows,cols,board);

    // std::cout << "Adding vegetation...\n";
    // add_trees(rows,cols,board);

    std::cout << "Removing small islands...\n";
    less_sand(rows,cols,board);
}

Board generate_random_Board(int rows, int cols){
    int** map = (int**)malloc(sizeof(int*)*rows);
    for(int i = 0; i<rows; i++) map[i] = (int*)malloc(sizeof(int)*cols);
    generate_random_slopes(rows, cols, map);
    generate_elevations(rows, cols, map);
    
    // print_matrix(rows, cols, map);

    std::cout << "Generating random map...\n";

    Board board = Board(rows, cols);
    for(int r = 0; r<rows; r++){
        Calculate_Percentage(r,c);
        for(int c = 0; c<cols; c++){
            int elevation = map[r][c];
            if(elevation <= ELEVATION_DEEPSEALEVEL) board.set_tile(r,c,Tiles_get_Tile("deepwater"));
            else if(elevation < ELEVATION_SEALEVEL) board.set_tile(r,c,Tiles_get_Tile("water"));
            // else if(elevation > ELEVATION_MOUNTAINLEVEL) terrain_map[r][c] = 'i';
            else board.set_tile(r,c,Tiles_get_Tile("grass"));
        }
    }

    add_terrain(rows, cols, &board);

    // Clean-up
    for(int i = 0; i<rows; i++) free(map[i]);
    free(map);

    std::cout << "Generation Complete!\n\n"; 

    return board;
}

void add_vegetation_on_grass(int rows, int cols, Board* ground, Board* overlay){
    std::cout << "Adding vegetation...\n";
    for(int r = 0; r<rows; r++){
        Calculate_Percentage(r,c);
        for(int c = 0; c<cols; c++){
            int chance = rand()%(4+MAPGEN_VEGETATION_TYPES);
            if(!chance) continue;
            
            Tile self, left, right, up, down;
            self = ground->get_tile(r,c);
            if(c > 0) left = ground->get_tile(r,c-1);
            if(r > 0) up = ground->get_tile(r-1,c);
            if(c < cols-1) right = ground->get_tile(r,c+1);
            if(r < rows-1) down = ground->get_tile(r+1,c);

            int grass_neighbor_count = ( Tile_is_Grass(left) + 
                                        Tile_is_Grass(up)   +
                                        Tile_is_Grass(right)+
                                        Tile_is_Grass(down) );
            bool self_is_grass = Tile_is_Grass(self);
            // std::cout << "water neighbors = " << has_water_neighbor << " is water = " << self_is_water << "\n";
            if(self_is_grass && grass_neighbor_count>2){
                switch(chance){
                    default:
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        break;

                    case 4:
                        overlay->set_tile(r,c,Tiles_get_Tile("tree"));
                        break;
                    case 5:
                        overlay->set_tile(r,c,Tiles_get_Tile("shrub"));
                        break;
                    case 6:
                        overlay->set_tile(r,c,Tiles_get_Tile("bush"));
                        break;
                    case 7:
                        overlay->set_tile(r,c,Tiles_get_Tile("grasses"));
                        break;
                }
                // overlay->set_tile(r,c,Tiles_get_Tile("tree"));
                // std::cout << "Placed Sand!\n";
            }

        }
    }
}