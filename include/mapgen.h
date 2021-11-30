#pragma once

#include <board.h>

#define RENDER_SUITE RENDER_NORMAL

#if RENDER_SUITE == RENDER_NORMAL
    #define DEFAULT_MAP_SIZE_X 128 // 16
    #define DEFAULT_MAP_SIZE_Y 128 // 16

    #define MAX_SLOPE_DIFFERENTIAL 4

    #define ELEVATION_ADD_RANDOM_NOISE true
    #define MAPGEN_VEGETATION_TYPES 4

    #define ELEVATION_MINIMUM 0
    #define ELEVATION_STARTING 2
    #define ELEVATION_DEEPSEALEVEL 0
    #define ELEVATION_SEALEVEL 1
    #define ELEVATION_MOUNTAINLEVEL 7
    #define ELEVATION_MAXIMUM 10
#endif

void generate_random_slopes(int rows, int cols, int** map);
void generate_elevations(int rows, int cols, int** maps);

Board generate_random_Board(int rows, int cols);

void add_vegetation_on_grass(int rows, int cols, Board* ground, Board* overlay);