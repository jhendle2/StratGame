#pragma once

#include <board.h>

#define MAX_SLOPE_DIFFERENTIAL 4

#define ELEVATION_ADD_RANDOM_NOISE true

#define ELEVATION_MINIMUM 0
#define ELEVATION_SEALEVEL 1
#define ELEVATION_MOUNTAINLEVEL 7
#define ELEVATION_MAXIMUM 10

void generate_random_slopes(int rows, int cols, int** map);
void generate_elevations(int rows, int cols, int** maps);
// void generate_terrain(int rows, int cols, Board board);

Board generate_random_Board(int rows, int cols);